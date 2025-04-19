/*
notes: you need to have downloaded brew SDL2/SDL and then SDL2/SDL_ttf.h the ttf.h is for the numbers that
keep track of the score

Compile:
clang -o pongtest pongtest.c -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf

Run:
./pongtest

*/


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 800
#define HIGHT 600


struct Circle{
    double x;
    double y;
    double r;
};

void FillCircle(SDL_Renderer* renderer, struct Circle circle){
    double radius = pow(circle.r, 2);
    for (double x = circle.x - circle.r; x <= circle.x + circle.r; x++){
        for(double y = circle.y - circle.r; y <= circle.y + circle.r; y++){
            double dist = pow(x-circle.x, 2) + pow(y-circle.y, 2);
            if(dist <= radius){
                SDL_RenderDrawPoint(renderer, (int)x, (int)y);
            }
        }
    }
}



int main (){

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window* window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HIGHT, SDL_WINDOW_SHOWN);
    SDL_RaiseWindow(window);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(! renderer){
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    TTF_Font* font = TTF_OpenFont("OpenSans-Regular.ttf", 48); // Make sure the TTF file is in your project directory
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 1;
    }


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    int player1HIGHT = 200;
    int player2HIGHT = 200;
    int ballx = 200;
    int bally = 200;
    int ballydirection = 1;
    int ballxdirection = 1;
    int highchange = 5;
    int speed = 3;
    int lastmove1 = 1;
    int lastmove2 = 1;

    int score1 = 0;
    int score2 = 0;

    SDL_Rect rect1 = {0,player1HIGHT,50,200};
    SDL_Rect rect2 = {WIDTH - 50,player2HIGHT,50,200};
    struct Circle circle1 = {WIDTH -30,HIGHT -30,30};

    SDL_RenderFillRect(renderer, &rect1);
    SDL_RenderFillRect(renderer, &rect2);

    SDL_RenderPresent(renderer);


    SDL_Event event;
    SDL_Event event2;
    bool quit = false;
    while(!quit){
        SDL_Rect rect3 = {0,player1HIGHT,50,200};
        SDL_Rect rect4 = {WIDTH - 50,player2HIGHT,50,200};
        SDL_Rect rect5 = {400,0,5,50};
        SDL_Rect rect6 = {400,100,5,50};
        SDL_Rect rect7 = {400,200,5,50};
        SDL_Rect rect8 = {400,300,5,50};
        SDL_Rect rect9 = {400,400,5,50};
        SDL_Rect rect10 = {400,500,5,50};
        srand(time(NULL));

        int randhigh = ((rand() % 11)-8); // 40% chance of chnging dircetion

        struct Circle circle = {ballx,bally,30};
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                quit = true;
            }
            if(event.type == SDL_KEYDOWN){
                if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    player2HIGHT -= 50;
                    lastmove2 = 1;
                    break;
                case SDLK_DOWN:
                    player2HIGHT += 50;
                    lastmove2 = -1;
                    break;
                case SDLK_w:
                    player1HIGHT -= 50;
                    lastmove1 = 1;
                    break;
                case SDLK_s:
                    player1HIGHT += 50;
                    lastmove1 = -1;
                    break;
                default:
                    break;
                }
                
                }
            }
        }


        if((bally >= player2HIGHT && bally <= (player2HIGHT + 200)) && (ballx + 30 >= WIDTH - 50)){
            ballxdirection *= -1;
            highchange -= randhigh;
            speed += 1;
            if(lastmove2 == ballydirection){ballydirection *= -1;}
        }
        if((bally >= player1HIGHT && bally <= player1HIGHT + 200) && (ballx - 30 <= 50)){
            ballxdirection *= -1;
            highchange += randhigh;
            if(lastmove1 == ballydirection){ballydirection *= -1;}
        }


        if(!((bally + 30) < HIGHT && (bally-30) > 0)){
            ballydirection *= -1;
        }
        bally += (highchange * ballydirection);

        if(((ballx + 30) >= WIDTH || (ballx-30) <= 0)){
            if((ballx + 30) >= WIDTH){score2++;}
            if((ballx-30) <= 0){score2++;}
            ballx = HIGHT/2;
            bally = WIDTH/2;
            speed = 4;
            highchange = 5;
            SDL_Delay(2000);
        }
        ballx += (speed * ballxdirection);



        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        char score1Text[32];
        char score2Text[32];
        sprintf(score1Text, "%d", score1);
        sprintf(score2Text, "%d", score2);

        SDL_Color color = {255, 255, 255};

        SDL_Surface* score1Surface = TTF_RenderText_Solid(font, score1Text, color);
        SDL_Texture* score1Texture = SDL_CreateTextureFromSurface(renderer, score1Surface);
        SDL_Rect score1Rect = {WIDTH / 4 - score1Surface->w / 2, 50, score1Surface->w, score1Surface->h};
        SDL_FreeSurface(score1Surface);
        SDL_RenderCopy(renderer, score1Texture, NULL, &score1Rect);
        SDL_DestroyTexture(score1Texture);

// Render score 2
        SDL_Surface* score2Surface = TTF_RenderText_Solid(font, score2Text, color);
        SDL_Texture* score2Texture = SDL_CreateTextureFromSurface(renderer, score2Surface);
        SDL_Rect score2Rect = {3 * WIDTH / 4 - score2Surface->w / 2, 50, score2Surface->w, score2Surface->h};
        SDL_FreeSurface(score2Surface);
        SDL_RenderCopy(renderer, score2Texture, NULL, &score2Rect);
        SDL_DestroyTexture(score2Texture);

        SDL_RenderFillRect(renderer, &rect3);
        SDL_RenderFillRect(renderer, &rect4);
        SDL_RenderFillRect(renderer, &rect5);
        SDL_RenderFillRect(renderer, &rect6);
        SDL_RenderFillRect(renderer, &rect7);
        SDL_RenderFillRect(renderer, &rect8);
        SDL_RenderFillRect(renderer, &rect9);
        SDL_RenderFillRect(renderer, &rect10);
        FillCircle(renderer, circle);

        SDL_RenderPresent(renderer);
        SDL_Delay(20);
        
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}