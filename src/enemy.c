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

#include "enemy.h"
#include "animation.h"

bool Enemy_load(SDL_Renderer *renderer, Enemy *enemy, const char *image)
{
    // Load enemy image
    if(!Image_load(renderer, &enemy->image, image))
    {
        return false;

    }
    enemy->destroyed=false;
    return true;
}

void Enemy_destroy(Enemy *enemy)
{
    Image_destroy(&enemy->image);

}

void Enemy_setX(Enemy *enemy, int x)
{
    // Enemy x coordinate
    enemy->image.rect.x = x;
}

void Enemy_setY(Enemy *enemy, int y)
{
    // Enemy y coordinate
    enemy->image.rect.y = y;
}

void Enemy_setCoordinates(Enemy *enemy, int x, int y)
{
    Enemy_setX(enemy, x);
    Enemy_setY(enemy, y);
}

void Enemy_roaming(Enemy *enemy)
{
    if(enemy->destroyed==false)
    {
       if((enemy->image.rect.x)==(enemy->initialx+35))
        {
            enemy->direction=DIRECTION_LEFT;
        }
        if((enemy->image.rect.x)==(enemy->initialx-35))
        {
            enemy->direction=DIRECTION_RIGHT;
        }
    }

}
void Enemy_moveX(Enemy *enemy, int x)
{
    Enemy_setX(enemy, enemy->image.rect.x + x);
}

void Enemy_move(Enemy *enemy, int framerate)
{
    if(enemy->destroyed==false)
    {
    int enemyStep = enemy->speed / framerate;

    if (enemy->direction & DIRECTION_RIGHT)

    {
        Enemy_moveX(enemy, enemyStep);
    }
    else if (enemy->direction & DIRECTION_LEFT)

    {
        Enemy_moveX(enemy, -enemyStep);
    }

}
}


void Enemy_render(SDL_Renderer *renderer, Enemy *enemy)
{
    if(enemy->destroyed==false)
    {
    // Render enemy
    Image_render(renderer, &enemy->image);
    }
}

