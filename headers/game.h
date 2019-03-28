#pragma once
#include <SDL2/SDL.h>

class Game {
	public:
		//Game();
		//~Game();
	public:
		bool init();
		bool event(SDL_Event* event);
		void update();
		void quit();
	
		SDL_Surface* screen{NULL};
		SDL_Surface* test{NULL};
		SDL_Window* game_window{NULL};
	private:
		int x{20};
		int y{50};
		int vx;
		int vy;
};
	
