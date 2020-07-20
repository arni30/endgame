#ifndef HEADER_ENDGAME
#define HEADER_ENDGAME

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#define MX_SCREEN_WIDTH 1200
#define MX_SCREEN_HEIGHT 720
#define MX_TILE_SIZE 20
#define MX_PALISADE 30


int mx_strlen(const char *s);
void drawCoin(SDL_Texture *coin, SDL_Renderer *ren, SDL_Rect *coin_Pos);
void drawBackground(SDL_Texture *background, SDL_Renderer *ren);
void create_hero(SDL_Renderer *ren, SDL_Texture *player, SDL_Texture *skelet, SDL_Texture *background, SDL_Texture *palisade, SDL_Texture *coin, SDL_Texture *gameover);



#endif
