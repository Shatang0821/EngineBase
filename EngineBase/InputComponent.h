#ifndef _INPUTCOMPONENT_H_
#define _INPUTCOMPONENT_H_

#include "Component.h"

enum InputType;

struct KeyBindInfo
{
	std::function<void()> func;
	InputType type;
	bool isPressed = false;	
};
class InputComponent : public Component
{
public:
	void SetMapping(std::string mappingName, int value);
	template<typename T>
	void BindAction(std::string actionName, InputType type,T*obj,void(T::*func)()) {
		if (mappings.find(actionName) != mappings.end()) {
			callbacks.insert({ actionName,KeyBindInfo{std::bind(func,obj),type ,false} });
		}
	}

	virtual void Update(float DeltaTime) override;
private:
	std::map<std::string, int>mappings;
	std::map<std::string, KeyBindInfo>callbacks;
};

enum InputType 
{
	Pressed,
	Released,
	Holding
};

#endif // !_INPUTCOMPONENT_H_


