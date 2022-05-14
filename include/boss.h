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

#ifndef BOSS_H
#define BOSS_H

#include "utils.h"
#include "image.h"
#include "plane.h"
#include "victory.h"
#include "bullet.h"
#include "bullet2.h"
#include "bossattack.h"
#include <SDL_mixer.h>

struct Boss
{
    // Boss
    Image image;

    // Direction
    Direction direction;

    // Speed in pixel/second
    int speed;

    // Margin
    int margin;

    bool destroyed ;

    bool shown;

    bool aggro;

    Mix_Chunk *bossappear;

    int hp;

    bool stage;

};
typedef struct Boss Boss;


bool Boss_load(SDL_Renderer *renderer, Boss *boss, const char *image);
void Boss_destroy(Boss *boss);

void Boss_setX(Boss *boss, int x);
void Boss_setY(Boss *boss, int y);
void Boss_AI(Boss *boss, Bullet *bullet, Plane *plane, Bossattack *bossattack, Victory *victory, Defeat *defeat, Ultimate *ultimate);
void Boss_AI2(Boss *boss, Bullet2 *bullet2, Plane *plane);
void Boss_setCoordinates(Boss *boss, int x, int y);
void Boss_moveX(Boss *boss, int x);
void Ultimate_followDirection(Ultimate *ultimate, Boss *boss, Plane *plane);
void Boss_followDirection(Boss *boss, Plane *plane);
void Boss_moveY(Boss *boss, int y);
void Boss_render(SDL_Renderer *renderer, Boss *boss);
void Boss_move(Boss *boss, int screenWidth, int framerate, Plane *plane);

#endif // BOSS_H
