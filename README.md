# Snake-in-C

notes: you need to have downloaded brew SDL2/SDL and then SDL2/SDL_ttf.h the ttf.h is for the numbers that keep track of the score in the pong game.

UP ARROW to shoot;
left and right arrow to move;

Compile on mac:
clang -o spaceInvadef spaceInvadef.c -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf

Complie on linux:
gcc -o spaceInvadef spaceInvadef.c -lSDL2 -lSDL2_ttf

Compile on Windows:
gcc -o spaceInvadef.exe spaceInvadef.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf


Run:
./spaceInvadef
