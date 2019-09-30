#include "minilib.h"
#include <stddef.h>
//#include "../framework/SDL2.framework/Headers/SDL.h"

//#include "../inc/minilib.h"


void render_UPDATE(SDL_Renderer* render, SDL_Texture* texture[], SDL_Rect* destrect[], int states[])
{
	SDL_RenderClear(render);
	if(states[0]) SDL_RenderCopy(render, texture[0],NULL,destrect[0]);
	if(states[1]) SDL_RenderCopy(render, texture[1],NULL,destrect[1]);
}
void event(SDL_Rect *player_RECT, SDL_Texture *background ,SDL_Renderer *ren,
SDL_Rect *background_RECT, SDL_Texture *player){
    
    SDL_Texture* ARRAY_textures[2] = {background, player};
    SDL_Rect* ARRAY_rect[2] = {background_RECT, player_RECT};
    int ARRAY_texturesState[2] = {1,1};SDL_Event event;
    bool quit = false;
    while(!quit){
	    while(SDL_PollEvent(&event))
	    {
		    SDL_PumpEvents(); // обработчик событий.

            switch(event.type){
                case SDL_QUIT: quit = true; break;
                case SDL_KEYDOWN: 
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE: quit = true; break;
                        case SDLK_LEFT: player_RECT->x -= 10;break;
                        case SDLK_RIGHT: player_RECT->x += 10;break;
                        case SDLK_UP: player_RECT->y -= 10;break;
                        case SDLK_DOWN: player_RECT->y += 10;break;
                        case SDLK_SPACE: player_RECT->y -=10; player_RECT->x += 10; break;

                    }
            }
        }
        render_UPDATE(ren, ARRAY_textures, ARRAY_rect, ARRAY_texturesState);
        SDL_RenderPresent(ren);
    }
}
int main(){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
	    printf("SDL_Init Error: %s", SDL_GetError());
	    return 1;
    }

    SDL_Window* window = SDL_CreateWindow("endgame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL){
        printf("error creating window %s", SDL_GetError());
        return 1;
    }
    SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Rect player_RECT;
		player_RECT.x = 0;   //Смещение полотна по Х
		player_RECT.y = 0;   //Смещение полотна по Y
		player_RECT.w = 70; //Ширина полотна
		player_RECT.h = 100; //Высота полотна

    SDL_Rect background_RECT;
		background_RECT.x = 0;
		background_RECT.y = 0;
		background_RECT.w = SCREEN_WIDTH;
		background_RECT.h = SCREEN_HEIGHT;

    SDL_Texture *player =  IMG_LoadTexture(ren,"1.bmp");
    SDL_Texture *background =  IMG_LoadTexture(ren,"tex.bmp");


    SDL_RenderClear(ren); //Очистка рендера
    SDL_RenderCopy(ren,background,NULL,&background_RECT); //Копируем в рендер фон
    SDL_RenderCopy(ren, player, NULL, &player_RECT); //Копируем в рендер персонажа
    SDL_RenderPresent(ren); //Погнали!!
    
    

    event(&player_RECT, background, ren, &background_RECT, player);
    // SDL_Event event;
    // bool quit = false;
    // while(!quit){
	//     while(SDL_PollEvent(&event))
	//     {
	// 	    SDL_PumpEvents(); // обработчик событий.

    //         switch(event.type){
    //             case SDL_QUIT: quit = true; break;
    //             case SDL_KEYDOWN: 
    //                 switch(event.key.keysym.sym){
    //                     case SDLK_ESCAPE: quit = true; break;
    //                     case SDLK_LEFT: player_RECT.x -= 10;break;
    //                     case SDLK_RIGHT: player_RECT.x += 10;break;
    //                     case SDLK_UP: player_RECT.y += 10;break;
    //                     case SDLK_DOWN: player_RECT.y -= 10;break;
    //                     case SDLK_SPACE: player_RECT.y -=10; player_RECT.x += 10; break;

    //                 }
    //         }
            



	//     }
    // render_UPDATE(ren, ARRAY_textures, ARRAY_rect, ARRAY_texturesState);
    // SDL_RenderPresent(ren);
    // }
    SDL_DestroyTexture(player);
    SDL_DestroyTexture(background);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();	
    return 1;
}

