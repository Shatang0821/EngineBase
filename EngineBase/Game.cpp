//#include <iostream>
#include "stdafx.h"
#include "myApp.h"

class Engine
{
public:
	/**
	 * @brief エンジン初期化処理
	 */
	static void Init()
	{
		//Engine初期化

		//ワールド初期化
		mainWorld.currentLevel = new Level;
		mainWorld.gameInstance = new GameInstance;
	}

	/**
	 * @brief エンジン更新処理
	 */
	static void Tick()
	{
		mainWorld.Input();
		mainWorld.Update(0.016f);
		mainWorld.Render();
	}

	/**
	 * @brief エンジン終了処理
	 */
	static void Exit() {

	}

};

class TestObject : public Object

{
private:
	Timer TimeHandle;
	Timer TimeHandle2;
public:
	TestObject() {
		TimeHandle.Bind(0.5,this,&TestObject::Func,true);
		TimeHandle2.Bind(2.0,this,&TestObject::Func2,true);
	}

private:
	void Func()
	{
		std::cout << "Hello World" << std::endl;
	}
	void Func2()
	{
		std::cout << "By World" << std::endl;
	}

};


int main() {
	Engine::Init();
	
	TestObject testObj;

	while (true)
	{
		Engine::Tick();
	}
	return 0;
}