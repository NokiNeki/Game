#include "sprite.h"
#include "hud.h"
#include "items.h"
#include "raylib.h"

void drawHealth(Hud *hud) {
  int screenWidth = GetScreenWidth();

  DrawTexture(hud->health.currentHeart, screenWidth-(16*hud->health.scale)-20, 20, RAYWHITE);
}

void drawHotbar(Hud *hud) {
  int screenWidth = GetScreenWidth();
  int screenHeight = GetScreenHeight();
  int startpoint = (screenWidth/2) - ((hud->hotbarSize*16*(hud->hotbarScale))/2);

  int selected = hud->selectedHotbar;

  for (int i = 0; i < hud->hotbarSize; i++) {
    DrawTexture(
      i != selected ? hud->hotbarBox : hud->hotbarSelection, 
      startpoint+(i*16*(hud->hotbarScale)), 
      screenHeight-60, RAYWHITE
    );
  }
}

void selectHotbar(Hud *hud) {
  float mouseScroll = GetMouseWheelMove();

  hud->selectedHotbar += mouseScroll;
  hud->selectedHotbar = hud->selectedHotbar < 0 ? 0 : hud->selectedHotbar;
  hud->selectedHotbar = hud->selectedHotbar > hud->hotbarSize-1 ? hud->hotbarSize-1 : hud->selectedHotbar;
}