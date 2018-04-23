#include <SDL.h>
#include <algorithm>
#include <iostream>

#include "game.h"
#include "graphics.h"
#include "input.h"
#include "controls.h"

//Game class
//Holds all the information for the main game loop, it's essentially a game manager

namespace
{
	const int FPS = 60;
	const int MAX_FRAME_TIME = 6 * 1000 / FPS;
}

Game::Game()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	srand(SDL_GetPerformanceCounter());
	gameLoop();
}

Game::~Game()
{

}

void Game::gameLoop()
{
	Graphics graphics;
	Input input;
	Controls controls;
	SDL_Event event;
	

	level = Level(graphics, 0,0);
	//projectile = Projectile(graphics, 100, 400);
	player = Player(graphics, globals::SCREEN_WIDTH / 2 - 64, 600);


	int LAST_UPDATE_TIME = SDL_GetTicks();
	//Start of the game loop
	while (running == true) {
		input.beginNewFrame();

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.repeat == 0)
				{
					input.KeyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				input.KeyUpEvent(event);
			}
			else if (event.type == SDL_QUIT)
			{
				running = false;
			}
		}

		// exit the game if escape is pressed
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true)
		{
			running = false;
		}

		// what allows the player to control the spaceship
		controls.playerControls(player, input, graphics);
		
		// frame rate handler
		const int CURENT_TIME_MS = SDL_GetTicks();
		int ELAPSE_TIME_MS = CURENT_TIME_MS - LAST_UPDATE_TIME;
		update(std::min(ELAPSE_TIME_MS, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURENT_TIME_MS;

		// update the graphics ons screen
		drawGraphics(graphics);
	}

}

void Game::drawGraphics(Graphics &graphics)
{
	graphics.clear();

	level.draw(graphics);
	player.draw(graphics);
	//projectile.draw(graphics);

	graphics.flip();
}

void Game::update(float elapsedTime)
{
	level.update(elapsedTime);
	//projectile.update(elapsedTime);
	player.levelCollisions(player.playerBoxCollider, level.levelBoxCollider);
	player.update(elapsedTime);
	
	

}