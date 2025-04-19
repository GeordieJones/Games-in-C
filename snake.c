/*
notes: you need to have downloaded brew SDL2/SDL and then SDL2/SDL_ttf.h the ttf.h is for the numbers that
keep track of the score

Compile:
clang -o snake snake.c -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf

Run:
./snake

*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 600
#define HEIGHT 600

int squareHeight = HEIGHT / 9;
int squareWidth = WIDTH / 10;

SDL_Rect board [10][9];


int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_RaiseWindow(window);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("SDL RENDERER ERROR %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int speed = 15;
    int direct = 1;
    int x = 180;
    int y = 66;

    SDL_Event event;
    bool quit = false;
    while(!quit){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = true;
            } /*
            Directions:
                        2
                    3       1
                        4
               */
            if(event.type == SDL_KEYDOWN){
                if(event.type == SDL_KEYDOWN){
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_UP:
                        direct = 2;
                        break;
                    case SDLK_LEFT:
                        direct = 3;
                        break;
                    case SDLK_DOWN:
                        direct = 4;
                        break;
                    case SDLK_RIGHT:
                        direct = 1;
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        switch (direct)
                    {
                    case 1:
                        x += speed;
                        break;
                    case 2:
                        y -= speed;
                        break;
                    case 3:
                        x -= speed;
                        break;
                    case 4:
                        y += speed;
                        break;
                    default:
                        break;
                    }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect head= {x, y, squareWidth, squareHeight};
        SDL_RenderFillRect(renderer, &head);

        


        for(int r = 0; r < HEIGHT / squareHeight; r++){
            for(int c = 0; c < WIDTH / squareWidth; c++){
                board[c][r].x = c * squareWidth;
                board[c][r].y = r * squareHeight;
                board[c][r].w = squareWidth;
                board[c][r].h = squareHeight;
                SDL_RenderDrawRect(renderer, &board[c][r]);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }



    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();



    return 0;
}