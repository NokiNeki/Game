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

bool playerCollision(Player player) {
  int xpos = player.origin.x / (16*player.scale);
  int ypos = player.origin.y / (16*player.scale); 
  // printf("Block ID: %d\n", player.currentChunk->blocks[ypos][xpos].id);
  int newx = (player.origin.x + (player.momentum.x)) / (16*player.scale);
  int newy = (player.origin.y + (player.momentum.y)) / (16*player.scale);
  if (newx > -1 && newx < CHUNK_WIDTH && newy > -1 && newy < CHUNK_HEIGHT) {
    // printf("Block ID UPCOMING: %d\n\n", player.currentChunk->blocks[newy][newx].id);
    return player.currentChunk->blocks[newy][newx].id == 2 ? true : false;
  }
  return false;
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

  if (!playerCollision(*player)) {
    player->pos.x += player->momentum.x;
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
