#include "stdafx.h"
#include "StateMachine.h"
#include "BaseState.h"

StateMachine::~StateMachine()
{
	for (auto& state : StateMap)
	{
		delete state.second;
		state.second = nullptr;
	}
	StateMap.clear();
	currentState = nullptr;
}

void StateMachine::RegisterState(int StateId, BaseState* state)
{
	if (StateMap.find(StateId) == StateMap.end()) {
		StateMap.insert({ StateId, state });
	}
}

void StateMachine::ChangeState(int StateId)
{
	if(currentState != nullptr)
		currentState->Exit();

	currentState = StateMap[StateId];
	if (currentState != nullptr)
		currentState->Enter();
	else
	{
		std::cout<<"State Not Found"<<std::endl;
	}
}

void StateMachine::LogicUpdate(float deltaTime)
{
	currentState->LogicUpdate(deltaTime);
}

void StateMachine::PhysicsUpdate(float fixedDeltaTime)
{
	currentState->PhysicsUpdate(fixedDeltaTime);
}
