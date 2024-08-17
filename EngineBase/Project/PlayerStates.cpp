#include "stdafx.h"
#include "PlayerStates.h"
#include "Player.h"
#include "../Engine/World.h"
#include "GameController.h"
PlayerBaseState::PlayerBaseState(StateMachine* sm, Player* p, std::string name)
	: BaseState(sm)
	, player(p)
	, aniName(name)
	, stateTime(0.0f)
{
	mainController = dynamic_cast<GameController*>(mainWorld.GetMainController());
	if (mainController == nullptr)
	{
		std::cout << "Controller is nullptr" << std::endl;
	}
};
void PlayerBaseState::Enter() {
	player->SetAnimation(aniName);
	stateTime = 0.0f;
	std::cout << "Entering " << typeid(*this).name() << std::endl;
};

#pragma region Idle

void PlayerIdleState::Enter()
{
	PlayerBaseState::Enter();
	player->SetVelocityX(0);
}

void PlayerIdleState::LogicUpdate(float deltaTime)
{
	PlayerBaseState::LogicUpdate(deltaTime);
	//std::cout << "Idle State Time: " << stateTime << std::endl;
	if (mainController->GetAxis().x != 0)
	{
		stateMachine->ChangeState(PlayerStateType::RUN);
		return;
	}

	if (mainController->GetJump())
	{
		stateMachine->ChangeState(PlayerStateType::JUMP);
		return;
	}


};

#pragma endregion



#pragma region Run

void PlayerRunState::Enter()
{
	PlayerBaseState::Enter();
}

void PlayerRunState::LogicUpdate(float deltaTime)
{
	PlayerBaseState::LogicUpdate(deltaTime);
	if (mainController->GetAxis().x == 0)
	{
		stateMachine->ChangeState(PlayerStateType::IDLE);
		return;
	}

	if (mainController->GetJump())
	{
		stateMachine->ChangeState(PlayerStateType::JUMP);
		return;
	}
}

void PlayerRunState::PhysicsUpdate(float fixedDeltaTime)
{
	player->SetVelocityX(mainController->GetAxis().x * 100);
}

#pragma endregion

#pragma region Jump

void PlayerJumpState::Enter()
{
	PlayerBaseState::Enter();
	player->SetVelocityY(100);
}

void PlayerJumpState::LogicUpdate(float deltaTime)
{
	PlayerBaseState::LogicUpdate(deltaTime);
	if (player->GetVelocity().y <= 0)
	{
		stateMachine->ChangeState(PlayerStateType::FALL);
		return;
	}
}


#pragma endregion

#pragma region Fall

void PlayerFallState::Enter()
{
	PlayerBaseState::Enter();
}

void PlayerFallState::LogicUpdate(float deltaTime)
{
	PlayerBaseState::LogicUpdate(deltaTime);
	if (player->GetVelocity().y == 0)
	{
		stateMachine->ChangeState(PlayerStateType::IDLE);
		return;
	}
}


#pragma endregion

