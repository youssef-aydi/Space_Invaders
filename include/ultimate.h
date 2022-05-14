/*
 * Copyright (c) 2022 Amine Ben Hassouna <amine.benhassouna@gmail.com> Youssef Aydi <youssef.aydi@medtech.tn> Aymen Hammami <hammami.aym@outlook.com> Aziz Maazouz <aziz.maazouz@medtech.tn>
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

#ifndef ULTIMATE_H
#define ULTIMATE_H
#include <SDL_mixer.h>
#include "utils.h"
#include "image.h"

typedef struct Animation Animation;
typedef struct Bossattack Bossattack;
typedef struct Boss Boss;

struct Ultimate
{
    // Ultimate
    Image image[2];

    // Direction
    Direction direction;

    // Speed in pixel/second
    int speed;

    // Margin
    int margin;

    bool shown;
    bool image1;
    bool image2;

    Mix_Chunk *ultimatesound;
    int succ;


};
typedef struct Ultimate Ultimate;


bool Ultimate_load(SDL_Renderer *renderer, Ultimate *ultimate, const char *image1, const char *image2);
void Ultimate_destroy(Ultimate *ultimate);
void Ultimate_setX(Ultimate *ultimate, int x);
void Ultimate_setY(Ultimate *ultimate, int y);
void Ultimate_setCoordinates(Ultimate *ultimate, int x, int y/*, Animation *animation*/);
void Ultimate_render(SDL_Renderer *renderer, Ultimate *ultimate);
void Ultimate_moveX(Ultimate *ultimate, int x);
void Ultimate_moveY(Ultimate *ultimate, int y);
void Ultimate_move(Ultimate *ultimate, Boss *boss/*, int screenWidth*/, int framerate);

#endif // Ultimate_H
