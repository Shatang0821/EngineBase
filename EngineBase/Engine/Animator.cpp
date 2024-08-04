#include "stdafx.h"
#include "Animator.h"
#include "ResourceManager.h"

void Animation::Load(ResID id, POINT delta)
{
	AnimationResource aniRes = ResourceManager::Instance()->FetchAnim(id);
	num = aniRes.num;
	textures = aniRes.texs;
	offset = delta;
}

void Animator::Update(float DeltaTime)
{
	//�A�j���[�V�����̍X�V
	if (!rendererAttached) {
		rendererAttached = pOwner->GetComponentByClass<SpriteRenderer>();
		rendererAttached->sprite = aniNode->textures[aniNode->index];
	}
	else if(aniNode) {
		//�A�j���[�V�����̍X�V
		rendererAttached->sprite = aniNode->textures[aniNode->index];
		rendererAttached->spriteInfo.offset = aniNode->offset;
	}
		
}

void Animator::Insert(std::string name, Animation& ani)
{
	if(!ani.textures.empty()) animations.insert({ name,ani });
}

void Animator::SetNode(std::string nodeName)
{
	if (aniNode) aniNode->clock.Stop();
	aniNode = &(animations.find(nodeName)->second);
	aniNode->clock.Continue();
}

void Animator::SetCalled(bool called)
{
	called ? aniNode->clock.Continue() : aniNode->clock.Stop();
}


