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

#include "heart.h"

bool Heart_load(SDL_Renderer *renderer, Heart *heart, const char *image)
{
    // Load heart image
    if(!Image_load(renderer, &heart->image, image))
    {
        return false;

    }
    heart->destroyed=false;
    return true;
}

void Heart_destroy(Heart *heart)
{
    Image_destroy(&heart->image);

}

void Heart_setX(Heart *heart, int x)
{
    // Heart x coordinate
    heart->image.rect.x = x;
}

void Heart_setY(Heart *heart, int y)
{
    // Heart y coordinate
    heart->image.rect.y = y;
}

void Heart_setCoordinates(Heart *heart, int x, int y)
{
    Heart_setX(heart, x);
    Heart_setY(heart, y);
}
void Heart_render(SDL_Renderer *renderer, Heart *heart)
{
    if(heart->destroyed==false)
    {
    // Render heart
    Image_render(renderer, &heart->image);
    }
}

