#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 800
#define HEIGHT 600
#define bullets 8

SDL_Rect shots [bullets];



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
    int shotspeed = 10;
    int count = 0;
    int num = 0;
        for(int i = 0; i<bullets; i++){
            shots[i].h = 20;
            shots[i].w = 5;
            shots[i].x = x + 37;
            shots[i].y = y;
        }

    while(!quit){
        bool t = false;

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
                        x -= playerspeed;
                        break;
                    case SDLK_UP:
                        t= true;
                        count ++;
                        num++;
                        break;
                    default:
                        break;
                }
            }

        }
        SDL_SetRenderDrawColor(renderer, 0,0,0, 255);
        SDL_RenderClear(renderer);

        for(int i = 0; i< bullets; i++){
            if((shots[i].y < y) && (shots[i].y > -20)){
                shots[i].y -= shotspeed;
                printf("shots at [%d] moved up\n", i);
            }
        }

        if(t){
            shots[count-1].y -= shotspeed+20;
        }else{
            for(int i = count; i< bullets; i++){
                shots[i].x = x +37;
            }
        }

        for(int i = 0; i< bullets; i++){
            if(shots[i].y <= -20){
                shots[i].y = y;
                num --;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255,0,0, 255);
        for(int i = 0; i< bullets; i++){
            SDL_RenderFillRect(renderer, &shots[i]);
        }
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