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

#ifndef PLANE_H
#define PLANE_H
#define ULTIMATE_RANGE   75  //Ultimate Difficulty: SMALLER---->HARDER

#include "utils.h"
#include "image.h"
#include "defeat.h"
#include "ultimate.h"
#include <SDL_mixer.h>

struct Plane
{
    // Plane
    Image image;

    // Direction
    Direction direction;

    // Speed in pixel/second
    int speed;

    // Margin
    int margin;

    int score;

    int hp;

    int planecounter;

    bool destroyed;




};
typedef struct Plane Plane;


bool Plane_load(SDL_Renderer *renderer, Plane *plane, const char *image);
void Plane_destroy(Plane *plane);

void Plane_setX(Plane *plane, int x);
void Plane_setY(Plane *plane, int y);
void Plane_AI(Plane *plane, Defeat *defeat);
void Plane_setCoordinates(Plane *plane, int x, int y);

void Plane_moveX(Plane *plane, int x);

void Plane_move(Plane *plane, Ultimate *ultimate, Defeat *defeat, int screenWidth, int framerate, Animation *animation);

void Plane_setDirection(Plane *plane, SDL_Keycode keycode);
void Plane_unsetDirection(Plane *plane, SDL_Keycode keycode);

void Plane_render(SDL_Renderer *renderer, Plane *plane);

#endif // PLANE_H
