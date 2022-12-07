#ifndef _ITEMS_H_
#define _ITEMS_H_

#include "raylib.h"

struct Item {
    int id;
    double hp;
    Texture2D texture;
};
typedef struct Item Item;

#endif