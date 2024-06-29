#include "stdafx.h"
#include "StaticMesh.h"

StaticMesh::StaticMesh()
{
	renderer = ConstructComponent<SpriteRenderer>(Vector2::Zero());
	renderer->AttachTo(root);
}
