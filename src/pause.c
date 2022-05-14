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

#include "pause.h"
#include "animation.h"
#include <SDL_mixer.h>
#include <time.h>
#include <windows.h>


bool Pause_load(SDL_Renderer *renderer, Pause *pause, const char *image1, const char *image2, const char *image3)
{
    // Load pause image
   for(int i=0; i<3; i++)
{
       if(i==0)
       {
           if(!Image_load(renderer, &pause->image[i], image1))
       {
           return false;
       }
       }
       if(i==1)
       {
           if(!Image_load(renderer, &pause->image[i], image2))
       {
           return false;
       }
       }
       if(i==2)
       {
           if(!Image_load(renderer, &pause->image[i], image3))
       {
           return false;
       }
       }


}
   pause->shown=false;
   pause->image1=true;
   pause->image2=false;
   pause->image3=false;

   return true;
}


void Pause_destroy(Pause *pause)
{
    for(int i=0; i<3; i++)
    {
        Image_destroy(&pause->image[i]);
    }

}

void Pause_setX(Pause *pause, int x1)
{
    // Pause x coordinate
   pause->image[0].rect.x = x1;
   pause->image[1].rect.x = x1;
   pause->image[2].rect.x = x1;



}

void Pause_setY(Pause *pause, int y1)
{
    // Pause y coordinate
    pause->image[0].rect.y = y1;
    pause->image[1].rect.y = y1;
    pause->image[2].rect.y = y1;
}

void Pause_setCoordinates(Pause *pause, int x1, int y1)
{
   Pause_setX(pause, x1);
   Pause_setY(pause, y1);
}

void Pause_render(SDL_Renderer *renderer, Pause *pause)
{
   if(pause->shown)
   {
       if(pause->image1==true && pause->image2==false && pause->image3==false)
       {
       Image_render(renderer, &pause->image[0]);
       Sleep(200);
       pause->image1=false;
       pause->image2=true;
       pause->image3=false;
       }
       else{
           if(pause->image1==false && pause->image2==true && pause->image3==false)
           {
           Image_render(renderer, &pause->image[1]);
           Sleep(200);
           pause->image1=false;
           pause->image2=false;
           pause->image3=true;
           }
           else
           {
               if(pause->image1==false && pause->image2==false && pause->image3==true)
               {
               Image_render(renderer, &pause->image[2]);
               Sleep(200);
               pause->image1=true;
               pause->image2=false;
               pause->image3=false;
               }
           }
       }
   }
}
