#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_
#include "BaseState.h"

class StateMachine
{
private:
	std::map<int, BaseState*> StateMap;

	BaseState* currentState;
public:
	StateMachine()
		: currentState(nullptr)
	{};
	~StateMachine() {};

	void RegisterState(int StateId,BaseState*);

	void ChangeState(int StateId);

	void LogicUpdate(float);
	void PhysicsUpdate(float);
};

#endif // !_STATEMACHINE_H_



