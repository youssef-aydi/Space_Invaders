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

#include "victory.h"
#include "animation.h"
#include <SDL_mixer.h>


bool Victory_load(SDL_Renderer *renderer, Victory *victory, const char *image)
{
    // Load victory image
    if(!Image_load(renderer, &victory->image, image))
    {
        return false;
    }

    victory->shown = false;

    return true;
}

void Victory_destroy(Victory *victory)
{
    Image_destroy(&victory->image);

}

void Victory_setX(Victory *victory, int x)
{
    // Victory x coordinate
    victory->image.rect.x = x;
}

void Victory_setY(Victory *victory, int y)
{
    // Victory y coordinate
    victory->image.rect.y = y;
}

void Victory_setCoordinates(Victory *victory, int x, int y)
{
   Victory_setX(victory, x);
   Victory_setY(victory, y);
}
void Victory_render(SDL_Renderer *renderer, Victory *victory)
{
    if(victory->shown)
    {
        // Render victory
        Image_render(renderer, &victory->image);
        Mix_HaltChannel(5);
    }

}
