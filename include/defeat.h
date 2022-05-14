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

#ifndef DEFEAT_H
#define DEFEAT_H
#include <SDL_mixer.h>
#include "utils.h"
#include "image.h"
typedef struct Animation Animation;

struct Defeat
{
    // Defeat
    Image image;

    // Direction
    Direction direction;

    // Speed in pixel/second
    int speed;

    // Margin
    int margin;

    bool shown;

    Mix_Chunk *planedeathsound;

};
typedef struct Defeat Defeat;


bool Defeat_load(SDL_Renderer *renderer, Defeat *defeat, const char *image);
void Defeat_destroy(Defeat *defeat);
void Defeat_setX(Defeat *defeat, int x);
void Defeat_setY(Defeat *defeat, int y);
void Defeat_setCoordinates(Defeat *defeat, int x, int y);
void Defeat_render(SDL_Renderer *renderer, Defeat *defeat);

#endif // Defeat_H
