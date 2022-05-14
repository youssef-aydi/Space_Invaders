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

#include "plane.h"
#include "animation.h"

bool Plane_load(SDL_Renderer *renderer, Plane *plane, const char *image)
{
    // Load plane image
    if(!Image_load(renderer, &plane->image, image))
    {
        return false;
    }

    plane->destroyed=false;
    plane->planecounter=-1;

    return true;
}

void Plane_destroy(Plane *plane)
{
    Image_destroy(&plane->image);
}

void Plane_setX(Plane *plane, int x)
{
    // Plane x coordinate
    plane->image.rect.x = x;


}

void Plane_setY(Plane *plane, int y)
{
    // Plane y coordinate
    plane->image.rect.y = y;


}

void Plane_AI(Plane *plane, Defeat *defeat)
{
    if(plane->hp==0)
    {
       plane->destroyed=true;
       defeat->shown=true;

    }
}

void Plane_setCoordinates(Plane *plane, int x, int y)
{
    Plane_setX(plane, x);
    Plane_setY(plane, y);
}

void Plane_moveX(Plane *plane, int x)
{
    Plane_setX(plane, plane->image.rect.x + x);
}

void Plane_setDirection(Plane *plane, SDL_Keycode keycode)
{
    switch (keycode)
    {

    case SDLK_RIGHT:
        plane->direction &= ~SDLK_LEFT;
        plane->direction |= DIRECTION_RIGHT;
        break;

    case SDLK_LEFT:
        plane->direction &= ~DIRECTION_RIGHT;
        plane->direction |= DIRECTION_LEFT;
        break;
    }
}

void Plane_unsetDirection(Plane *plane, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_RIGHT:
        plane->direction &= ~DIRECTION_RIGHT;
        break;

    case SDLK_LEFT:
        plane->direction &= ~DIRECTION_LEFT;
        break;
    }
}

void Plane_render(SDL_Renderer *renderer, Plane *plane)
{

    if(plane->destroyed==false)
    {
        // Render plane
    Image_render(renderer, &plane->image);
    }
}

void Plane_move(Plane *plane, Ultimate *ultimate, Defeat *defeat, int screenWidth, int framerate, Animation *animation)
{
    int planeStep = plane->speed / framerate;

    if(ultimate->shown==true)
    {
        for(int i=0; i<2; i++)
        {
        int plane_left_side = plane->image.rect.x;
        int plane_right_side = plane->image.rect.x + plane->image.rect.w;
        int ultimate_left_side = ultimate->image[i].rect.x + ULTIMATE_RANGE;
        int ultimate_right_side = ultimate->image[i].rect.x + ultimate->image[i].rect.w - ULTIMATE_RANGE;
        if((plane_right_side >= ultimate_left_side)&&(plane_left_side <= ultimate_right_side))
        {
            plane->hp=0;
            defeat->shown=true;
            for (int j=0 ; j<HEART_NUM  ;j++)
        {
            animation->heart[j].destroyed= true;
        }
        }


    }
    }
    if( (plane->direction & DIRECTION_RIGHT)
            && plane->image.rect.x + plane->image.rect.w + planeStep <= screenWidth - plane->margin)
    {
        Plane_moveX(plane, planeStep);
    }
    else if( (plane->direction & DIRECTION_LEFT)
             && plane->image.rect.x - planeStep >= plane->margin)
    {
        Plane_moveX(plane, -planeStep);
    }

}
