#include "stdafx.h"
#include "Collider.h"
#include "Debug.h"
#include "SceneComponent.h"

bool CircleCollider::CollisionJudge(Collider* another)
{
	if (another->GetShape() == COLLIDER_SHAPE_CIRCLE) {
		//�~�Ɖ~�̓����蔻��
		CircleCollider* circle = Cast<CircleCollider>(another);
		return Vector2::Distance(GetWorldPosition(),circle->GetWorldPosition()) <= radius + circle->GetRadius();
	}
	else if (another->GetShape() == COLLIDER_SHAPE_BOX) {
		//�~�Ƌ�`�̓����蔻��
		BoxCollider* box = Cast<BoxCollider>(another);
		//�~�̒��S���W�Ƌ�`�̒��S���W
		Vector2 pos = GetWorldPosition();
		Vector2 boxPos = box->GetWorldPosition();
		//��`�̃T�C�Y
		Vector2 size = box->GetSize();

		//��`�̏㉺���E�̍��W���v�Z
		float top = boxPos.y - size.y / 2, bottom = boxPos.y + size.y / 2,
			left = boxPos.x - size.x / 2, right = boxPos.x + size.x / 2;

		//�~�̒��S����`�̒��ɂ���ꍇ
		if(pos.x <= right && pos.x >= left && pos.y <= bottom && pos.y >= top)
			return true;
		else {
			if(pos.x <= left) {
				if(pos.y <= top) {
					//�~�̒��S����`�̍���ɂ���ꍇ
					return Vector2::Distance(pos, Vector2(left, top)) <= radius;
				}
				else if(pos.y >= bottom) {
					//�~�̒��S����`�̍����ɂ���ꍇ
					return Vector2::Distance(pos, Vector2(left, bottom)) <= radius;
				}
				else {
					//�~�̒��S����`�̍��ӂɂ���ꍇ
					return pos.x + radius >= left;
				}
			}
			else if(pos.x >= right) {
				if(pos.y <= top) {
					//�~�̒��S����`�̉E��ɂ���ꍇ
					return Vector2::Distance(pos, Vector2(right, top)) <= radius;
				}
				else if(pos.y >= bottom) {
					//�~�̒��S����`�̉E���ɂ���ꍇ
					return Vector2::Distance(pos, Vector2(right, bottom)) <= radius;
				}
				else {
					//�~�̒��S����`�̉E�ӂɂ���ꍇ
					return pos.x - radius <= right;
				}
			}
			else if(pos.y <= top) {
				//�~�̒��S����`�̏�ӂɂ���ꍇ
				return pos.y + radius >= top;
			}
			else if(pos.y >= bottom) {
				//�~�̒��S����`�̉��ӂɂ���ꍇ
				return pos.y - radius <= bottom;
			}
		}
	}
	return false;
}

bool BoxCollider::CollisionJudge(Collider* another)
{
	if (another->GetShape() == COLLIDER_SHAPE_CIRCLE) {
		//��`�Ɖ~�̓����蔻��
		CircleCollider* circle = Cast<CircleCollider>(another);
		//��`�̒��S���W
		Vector2 pos = GetWorldPosition();
		//�~�̒��S���W
		Vector2 circlePos = circle->GetWorldPosition();
		//�~�̔��a
		float radius = circle->GetRadius();

		//��`�̏㉺���E�̍��W���v�Z
		float top = pos.y - size.y / 2, bottom = pos.y + size.y / 2,
			left = pos.x - size.x / 2, right = pos.x + size.x / 2;

		//�~�̒��S����`�̒��ɂ���ꍇ
		if (circlePos.x <= right && circlePos.x >= left && circlePos.y <= bottom && circlePos.y >= top)
			return true;
		else {
			if (circlePos.x <= left) {
				if (circlePos.y <= top) {
					//�~�̒��S����`�̍���ɂ���ꍇ
					return Vector2::Distance(circlePos, Vector2(left, top)) <= radius;
				}
				else if (circlePos.y >= bottom) {
					//�~�̒��S����`�̍����ɂ���ꍇ
					return Vector2::Distance(circlePos, Vector2(left, bottom)) <= radius;
				}
				else {
					//�~�̒��S����`�̍��ӂɂ���ꍇ
					return circlePos.x + radius >= left;
				}
			}
			else if (circlePos.x >= right) {
				if (circlePos.y <= top) {
					//�~�̒��S����`�̉E��ɂ���ꍇ
					return Vector2::Distance(circlePos, Vector2(right, top)) <= radius;
				}
				else if (circlePos.y >= bottom) {
					//�~�̒��S����`�̉E���ɂ���ꍇ
					return Vector2::Distance(circlePos, Vector2(right, bottom)) <= radius;
				}
				else {
					//�~�̒��S����`�̉E�ӂɂ���ꍇ
					return circlePos.x - radius <= right;

				}
			}
			else if (circlePos.y <= top) {
				//�~�̒��S����`�̏�ӂɂ���ꍇ
				return circlePos.y + radius >= top;
			}
			else if (circlePos.y >= bottom) {
				//�~�̒��S����`�̉��ӂɂ���ꍇ
				return circlePos.y - radius <= bottom;
			}
			return false;
		}
	}
	else {
		//��`�Ƌ�`�̓����蔻��
		BoxCollider* box = Cast<BoxCollider>(another);
		//���g�̍���̍��W
		Vector2 pos = GetWorldPosition() - size / 2;
		//another�̍���̍��W
		Vector2 anotherPos = box->GetWorldPosition() - box->GetSize() / 2;

		//���g��another�̋�`���d�Ȃ��Ă���ꍇ
		return(pos.x <= anotherPos.x + box->GetSize().x && pos.x + size.x >= anotherPos.x &&
			pos.y <= anotherPos.y + box->GetSize().y && pos.y + size.y >= anotherPos.y);
	}
	return false;
}

