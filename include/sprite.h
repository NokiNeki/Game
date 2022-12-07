/*
*   LICENSE: zlib/libpng
*
*   Game is licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software:
*
*   Copyright (c) 1000-2022 Nicholas Kovacs (@Znoki)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/


#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "raylib.h"
#include "items.h"
#include "world.h"

#define INVENTORY_SIZE 26 // First 6 are hotbar

extern Texture2D textureFromSpriteSheet(Texture2D spriteSheet, int scale, Rectangle pos);

struct Player {
  Vector2     pos;
  int         direction;
  Chunk       *currentChunk;

  int         health;
  Item        inventory[INVENTORY_SIZE];
  Item        selectedItem;

  Texture2D   texture;
  Texture2D   textureL;
  Texture2D   textureR;
  Vector2     textureSize;
  double      scale;

  int         grounded;
  Vector2     momentum;
  int         maxSpeed;
  int         accelerator;
  int         deaccelerator;
  int         accelerator_counter;
};
typedef struct Player Player;

extern void playerMove(struct Player *player, int moveSpeed, int interval);

extern void playerCollision(Player player, Chunk chunk);


struct Heart {
  Texture2D   texture[5];
  Texture2D   currentHeart;
  int         status;
  double      scale;
};
typedef struct Heart Heart;

#endif
