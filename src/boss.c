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

#include "boss.h"
#include "animation.h"
#include <SDL2_framerate.h>
#include <SDL2_gfxPrimitives.h>

bool Boss_load(SDL_Renderer *renderer, Boss *boss, const char *image)
{
    // Load boss image
    if(!Image_load(renderer, &boss->image, image))
    {
        return false;
    }

    boss->shown = false;
    boss->destroyed=false;
    boss->stage = false;
    return true;
}

void Boss_destroy(Boss *boss)
{
    Image_destroy(&boss->image);

}

void Boss_setX(Boss *boss, int x)
{
    // Boss x coordinate
    boss->image.rect.x = x;
}

void Boss_setY(Boss *boss, int y)
{
    // Boss y coordinate
    boss->image.rect.y = y;
}

void Boss_AI(Boss *boss, Bullet *bullet, Plane *plane, Bossattack *bossattack, Victory *victory, Defeat *defeat, Ultimate *ultimate)
{
    if(boss->shown==true)
    {
        int bullet_left_side = bullet->image.rect.x;
        int bullet_right_side = bullet->image.rect.x + bullet->image.rect.w;

    int bullet_top = bullet->image.rect.y;
    int boss_top = boss->image.rect.y;
    int boss_left_side = boss->image.rect.x-20;
    int boss_right_side = boss->image.rect.x + boss->image.rect.w-20;
    int boss_bottom = boss->image.rect.y + boss->image.rect.h;
    int plane_real_time_x =plane->image.rect.x+(plane->image.rect.w/2);
    if( (bullet_left_side  >= boss_left_side) && (bullet_right_side  <= boss_right_side)

   && (bullet_top  <= boss_bottom -100 && (bullet_top >= boss_top)))
    {
      boss->hp=boss->hp-1;
      plane->score=plane->score+5;
      Bullet_setCoordinates(bullet,20000,0);


    }
    if((boss_left_side <= plane_real_time_x) && (boss_right_side>=plane_real_time_x) && (boss->aggro==true))
    {
        if(ultimate->shown==false)
        {
        bossattack->shown=true;
        }
        bossattack->direction = DIRECTION_DOWN;

        if(bossattack->fix==1)
        {
            Bossattack_setCoordinates(bossattack,plane_real_time_x, boss->image.rect.y+(boss->image.rect.h/2));
            bossattack->fix++;

        }


    }
    if(boss->hp==0)
    {
     plane->score=plane->score+495;
     plane->score=plane->score + (plane->hp*5);
     boss->destroyed=true;
     Bullet_setCoordinates(bullet,20000,0);
     Boss_setX(boss,30000);
     Mix_FreeChunk(boss->bossappear);
     Mix_FreeChunk(defeat->planedeathsound);
     Mix_PlayChannel(-1,victory->bossdeath,0);
     victory->shown=true;
     plane->destroyed=true;
     bossattack->shown=false;
    }
    if(defeat->shown==true)
    {
        boss->shown=false;
        ultimate->shown=false;
        bossattack->shown=false;
        Mix_FreeChunk(victory->bossdeath);
        Mix_FreeChunk(ultimate->ultimatesound);
        Mix_PlayChannel(-1,defeat->planedeathsound,0);
    }

}
}

void Boss_AI2(Boss *boss, Bullet2 *bullet2, Plane *plane)
{
    if(boss->shown==true)
    {
        int bullet2_left_side = bullet2->image.rect.x;
        int bullet2_right_side = bullet2->image.rect.x + bullet2->image.rect.w;

    int bullet2_top = bullet2->image.rect.y;
    int boss_top = boss->image.rect.y;
    int boss_left_side = boss->image.rect.x-20;
    int boss_right_side = boss->image.rect.x + boss->image.rect.w-20;
    int boss_bottom = boss->image.rect.y + boss->image.rect.h;
    if( (bullet2_left_side  >= boss_left_side) && (bullet2_right_side  <= boss_right_side)

   && (bullet2_top  <= boss_bottom -100 && (bullet2_top >= boss_top)))
    {
      boss->hp=boss->hp-1;
      plane->score=plane->score+5;
      Bullet2_setCoordinates(bullet2,20000,0);


    }


}
}

