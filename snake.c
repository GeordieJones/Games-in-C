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
#define MAX_BODY_LENGTH 5000
#define STARTX 180
#define STARTY 66
#define freemode false

int squareHeight = HEIGHT / 9;
int squareWidth = WIDTH / 10;

SDL_Rect board [10][9];

struct loc{
    int x;
    int y;
};

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

struct Circle apple(int size ){
    int randy = ((rand() % 9));
    int randx = ((rand() % 10));
    struct Circle apple = {(randx * squareWidth) + 30, (randy * squareHeight) + 30,size};
    return apple;
}



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
int speed = 2;
int direction = 1;
int x = STARTX;
int y = STARTY;
int pendingDirection = 1;
int count = 0;
int c = 0;
srand(time(NULL));
struct loc places[MAX_BODY_LENGTH];
struct Circle a1 = apple(30);
struct Circle a2 = apple(30);
struct Circle a3 = apple(30);
struct Circle a4 = apple(30);
struct Circle a5 = apple(30);


SDL_Event event;
bool quit = false;

while (!quit) {
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (direction != 4) pendingDirection = 2;
                    break;
                case SDLK_LEFT:
                    if (direction != 1) pendingDirection = 3;
                    break;
                case SDLK_DOWN:
                    if (direction != 2) pendingDirection = 4;
                    break;
                case SDLK_RIGHT:
                    if (direction != 3) pendingDirection = 1;
                    break;
                default:
                    break;
            }
        }
    }

    

    bool alignedToGrid = (x % squareWidth == 0) && (y % squareHeight == 0);
    if (alignedToGrid) {
        direction = pendingDirection;
    }

    // Move based on current direction
    switch (direction) {
        case 1: x += speed; break; // right
        case 2: y -= speed; break; // up
        case 3: x -= speed; break; // left
        case 4: y += speed; break; // down
    }

    int bodyLength = count * (squareWidth / speed);
    bool bodycheck = true;

    for (int i = 1; i < bodyLength; i++) {  // start at 1 to skip head
        int index = (c - i - 1 + MAX_BODY_LENGTH) % MAX_BODY_LENGTH;
        if (x == places[index].x && y == places[index].y) {
            bodycheck = false;
            break;
        }
    }

    if(freemode){
        if (x >= WIDTH){
            x = 0;
        }
        if (x < 0){
            x = WIDTH;
        }
        if (y >= HEIGHT) {
            y = 0;
            }
        if (y < 0) {
            y = HEIGHT - squareHeight;
        }
    }
    else{
        if (x >= WIDTH){
            x = STARTX;
            y = STARTY;
            count = 0;
            direction = 1;
            pendingDirection = 1;
            SDL_Delay(1000);
        }
        if (x < 0){
            x = STARTX;
            y = STARTY;
            count = 0;
            direction = 1;
            pendingDirection = 1;
            SDL_Delay(1000);
        }
        if (y >= HEIGHT) {
            x = STARTX;
            y = STARTY;
            count = 0;
            direction = 1;
            pendingDirection = 1;
            SDL_Delay(1000);
        }
        if (y < 0) {
            x = STARTX;
            y = STARTY;
            count = 0;
            direction = 1;
            pendingDirection = 1;
            SDL_Delay(1000);
        }
        if(!bodycheck){
            x = STARTX;
            y = STARTY;
            count = 0;
            direction = 1;
            pendingDirection = 1;
            SDL_Delay(1000);
        }
    }


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_Rect head = {x, y, squareWidth, squareHeight};
    SDL_RenderFillRect(renderer, &head);

    bool a5check = ((head.x+30 == a5.x) && (head.y+30 == a5.y));
    bool a1check = ((head.x+30 == a1.x) && (head.y+30 == a1.y));
    bool a2check = ((head.x+30 == a2.x) && (head.y+30 == a2.y));
    bool a3check = ((head.x+30 == a3.x) && (head.y+30 == a3.y));
    bool a4check = ((head.x+30 == a4.x) && (head.y+30 == a4.y));

    if(a5check ||a1check ||a2check||a3check||a4check){
        count ++;
        if(a1check) a1 = apple(30);
        if(a2check) a2 = apple(30);
        if(a3check) a3 = apple(30);
        if(a4check) a4 = apple(30);
        if(a5check) a5 = apple(30);
    }



    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int r = 0; r < HEIGHT / squareHeight; r++) {
        for (int c = 0; c < WIDTH / squareWidth; c++) {
            board[c][r].x = c * squareWidth;
            board[c][r].y = r * squareHeight;
            board[c][r].w = squareWidth;
            board[c][r].h = squareHeight;
            SDL_RenderDrawRect(renderer, &board[c][r]);
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    FillCircle(renderer, a5);
    FillCircle(renderer, a1);
    FillCircle(renderer, a2);
    FillCircle(renderer, a3);
    FillCircle(renderer, a4);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    places[c % MAX_BODY_LENGTH].x = x;
    places[c % MAX_BODY_LENGTH].y = y;
    c++;


    for(int i = 0; i< bodyLength; i++){
        int index = (c - i - 1 + MAX_BODY_LENGTH) % MAX_BODY_LENGTH;
        SDL_Rect body = {places[index].x, places[index].y, squareWidth, squareHeight};
        SDL_RenderFillRect(renderer, &body);
    }


    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}



    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();



    return 0;
}