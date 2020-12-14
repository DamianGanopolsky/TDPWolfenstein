#include "Status_panel.h"
#include "const.h"
#include <SDL2/SDL_image.h>

Status_panel::Status_panel() {	
}
Status_panel::~Status_panel() {
}

void Status_panel::copy_to_rederer(SDL_Renderer& renderer) {
	SDL_Surface *status_img = IMG_Load("../ray_casting/sprites/hud.png");
	SDL_Texture *status_tex = SDL_CreateTextureFromSurface(&renderer, status_img);
	SDL_FreeSurface(status_img);
	SDL_Rect SrcR;
	SrcR.w = PANEL_WIDTH;
	SrcR.h = PANEL_HEIGHT * 0.2;
	SrcR.x = 0;
	SrcR.y = PANEL_HEIGHT - SrcR.h;
    SDL_RenderCopy(&renderer, status_tex, NULL, &SrcR);

	SDL_Surface *pistola_img = IMG_Load("../ray_casting/sprites/pistola.png");
	SDL_Texture *pistola_tex = SDL_CreateTextureFromSurface(&renderer, pistola_img);
	SDL_FreeSurface(pistola_img);
	SDL_Rect SrcR2;
	SrcR2.w = PANEL_WIDTH * 0.25;
	SrcR2.h = PANEL_HEIGHT * 0.25;
	SrcR2.x = (PANEL_WIDTH - SrcR2.w) / 2 ;
	SrcR2.y = SrcR.y - SrcR2.h;
    SDL_RenderCopy(&renderer, pistola_tex, NULL, &SrcR2);
}