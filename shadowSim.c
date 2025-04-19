/*
clang -o shadowSim shadowSim.c -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2

(base) The_real_G@Geordies-MacBook-Air AnimatedC % ./shadowSim
*/
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

struct Circle{
    double x;
    double y;
    double r;
};
struct Shadow{
    int top;
    int bottom;
    int length;
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

int xAnglePoint(struct Circle circle1, struct Circle circle2){
    double dist = circle1.x - circle2.x;
    double hight = circle1.y - circle2.y;

    double angle = tan(hight / dist);

    double xpoint = circle2.x + ((circle2.r)*(cos(angle)));
    return (int)(xpoint);
}

int yAnglePoint(struct Circle circle1, struct Circle circle2){
    double dist = circle1.x - circle2.x;
    double hight = circle1.y - circle2.y;

    double angle = tan(hight / dist);

    double ypoint = circle2.y + ((circle2.r)*(sin(angle)));
    return (int)(ypoint);
}

void rays(struct Circle light, struct Circle shade, SDL_Renderer* renderer, struct Shadow area){
    int yangle = yAnglePoint(light, shade);
    int xangle = xAnglePoint(light, shade);
    // center line
    int botFract = light.x - shade.x;
    int topFract = light.y - shade.y;
    double interval = ((double) topFract/(double) botFract);
    double y = light.y;

    // top line
    int lTop = (light.y-light.r);
    int topspec = (light.y - light.r) - (shade.y-shade.r);
    double intervalsp = ((double) topspec /(double) botFract);
    double topY = lTop;

    //bottom line
    int lBot = (light.y + light.r);
    int botspec = (light.y + light.r) - (shade.y + shade.r);
    double intervalbt = ((double) botspec /(double) botFract);
    double botY = lBot;

    for(int x = light.x; x <= WIDTH; x+= 1){
        SDL_RenderDrawPoint(renderer, x, (int)y);
        SDL_RenderDrawPoint(renderer, x, (int)topY );
        SDL_RenderDrawPoint(renderer, x, (int)botY );
        
        if(x > shade.x){
            for(int ycheck = 0; ycheck < HEIGHT; ycheck++){
                if(ycheck < botY && ycheck > topY){
                    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                    SDL_RenderDrawPoint(renderer, x, ycheck);
                }
            }
        }

        y += interval;
        topY += intervalsp;
        botY += intervalbt;
    }
    
}

void fillShade (SDL_Renderer* renderer){
    
}

int main() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Shadow", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
    SDL_RaiseWindow(window);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // RGB: black
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // Present the renderer (display the drawing)
    struct Circle circle1 = {200,200,70};
    struct Circle circle2 = {600,200,120};
    struct Shadow shadow;









    

    SDL_Event event;
    bool quit = false;
    while (!quit) { 
        // Poll for events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true; // Close the window when the user clicks the close button
            }
            if (event.type == SDL_MOUSEMOTION && event.motion.state != 0) {
                circle1.x = event.motion.x;
                circle1.y = event.motion.y;
            }
            
        }
    // clears screen to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // RGB: black
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


    FillCircle(renderer, circle1);
    
    
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    rays(circle1, circle2, renderer, shadow);



    SDL_SetRenderDrawColor(renderer, 255, 255, 225, 255);
    FillCircle(renderer, circle2);

    SDL_RenderPresent(renderer);
    SDL_Delay(10);
    }















    // Clean up and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
