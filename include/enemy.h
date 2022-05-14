/*
 * Copyright (c) 2018 Amine Ben Hassouna <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef ENEMY_H
#define ENEMY_H
#include "utils.h"
#include "image.h"

typedef struct Animation Animation;
struct Enemy
{
    // Enemy
    Image image;

    // Direction
    Direction direction;

    // Speed in pixel/second
    int speed;

    // Margin
    int margin;

    bool destroyed;

    int initialx;
    int initialy;
    int addery;


};
typedef struct Enemy Enemy;


bool Enemy_load(SDL_Renderer *renderer, Enemy *enemy, const char *image);
void Enemy_destroy(Enemy *enemy);

void Enemy_setX(Enemy *enemy, int x);
void Enemy_setY(Enemy *enemy, int y);
void Enemy_setCoordinates(Enemy *enemy, int x, int y);
void Enemy_roaming(Enemy *enemy);
void Enemy_moveX(Enemy *enemy, int x);
void Enemy_move(Enemy *enemy, int framerate);
//void Enemy_respawn(Enemy *enemy, Animation *animation);
void Enemy_render(SDL_Renderer *renderer, Enemy *enemy);

#endif // ENEMY_H
