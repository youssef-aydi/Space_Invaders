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

#include "menu.h"
#include "animation.h"
#include <SDL_mixer.h>


bool Menu_load(SDL_Renderer *renderer, Menu *menu, const char *image)
{
    // Load menu image
    if(!Image_load(renderer, &menu->image, image))
    {
        return false;
    }

    return true;
}

void Menu_destroy(Menu *menu)
{
    Image_destroy(&menu->image);

}

void Menu_setX(Menu *menu, int x)
{
    // Menu x coordinate
    menu->image.rect.x = x;
}

void Menu_setY(Menu *menu, int y)
{
    // Menu y coordinate
    menu->image.rect.y = y;
}

void Menu_setCoordinates(Menu *menu, int x, int y)
{
   Menu_setX(menu, x);
   Menu_setY(menu, y);
}
void Menu_render(SDL_Renderer *renderer, Menu *menu, Animation *animation)
{
    if(animation->start==false)
    {
        // Render menu
        Image_render(renderer, &menu->image);
    }

}