void CircleCollider::Update(float DeltaTime)
{
	//���a�̓I�u�W�F�N�g�̃X�P�[���ɉ����čX�V����
	radius = radius_init * sqrtf(GetWorldScale().x * GetWorldScale().y);
}

void CircleCollider::DrawDebugLine()
{
	auto pos = GetWorldPosition() - mainWorld.mainCamera->GetCameraPosition() + Vector2(WIDTH / 2,HEIGHT / 2);

	Debug::DrawCircle(pos, int(radius * (2 / mainWorld.mainCamera->springArmLength_virtual)), 32, D3DCOLOR_XRGB(0, 255, 0));
}

bool CircleCollider::IsMouseOver()
{
	return Vector2::Distance(GetWorldPosition(), mainWorld.mainController->GetMousePosition()) <= radius;
}



void BoxCollider::Update(float DeltaTime)
{
	//�T�C�Y���I�u�W�F�N�g�̃X�P�[���ɉ����čX�V����
	size = size_init * GetWorldScale(); 
}

void BoxCollider::DrawDebugLine()
{
	auto pos = GetWorldPosition() - mainWorld.mainCamera->GetCameraPosition() + Vector2(WIDTH / 2, HEIGHT / 2);

	Debug::DrawBox(pos, size * (2 / mainWorld.mainCamera->springArmLength_virtual), D3DCOLOR_XRGB(255, 0, 0));
}

bool BoxCollider::IsMouseOver()
{
	Vector2 pos = GetWorldPosition();
	Vector2 mousePos = mainWorld.mainController->GetMousePosition();

	//��`�̏㉺���E�̍��W���v�Z
	return (mousePos.x >= pos.x - size.x / 2 && mousePos.x <= pos.x + size.x / 2
		&& mousePos.y >= pos.y - size.y / 2 && mousePos.y <= pos.y + size.y / 2);
}

const std::vector<Object*>& Collider::GetCollisions(std::string type)
{
	aims.clear();
	//�Փ˂��Ă���R���C�_�[����łȂ��ꍇ
	if (!collisions.empty()) {
		for (auto it = collisions.begin(); it != collisions.end(); it++) {
			//�R���C�_�[�̃^�C�v��type�ƈ�v����ꍇ
			if ((*it)->GetType() == type)
				//aims�ɃR���C�_�[�̃I�[�i�[(Object)��ǉ�
				aims.push_back((*it)->pOwner);
		}
	}

	return aims;
}

void Collider::Inser(Collider* another)
{
	//collisions��another���܂܂�Ă��Ȃ��ꍇ�A����CollisionJudge��true�̏ꍇ
	if (collisions.find(another) == collisions.end() && CollisionJudge(another)) {
		//�Փ˂��Ă���R���C�_�[��ǉ�
		collisions.insert(another);
		//another��collisions�Ɏ��g��ǉ�
		another->collisions.insert(this);
	}
}
