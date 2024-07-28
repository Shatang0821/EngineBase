#include "stdafx.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "Debug.h"
#include "SceneComponent.h"


const std::vector<Object*>& Collider::GetCollisions(std::string type)
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
		OnComponentEndOverlap.BroadCast(this,another, another->pOwner);
		another->OnComponentEndOverlap.BroadCast(another,this, pOwner);
	}
	//コライダーを削除するときに、衝突しているコライダーコンテナをクリアする
	collisions.clear();
}

void Collider::Inser(Collider* another)
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
		//デリケート関数を呼び出す
		OnComponentBeginOverlap.BroadCast(this,another, another->pOwner);
		another->OnComponentBeginOverlap.BroadCast(another,this, pOwner);
	}
}

void Collider::Erase()
{
	collisions_to_erase.clear();
	for (auto& another : collisions) {

		if (!CollisionJudge(another)) {
			another->collisions.erase(this);
			collisions_to_erase.push_back(another);
			//デリケート関数を呼び出す
			OnComponentEndOverlap.BroadCast(this,another, another->pOwner);
			another->OnComponentEndOverlap.BroadCast(another,this, pOwner);
		}
	}

	for(auto& another : collisions_to_erase)
		collisions.erase(another);
}


bool CircleCollider::CollisionJudge(Collider* another)
{
	if (another->GetShape() == ColliderShape::COLLIDER_SHAPE_CIRCLE) {
		//円と円の当たり判定
		CircleCollider* circle = Cast<CircleCollider>(another);
		return Vector2::Distance(GetWorldPosition(),circle->GetWorldPosition()) <= radius + circle->GetRadius();
	}
	else if (another->GetShape() == ColliderShape::COLLIDER_SHAPE_BOX) {
		//円と矩形の当たり判定
		BoxCollider* box = Cast<BoxCollider>(another);
		//円の中心座標と矩形の中心座標
		Vector2 pos = GetWorldPosition();
		Vector2 boxPos = box->GetWorldPosition();
		//矩形のサイズ
		Vector2 size = box->GetSize();

		//矩形の上下左右の座標を計算
		float top = boxPos.y - size.y / 2, bottom = boxPos.y + size.y / 2,
			left = boxPos.x - size.x / 2, right = boxPos.x + size.x / 2;

		//円の中心が矩形の中にある場合
		if(pos.x <= right && pos.x >= left && pos.y <= bottom && pos.y >= top)
			return true;
		else {
			if(pos.x <= left) {
				if(pos.y <= top) {
					//円の中心が矩形の左上にある場合
					return Vector2::Distance(pos, Vector2(left, top)) <= radius;
				}
				else if(pos.y >= bottom) {
					//円の中心が矩形の左下にある場合
					return Vector2::Distance(pos, Vector2(left, bottom)) <= radius;
				}
				else {
					//円の中心が矩形の左辺にある場合
					return pos.x + radius >= left;
				}
			}
			else if(pos.x >= right) {
				if(pos.y <= top) {
					//円の中心が矩形の右上にある場合
					return Vector2::Distance(pos, Vector2(right, top)) <= radius;
				}
				else if(pos.y >= bottom) {
					//円の中心が矩形の右下にある場合
					return Vector2::Distance(pos, Vector2(right, bottom)) <= radius;
				}
				else {
					//円の中心が矩形の右辺にある場合
					return pos.x - radius <= right;
				}
			}
			else if(pos.y <= top) {
				//円の中心が矩形の上辺にある場合
				return pos.y + radius >= top;
			}
			else if(pos.y >= bottom) {
				//円の中心が矩形の下辺にある場合
				return pos.y - radius <= bottom;
			}
		}
	}
	return false;
}

void CircleCollider::Update(float DeltaTime)
{
	//半径はオブジェクトのスケールに沿って更新する
	radius = radius_init * sqrtf(GetWorldScale().x * GetWorldScale().y);
}