void Boss_setCoordinates(Boss *boss, int x, int y)
{
    Boss_setX(boss, x);
    Boss_setY(boss, y);
}

void Boss_moveX(Boss *boss, int x)
{
    Boss_setX(boss, boss->image.rect.x + x);
}

void Ultimate_followDirection(Ultimate *ultimate, Boss *boss, Plane *plane)
{
   if(ultimate->shown==true)
   {

       if((plane->image.rect.x+(plane->image.rect.w/2))==(boss->image.rect.x+(boss->image.rect.w/2)))
       {
           ultimate->direction=boss->direction;
       }
       if((plane->image.rect.x+(plane->image.rect.w/2))<(boss->image.rect.x+(boss->image.rect.w/2)))
       {
           ultimate->direction=boss->direction;
       }
       if((plane->image.rect.x+(plane->image.rect.w/2))>(boss->image.rect.x+(boss->image.rect.w/2)))
       {
           ultimate->direction=boss->direction;
       }


   }


}
void Boss_followDirection(Boss *boss, Plane *plane)
{
   if(boss->shown==true)
   {
       if(boss->image.rect.y+(boss->image.rect.h/2) < 200)
       {
           boss->direction=DIRECTION_DOWN;
       }
       else
       {
           boss->speed= PLANE_SPEED / BOSS_SPEED_RATIO;
           boss->aggro= true;
       if((plane->image.rect.x+(plane->image.rect.w/2))==(boss->image.rect.x+(boss->image.rect.w/2)))
       {
           boss->direction=DIRECTION_STOP;


       }
       else
       {
           if((plane->image.rect.x+(plane->image.rect.w/2))<(boss->image.rect.x+(boss->image.rect.w/2)))
           {
               boss->direction=DIRECTION_LEFT;
           }
           else
           {
//               if((plane->image.rect.x+(plane->image.rect.w/2))>(boss->image.rect.x+(boss->image.rect.w/2)))
//               {
                   boss->direction=DIRECTION_RIGHT;
//               }

           }

       }



       }

   }


}


void Boss_moveY(Boss *boss, int y)
{
    Boss_setY(boss, boss->image.rect.y + y);
}

void Boss_render(SDL_Renderer *renderer, Boss *boss)
{
    if(boss->shown)
    {
        // Render boss
        Image_render(renderer, &boss->image);
        const SDL_Color COLOR_WHITE = {255, 255, 255, 255};
        char life[30];
        sprintf(life, "BOSS HP: %d", boss->hp);
        stringRGBA(renderer, boss->image.rect.x+(boss->image.rect.w/2)-45, boss->image.rect.y+(boss->image.rect.h/2)-150, life, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a);
        boss->stage=true;
    }
    if(boss->destroyed==true)
    {
    boss->shown=false;
    }

}
void Boss_move(Boss *boss, int screenWidth, int framerate, Plane *plane)
{
    if(boss->shown==true)
    {
    int bossStep = boss->speed / framerate;

    if(boss->direction & DIRECTION_STOP)
    {
        Boss_setX(boss,plane->image.rect.x+(plane->image.rect.w/2));
    }
    else
    {
    if( (boss->direction & DIRECTION_RIGHT)
            && boss->image.rect.x + boss->image.rect.w + bossStep <= screenWidth - 20)
    {
        Boss_moveX(boss, bossStep);
    }
    else if( (boss->direction & DIRECTION_LEFT)
             && boss->image.rect.x - bossStep >= 20)
    {
        Boss_moveX(boss, -bossStep);
    }
    if( (boss->direction & DIRECTION_DOWN) )
        {
            Boss_moveY(boss, bossStep);
    }

    }
}
}
