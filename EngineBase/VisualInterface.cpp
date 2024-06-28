#include "stdafx.h"
#include "VisualInterface.h"
#include "World.h"

LayerInterface::LayerInterface()
{
	mainWorld.GameRenderers.insert(this);
}

LayerInterface::~LayerInterface()
{
	mainWorld.GameRenderers.erase(this);
}

void LayerInterface::SetLayer(int layer)
{
	//set‚É“ü‚ê’¼‚·
	mainWorld.GameRenderers.erase(this);
	this->layer = layer;
	mainWorld.GameRenderers.insert(this);
}

int LayerInterface::GetLayer() const
{
	return layer;
}


