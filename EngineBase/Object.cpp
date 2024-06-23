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
		//endを超えないように制御する
		if (components_iter == components.end()) break;
		components_iter++;
	}
}

void Object::Destroy()
{
	if (parent) parent->children.erase(this);

	std::stack<Object*>objects_to_delete;
	objects_to_delete.push(this);

	// オブジェクトを削除するためのスタックが空になるまでループ
	while (!objects_to_delete.empty()) {
		// スタックのトップにあるオブジェクトを取得
		Object* current_obj = objects_to_delete.top();
		// 取得したオブジェクトをスタックから取り除く
		objects_to_delete.pop();

		// 子オブジェクトが存在するか確認
		if (!current_obj->children.empty()) {
			// 子オブジェクトを順番に処理
			for (auto& children : current_obj->children) {
				// 子オブジェクトをスタックに追加
				objects_to_delete.push(children);
			}
		}
		// 現在のオブジェクトを削除予定リストに追加
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
