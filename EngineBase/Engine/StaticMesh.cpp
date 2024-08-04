#include "stdafx.h"
#include "StaticMesh.h"

StaticMesh::StaticMesh()
{
	renderer = ConstructComponent<SpriteRenderer>();
	renderer->SetLocalPosition(Vector2::Zero());
	renderer->AttachTo(root);
}
