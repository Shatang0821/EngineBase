#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Object.h"

class Controller :public Object
{
protected:
	class Camera* camera;
public:
	Controller();

	//���͏���
	void PickInfo(){}
};

#endif // !_CONTROLLER_H_

