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

#ifndef bossattack_H
#define bossattack_H
#define ULTIMATE_COOLDOWN 100 // Ultimate Difficulty: SMALLER---->FASTER
#define HEART_NUM 5

#include "utils.h"
#include "image.h"
#include "plane.h"
#include "ultimate.h"
#include "victory.h"
#include "heart.h"

typedef struct Animation Animation;

struct Bossattack
{
    // Bossattack
    Image image;

    // Direction
    Direction direction;

    // Speed in pixel/second
    int speed;

    // Margin
    int margin;

    bool shown;

    int counter;

    int fix;



};
typedef struct Bossattack Bossattack;


bool Bossattack_load(SDL_Renderer *renderer, Bossattack *bossattack, const char *image);
void Bossattack_destroy(Bossattack *bossattack);

void Bossattack_setX(Bossattack *bossattack, int x);
void Bossattack_setY(Bossattack *bossattack, int y);
void Bossattack_setCoordinates(Bossattack *bossattack, int x, int y);
void Bossattack_limits(Bossattack *bossattack, Plane *plane, int x1, int x2, int x3, Ultimate *ultimate, Victory *victory, Defeat *defeat);
void Bossattack_moveY(Bossattack*bossattack, int y);

void Bossattack_move(Bossattack *bossattack, Plane *plane, int framerate, Animation *animation);
void Ultimate_enable(Bossattack *bossattack, Ultimate *ultimate);
void Ultimate_disable(Bossattack *bossattack, Ultimate *ultimate, Plane *plane);
void Ultimate_relationship(Bossattack *bossattack, Ultimate *ultimate, Plane *plane, Victory *victory, Defeat *defeat);
void Bossattack_render(SDL_Renderer *renderer, Bossattack *bossattack);


#endif // bossattack_H
