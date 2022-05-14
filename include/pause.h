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

#ifndef PAUSE_H
#define PAUSE_H
#include <SDL_mixer.h>
#include "utils.h"
#include "image.h"
#include <time.h>
#include <windows.h>
typedef struct Animation Animation;

struct Pause
{
    // Pause
    Image image[3];

    // Direction
    Direction direction;

    // Speed in pixel/second
    int speed;

    // Margin
    int margin;

    bool shown;
    bool image1;
    bool image2;
    bool image3;

    Mix_Chunk *pausesound;


};
typedef struct Pause Pause;

bool Pause_load(SDL_Renderer *renderer, Pause *pause, const char *image1, const char *image2, const char *image3);
void Pause_destroy(Pause *pause);
void Pause_setX(Pause *pause, int x1);
void Pause_setY(Pause *pause, int y1);
void Pause_setCoordinates(Pause *pause, int x1, int y1);
void Pause_render(SDL_Renderer *renderer, Pause *pause);

#endif // Pause_H
