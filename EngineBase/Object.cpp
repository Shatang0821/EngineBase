#include "Object.h"
#include <stack>
#include "World.h"

void Object::RegisterComponent(Component* pCom)
{
	components.insert(pCom);
}

void Object::UnregisterComponent(Component* pCom)
{
	auto it = components.find(pCom);
	components_iter = components.erase(it);
}

void Object::AttachTo(Object* par)
{
	if (par) {
		parent->children.insert(this);
		parent = par;
	}
}

void Object::DetachFrom(Object* par)
{
	if (par) {
		par->children.erase(this);
		parent = nullptr;
	}
	
}

void Object::Update(float DeltaTime)
{
	components_iter = components.begin();
	while (components_iter != components.end()) {
		(*components_iter)->Update(DeltaTime);
		//end�𒴂��Ȃ��悤�ɐ��䂷��
		if (components_iter == components.end()) break;
		components_iter++;
	}
}

void Object::Destroy()
{
	if (parent) parent->children.erase(this);

	std::stack<Object*>objects_to_delete;
	objects_to_delete.push(this);

	// �I�u�W�F�N�g���폜���邽�߂̃X�^�b�N����ɂȂ�܂Ń��[�v
	while (!objects_to_delete.empty()) {
		// �X�^�b�N�̃g�b�v�ɂ���I�u�W�F�N�g���擾
		Object* current_obj = objects_to_delete.top();
		// �擾�����I�u�W�F�N�g���X�^�b�N�����菜��
		objects_to_delete.pop();

		// �q�I�u�W�F�N�g�����݂��邩�m�F
		if (!current_obj->children.empty()) {
			// �q�I�u�W�F�N�g�����Ԃɏ���
			for (auto& children : current_obj->children) {
				// �q�I�u�W�F�N�g���X�^�b�N�ɒǉ�
				objects_to_delete.push(children);
			}
		}
		// ���݂̃I�u�W�F�N�g���폜�\�胊�X�g�ɒǉ�
		mainWorld.GameObjects_to_delete.insert(current_obj);
	}

}

Vector2 Object::GetWorldPosition() const
{
	if (parent) return parent->GetWorldPosition() + GetLocalPosition();
	else return GetLocalPosition();
}

float Object::GetWorldRotation() const
{
	if (parent) return parent->GetWorldRotation() + GetLocalRotation();
	else return GetLocalRotation();
}

Vector2 Object::GetWorldScale() const
{
	if (parent) return parent->GetWorldScale() + GetWorldScale();
	else return GetLocalScale();
}
