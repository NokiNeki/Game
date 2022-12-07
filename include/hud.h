#ifndef _HUD_H_
#define _HUD_H_

#include "items.h"
#include "sprite.h"

struct Hud {
  Texture2D hotbarBox;
  Texture2D hotbarSelection;
  int       hotbarScale;
  int       hotbarSize;
  int       selectedHotbar;
  Vector2   hotbarPos;

  Heart     health;
};
typedef struct Hud Hud;

extern void drawHealth(Hud *hud);

extern void drawHotbar(Hud *hud);
extern void selectHotbar(Hud *hud);

#endif
