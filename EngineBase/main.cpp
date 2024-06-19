#include <iostream>

#include "SceneComponent.h"
#include "Object.h"

int main() {
	Object owner;
	owner.ConstructComponent<SceneComponent>(Vector2::Zero());
}