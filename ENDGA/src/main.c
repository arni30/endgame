#include "minilib.h"
//#include "../framework/SDL2.framework/Headers/SDL.h"

//#include "../inc/minilib.h"

int xTiles = MX_SCREEN_WIDTH / MX_PALISADE;
    int yTiles = MX_SCREEN_HEIGHT / MX_PALISADE;
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}


void create_hero(SDL_Renderer *ren, SDL_Texture *player, SDL_Texture *background, SDL_Texture *palisade, SDL_Texture *coin){
    int frameTime = 0;
    int frameW = 0;
    int frameH = 0;
    int textW = 0;
    int textH = 0;

    
    SDL_QueryTexture(player, NULL, NULL, &textW, &textH);
    frameW = (textW - 65) / 8;
    frameH = textH / 4;
    
    SDL_Rect player_Pos = {0, 0, frameW, frameH};

    SDL_Rect coin_Pos = {60, 60, MX_TILE_SIZE, MX_TILE_SIZE};
    
    SDL_Rect player_RECT = {(MX_SCREEN_WIDTH - frameW)/2, (MX_SCREEN_HEIGHT - frameH)/2, frameW*1.2, frameH*1.2};
    SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_Event event;
    bool quit = false;

    while(!quit){
	    while(SDL_PollEvent(&event))
	    {   
		    SDL_PumpEvents(); // обработчик событий.

            switch(event.type){
                case SDL_QUIT: quit = true; break;
                case SDL_KEYDOWN: 
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE: quit = true;break;
                        case SDLK_LEFT: player_RECT.x -= 30;frameTime++;player_Pos.y = frameH;break;
                        case SDLK_RIGHT: player_RECT.x += 30;frameTime++;player_Pos.y = 3*frameH;break;
                        case SDLK_UP: player_RECT.y -= 30;frameTime++;player_Pos.y = 0;break;
                        case SDLK_DOWN: player_RECT.y += 30;frameTime++;player_Pos.y = 2 * frameH;break;
                    }
            }
            if (frameTime == 1){
                frameTime = 0;
                player_Pos.x += frameW;
                if (player_Pos.x > textW - 65) player_Pos.x = 0;
            }
        }
        
        if(player_RECT.x <= 30) player_RECT.x = 30;
        if(player_RECT.y >= MX_SCREEN_HEIGHT - MX_PALISADE - frameH) player_RECT.y = MX_SCREEN_HEIGHT - MX_PALISADE - frameH;
        if (player_RECT.y <= 0) player_RECT.y = 0;
        if(player_RECT.x >= MX_SCREEN_WIDTH - frameW) player_RECT.x = MX_SCREEN_WIDTH - frameW;
        SDL_RenderClear(ren);
        drawBackground(background, ren);
        drawCoin(coin,ren, &coin_Pos);

        if(player_RECT.x == coin_Pos.x && player_RECT.y == coin_Pos.y){
            coin_Pos.w = 0;
            coin_Pos.x = 10*(rand()%(MX_SCREEN_WIDTH - MX_PALISADE - MX_TILE_SIZE)/10) +(MX_PALISADE );
            coin_Pos.y = 10*(rand()%(MX_SCREEN_HEIGHT - MX_PALISADE - MX_TILE_SIZE)/10) +(MX_PALISADE);
        
        }
        for(int i = 0; i <=MX_SCREEN_WIDTH; i+=MX_PALISADE){
            for (int  j = 0;j <= MX_SCREEN_HEIGHT; j+=MX_PALISADE){
                if(i == 0||i == MX_SCREEN_WIDTH-MX_PALISADE){
                    renderTexture(palisade, ren, i, j, MX_PALISADE, MX_PALISADE);
                }
                if(j == 0||j == MX_SCREEN_HEIGHT-MX_PALISADE){
                    renderTexture(palisade, ren, i, j, MX_PALISADE, MX_PALISADE);
                }
            }
    
        }
        
        SDL_RenderCopy(ren, player, &player_Pos, &player_RECT);
        SDL_RenderPresent(ren);
        SDL_Delay(100/60);
    }
}

int main(){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        write(2, "SDL_Init Error: ", mx_strlen("SDL_Init Error: "));
        write(2, SDL_GetError(), mx_strlen(SDL_GetError()));
        return 1;
    } 
    SDL_Window* win = SDL_CreateWindow("endgame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, MX_SCREEN_WIDTH, MX_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(win == NULL){
        write(2, "SDL_CreateWindow Error: ", mx_strlen("SDL_CreateWindow Error: "));
        write(2, SDL_GetError(), mx_strlen(SDL_GetError()));
	      return 1;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL){
        write(2, "SDL_CreateRenderer Error: ", mx_strlen("SDL_CreateRenderer Error: "));
        write(2, SDL_GetError(), mx_strlen(SDL_GetError()));
	      return 1;
    }

    SDL_Texture *player =  IMG_LoadTexture(ren,"hero.png");
    SDL_Texture *background = IMG_LoadTexture(ren,"background.bmp");
    SDL_Texture *palisade = IMG_LoadTexture(ren,"sqr.png");
    SDL_Texture *coin = IMG_LoadTexture(ren, "con1.png");

    SDL_RenderPresent(ren);
    create_hero(ren, player,background,palisade,coin);
    
    SDL_DestroyTexture(coin);
    SDL_DestroyTexture(player);
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();	
    return 1;
}




void drawCoin(SDL_Texture *coin, SDL_Renderer *ren, SDL_Rect *coin_Pos){
    //rand()%(MX_SCREEN_WIDTH - MX_PALISADE) +MX_PALISADE
    renderTexture(coin, ren, coin_Pos->x, coin_Pos->y, MX_TILE_SIZE, MX_TILE_SIZE);
}

void drawBackground(SDL_Texture *background, SDL_Renderer *ren){
    for (int i = 0; i < xTiles * yTiles; ++i){
	    int x = i % xTiles;
	    int y = i / xTiles;
	    renderTexture(background, ren, x * MX_PALISADE, y * MX_PALISADE, MX_PALISADE, MX_PALISADE);
    }
}
