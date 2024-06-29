#ifndef _GAMELEVEL_H_
#define _GAMELEVEL_H_

#include "Level.h"
#include "StaticMesh.h"
#include "SpriteRenderer.h"

class GameLevel :public Level {
	StaticMesh* buttle;

public:
	GameLevel();
	virtual void Update(float DeltaTime) override;
};

#endif // !_GAMELEVEL_H_
