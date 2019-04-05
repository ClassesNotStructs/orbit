#include <iostream>
#include "game.h" 
#include "helpers.h"
bool Game::init(double g_x, double g_y) {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) return false;
	
	//create main window
	game_window = SDL_CreateWindow("yow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

	if(game_window == NULL) return false;

	//create renderer and set draw color
	renderer = SDL_CreateRenderer(game_window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	//render starting frame
	SDL_RenderPresent(renderer);

	//create player
	player = new Player("assets/rocket.bmp", (SCREEN_WIDTH/2), (SCREEN_HEIGHT/2-400), renderer, g_x, g_y);

	//create star
	star = new Star("assets/sun.bmp", "assets/sun2.bmp", (SCREEN_WIDTH/2), (SCREEN_HEIGHT/2), renderer, 1000);

	//create the player texture
	//test = SDL_CreateTextureFromSurface(renderer, surfaceFromBMP("assets/rocket.bmp"));
	//if(test == NULL) return false;

	//create the rect that controlles the player rendering location and size
	//dstrect = new SDL_Rect;
	//dstrect->x = x;
	//dstrect->y = y;
	//dstrect->w = 35;
	//dstrect->h = 35;

	return true;
}

void Game::update() {
	//animate sun
	star->update();

	//change player accelerations
	std::cout << "Star: (" << star->getx() << ", " << star->gety() << ")\n";
	std::cout << "Player: (" << player->getx() + 5 << ", " << player->gety() + 3 << ")\n";
	tmp = gravitationalAcceleration(star->getx(), star->gety(), player->getx()+5, player->gety()+3, 10000, 1, 1);
	player->accelerate(tmp[0], tmp[1]);
	player->update();

	//clear the window
	if(SDL_RenderClear(renderer)) std::cout << SDL_GetError();

	//background image
	//
	//rendercopy the star
	star->render(renderer);
	
	//rendercopy the player
	player->render(renderer);

	//render the changes
	SDL_RenderPresent(renderer);
}

bool Game::event(SDL_Event* event) {
	switch(event->type) {
		case SDL_QUIT:
			return false;
		case SDL_KEYDOWN:
			std::cout << SDL_GetKeyName(event->key.keysym.sym) << " was pressed\n";
			switch(event->key.keysym.sym) {
				case SDLK_w: 
					w_pressed = 1;
					break;
			 	case SDLK_s: 
					s_pressed = 1;
					break;
				case SDLK_a:
					a_pressed = 1;
					break;
				case SDLK_d:
					d_pressed = 1;
					break;
			}
			break;
		case SDL_KEYUP:
			std::cout << SDL_GetKeyName(event->key.keysym.sym) << " was released lol\n";
			switch(event->key.keysym.sym) {
				case SDLK_w:
					w_pressed=0;
					break;
				case SDLK_s:
					s_pressed=0;
					break;
				case SDLK_a:
					a_pressed=0;
					break;
				case SDLK_d:
					d_pressed=0;
					break;
			}
			break;
	}
	if(w_pressed) player->accelerate(0, -.25);
	if(s_pressed) player->accelerate(0, .25);
	if(a_pressed) player->accelerate(-.25, 0);
	if(d_pressed) player->accelerate(.25, 0);
	return true;
}
	

void Game::quit() {
	//SDL_FreeSurface(screen);
	SDL_DestroyTexture(test);
	SDL_DestroyWindow(game_window);
	SDL_Quit();
}
