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

#include "bossattack.h"
#include "animation.h"

bool Bossattack_load(SDL_Renderer *renderer, Bossattack *bossattack, const char *image)
{
    // Load bossattack image
    if(!Image_load(renderer, &bossattack->image, image))
    {
        return false;
    }
    bossattack->shown = false;

    return true;
}

void Bossattack_destroy(Bossattack *bossattack)
{
    Image_destroy(&bossattack->image);

}

void Bossattack_setX(Bossattack *bossattack, int x)
{
    // bossattack x coordinate
    bossattack->image.rect.x = x;
}

void Bossattack_setY(Bossattack *bossattack, int y)
{
    // bossattack y coordinate

    bossattack->image.rect.y = y;
}


void Bossattack_setCoordinates(Bossattack *bossattack, int x, int y)
{
   Bossattack_setX(bossattack, x);
   Bossattack_setY(bossattack, y);
}
void Bossattack_limits(Bossattack *bossattack, Plane *plane, int x1, int x2, int x3, Ultimate *ultimate, Victory *victory, Defeat *defeat)
{
    int bossattack_bottom = bossattack->image.rect.y + bossattack->image.rect.h;
    int plane_bottom = plane->image.rect.y + plane->image.rect.h;
    int boss_left_side = x1-20;
    int boss_right_side = x2-20;
    int plane_real_time_x =plane->image.rect.x+(plane->image.rect.w/2);
    if((bossattack_bottom > (plane_bottom+200)) && (boss_left_side <= plane_real_time_x) && (boss_right_side>=plane_real_time_x))
        {
           if(ultimate->shown==false)
           {
           Bossattack_setCoordinates(bossattack,plane_real_time_x, x3);
           }
           bossattack->counter++;
           Ultimate_relationship(bossattack, ultimate, plane, victory, defeat);


        }
}
void Bossattack_moveY(Bossattack *bossattack, int y)
{
    Bossattack_setY(bossattack, bossattack->image.rect.y + y);
}

void Ultimate_enable(Bossattack *bossattack, Ultimate *ultimate)
{
    if(ultimate->shown==false)
    {
    if(bossattack->counter == 5)
    {
       Mix_PlayChannel(5,ultimate->ultimatesound,0);
       Bossattack_setX(bossattack,5000);
       bossattack->shown=false;
       ultimate->shown=true;
    }
    }

}
void Ultimate_disable(Bossattack *bossattack, Ultimate *ultimate, Plane *plane)
{
    if(ultimate->shown==true)
    {
    if(bossattack->counter == ULTIMATE_COOLDOWN)
    {
        Mix_HaltChannel(5);
        ultimate->shown=false;
        bossattack->shown=true;
        Bossattack_setX(bossattack,plane->image.rect.x+(plane->image.rect.w/2));
        bossattack->counter=-1;
    }
    }
}
void Ultimate_relationship(Bossattack *bossattack, Ultimate *ultimate, Plane *plane, Victory *victory, Defeat *defeat)
{
    if((victory->shown==false)&&(defeat->shown==false))
    {
    Ultimate_enable(bossattack,ultimate);
    Ultimate_disable(bossattack,ultimate,plane);
    }
}

void Bossattack_render(SDL_Renderer *renderer, Bossattack *bossattack)
{
if (bossattack->shown)
    {
    // Render Bossattack
    Image_render(renderer, &bossattack->image);
    }

}



void Bossattack_move(Bossattack *bossattack, Plane *plane, int framerate, Animation *animation)
{
    int bossattackStep = bossattack->speed / framerate;

    if( (bossattack->direction & DIRECTION_UP))
    {
        Bossattack_moveY(bossattack, -bossattackStep);

    }

    else if( (bossattack->direction & DIRECTION_DOWN))
    {
        Bossattack_moveY(bossattack, bossattackStep);
        int bossattack_left_side = bossattack->image.rect.x;
        int bossattack_right_side = bossattack->image.rect.x + bossattack->image.rect.w;
        int plane_left_side = plane->image.rect.x;
        int plane_right_side = plane->image.rect.x + plane->image.rect.w;
        int bossattack_bottom = bossattack->image.rect.y + bossattack->image.rect.h;
        int plane_top = plane->image.rect.y;
        int plane_bottom = plane->image.rect.y + plane->image.rect.h;

             if( (bossattack_left_side  >= plane_left_side) && (bossattack_right_side  <= plane_right_side)

            && (bossattack_bottom  >= plane_top) && (bossattack_bottom <= plane_bottom ))
             {
                 plane->hp=plane->hp-1;
                 bossattack->shown = false;
                 Bossattack_setX(bossattack,20000);
                 plane->planecounter++;
                 for (int i=0 ; i<HEART_NUM  ;i++)
                 {
                       if(plane->planecounter == i)
                       {
                           animation->heart[i].destroyed=true;
                       }

                 }





             }

    }

}
