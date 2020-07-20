#define NAME_WINDOW "GAME"

#include "head.h"

int head = 0;
int apple = 45;
int direction = 1;
int tail[BOARD_SIZE] = {0};
int accumulator = 0;
int length = 0;
int i = 0;
bool isDead = false;
SDL_Renderer* ctx = NULL;
//SDL_Window* canvas = NULL;
Uint32 previousTicks = 0;

void draw(int position, int r, int g, int b )
{
    SDL_Rect rect = { position % BOARD_COLS, position / BOARD_COLS, SIZE, SIZE };
    rect.x *= SIZE;
    rect.y *= SIZE;
    SDL_SetRenderDrawColor( ctx, r, g, b, SDL_ALPHA_OPAQUE );
    SDL_RenderFillRect( ctx, &rect );
}

int randm()
{
    return rand() % BOARD_SIZE;
}

bool isOnLimits()
{
    return (direction ==  1 && head % BOARD_COLS == 0) ||
           (direction == -1 && (head + 1) % BOARD_COLS == 0);
}

bool hasCollisionWithTail(int position)
{
    for (int i = 0; i < length; i++) {
        if (tail[i] == position) {
            return true;
        }
    }
    return false;
}

void placeApple()
{
    for ( ;; ) {
        apple = randm();
        if ( head != apple || !hasCollisionWithTail(apple) ) {
            break;
        }
    }
}

void setDirection(int dir) {
    if (dir != -direction || length == 0) {
        direction = dir;
    }
}

void drawBoard()
{
    for (int i = 0; i < length; ++i) {
        draw(tail[i], 0, 255, 0);
    }
    draw(head, 10, 150, 10);
    draw(apple, 255, 255, 255);
}

void move()
{
    tail[i] = head;
    head += direction;
    if (++i >= length) {
        i = 0;
    }
    if (isOnLimits()) {
        head -= BOARD_COLS * direction;
    } else if (head < 0) {
        head += BOARD_SIZE;
    } else if (head >= BOARD_SIZE) {
        head -= BOARD_SIZE;
    }
}

void update(int delta)
{
    accumulator += delta;
    if (accumulator >= TIMEOUT && !isDead) {
        accumulator = 0;
        move();
        if (head == apple) {
            placeApple();
            tail[length++] = head;
        } else if (hasCollisionWithTail(head)) {
            isDead = true;
        }
    }
    drawBoard();
}

int snake(void)
{
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
    SDL_Window* win = SDL_CreateWindow(NAME_WINDOW,
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       SIZE * BOARD_COLS, SIZE * BOARD_ROWS,0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    ctx = SDL_CreateRenderer(win, -1, render_flags);
    SDL_Event event;


    //if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    //    return EXIT_FAILURE;
    //}
    while (!SDL_QuitRequested()) {
        if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]) {
            setDirection(-BOARD_COLS);
        } else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]) {
            setDirection( BOARD_COLS);
        } else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]) {
            setDirection(-1);
        } else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]) {
            setDirection(1);
        } 
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    if(!isDead){
                        SDL_DestroyWindow(win);
                        return 0;
                    }
                    if(isDead){
                        SDL_DestroyWindow(win);
                        return 1;
                    }
                }
            }
        }


        SDL_SetRenderDrawColor(ctx, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(ctx);
        Uint32 current = SDL_GetTicks();
        Uint32 delta = current - previousTicks;
        previousTicks = current;
        update(delta);
        SDL_RenderPresent(ctx);

    }

    //SDL_DestroyRenderer(ctx);
    //SDL_DestroyWindow(canvas);
    //SDL_DestroyWindow(win);
    //SDL_Quit();
    return 1;
}
