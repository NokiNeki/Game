#ifndef _WORLD_H_
#define _WORLD_H_

#include "raylib.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640
#define CHUNK_SIZE 16
#define CHUNK_WIDTH 20
#define CHUNK_HEIGHT 14


struct Block {
    int id;
    Texture2D texture;
    Vector2 pos;
    Rectangle size;
};
typedef struct Block Block;

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};
typedef enum Direction Direction;

struct Chunk {
    Block blocks[CHUNK_HEIGHT][60];
    Vector2 pos;
    double scale;
    struct Chunk *chunkUp;
    struct Chunk *chunkRight;
    struct Chunk *chunkDown;
    struct Chunk *chunkLeft;
};
typedef struct Chunk Chunk;

struct Room {
    Vector2 pos;
    double scale;
    int size;
    Chunk chunks[];
};
typedef struct Room Room;

extern void drawRoom(Room r, Vector2 o);

extern void drawChunk(Chunk c, Vector2 o);

extern void drawBlock(Block b, Chunk c, Vector2 o);

#endif
