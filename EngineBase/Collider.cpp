#include "stdafx.h"
#include "Collider.h"
#include "Debug.h"
#include "SceneComponent.h"
#include "RigidBody.h"

bool (*Collider::collisionJudgeMap[3])(Collider*, Collider*) =
{ &Collider::collisionJudgeCircleToCircle,Collider::collisionJudgeCircleToBox,Collider::collisionJudgeBoxToBox };

HitResult(*Collider::collisionHitMap[3])(Collider*, Collider*) =
{ &Collider::collisionHitCircleToCircle,Collider::collisionHitCircleToBox,Collider::collisionHitBoxToBox };

void Collider::BeginPlay()
{
	SceneComponent::BeginPlay();
	
	rigidBodyAttached = pOwner->GetComponentByClass<RigidBody>();
	if (rigidBodyAttached) rigidBodyAttached->colliders.insert(this);
}

void Collider::Update(float DeltaTime)
{
	SceneComponent::Update(DeltaTime);

	if(collisionMode == CollisionMode::NONE) return;

	//衝突エリアの左上の座標の計算
	Vector2 half;
	if (shape == ColliderShape::COLLIDER_SHAPE_CIRCLE) {
		float a = Cast<CircleCollider>(this)->GetRadius();
		half = Vector2(a, a);
	}
	else if (shape == ColliderShape::COLLIDER_SHAPE_BOX) {
		half = Cast<BoxCollider>(this)->GetSize() / 2;
	}

	//衝突エリアの左上の座標
	Vector2 pos = GetWorldPosition() - half;
	Pair newPoint(Math::clamp(int(pos.x) / 100, 0, 7), Math::clamp(int(pos.y) / 100, 0, 5));
	pos += half * 2;
	Pair newPoint_1(Math::clamp(int(pos.x) / 100, 0, 7), Math::clamp(int(pos.y) / 100, 0, 5));
	//衝突エリアが変更されていない場合
	if(newPoint == point && newPoint_1 == point_1) return;

	//衝突エリアをクリア
	if (point != Pair(-1, -1)) {
		for (int i = point.x; i <= point_1.x; i++) {
			for (int j = point.y; j <= point_1.y; j++) {
				mainWorld.ColliderZones[i][j].erase(this);
			}
		}
	}

	//衝突エリアを更新
	point = newPoint;
	point_1 = newPoint_1;
	for(int i = point.x; i <= point_1.x; i++) {
		for(int j = point.y; j <= point_1.y; j++) {
			mainWorld.ColliderZones[i][j].insert(this);
		}
	}
}

const std::vector<Object*>& Collider::GetCollisions(CollisionType type)
{
	aims.clear();
	//衝突しているコライダーが空でない場合
	if (!collisions.empty()) {
		for (auto it = collisions.begin(); it != collisions.end(); it++) {
			//コライダーのタイプがtypeと一致する場合
			if ((*it)->GetType() == type)
				//aimsにコライダーのオーナー(Object)を追加
				aims.push_back((*it)->pOwner);
		}
	}

	return aims;
}

void Collider::Clear()
{
	//衝突しているコライダーのコンテナから自分をクリアする
	for (auto& another : collisions) {
		another->collisions.erase(this);
		if (another->collisionMode == CollisionMode::COLLISION && this->collisionMode == CollisionMode::COLLISION) continue;
		OnComponentEndOverlap.BroadCast(this,another, another->pOwner);
		another->OnComponentEndOverlap.BroadCast(another,this, pOwner);
	}
	//コライダーを削除するときに、衝突しているコライダーコンテナをクリアする
	collisions.clear();
	if(point != Pair(-1,-1))
	{
		for (int i = point.x; i <= point_1.x; ++i)for (int j = point.y; j <= point_1.y; ++j)mainWorld.ColliderZones[i][j].erase(this);
	}
	point = {-1,-1},point_1 = {-1,-1};
}

void Collider::Insert(Collider* another)
{
	//タイプのマッピングが存在し、衝突しているコライダーがまだ衝突リストにない、かつ当たり判定がtrueの場合
	if (CollisionManager::Instance()->FindMapping(type, another->GetType())
		&& collisions.find(another) == collisions.end()
		&& CollisionJudge(another))
	{
		//衝突しているコライダーを追加
		collisions.insert(another);
		//anotherのcollisionsに自身を追加
		another->collisions.insert(this);
		if(another->collisionMode == CollisionMode::COLLISION && this->collisionMode == CollisionMode::COLLISION)
		{
			HitResult hitResult = this->CollisionHit(another);
			//デリケート関数を呼び出す
			OnComponentHit.BroadCast(this, another, another->pOwner, hitResult.ImpactNormal * -1, hitResult);
			another->OnComponentHit.BroadCast(another, this, pOwner, hitResult.ImpactNormal, { hitResult.ImpactPoint,hitResult.ImpactNormal * -1,pOwner,this });
		}
		else {
			//デリケート関数を呼び出す
			OnComponentBeginOverlap.BroadCast(this, another, another->pOwner);
			another->OnComponentBeginOverlap.BroadCast(another, this, pOwner);
		}
		
	}
}