void CircleCollider::DrawDebugLine()
{
	auto pos = Transform::WordToScreen(GetWorldPosition());// mainWorld.mainCamera->GetCameraPosition()) / mainWorld.mainCamera->GetZoomFactor() + Vector2(WIDTH / 2, HEIGHT / 2);

	Debug::DrawCircle(pos, int(radius / mainWorld.mainCamera->springArmLength_virtual), 32, D3DCOLOR_XRGB(0, 255, 0));
}

bool CircleCollider::IsMouseOver()
{
	return Vector2::Distance(GetWorldPosition(), mainWorld.mainController->GetMousePosition()) <= radius;
}



bool BoxCollider::CollisionJudge(Collider* another)
{
	if (another->GetShape() == ColliderShape::COLLIDER_SHAPE_CIRCLE) {
		//矩形と円の当たり判定
		CircleCollider* circle = Cast<CircleCollider>(another);
		//矩形の中心座標
		Vector2 pos = GetWorldPosition();
		//円の中心座標
		Vector2 circlePos = circle->GetWorldPosition();
		//円の半径
		float radius = circle->GetRadius();

		//矩形の上下左右の座標を計算
		float top = pos.y - size.y / 2, bottom = pos.y + size.y / 2,
			left = pos.x - size.x / 2, right = pos.x + size.x / 2;

		//円の中心が矩形の中にある場合
		if (circlePos.x <= right && circlePos.x >= left && circlePos.y <= bottom && circlePos.y >= top)
			return true;
		else {
			if (circlePos.x <= left) {
				if (circlePos.y <= top) {
					//円の中心が矩形の左上にある場合
					return Vector2::Distance(circlePos, Vector2(left, top)) <= radius;
				}
				else if (circlePos.y >= bottom) {
					//円の中心が矩形の左下にある場合
					return Vector2::Distance(circlePos, Vector2(left, bottom)) <= radius;
				}
				else {
					//円の中心が矩形の左辺にある場合
					return circlePos.x + radius >= left;
				}
			}
			else if (circlePos.x >= right) {
				if (circlePos.y <= top) {
					//円の中心が矩形の右上にある場合
					return Vector2::Distance(circlePos, Vector2(right, top)) <= radius;
				}
				else if (circlePos.y >= bottom) {
					//円の中心が矩形の右下にある場合
					return Vector2::Distance(circlePos, Vector2(right, bottom)) <= radius;
				}
				else {
					//円の中心が矩形の右辺にある場合
					return circlePos.x - radius <= right;

				}
			}
			else if (circlePos.y <= top) {
				//円の中心が矩形の上辺にある場合
				return circlePos.y + radius >= top;
			}
			else if (circlePos.y >= bottom) {
				//円の中心が矩形の下辺にある場合
				return circlePos.y - radius <= bottom;
			}
			return false;
		}
	}
	else {
		//矩形と矩形の当たり判定
		BoxCollider* box = Cast<BoxCollider>(another);
		//自身の左上の座標
		Vector2 pos = GetWorldPosition() - size / 2;
		//anotherの左上の座標
		Vector2 anotherPos = box->GetWorldPosition() - box->GetSize() / 2;

		//自身の右下の座標
		Vector2 posBottomRight = pos + size;
		//anotherの右下の座標
		Vector2 anotherPosBottomRight = anotherPos + box->GetSize();

		//自身とanotherの矩形が重なっている場合のコードを書いて

		return (pos.x < anotherPosBottomRight.x && posBottomRight.x > anotherPos.x &&
				pos.y < anotherPosBottomRight.y && posBottomRight.y > anotherPos.y);
		
	}	
	return false;
}

void BoxCollider::Update(float DeltaTime)
{
	//サイズがオブジェクトのスケールに沿って更新する
	size = size_init * GetWorldScale(); 
}

void BoxCollider::DrawDebugLine()
{
	auto pos = Transform::WordToScreen(GetWorldPosition());// (GetWorldPosition() - mainWorld.mainCamera->GetCameraPosition()) / mainWorld.mainCamera->GetZoomFactor() + Vector2(WIDTH / 2, HEIGHT / 2);

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


