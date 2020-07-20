#include "minilib.h"

#define NAME_WINDOW "Menu"

#define WINDOW_WIDTH (2550)
#define WINDOW_HEIGHT (1390)
#define MAX_SND_CHANNELS 10 // max number of sounds

//specify the channel through which a sound will play
//Mix_Chunk *sounds[SND_MAX];
Mix_Music *music;

// enum
// {
//     CH_ANY = -1,
//     CH_HERO,
//     CH_ENEMIE_FIRE
// };

// enum
// {
//     SND_GAME_SOUND,
//     SND_MAX
// };

// speed in pixels/second



// static void loadSounds(void)
// {
//     sounds[SND_GAME_SOUND] = Mix_LoadWAV("music.mp3");
// }


void loadMusic(char *filename)
{
    if (music != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = NULL;
    }

    music = Mix_LoadMUS(filename);      //Note that this doesn't start playing the music; it only loads it into memory for us to use later. To play music, we have to call a different function which we'll cover next:
}


/*The playMusic function we've created does just that: it calls the SDL function Mix_PlayMusic. 
This function takes just two arguments - the Mix_Music pointer (music) and the number of times the music should loop. 
If we want it to loop forever, we pass -1. Otherwise, we pass over the number of times want to loop. 
Our playMusic function only supports looping forever or playing once, but it's sufficient. */

void playMusic(int loop)
{
    Mix_PlayMusic(music, (loop) ? -1 : 0);
}


// void playSound(int id, int channel)
// {
//     Mix_PlayChannel(channel, sounds[id], 0);
// }

  // void initSounds(void)
  //   {
  //       memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);
        
  //       music = NULL;
        
  //       loadSounds();
  //   }



