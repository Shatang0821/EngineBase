#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "StaticMesh.h"
#include "Animator.h"

class Player : public StaticMesh
{
	Animation ani;
	Animator* animator;
public :
	Player();
};


#endif // !_PLAYER_H_


