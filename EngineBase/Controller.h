#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "Object.h"

class Controller :public Object
{
private:
	class Camera* camera;
public:
	Controller();

	//“ü—Íˆ—
	void PickInfo(){}
};

#endif // !_CONTROLLER_H_

