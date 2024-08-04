#ifndef _GAMELEVEL_H_
#define _GAMELEVEL_H_

#include "Engine/Level.h"
#include "Engine/StaticMesh.h"
#include "Engine/SpriteRenderer.h"

#include "Player.h"
class GameLevel :public Level {
	StaticMesh* buttle;

	Player* player;
public:
	GameLevel();
	virtual void Update(float DeltaTime) override;
};

#endif // !_GAMELEVEL_H_
