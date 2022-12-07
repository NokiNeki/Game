#include "raylib.h"
#include "world.h"

void drawChunk(Chunk c, Vector2 o) {
    for (int x = 0; x < CHUNK_HEIGHT; x++) {
        for (int y = 0; y < CHUNK_WIDTH; y++) {
            drawBlock(c.blocks[x][y], c, o);
        }
    }
}

void drawBlock(Block b, Chunk c, Vector2 o) {
    DrawTexture(b.texture, c.pos.x+b.pos.x-o.x, c.pos.y+b.pos.y-o.y, RAYWHITE);
}