#include "World.h"


class Engine
{
public:
	/**
	 * @brief �G���W������������
	 */
	static void Init()
	{
		//Engine������

		//���[���h������
		mainWorld.currentLevel = new Level;
		mainWorld.gameInstance = new GameInstance;
	}

	/**
	 * @brief �G���W���X�V����
	 */
	static void Tick()
	{
		mainWorld.Input();
		mainWorld.Update(0.016f);
		mainWorld.Render();
	}

	/**
	 * @brief �G���W���I������
	 */
	static void Exit() {

	}

};

int main() {
	Engine::Init();


	return 0;
}