#include "sprite.h"
#include "raylib.h"
#include "items.h"

Texture2D textureFromSpriteSheet(Texture2D spriteSheet, int scale, Rectangle pos){
  Image sprite = LoadImageFromTexture(spriteSheet);
  ImageCrop(&sprite, pos);
  ImageResizeNN(&sprite, pos.width*scale, pos.height*scale);
  return LoadTextureFromImage(sprite);
}

void playerMove(struct Player *player, int moveSpeed, int interval) {
  player->accelerator_counter += 1;

  if (player->accelerator_counter >= interval) {

    // Up and Down ------------------------------------------------------------
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_S)) {

      if (IsKeyDown(KEY_S)) {
        player->momentum.y += player->accelerator;
      }
      if (IsKeyDown(KEY_W)) {
        player->momentum.y -= player->accelerator;
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
      }
      if (IsKeyDown(KEY_A)) {
        player->momentum.x -= player->accelerator;
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

  player->pos.x += player->momentum.x;
  player->pos.y += player->momentum.y;

  // Sprite Direction ---------------------------------------------------------
  if (player->momentum.x < 0) {
    player->direction = 0;
    player->texture = player->textureL;
    player->hat = player->hatL;
    player->hatPos = player->hatPosL;
  }
  else if (player->momentum.x > 0) {
    player->direction = 1;
    player->texture = player->textureR;
    player->hat = player->hatR;
    player->hatPos = player->hatPosR;
  }
}
