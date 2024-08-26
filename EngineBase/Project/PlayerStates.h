#ifndef _PLAYERSTATES_H_
#define _PLAYERSTATES_H_

#include "BaseState.h"

enum PlayerStateType
{
	IDLE,
	RUN,
	JUMP,
	FALL,
};

class PlayerBaseState : public BaseState
{
protected:
	class Player* player;
	std::string aniName;
	float stateTime;

	class GameController* mainController;
public:
	PlayerBaseState(StateMachine* sm, class Player* p, std::string name);

	virtual void Enter() override;

	virtual void LogicUpdate(float deltaTime) override {
		stateTime += deltaTime;
	};

	virtual void PhysicsUpdate(float fixedDeltaTime) override {};

	virtual void Exit() override {};
};

class PlayerIdleState : public PlayerBaseState
{
public:
    PlayerIdleState(StateMachine* sm, class Player* p,std::string name) : PlayerBaseState(sm, p, name) {};

	virtual void Enter() override;

	virtual void LogicUpdate(float deltaTime) override;

	virtual void PhysicsUpdate(float fixedDeltaTime) override {
		//std::cout << "Idle State Physics Time: " << stateTime << std::endl;
	};

	virtual void Exit() override {
		PlayerBaseState::Exit();
		//std::cout << "Exiting " << typeid(*this).name() << " State" << std::endl;
	};
};

class PlayerRunState : public PlayerBaseState
{
public:
	PlayerRunState(StateMachine* sm, class Player* p,std::string name) : PlayerBaseState(sm, p, name) {};

	virtual void Enter() override;

	virtual void LogicUpdate(float deltaTime) override;

	virtual void PhysicsUpdate(float fixedDeltaTime) override;

	virtual void Exit() override {
		PlayerBaseState::Exit();
		//std::cout << "Exiting " << typeid(*this).name() << " State" << std::endl;
	};
};

class PlayerJumpState : public PlayerBaseState
{
public:
	PlayerJumpState(StateMachine* sm, class Player* p, std::string name) : PlayerBaseState(sm, p, name) {};

	virtual void Enter() override;

	virtual void LogicUpdate(float deltaTime) override;

	virtual void PhysicsUpdate(float fixedDeltaTime) override;

	virtual void Exit() override;
};

class PlayerFallState : public PlayerBaseState
{
public:
	PlayerFallState(StateMachine* sm, class Player* p, std::string name) : PlayerBaseState(sm, p, name) {};

	virtual void Enter() override;

	virtual void LogicUpdate(float deltaTime) override;

	virtual void PhysicsUpdate(float fixedDeltaTime) override;

	virtual void Exit() override;
};

#endif // !_PLAYERSTATES_H_



