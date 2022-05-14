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

#include "bullet.h"
#include "animation.h"
#include <SDL_mixer.h>


bool Bullet_load(SDL_Renderer *renderer, Bullet *bullet, const char *image)
{
    // Load bullet image
    if(!Image_load(renderer, &bullet->image, image))
    {
        return false;
    }

    bullet->shown = false;

    return true;
}

void Bullet_destroy(Bullet *bullet)
{
    Image_destroy(&bullet->image);

}

void Bullet_setX(Bullet *bullet, int x)
{
    // Bullet x coordinate
    bullet->image.rect.x = x;
}

void Bullet_setY(Bullet *bullet, int y)
{
    // Bullet y coordinate
    bullet->image.rect.y = y;
}

void Bullet_setCoordinates(Bullet *bullet, int x, int y)
{
   Bullet_setX(bullet, x);
   Bullet_setY(bullet, y);
}

void Bullet_moveY(Bullet *bullet, int y)
{
    Bullet_setY(bullet, bullet->image.rect.y + y);
}

void Bullet_setDirection(Bullet *bullet, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_SPACE:
       bullet->direction &= ~DIRECTION_DOWN;
       bullet->direction |= DIRECTION_UP;
    break;
  }
}


void Bullet_render(SDL_Renderer *renderer, Bullet *bullet)
{
    if(bullet->shown)
    {
        // Render bullet
        Image_render(renderer, &bullet->image);
    }

}

void Bullet_move(Bullet *bullet, int framerate, Animation *animation)

{
    int bulletStep = bullet->speed / framerate;
    if( (bullet->direction & DIRECTION_UP))

    {
    Bullet_moveY(bullet, -bulletStep);
    for(int i = 0; i < ENEMY_NUM; i++)

     {

       int bullet_left_side = bullet->image.rect.x;
       int bullet_right_side = bullet->image.rect.x + bullet->image.rect.w;
       int enemy_left_side = animation->enemy[i].image.rect.x;

            int enemy_right_side = animation->enemy[i].image.rect.x + animation->enemy[i].image.rect.w;
            int bullet_top = bullet->image.rect.y;
            int enemy_top = animation->enemy[i].image.rect.y;
            int enemy_bottom = animation->enemy[i].image.rect.y + animation->enemy[i].image.rect.h;

            if( (bullet_left_side  >= enemy_left_side) && (bullet_right_side  <= enemy_right_side)

           && (bullet_top  <= enemy_bottom ) && (bullet_top) >= enemy_top)

            {
            animation->plane.score=animation->plane.score+5;

            animation->enemy[i].destroyed = true;
            animation->bullet.shown = false;

            Bullet_setCoordinates(&animation->bullet,20000,0);
            Enemy_setX(&animation->enemy[i],10000);

            Mix_PlayChannel(0,animation->bullet.enemydeathsound,0);

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
            Mix_FreeChunk(animation->bullet.enemydeathsound);
            Mix_PlayChannel(0,animation->boss.bossappear,0);
            animation->boss.shown=true;
            }

            }


    }
    }





    else if( (bullet->direction & DIRECTION_DOWN))

    {

        Bullet_moveY(bullet, bulletStep);

    }

}
