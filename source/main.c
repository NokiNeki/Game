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
  Texture2D spriteSheet = LoadTexture("./Resources/sprite.png");

  Player player;
  player.pos =                  (Vector2){0, 0};
  player.direction =            (Vector2){0, 0};
  player.accelerator =          1;
  player.deaccelerator =        3;
  player.maxSpeed =             8;
  player.accelerator_counter =  0;
  player.textureSize =          (Vector2){16,16};
  player.scale =                SCALE;
  player.momentum =             (Vector2){0, 0};
  player.start = (Vector2){(SCREEN_WIDTH/2)-((player.textureSize.x*player.scale)/2),(SCREEN_HEIGHT/2)-((player.textureSize.y*player.scale)/2)};
  player.origin = (Vector2){player.pos.x-SCREEN_WIDTH/2, player.pos.y-SCREEN_HEIGHT/2};

  player.textureL = textureFromSpriteSheet(spriteSheet, player.scale, (Rectangle){16,16*0, 16,16});
  player.textureR = textureFromSpriteSheet(spriteSheet, player.scale, (Rectangle){0,16*0, 16,16});
  player.texture =  player.textureR;

  player.hatL = textureFromSpriteSheet(spriteSheet, player.scale, (Rectangle){16,16*1, 16,16});
  player.hatPosL = (Vector2){15,-30};
  player.hatR = textureFromSpriteSheet(spriteSheet, player.scale, (Rectangle){0,16*1, 16,16});
  player.hatPosR = (Vector2){-15,-30};
  player.hat = player.hatR;
  player.hatPos = player.hatPosR;

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
  hud.hotbarSize =      7;
  hud.hotbarBox =       textureFromSpriteSheet(hudSheet, hud.hotbarScale, (Rectangle){16,16, 16,16});
  hud.hotbarSelection = textureFromSpriteSheet(hudSheet, hud.hotbarScale, (Rectangle){0,16, 16,16});
  hud.selectedHotbar = hud.hotbarSize/2;

  Chunk chunk;
  chunk.scale = SCALE;
  chunk.pos =   (Vector2){0,0};
  {
    Texture2D c = textureFromSpriteSheet(blockSheet, chunk.scale, (Rectangle){16,0, 16,16});
    Texture2D d = textureFromSpriteSheet(blockSheet, chunk.scale, (Rectangle){16,16, 16,16});
    for (int i = 0; i < CHUNK_HEIGHT; i++) {
      for (int j = 0; j < CHUNK_WIDTH; j++) {
        if ((i == 0 || i == CHUNK_HEIGHT-1) || (j == 0 || j == CHUNK_WIDTH-1)) {
          chunk.blocks[i][j].texture = d;
          chunk.blocks[i][j].id = (BlockID)WALL;
        } else {
          chunk.blocks[i][j].texture = c;
          chunk.blocks[i][j].id = (BlockID)BACKGROUND;
        }
        chunk.blocks[i][j].pos = (Vector2){16*j*chunk.scale, 16*i*chunk.scale};
      }
    }
    chunk.blocks[7][CHUNK_WIDTH-1].id = 1;
    chunk.blocks[7][CHUNK_WIDTH-1].texture = c;
    chunk.blocks[6][CHUNK_WIDTH-1].id = 1;
    chunk.blocks[6][CHUNK_WIDTH-1].texture = c;
  }

  Chunk chunk2 = chunk;
  chunk2.pos = (Vector2){CHUNK_WIDTH*16*chunk2.scale, 0};
  chunk2.chunkLeft = &chunk;

  player.currentChunk = &chunk;

  int heartCounter = 0; // TESTING!!!!

  // Game Loop: ---------------------------------------------------------------------------------------------------------------------------
  while (!WindowShouldClose()) {

    player.origin = (Vector2){player.pos.x+SCREEN_WIDTH/2, player.pos.y+SCREEN_HEIGHT/2};
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

    playerCollision(player);

    BeginDrawing();

      ClearBackground(RAYWHITE);

      drawChunk(chunk, player.pos);
      drawChunk(chunk2, player.pos);
      DrawTexture(player.texture, player.start.x, player.start.y, RAYWHITE);
      DrawTexture(player.hat, player.start.x+player.hatPos.x, player.start.y+player.hatPos.y, RAYWHITE);
      drawHealth(&hud);
      drawHotbar(&hud);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
