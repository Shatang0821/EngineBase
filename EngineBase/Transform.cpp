#include "stdafx.h"
#include "Transform.h"
#include "World.h"

Vector2 Transform::WorldToCamera(const Vector2& worldPos){
	auto zoomFactor = mainWorld.GetMainCamera()->GetZoomFactor();
	auto cameraPos = mainWorld.GetMainCamera()->GetCameraPosition();
	return (worldPos - cameraPos) / zoomFactor;
}

Vector2 Transform::WordToScreen(const Vector2& worldPos){
	auto screenCenter = Vector2(WIDTH / 2, HEIGHT / 2);
	return WorldToCamera(worldPos) + screenCenter;
}

