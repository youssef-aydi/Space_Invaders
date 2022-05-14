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

#ifndef VICTORY_H
#define VICTORY_H
#include <SDL_mixer.h>
#include "utils.h"
#include "image.h"
typedef struct Animation Animation;

struct Victory
{
    // Victory
    Image image;

    // Direction
    Direction direction;

    // Speed in pixel/second
    int speed;

    // Margin
    int margin;

    bool shown;

    Mix_Chunk *bossdeath;


};
typedef struct Victory Victory;


bool Victory_load(SDL_Renderer *renderer, Victory *victory, const char *image);
void Victory_destroy(Victory *victory);
void Victory_setX(Victory *victory, int x);
void Victory_setY(Victory *victory, int y);
void Victory_setCoordinates(Victory *victory, int x, int y);
void Victory_render(SDL_Renderer *renderer, Victory *victory);

#endif // Victory_H
