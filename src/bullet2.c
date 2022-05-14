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

#include "bullet2.h"
#include "animation.h"
#include <SDL_mixer.h>


bool Bullet2_load(SDL_Renderer *renderer, Bullet2 *bullet2, const char *image)
{
    // Load bullet2 image
    if(!Image_load(renderer, &bullet2->image, image))
    {
        return false;
    }

    bullet2->shown = false;

    return true;
}

void Bullet2_destroy(Bullet2 *bullet2)
{
    Image_destroy(&bullet2->image);

}

void Bullet2_setX(Bullet2 *bullet2, int x)
{
    // Bullet2 x coordinate
    bullet2->image.rect.x = x;
}

void Bullet2_setY(Bullet2 *bullet2, int y)
{
    // Bullet2 y coordinate
    bullet2->image.rect.y = y;
}

void Bullet2_setCoordinates(Bullet2 *bullet2, int x, int y)
{
   Bullet2_setX(bullet2, x);
   Bullet2_setY(bullet2, y);
}

void Bullet2_moveY(Bullet2 *bullet2, int y)
{
    Bullet2_setY(bullet2, bullet2->image.rect.y + y);
}

void Bullet2_setDirection(Bullet2 *bullet2, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_SPACE:
       bullet2->direction &= ~DIRECTION_DOWN;
       bullet2->direction |= DIRECTION_UP;
    break;
  }
}


void Bullet2_render(SDL_Renderer *renderer, Bullet2 *bullet2)
{
    if(bullet2->shown)
    {
        // Render bullet2
        Image_render(renderer, &bullet2->image);
    }

}

void Bullet2_move(Bullet2 *bullet2, int framerate, Animation *animation)

{
    int bullet2Step = bullet2->speed / framerate;
    if( (bullet2->direction & DIRECTION_UP))

    {
    Bullet2_moveY(bullet2, -bullet2Step);
    for(int i = 0; i < ENEMY_NUM; i++)

     {

       int bullet2_left_side = bullet2->image.rect.x;
       int bullet2_right_side = bullet2->image.rect.x + bullet2->image.rect.w;
       int enemy_left_side = animation->enemy[i].image.rect.x;

            int enemy_right_side = animation->enemy[i].image.rect.x + animation->enemy[i].image.rect.w;
            int bullet2_top = bullet2->image.rect.y;
            int enemy_top = animation->enemy[i].image.rect.y;
            int enemy_bottom = animation->enemy[i].image.rect.y + animation->enemy[i].image.rect.h;

            if( (bullet2_left_side  >= enemy_left_side) && (bullet2_right_side  <= enemy_right_side)

           && (bullet2_top  <= enemy_bottom ) && (bullet2_top >= enemy_top))

            {
            animation->plane.score=animation->plane.score+5;

            animation->enemy[i].destroyed = true;
            animation->bullet2.shown = false;

            Bullet2_setCoordinates(&animation->bullet2,20000,0);
            Enemy_setX(&animation->enemy[i],10000);

            Mix_PlayChannel(0,animation->bullet2.enemydeathsound,0);

            if(animation->plane.score/5==(ENEMY_NUM))
            {
                if(animation->currentstage==1)
                {

                for(int j=0; j<ENEMY_NUM; j++)
                {
                    if((animation->enemy[j].addery/10)%2==0)
                    {
                        animation->enemy[j].direction = DIRECTION_LEFT;
                    }
                    else
                    {
                        animation->enemy[j].direction = DIRECTION_RIGHT;
                    }
                    animation->enemy[j].destroyed=false;
                    Enemy_setCoordinates(&animation->enemy[j],animation->enemy[j].initialx,animation->enemy[j].initialy);

                }
                }
                animation->currentstage++;


            }
            if(animation->plane.score/5==(ENEMY_NUM*2))
            {
            Mix_FreeChunk(animation->bullet2.enemydeathsound);
            Mix_PlayChannel(0,animation->boss.bossappear,0);
            animation->boss.shown=true;
            }

            }
    }
    }





    else if( (bullet2->direction & DIRECTION_DOWN))

    {

        Bullet2_moveY(bullet2, bullet2Step);

    }

}
