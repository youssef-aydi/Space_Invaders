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

#ifndef ANIMATION_H
#define ANIMATION_H

#include "utils.h"
#include "plane.h"
#include "enemy.h"
#include "background.h"
#include "bullet.h"
#include "bullet2.h"
#include "boss.h"
#include "victory.h"
#include "bossattack.h"
#include "defeat.h"
#include "ultimate.h"
#include "heart.h"
#include "pause.h"
#include "menu.h"
#include <time.h>
#include <windows.h>

#define WAVES_SOUND "assets/Space-Invaders-OST.wav"

#define PLANE_IMG       "assets/plane.png"
#define PLANE_SPEED      600
#define PLANE_MARGIN     20
#define PLANE_HP         5

#define ENEMY_IMG        "assets/enemy.png"
#define ENEMY_MARGIN     600
#define ENEMY_NUM        30
#define ENEMY_SPEED      60

#define HEART_IMG        "assets/heart.png"
#define HEART_MARGIN     800
#define HEART_NUM        5

#define OCEAN_IMG        "assets/ocean.jpg"
#define OCEAN_SPEED      200

#define BULLET_IMG       "assets/bullet.png"
#define BULLET_SPEED     800
#define BULLET_MARGIN    -600

#define BULLET2_IMG       "assets/bullet2.png"
#define BULLET2_SPEED     800
#define BULLET2_MARGIN    -600

#define BOSSATTACK_IMG       "assets/bossattack.png"
#define BOSSATTACK_SPEED     700
#define BOSSATTACK_MARGIN    -600

#define BOSS_IMG         "assets/boss.png"
#define BOSS_MARGIN      800
#define BOSS_HP          90
#define BOSS_SPEED_RATIO 3

#define VICTORY_IMG      "assets/victory.png"
#define VICTORY_MARGIN   400

#define DEFEAT_IMG       "assets/defeat.png"
#define DEFEAT_MARGIN    400

#define MENU_IMG       "assets/menu.png"
#define MENU_MARGIN    400

#define ULTIMATE_IMG1     "assets/ultimate1.png"
#define ULTIMATE_IMG2     "assets/ultimate2.png"
#define ULTIMATE_MARGIN  800

#define PAUSE_IMG1      "assets/pause1.png"
#define PAUSE_IMG2      "assets/pause2.png"
#define PAUSE_IMG3      "assets/pause3.png"
#define PAUSE_MARGIN   400




struct Animation
{
    // Animation screen dimensions
    int width;
    int height;

    // Animation renderer
    SDL_Renderer *renderer;

    // Background and Plane
    Background background;
    Plane plane;
    Enemy enemy[ENEMY_NUM];
    Heart heart[HEART_NUM];
    Bullet bullet;
    Bullet2 bullet2;
    Victory victory;
    Defeat defeat;
    Boss boss;
    Bossattack bossattack;
    Ultimate ultimate;
    int counter;
    int currentlevel;
    int currentstage;
    Pause pause;
    Uint8 *wavBuffer;
    SDL_AudioDeviceID deviceId;
    bool mute;
    bool start;
    Menu menu;

};
typedef struct Animation Animation;


bool Animation_start(SDL_Renderer *renderer, int width, int height);

bool Animation_load(Animation *animation);
void Animation_destroy(Animation *animation);

bool Animation_handleEvent(Animation *animation, SDL_Event *e);
int Animation_song(Animation *animation);
void Animation_update(Animation *animation, int framerate);
void Animation_render(Animation *animation);

#endif // ANIMATION_H
