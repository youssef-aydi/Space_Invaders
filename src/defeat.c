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

#include "defeat.h"
#include "animation.h"
#include <SDL_mixer.h>


bool Defeat_load(SDL_Renderer *renderer, Defeat *defeat, const char *image)
{
    // Load defeat image
    if(!Image_load(renderer, &defeat->image, image))
    {
        return false;
    }

    defeat->shown = false;

    return true;
}

void Defeat_destroy(Defeat *defeat)
{
    Image_destroy(&defeat->image);

}

void Defeat_setX(Defeat *defeat, int x)
{
    // Defeat x coordinate
    defeat->image.rect.x = x;
}

void Defeat_setY(Defeat *defeat, int y)
{
    // Defeat y coordinate
    defeat->image.rect.y = y;
}

void Defeat_setCoordinates(Defeat *defeat, int x, int y)
{
   Defeat_setX(defeat, x);
   Defeat_setY(defeat, y);
}
void Defeat_render(SDL_Renderer *renderer, Defeat *defeat)
{
    if(defeat->shown)
    {
        // Render defeat
        Image_render(renderer, &defeat->image);
        Mix_HaltChannel(5);
    }

}
