#include "sprite.h"
#include "raylib.h"
#include "items.h"
#include "world.h"

#include <stdio.h>

Texture2D textureFromSpriteSheet(Texture2D spriteSheet, int scale, Rectangle pos){
  Image sprite = LoadImageFromTexture(spriteSheet);
  ImageCrop(&sprite, pos);
  ImageResizeNN(&sprite, pos.width*scale, pos.height*scale);
  return LoadTextureFromImage(sprite);
}

void changeChunk(Player *player) {
  // Moving right
  if (player->origin.x > player->currentChunk->pos.x+(CHUNK_WIDTH*16* player->scale)) {
    player->currentChunk = player->currentChunk->chunkRight;
  }

  // Moving left
  if (player->origin.x < player->currentChunk->pos.x) {
    player->currentChunk = player->currentChunk->chunkLeft;
  }
}

// Fix moving along the wall
Vector2 playerCollision(Player *player) {
  int xpos = (player->origin.x - player->currentChunk->pos.x) / (16*player->scale);
  int ypos = (player->origin.y - player->currentChunk->pos.y) / (16*player->scale); 
  int newx = ((player->origin.x - player->currentChunk->pos.x) + (player->momentum.x)) / (16*player->scale);
  int newy = ((player->origin.y - player->currentChunk->pos.y) + (player->momentum.y)) / (16*player->scale);

  Chunk chunkCheck = (*player->currentChunk);
  int subtraction = 0;

  // If player goes to the right of the chunk
  if (player->origin.x + (player->momentum.x) > player->currentChunk->pos.x+(CHUNK_WIDTH*16* player->scale)) {
    chunkCheck = *player->currentChunk->chunkRight;
    newx -= CHUNK_WIDTH;
    xpos -= CHUNK_WIDTH;
  }
  // If the player goes to the left of the chunk
  if (player->origin.x + (player->momentum.x) < player->currentChunk->pos.x) {
    chunkCheck = *player->currentChunk->chunkLeft;
    newx -= CHUNK_WIDTH;
    xpos -= CHUNK_WIDTH;
  }

  Vector2 colideVector = (Vector2){0, 0}; // 0 = false, 1 = true
  int xtally = 0;
  int ytally = 0;
  if (newx > -1 && newx < CHUNK_WIDTH) {
    xtally = colideVector.x <= 0 ? 1 : 0;
    colideVector.x = chunkCheck.blocks[ypos][newx].id == 2 ? 1 : 0;
    colideVector.x -= xtally;
  }
  if (newy > -1 && newy < CHUNK_HEIGHT) {
    ytally = colideVector.y >= 1 ? 1 : 0;
    colideVector.y = chunkCheck.blocks[newy][xpos].id == 2 ? 1 : 0;
    colideVector.y -= ytally;
  }

  return colideVector;
}

void playerMove(struct Player *player, int moveSpeed, int interval) {
  player->accelerator_counter += 1;
  player->direction = (Vector2){0, 0};

  if (player->accelerator_counter >= interval) {

    // Up and Down ------------------------------------------------------------
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S)) {

      if (IsKeyDown(KEY_S)) {
        player->momentum.y += player->accelerator;
        player->direction.x = -1;
      }
      if (IsKeyDown(KEY_W)) {
        player->momentum.y -= player->accelerator;
        player->direction.x = 1;
      }

      if (player->momentum.y > moveSpeed) {
        player->momentum.y = moveSpeed;
      }
      if (player->momentum.y < -1*moveSpeed) {
        player->momentum.y = -1*moveSpeed;
      }

    // Stopping:
    } 
    else if (player->momentum.y > 0+player->deaccelerator) {
      player->momentum.y -= player->deaccelerator;
    } 
    else if (player->momentum.y < 0-player->deaccelerator) {
      player->momentum.y += player->deaccelerator;
    } 
    else {
      player->momentum.y = 0;
    }

    // Left and Right ---------------------------------------------------------
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D)) {

      if (IsKeyDown(KEY_D)) {
        player->momentum.x += player->accelerator;
        player->direction.y = 1;
      }
      if (IsKeyDown(KEY_A)) {
        player->momentum.x -= player->accelerator;
        player->direction.y = 1;
      }

      if (player->momentum.x > moveSpeed) {
        player->momentum.x = moveSpeed;
      }
      if (player->momentum.x < -1*moveSpeed) {
        player->momentum.x = -1*moveSpeed;
      }

    // Stopping
    } 
    else if (player->momentum.x > 0+player->deaccelerator) {
      player->momentum.x -= player->deaccelerator;
    } 
    else if (player->momentum.x < 0-player->deaccelerator) {
      player->momentum.x += player->deaccelerator;
    } 
    else {
      player->momentum.x = 0;
    }
  }

  // Apply Motion if no collision ---------------------------------------------
  if (playerCollision(player).x != 1) {
    player->pos.x += player->momentum.x;
  }
  if (playerCollision(player).y != 1) {
    player->pos.y += player->momentum.y;
  }

  // Sprite Direction ---------------------------------------------------------
  if (player->momentum.x < 0) {
    player->texture = player->textureL;
    player->hat = player->hatL;
    player->hatPos = player->hatPosL;
  }
  else if (player->momentum.x > 0) {
    player->texture = player->textureR;
    player->hat = player->hatR;
    player->hatPos = player->hatPosR;
  }
}
