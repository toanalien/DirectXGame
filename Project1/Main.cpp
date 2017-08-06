#include <stdio.h>
#include <Windows.h>

//int main()
//{
//	while (1)
//	{
//		printf("this is my first game\n");
//		Sleep(1000);
//	}
//	return 0;
//}

class Game
{
private:
	int Num;
	bool IsExit;
public:
	Game(){};
	~Game(){};

	void InitGame();
	void RunGame();
	void DestroyGame();
};

void Game::InitGame()
{
	Num = 0;
	IsExit = false;
}

void Game::RunGame()
{
	while (!IsExit)
	{
		Num += 1;
		printf("Game update %d\n", Num);
		Sleep(1000);
	}
}

void Game::DestroyGame()
{
	printf("Game Over");
}

int main()
{
	Game* myGame = new Game();

	myGame->InitGame();
	myGame->RunGame();
	myGame->DestroyGame();

	delete myGame;
	return 0;
}