# Games-in_C

**About:** This is a project group of games I made in C using the SDL library in order to play these games you must first install SDL2/SDL via homebrew. These games are classic old games so the controls should be self explainitory and either use the arrow keys or the S and W for the pong game. Enjoy.



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
