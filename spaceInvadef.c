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
#define crabrow WIDTH / 80

SDL_Rect shots [bullets];


struct crab{
    int x;
    int y;
    int width;
    int height;
    int alive;
};


void createcharacter(SDL_Renderer* renderer, int r, int g, int b, int x, int y){
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_Rect boxbod = {x,y,80, 20};
    SDL_Rect botgun = {x+20,y-20, 40, 20};
    SDL_Rect gun = {x+35,y-40, 10, 30};
    SDL_RenderFillRect(renderer, &boxbod);
    SDL_RenderFillRect(renderer, &botgun);
    SDL_RenderFillRect(renderer, &gun);
}

void buildwall(SDL_Renderer* renderer,int r, int g, int b, int x, int y){
    SDL_SetRenderDrawColor(renderer, r,g,b,255);
    SDL_Rect boxbold = {x,y, 150, 50};
    SDL_RenderFillRect(renderer, &boxbold);
}

//crab is 60 by 40
void createcrabbody(SDL_Renderer* renderer,int r, int g, int b, int x, int y){
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_Rect leftclaw = {x,y,5, 20};
    SDL_Rect leftjoint = {x+5,y-5,5, 15};
    SDL_Rect leftbod = {x+10,y-10,40, 30};
    SDL_Rect rightclaw = {x + 55,y,5, 20};
    SDL_Rect rightjoint = {x+50,y-5,5, 15};
    SDL_Rect leftattena = {x + 15,y-20, 5, 20};
    SDL_Rect rightattena = {x + 40,y-20, 5, 20};
    SDL_RenderFillRect(renderer, &leftclaw);
    SDL_RenderFillRect(renderer, &leftjoint);
    SDL_RenderFillRect(renderer, &leftbod);
    SDL_RenderFillRect(renderer, &rightclaw);
    SDL_RenderFillRect(renderer, &rightjoint);
    SDL_RenderFillRect(renderer, &rightattena);
    SDL_RenderFillRect(renderer, &leftattena);
}

void crabeye(SDL_Renderer* renderer, int x, int y){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect eye1 = {x + 20,y-2, 5, 10};
    SDL_Rect eye2 = {x + 35,y-2, 5, 10};
    SDL_RenderFillRect(renderer, &eye1);
    SDL_RenderFillRect(renderer, &eye2);
}

void printCrab(SDL_Renderer* renderer, struct crab crabs [crabrow][3], int x){
    int yAdd = 0;
    for(int i = 0; i < 3; i++){
        for(int h = 0; h < crabrow; h++){
            if(crabs[h][i].alive == 1){
                SDL_SetRenderDrawColor(renderer, 0,0,255, 255);
                createcrabbody(renderer, 0, 255, 0, crabs[h][i].x + x, crabs[h][i].y + yAdd);
                SDL_SetRenderDrawColor(renderer, 0,0,255, 255);
                crabeye(renderer, crabs[h][i].x + x,crabs[h][i].y + yAdd);
            }
        }
    }
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
    struct crab crabs [crabrow][3];
    for(int i = 0; i < 3; i++){
        for(int h = 0; h < crabrow; h++){
            crabs[h][i].x = h*80;
            crabs[h][i].y = (i * 60)+40;
            crabs[h][i].width = 60;
            crabs[h][i].height = 40;
            crabs[h][i].alive = 1;
        }
    }
    SDL_Event event;
    bool quit = false;
    int x = WIDTH /2;
    int y = HEIGHT - 20;
    int playerspeed = 20;
    int shotspeed = 10;
    int count = 0;
    int num = 0;
    int intAdder= 2;
    int heightAdd = 0;
    int trav = 0;
    int tray = 0;

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
                        if(count == 8){
                            count = 1;
                            break;
                        }
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
            }else{
                if(shots[i].y == y){
                    shots[i].x = x +37;
                }
                
            }
        }

        if(t){
            shots[count-1].y -= shotspeed+20;
        }

        for(int i = 0; i< bullets; i++){

            for(int t = 0; t < 3; t++){
                for(int h = 0; h < crabrow; h++){
                    if(crabs[h][t].y - 40 == shots[i].y){
                        if((shots[i].x >= crabs[h][t].x) && (shots[i].x <= crabs[h][t].x+60) && (crabs[h][t].alive == 1)){
                            shots[i].y = y;
                            shots[i].x = x;
                            num--;
                            crabs[h][t].alive = 0;
                        }
                    }
                }
            }

            if(shots[i].y <= -20){
                shots[i].y = y;
                shots[i].x = x;
                num --;
            }
        }


        SDL_SetRenderDrawColor(renderer, 255,0,0, 255);
        for(int i = 0; i< bullets; i++){
            SDL_RenderFillRect(renderer, &shots[i]);
        }
        SDL_SetRenderDrawColor(renderer, 0,0,255, 255);
        createcharacter(renderer, 0, 0, 255, x, HEIGHT - 20);
        buildwall(renderer, 0,0,255,75, 450);
        buildwall(renderer, 0,0,255,330, 450);
        buildwall(renderer, 0,0,255,600, 450);

        printCrab(renderer, crabs, 0);

        if(trav == 60){
            intAdder *= -1;
            trav = -30;
            tray++;
        }

        if(tray == 4){
            tray = 0;
            heightAdd += 60;
        }
        


        for(int z = 0; z < 3; z++){
            for(int a = 0; a < crabrow; a++){
                crabs[a][z].x += intAdder;
                crabs[a][z].y += heightAdd;
            }
        }
        heightAdd = 0;

        trav++;

        SDL_RenderPresent(renderer);
        SDL_Delay(50);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    return 0;
}