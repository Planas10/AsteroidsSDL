#include <stdlib.h>

#include "Utils.h"
#include "GameEngine.h"

int main(int argc, char* argv[]) {
	
	srand(time(NULL));

	GameEngine engine(GAME_WIDTH, GAME_HEIGHT);
	engine.Update();
	engine.Finish();

	return 0;
}