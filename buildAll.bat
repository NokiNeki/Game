@ECHO off

@ECHO Deleting the lib file to make sure changes appear
del lib\libgame.a

@ECHO.
@ECHO Compile header/c files to object files for the lib
gcc -o include/sprite.o -c include/sprite.c
gcc -o include/world.o -c include/world.c
gcc -o include/hud.o -c include/hud.c

@ECHO.
@ECHO Put the object files into the lib file
ar -cvq lib/libgame.a include/*.o

@ECHO.
@ECHO Compile main file into an EXE
gcc source/main.c -o game.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm -lgame

@ECHO Done!