int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) // the frequency, format, channels, and chunkSize. 
    {
        printf("Couldn't initialize SDL Mixer\n");
        exit(1);
    }

    //Mix_AllocateChannels(MAX_SND_CHANNELS); //We now play 8 sound effects at the same time.

  

  //  initSounds();
    loadMusic("music.mp3");
    playMusic(-1); // allows music to loop

    SDL_Window* win = SDL_CreateWindow("Hello World",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
	    return 1;
    }

    playMusic(-1);
    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
      printf("error creating renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(win);
      SDL_Quit();
      return 1;
    }

    // load the image into memory using SDL_image library function
    SDL_Surface* terminal = IMG_Load("pizdec.png");
    SDL_Surface* terminal1 = IMG_Load("pizdec1.png");
    SDL_Surface* zero = IMG_Load("0.png");
    SDL_Surface* first = IMG_Load("1.png");
    SDL_Surface* second = IMG_Load("2.png");
    SDL_Surface* world = IMG_Load("name.png");
    SDL_Surface* space = IMG_Load("Duo.png");
    SDL_Surface* solo = IMG_Load("solo.png");
    SDL_Surface* solohard = IMG_Load("solohard.png");
    SDL_Surface* simple = IMG_Load("simple.png");
    SDL_Surface* start = IMG_Load("start.png");
    SDL_Surface* over = IMG_Load("game_over.png");

    if (!terminal)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture* trm = SDL_CreateTextureFromSurface(rend, terminal);
    SDL_Texture* trm1 = SDL_CreateTextureFromSurface(rend, terminal1);
    SDL_Texture* zer = SDL_CreateTextureFromSurface(rend, zero);
    SDL_Texture* fir = SDL_CreateTextureFromSurface(rend, first);
    SDL_Texture* sec = SDL_CreateTextureFromSurface(rend, second);
    SDL_Texture* nam = SDL_CreateTextureFromSurface(rend, world);
    SDL_Texture* spc = SDL_CreateTextureFromSurface(rend, space);
    SDL_Texture* sol = SDL_CreateTextureFromSurface(rend, solo);
    SDL_Texture* soh = SDL_CreateTextureFromSurface(rend, solohard);
    SDL_Texture* smp = SDL_CreateTextureFromSurface(rend, simple);
    SDL_Texture* srt = SDL_CreateTextureFromSurface(rend, start);
    SDL_Texture* ovr = SDL_CreateTextureFromSurface(rend, over);
    SDL_FreeSurface(terminal);
    if (!trm)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // struct to hold the position and size of the sprite
    SDL_Rect trm_dest;
    SDL_Rect trm1_dest;
    SDL_Rect zer_dest;
    SDL_Rect fir_dest;
    SDL_Rect sec_dest;
    SDL_Rect nam_dest;
    SDL_Rect spc_dest;
    SDL_Rect sol_dest;
    SDL_Rect soh_dest;
    SDL_Rect smp_dest;
    SDL_Rect srt_dest;
    SDL_Rect ovr_dest;

    // get and scale the dimensions of texture
    SDL_QueryTexture(trm, NULL, NULL, &trm_dest.w, &trm_dest.h);
    SDL_QueryTexture(trm, NULL, NULL, &trm1_dest.w, &trm1_dest.h);
    SDL_QueryTexture(zer, NULL, NULL, &zer_dest.w, &zer_dest.h);
    SDL_QueryTexture(fir, NULL, NULL, &fir_dest.w, &fir_dest.h);
    SDL_QueryTexture(sec, NULL, NULL, &sec_dest.w, &sec_dest.h);
    SDL_QueryTexture(nam, NULL, NULL, &nam_dest.w, &nam_dest.h);
    SDL_QueryTexture(spc, NULL, NULL, &spc_dest.w, &spc_dest.h);
    SDL_QueryTexture(sol, NULL, NULL, &sol_dest.w, &sol_dest.h);
    SDL_QueryTexture(soh, NULL, NULL, &soh_dest.w, &soh_dest.h);
    SDL_QueryTexture(smp, NULL, NULL, &smp_dest.w, &smp_dest.h);
    SDL_QueryTexture(srt, NULL, NULL, &srt_dest.w, &srt_dest.h);
    SDL_QueryTexture(ovr, NULL, NULL, &ovr_dest.w, &ovr_dest.h);
    
    trm_dest.w *= 1.4;
    trm_dest.h *= 1.4;

    trm1_dest.w *= 1.4;
    trm1_dest.h *= 1.4;

    zer_dest.w /= 1.3;
    zer_dest.h /= 1.3;

    fir_dest.w /= 1.3;
    fir_dest.h /= 1.3;

    sec_dest.w /= 1.3;
    sec_dest.h /= 1.3;

    sol_dest.w /= 1.3;
    sol_dest.h /= 1.3;

    soh_dest.w /= 1.3;
    soh_dest.h /= 1.3;

    spc_dest.w /= 1.3;
    spc_dest.h /= 1.3;

    smp_dest.w /= 1.3;
    smp_dest.h /= 1.3;

        // start sprite in center of screen
    float x_term = (WINDOW_WIDTH - trm_dest.w) / 2;
    float y_term = (WINDOW_HEIGHT - trm_dest.h) / 2;

    float x_term1 = (WINDOW_WIDTH - trm_dest.w) / 2;
    float y_term1 = (WINDOW_HEIGHT - trm_dest.h) / 2;

    float x_zero = (WINDOW_WIDTH - zer_dest.w) / 2;
    float y_zero = (WINDOW_HEIGHT - zer_dest.h) / 2;

    float x_first = (WINDOW_WIDTH - fir_dest.w) / 2;
    float y_first = (WINDOW_HEIGHT - fir_dest.h) / 2;

    float x_second = (WINDOW_WIDTH - sec_dest.w) / 2;
    float y_second = (WINDOW_HEIGHT - sec_dest.h) / 2;

    float x_world = (WINDOW_WIDTH - nam_dest.w) / 2;
    float y_world = (WINDOW_HEIGHT - nam_dest.h) / 2;

    // draw the image to the window
    SDL_RenderPresent(rend);

    // set to 1 when window close button is pressed
    int close_requested = 0;
    int counter = 0;
    int mems = 0;
    int mode = 0;
    int kek = 0;
    // wait a few seconds
    SDL_Event event;
    while (!close_requested)
    {
        // process events
        
        while (SDL_PollEvent(&event))
        {
            //SDL_Pumpevents();
            switch (event.type)
            {
            case SDL_QUIT: close_requested = true;
             break;
               case SDL_KEYDOWN:
                   switch(event.key.keysym.sym){

            case SDLK_ESCAPE:
                close_requested = true;
                break;

            case SDLK_DOWN:
            if(mems == 0){
                if(mode < 2)
                    mode ++;
            }
            break;

            case SDLK_UP:
                if(mems == 0){
                    if(mode > 0)
                        mode --;
                }
                break;

            case SDLK_LEFT:
            if(mems > -1)
            mems--;
            break;

            case SDLK_RIGHT:
            if(mems < 2)
            mems++;

            break;

            case SDLK_SPACE:
                counter++;
                if(counter > 1){
                    if(mems == -1)
                catgame();
                    if (mems == 0 && mode == 0)
                ugh();
                    if (mems == 0 && mode == 1)
                solomode();
                    if (mems == 0 && mode == 2)
                solohardmode();
                    if (mems == 0 && mode == 3)
                duo();
                    if (mems == 1)
                kek = snake();
                    if (mems == 2)
                coingame();
            }
                //close_requested = 1;
            break;

            // case SDLK_ESCAPE:
            //     close_requested = true;
            //     break;

            default:
                break;
            }
            default:
                break;
        }
    }

        trm1_dest.y = (int) y_term1;
        trm1_dest.x = (int) x_term1;

        trm_dest.y = (int) y_term;
        trm_dest.x = (int) x_term;

        zer_dest.y = (int) y_zero;
        zer_dest.x = (int) x_zero;

        fir_dest.y = (int) y_first;
        fir_dest.x = (int) x_first;

        sec_dest.y = (int) y_second;
        sec_dest.x = (int) x_second;

        nam_dest.y = (int) y_world;
        nam_dest.x = (int) x_world;

        sol_dest.y = (int) (WINDOW_HEIGHT - sol_dest.y) / 2;
        sol_dest.x = (int) (WINDOW_WIDTH - sol_dest.x) / 2;

        soh_dest.y = (int) (WINDOW_HEIGHT - soh_dest.y) / 2;
        soh_dest.x = (int) (WINDOW_WIDTH - soh_dest.x) / 2;

        spc_dest.y = (int) (WINDOW_HEIGHT - spc_dest.y) / 2;
        spc_dest.x = (int) (WINDOW_WIDTH - spc_dest.x) / 2;

        smp_dest.y = (int) (WINDOW_HEIGHT - smp_dest.y) / 2;
        smp_dest.x = (int) (WINDOW_WIDTH - smp_dest.x) / 2;

        srt_dest.y = (int) (WINDOW_HEIGHT - srt_dest.y) / 4;
        srt_dest.x = (int) (WINDOW_WIDTH - srt_dest.x / 2 - 40) / 2;

        ovr_dest.y = (int) (WINDOW_HEIGHT - ovr_dest.y) / 5;
        ovr_dest.x = (int) (WINDOW_WIDTH - ovr_dest.x / 1.3) / 2;

        // clear the window
        SDL_RenderClear(rend);

        // draw the image to the window
  
        SDL_RenderCopy(rend, trm, NULL, &trm_dest);
        
        if(counter == 0)
            SDL_RenderCopy(rend, srt, NULL, &srt_dest);

        if(counter > 0)
            SDL_RenderCopy(rend, trm1, NULL, &trm1_dest);
        if(mems == 0 && counter > 0)
            SDL_RenderCopy(rend, zer, NULL, &zer_dest);

        if(mems == 0 && counter > 0)
            if(mode == 0)
                SDL_RenderCopy(rend, smp, NULL, &smp_dest);

        if(mems == 0 && counter > 0)
            if(mode == 1)
                SDL_RenderCopy(rend, sol, NULL, &sol_dest);

        if(mems == 0 && counter > 0)
            if(mode == 2)
                SDL_RenderCopy(rend, soh, NULL, &soh_dest);

        if(mems == 0 && counter > 0)
            if(mode == 3)
                SDL_RenderCopy(rend, spc, NULL, &spc_dest);

        if(mems == -1 && counter > 0)
              SDL_RenderCopy(rend, nam, NULL, &nam_dest);

        if(mems == 1 && counter > 0){
                    SDL_RenderCopy(rend, fir, NULL, &fir_dest);
                if(kek)
                    SDL_RenderCopy(rend, ovr, NULL, &ovr_dest);
        }
              
        if(mems == 2 && counter > 0)  
              SDL_RenderCopy(rend, sec, NULL, &sec_dest);



        SDL_RenderPresent(rend);

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }
    
    // clean up resources before exiting
    SDL_DestroyTexture(trm);
    SDL_DestroyTexture(soh);
    SDL_DestroyTexture(sol);
    SDL_DestroyTexture(trm1);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