void Collider::Erase()
{
	collisions_to_erase.clear();
	for (auto& another : collisions) {

		if (!CollisionJudge(another)) {
			another->collisions.erase(this);
			collisions_to_erase.push_back(another);
			if (another->collisionMode == CollisionMode::COLLISION && this->collisionMode == CollisionMode::COLLISION) continue;
			//デリケート関数を呼び出す
			OnComponentEndOverlap.BroadCast(this,another, another->pOwner);
			another->OnComponentEndOverlap.BroadCast(another,this, pOwner);
		}
	}

	for(auto& another : collisions_to_erase)
		collisions.erase(another);
}

/* ---- 衝突 ---- */
bool Collider::CollisionJudge(Collider* another)
{
	int shape1 = int(this->shape), shape2 = int(another->shape);
	return collisionJudgeMap[shape1 * shape1 + shape2 * shape2](this, another);
}

bool Collider::collisionJudgeCircleToCircle(Collider* c1, Collider* c2)
{
	CircleCollider* circle1 = Cast<CircleCollider>(c1);
	CircleCollider* circle2 = Cast<CircleCollider>(c2);
	return Vector2::Distance(circle1->GetWorldPosition(), circle2->GetWorldPosition()) <= circle1->GetRadius() + circle2->GetRadius();
}

bool Collider::collisionJudgeCircleToBox(Collider* c1, Collider* c2)
{
	CircleCollider* circle; BoxCollider* box;
	if (c1->GetShape() == ColliderShape::COLLIDER_SHAPE_CIRCLE)
	{
		circle = Cast<CircleCollider>(c1), box = Cast<BoxCollider>(c2);
	}
	else
	{
		circle = Cast<CircleCollider>(c2), box = Cast<BoxCollider>(c1);
	}
	float radius = circle->GetRadius(); Vector2 pos = circle->GetWorldPosition();
	BoxCollider::Rect rect = box->GetRect();

	if (pos.x <= rect.right && pos.x >= rect.left && pos.y >= rect.top && pos.y <= rect.bottom)
		return true;
	else
	{
		if (pos.x < rect.left)
		{
			if (pos.y < rect.top)return Vector2::Distance(pos, { rect.left,rect.top }) <= radius;
			else if (pos.y > rect.bottom)return Vector2::Distance(pos, { rect.left,rect.bottom }) <= radius;
			else return rect.left - pos.x <= radius;
		}
		else if (pos.x > rect.right)
		{
			if (pos.y < rect.top)return Vector2::Distance(pos, { rect.right,rect.top }) <= radius;
			else if (pos.y > rect.bottom)return Vector2::Distance(pos, { rect.right,rect.bottom }) <= radius;
			else return pos.x - rect.right <= radius;
		}
		else
		{
			if (pos.y < rect.top)return rect.top - pos.y <= radius;
			else return pos.y - rect.bottom <= radius;
		}
	}
}

bool Collider::collisionJudgeBoxToBox(Collider* c1, Collider* c2)
{
	BoxCollider* box1 = Cast<BoxCollider>(c1);
	BoxCollider* box2 = Cast<BoxCollider>(c2);
	Vector2 pos1 = box1->GetWorldPosition() - box1->GetSize() / 2;
	Vector2 pos2 = box2->GetWorldPosition() - box2->GetSize() / 2;
	return (pos1.x < pos2.x + box2->GetSize().x && pos1.x + box1->GetSize().x > pos2.x &&
		pos1.y < pos2.y + box2->GetSize().y && pos1.y + box1->GetSize().y > pos2.y);
}

HitResult Collider::CollisionHit(Collider* another)
{
	int shape1 = int(this->shape), shape2 = int(another->shape);
	return collisionHitMap[shape1 * shape1 + shape2 * shape2](this, another);
}

HitResult Collider::collisionHitCircleToCircle(Collider* c1, Collider* c2)
{
	CircleCollider* circle1 = Cast<CircleCollider>(c1);
	CircleCollider* circle2 = Cast<CircleCollider>(c2);
	Vector2 impactNormal = (circle2->GetWorldPosition() - circle1->GetWorldPosition()).normalized();
	Vector2 impactPoint = circle1->GetWorldPosition() + impactNormal * circle1->GetRadius();
	return HitResult(impactPoint, impactNormal, circle2->pOwner, circle2);
}

