#include "minilib.h"

#define NAME_WINDOW "Hello World"

#define WINDOW_WIDTH (2550)
#define WINDOW_HEIGHT (1390)

// speed in pixels/second
#define SPEED (750)
#define BALL_SPEED (750)

int duo(void)
{
    int counter = 0;
    int counterbot = 0;
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("First",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT,0);
    if (!win)
    {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend)
    {
      printf("error creating renderer: %s\n", SDL_GetError());
      SDL_DestroyWindow(win);
      SDL_Quit();
      return 1;
    }

    // load the image into memory using SDL_image library function
    SDL_Surface* ball = IMG_Load("kek.png");
    SDL_Surface* platform = IMG_Load("platform.png");
    SDL_Surface* bot = IMG_Load("platform2.png");
    if (!ball || !platform)
    {
        printf("error creating surface\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // load the image data into the graphics hardware's memory
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, ball);
    SDL_Texture* mex = SDL_CreateTextureFromSurface(rend, platform);
    SDL_Texture* vex = SDL_CreateTextureFromSurface(rend, bot);
    SDL_FreeSurface(ball);
    SDL_FreeSurface(platform);
    SDL_FreeSurface(bot);
    if (!tex || !mex || !bot)
    {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    // struct to hold the position and size of the sprite
    SDL_Rect dest;
    SDL_Rect platform_dest;
    SDL_Rect bot_dest;

    // get and scale the dimensions of texture
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    SDL_QueryTexture(mex, NULL, NULL, &platform_dest.w, &platform_dest.h);
    SDL_QueryTexture(vex, NULL, NULL, &bot_dest.w, &bot_dest.h);
    dest.w /= 3;
    dest.h /= 3;

    platform_dest.w /= 3;
    platform_dest.h /= 2;

    bot_dest.w /= 3;
    bot_dest.h /= 2;

    // start sprite in center of screen
    float x_pos = (WINDOW_WIDTH - dest.w) / 2;
    float y_pos = (WINDOW_HEIGHT - dest.h) / 2;

    float x_platform = (0);
    float y_platform = (WINDOW_HEIGHT - platform_dest.h) / 2;

    float x_bot = (WINDOW_WIDTH - bot_dest.w);
    float y_bot = (WINDOW_HEIGHT- bot_dest.h) / 2;

    // give sprite initial velocity
    float x_vel = BALL_SPEED;
    float y_vel = BALL_SPEED;
    float y_speed = 0;
    float y_speed_bot = 0;

    // keep track of which inputs are given
    int up = 0;
    int down = 0;
    
    int sup = 0;
    int sdown = 0;
    // set to 1 when window close button is pressed
    int close_requested = 0;
    //float vec_ball_speed = BALL_SPEED;
    //int plat_size = platform_dest.w / 8;
    // animation loop
        SDL_Event event;
    while (!close_requested) {
        // process events

    while (SDL_PollEvent(&event)) {
            //SDL_Pumpevents();
            switch (event.type) {
            case SDL_QUIT:
                close_requested = 1;
                break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {

            case SDLK_ESCAPE:
            close_requested = true;
            break;

            case SDLK_w:
                up = 1;
                break;

            case SDLK_s:
                down = 1;
                break;


            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            //     case SDL_SCANCODE_UP:
            //     sup = 0;
            //     break;

            // case SDL_SCANCODE_DOWN:
            //     sup = 0;
            //     break;
            case SDLK_w:
                up = 0;
                break;

            case SDLK_s:
                down = 0;
                break; 

            default:
                break;

            }
            default:
                break;
            }

            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {

            case SDLK_UP:
                sup = 1;
                break;

            case SDLK_DOWN:
                sdown = 1;
                break;

            default:
                break;
            }
            case SDL_KEYUP:
            switch (event.key.keysym.scancode) {

            case SDL_SCANCODE_UP:
                sup = 0;
                break;

            case SDL_SCANCODE_DOWN:
                sup = 0;
                break;

            default:
                break;

            }
            default:
                break;
        }
    }

        //collision detection with bounds
        // if (x_pos == platform_dest.w && y_pos == platform_dest.h)
        // {
        //     x_pos = 0;
        //     x_vel = -x_vel;
        // }

        if (x_pos <= -dest.w)
        {
            x_pos = (WINDOW_WIDTH - dest.w) / 2;
            y_pos = (WINDOW_HEIGHT - dest.h) / 2;
            x_vel = -x_vel;
            y_vel = BALL_SPEED;
            counter ++;

        }
        if (x_pos + platform_dest.w >= x_platform && x_pos <= x_platform + platform_dest.w)
        {
        if (y_pos + platform_dest.w >= y_platform && y_pos <= y_platform + platform_dest.h)
        {


            if (x_pos + platform_dest.w < x_platform + platform_dest.w)
            {
                x_vel = -x_vel;
            }
        }
    }


        if (x_pos >= WINDOW_WIDTH - dest.w)
        {
            x_pos = (WINDOW_WIDTH - dest.w) / 2;
            y_pos = (WINDOW_HEIGHT - dest.h) / 2;
            x_vel = -x_vel;
            counterbot ++;
            y_vel = BALL_SPEED;
            // vec_ball_speed = SPEED;
        }

        if (x_pos + bot_dest.w >= x_bot && x_pos <= x_bot + bot_dest.w)
        {
        if (y_pos + bot_dest.w >= y_bot && y_pos <= y_bot + bot_dest.h)
        {


            if (x_pos + bot_dest.w < x_bot + bot_dest.w)
            {

                // vertical collision
                 x_vel = -x_vel;
            //     if (y_speed_bot > 0 && y_vel > 0){
            //         y_vel *= 1.2;
            //         y_speed_bot *= 1.2;
            //         if(y_speed_bot > SPEED)
            //             y_speed_bot = 750;
            //     }

            //     if (y_speed_bot < 0 && y_vel < 0){
            //         y_vel *= 1.2;
            //         y_speed_bot *= 1.2;
            //             if(y_speed_bot > SPEED)
            //         y_speed_bot = 750;
            //     }

            //     if (y_speed_bot > 0 && y_vel < 0) {
            //     y_vel /= 1.4;
            //     y_speed_bot /= 1.4;
            //     }
            //     if (y_speed_bot < 0 && y_vel > 0) {
            //     y_vel /= 1.4;
            //     y_speed_bot /= 1.4;
            //     }
            }
            // else
            // {
            //     this->move(player1.getX() + player1.getW() - this->_x, 0);
            //     collision(player1);
            // }
        }
    }


        if (y_pos <= 0)
        {
            y_pos = 0;
            y_vel = -y_vel;
        }
        if (x_pos >= WINDOW_WIDTH - dest. w) 
        {
            x_pos = WINDOW_WIDTH - dest.w;
            x_vel = -x_vel;
        }
        if (y_pos >= WINDOW_HEIGHT - dest.h)
        {
            y_pos = WINDOW_HEIGHT - dest.h;
            y_vel = -y_vel;
        }


        // determine velocity
        y_speed = 0;
        y_speed_bot = 0;

        if (sup && !sdown) y_speed_bot = -SPEED;
        if (sdown && !sup) y_speed_bot = SPEED;

        if (up && !down) y_speed = -SPEED;
        if (down && !up) y_speed = SPEED;


        // update positions
        x_pos += x_vel / 60;
        y_pos += y_vel / 60;
        y_platform += y_speed / 60;
        y_bot += y_speed_bot / 60;
     //   y_platform = y_platform / 60;

        // set the positions in the struct
        dest.y = (int) y_pos;
        dest.x = (int) x_pos;
        platform_dest.y = (int) y_platform;
        platform_dest.x = (int) x_platform;
        bot_dest.y = (int) y_bot;
        bot_dest.x = (int) x_bot;


        if (y_bot <= 0) y_bot = 0;
        if (y_bot >= WINDOW_HEIGHT - bot_dest.h) y_bot = WINDOW_HEIGHT - bot_dest.h;

        if (y_platform <= 0) y_platform = 0;
        if (y_platform >= WINDOW_HEIGHT - platform_dest.h) y_platform = WINDOW_HEIGHT - platform_dest.h;
        
        // clear the window
        SDL_RenderClear(rend);

        // draw the image to the window
        SDL_RenderCopy(rend, tex, NULL, &dest);
        SDL_RenderCopy(rend, mex, NULL, &platform_dest);
        SDL_RenderCopy(rend, vex, NULL, &bot_dest);
        SDL_RenderPresent(rend);

        // wait 1/60th of a second
        SDL_Delay(1000/60);
    }
    // clean up resources before exiting
    SDL_DestroyTexture(vex);
    SDL_DestroyTexture(mex);
    SDL_DestroyTexture(tex);
   // SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
  //  SDL_Quit();
    return 1;
}
