#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600

void createcharacter(SDL_Renderer* renderer, int r, int g, int b, int x, int y){
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_Rect boxbod = {x,y,80, 20};
    SDL_Rect botgun = {x+20,y-20, 40, 20};
    SDL_Rect gun = {x+35,y-40, 10, 30};
    SDL_RenderFillRect(renderer, &boxbod);
    SDL_RenderFillRect(renderer, &botgun);
    SDL_RenderFillRect(renderer, &gun);
}

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Space Invader", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_RaiseWindow(window);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("SDL failied to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    SDL_Event event;
    bool quit = false;
    int x = WIDTH /2;
    int y = HEIGHT - 20;
    int playerspeed = 20;
    while(!quit){

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        x += playerspeed;
                        break;
                    case SDLK_LEFT:
                        x-=playerspeed;
                }
            }

        }
        SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0,0,255, 255);
        createcharacter(renderer, 0, 0, 255, x, HEIGHT - 20);


        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}