HitResult Collider::collisionHitCircleToBox(Collider* c1, Collider* c2)
{
	CircleCollider* circle;
	BoxCollider* box;

	if (c1->GetShape() == ColliderShape::COLLIDER_SHAPE_CIRCLE) {
		circle = Cast<CircleCollider>(c1);
		box = Cast<BoxCollider>(c2);
	}
	else {
		circle = Cast<CircleCollider>(c2);
		box = Cast<BoxCollider>(c1);
	}
	float radius = circle->GetRadius();
	Vector2 pos = circle->GetWorldPosition();
	BoxCollider::Rect rect = box->GetRect();

	Vector2 impactNormal;
	Vector2 impactPoint;

	if (pos.x <= rect.right && pos.x >= rect.left && pos.y >= rect.top && pos.y <= rect.bottom)
	{
		impactPoint = pos;
		impactNormal = (c2->GetWorldPosition() - c1->GetWorldPosition()).normalized();
	}
	else
	{
		if (pos.x < rect.left)
		{
			if (pos.y < rect.top) { impactPoint = { rect.left,rect.top };  impactNormal = (impactPoint - circle->GetWorldPosition()).normalized(); }
			else if (pos.y > rect.bottom) { impactPoint = { rect.left,rect.bottom };  impactNormal = (impactPoint - circle->GetWorldPosition()).normalized(); }
			else { impactPoint = { rect.left,pos.y };  impactNormal = { 1,0 }; }
		}
		else if (pos.x > rect.right)
		{
			if (pos.y < rect.top) { impactPoint = { rect.right,rect.top };  impactNormal = (impactPoint - circle->GetWorldPosition()).normalized(); }
			else if (pos.y > rect.bottom) { impactPoint = { rect.right,rect.bottom };  impactNormal = (impactPoint - circle->GetWorldPosition()).normalized(); }
			else { impactPoint = { rect.right,pos.y }; impactNormal = { -1,0 }; }
		}
		else
		{
			if (pos.y < rect.top) { impactPoint = { pos.x,rect.top }; impactNormal = { 0,1 }; }
			else { impactPoint = { pos.x,rect.bottom }; impactNormal = { 0,-1 }; }
		}
	}



	return HitResult(impactPoint, impactNormal * (c1 == circle ? 1.f : -1.f), c2->pOwner, c2);
}

HitResult Collider::collisionHitBoxToBox(Collider* c1, Collider* c2)
{
	BoxCollider* box1 = Cast<BoxCollider>(c1);
	BoxCollider* box2 = Cast<BoxCollider>(c2);
	BoxCollider::Rect r1 = box1->GetRect(), r2 = box2->GetRect();
	Vector2 overlapRect = BoxCollider::GetOverlapRect(r1, r2);
	Vector2 impactNormal;

	if (overlapRect.x >= overlapRect.y)
	{
		box1->GetWorldPosition().y - box2->GetWorldPosition().y > 0 ? impactNormal = { 0,-1 } : impactNormal = { 0,1 };
	}
	else
	{
		box1->GetWorldPosition().x - box2->GetWorldPosition().x > 0 ? impactNormal = { -1,0 } : impactNormal = { 1,0 };
	}

	//
	float centerX = max(r1.left, r2.left) + overlapRect.x / 2;
	float centerY = max(r1.bottom, r2.bottom) + overlapRect.y / 2;

	return HitResult({ centerX, centerY }, impactNormal, box2->pOwner, box2);
}


/* ---- CIRCLE ---- */
void CircleCollider::Update(float DeltaTime)
{
	Collider::Update(DeltaTime);
	//半径はオブジェクトのスケールに沿って更新する
	radius = radius_init * sqrtf(GetWorldScale().x * GetWorldScale().y);
}

void CircleCollider::DrawDebugLine()
{
	auto pos = Transform::WordToScreen(GetWorldPosition());

	Debug::DrawCircle(pos, int(radius / mainWorld.mainCamera->springArmLength_virtual), 32, D3DCOLOR_XRGB(0, 255, 0));
}

bool CircleCollider::IsMouseOver()
{
	return Vector2::Distance(GetWorldPosition(), mainWorld.mainController->GetMousePosition()) <= radius;
}

/* ---- BOX ---- */
void BoxCollider::Update(float DeltaTime)
{
	Collider::Update(DeltaTime);
	//サイズがオブジェクトのスケールに沿って更新する
	size = size_init * GetWorldScale(); 
	Vector2 pos = GetWorldPosition();
	rect = { pos.x - size.x / 2, pos.y - size.y / 2, pos.x + size.x / 2, pos.y + size.y / 2 };
	//std::cout << rect.left << " " << rect.top << " " << rect.right << " " << rect.bottom << std::endl;
}

void BoxCollider::DrawDebugLine()
{
	auto pos = Transform::WordToScreen(GetWorldPosition());

	Debug::DrawBox(pos, size / mainWorld.mainCamera->springArmLength_virtual, D3DCOLOR_XRGB(255, 0, 0));
}

bool BoxCollider::IsMouseOver()
{
	Vector2 pos = GetWorldPosition();
	Vector2 mousePos = mainWorld.mainController->GetMousePosition();

	//矩形の上下左右の座標を計算
	return (mousePos.x >= pos.x - size.x / 2 && mousePos.x <= pos.x + size.x / 2
		&& mousePos.y >= pos.y - size.y / 2 && mousePos.y <= pos.y + size.y / 2);
}

Vector2 BoxCollider::GetOverlapRect(const Rect& r1, const Rect& r2)
{
	return {min(r1.right, r2.right) - max(r1.left, r2.left) , min(r1.bottom, r2.bottom) - max(r1.top, r2.top) };
}


