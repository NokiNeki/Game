#include <stdio.h>
#include "sprite.h"
#include "world.h"
#include "items.h"
#include "hud.h"
#include "raylib.h"

#define SCALE 3

int main() {

  const int screenWidth = 960;
  const int screenHeight = 640;

  InitWindow(screenWidth, screenHeight, "Game");
  SetTargetFPS(30);
  SetExitKey(0);


  Texture2D itemSheet = LoadTexture("./Resources/items.png");
  Texture2D blockSheet = LoadTexture("./Resources/blocks.png");
  Texture2D hudSheet = LoadTexture("./Resources/hud.png");

  Player player;
  player.pos =                  (Vector2){0, 0};
  player.direction =            0;
  player.accelerator =          1;
  player.deaccelerator =        3;
  player.maxSpeed =             8;
  player.accelerator_counter =  0;
  player.textureSize =          (Vector2){16,16};
  player.scale =                SCALE;
  player.momentum =             (Vector2){0, 0};

  player.textureL = textureFromSpriteSheet(itemSheet, player.scale, (Rectangle){16,16*2, 16,16});
  player.textureR = textureFromSpriteSheet(itemSheet, player.scale, (Rectangle){0,16*2, 16,16});
  player.texture =  player.textureR;


  Heart heart;
  heart.status = 0;
  heart.scale = SCALE;
  {
    for (int i = 0; i < 5; i++) {
      heart.texture[i] = textureFromSpriteSheet(itemSheet, heart.scale, (Rectangle){16*i,16*1, 16,16});
    }
  }
  heart.currentHeart = heart.texture[heart.status];

  Hud hud;
  hud.hotbarScale =     SCALE;
  hud.health =          heart;
  hud.hotbarSize =      5;
  hud.hotbarBox =       textureFromSpriteSheet(hudSheet, hud.hotbarScale, (Rectangle){16,16, 16,16});
  hud.hotbarSelection = textureFromSpriteSheet(hudSheet, hud.hotbarScale, (Rectangle){0,16, 16,16});

  Chunk chunk;
  chunk.scale = SCALE;
  chunk.pos =   (Vector2){0,0};
  {
    Texture2D c = textureFromSpriteSheet(blockSheet, chunk.scale, (Rectangle){16,0, 16,16});
    for (int i = 0; i < CHUNK_HEIGHT; i++) {
      for (int j = 0; j < CHUNK_WIDTH; j++) {
        chunk.blocks[i][j].texture = c;
        chunk.blocks[i][j].pos = (Vector2){16*j*chunk.scale, 16*i*chunk.scale};
      }
    }
  }

  Chunk chunk2 = chunk;
  chunk2.pos = (Vector2){CHUNK_WIDTH*16*chunk2.scale, 0};
  chunk2.chunkLeft = &chunk;

  int heartCounter = 0; // TESTING!!!!

  // Game Loop: ---------------------------------------------------------------------------------------------------------------------------
  while (!WindowShouldClose()) {

    playerMove(&player, player.maxSpeed, 20);
    selectHotbar(&hud);

    {
      heartCounter++;
      if (heartCounter > 10) {
        hud.health.status++;
        heartCounter = 0;
      }
      if (hud.health.status > 4) {
        hud.health.status = 0;
      }
      hud.health.currentHeart = hud.health.texture[hud.health.status];
    }

    BeginDrawing();

      ClearBackground(RAYWHITE);

      drawChunk(chunk, player.pos);
      drawChunk(chunk2, player.pos);
      DrawTexture(player.texture, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, RAYWHITE);
      drawHealth(&hud);
      drawHotbar(&hud);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
