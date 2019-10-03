#ifndef MINILIB_H
#define MINILIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <unistd.h>


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



#define MX_SCREEN_WIDTH 1200
#define MX_SCREEN_HEIGHT 720
#define MX_BACKGROUND 60
#define MX_TILE_SIZE 20
#define MX_PALISADE 30
#define SPEED 150




void drawCoin(SDL_Texture *coin, SDL_Renderer *ren, SDL_Rect *coin_RECT);
void drawBackground(SDL_Texture *background, SDL_Renderer *ren);
int mx_strlen(const char *s);
#endif
