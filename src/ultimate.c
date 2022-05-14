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

#include "ultimate.h"
#include <SDL_mixer.h>
#include "animation.h"
#include "bossattack.h"


bool Ultimate_load(SDL_Renderer *renderer, Ultimate *ultimate, const char *image1, const char *image2)
{
    // Load ultimate image
   for(int i=0; i<2; i++)
{
       if(i==0)
       {
           if(!Image_load(renderer, &ultimate->image[i], image1))
       {
           return false;
       }
       }
       if(i==1)
       {
           if(!Image_load(renderer, &ultimate->image[i], image2))
       {
           return false;
       }
       }


}
   ultimate->shown=false;
   ultimate->image1=true;
   ultimate->image2=false;
   ultimate->succ=0;

   return true;
}

void Ultimate_destroy(Ultimate *ultimate)
{
    for(int i=0; i<2; i++)
    {
    Image_destroy(&ultimate->image[i]);
    }
}

void Ultimate_setX(Ultimate *ultimate, int x)
{
    // Ultimate x coordinate
    for(int i=0; i<2; i++)
    {
        ultimate->image[i].rect.x = x;
    }


}

void Ultimate_setY(Ultimate *ultimate, int y)
{
    // Ultimate y coordinate
    for(int i=0; i<2; i++)
    ultimate->image[i].rect.y = y;
}

void Ultimate_setCoordinates(Ultimate *ultimate, int x, int y)
{
   Ultimate_setX(ultimate, x);
   Ultimate_setY(ultimate, y);

}



void Ultimate_render(SDL_Renderer *renderer, Ultimate *ultimate)
{
    if(ultimate->shown)
    {
        ultimate->succ++;
        if(/*ultimate->image1==true && ultimate->image2==false &&*/ ultimate->succ < 11)
        {
        Image_render(renderer, &ultimate->image[0]);
        ultimate->image1=false;
        ultimate->image2=true;

        }
        else
        {
//            if(ultimate->image1==false && ultimate->image2==true)
//            {
            Image_render(renderer, &ultimate->image[1]);

            ultimate->image1=true;
            ultimate->image2=false;

//            }

        }
        if (ultimate->succ>20)
        {
            ultimate->succ=0;
        }

}
}

void Ultimate_moveX(Ultimate *ultimate, int x)
{
    for (int i=0; i<2; i++)
    {
    Ultimate_setX(ultimate, ultimate->image[i].rect.x + x);
    }

}

void Ultimate_moveY(Ultimate *ultimate, int y)
{
    for (int i=0; i<2; i++)
    {
    Ultimate_setY(ultimate, ultimate->image[i].rect.y + y);
    }
}

void Ultimate_move(Ultimate *ultimate, Boss *boss/*, int screenWidth*/, int framerate)
{
    if(ultimate->shown==true)
    {
    int ultimateStep = ultimate->speed / framerate;
    int bossStep = boss->speed / framerate;

    for(int i=0; i<2; i++)
    {
    if( (ultimate->direction & DIRECTION_RIGHT)
            && boss->image.rect.x + boss->image.rect.w + bossStep <= 0 )
    {
        Ultimate_moveX(ultimate, ultimateStep);
    }

    else if( (ultimate->direction & DIRECTION_LEFT)
             && boss->image.rect.x - bossStep >= 0)
    {
        Ultimate_moveX(ultimate, -ultimateStep);
    }
    }
}
}
