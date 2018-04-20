#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "level.h"
//#include "serialInterface.h"

class Graphics;

class Game {
public:
	//SerialInterface *serialInterface;

	Game();
	~Game();
	bool running = true;

private:
	void gameLoop();
	void drawGraphics(Graphics &graphics);
	void update(float elapsedTime);

	Player player;
	Level level;

};

#endif // GAME_H
