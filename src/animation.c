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
#include "utils.h"
#include "animation.h"
#include <SDL_mixer.h>
#include <SDL2_framerate.h>
#include <SDL2_gfxPrimitives.h>
#include <time.h>
#include <windows.h>

bool Animation_start(SDL_Renderer *renderer, int width, int height)
{
    Animation animation = {0};
    animation.renderer  = renderer;
    animation.width     = width;
    animation.height    = height;

    // Load animation assets
    if(!Animation_load(&animation))
        return false;
    Mix_PlayChannel(7,animation.menu.menusong,10);

    // Initialize framerate manager : 60 FPS
    FPSmanager fpsmanager;
    SDL_initFramerate(&fpsmanager);
    SDL_setFramerate(&fpsmanager, 60);

    // Initialize start frame
    int frame = SDL_getFramecount(&fpsmanager);

    Animation_song(&animation);

    // Event loop exit flag
    bool quit = false;

    // Event loop
    while(!quit)
    {
        SDL_Event e;

        // Get available event
        while(SDL_PollEvent(&e))
        {
            // Handle animation events
            quit = Animation_handleEvent(&animation, &e);
        }

        // Each new frame
        int currentFrame = SDL_getFramecount(&fpsmanager);
        if(currentFrame != frame)
        {
            // Update animation frame
            Animation_update(&animation, SDL_getFramerate(&fpsmanager));

            currentFrame = frame;
        }

        // Render animation
        Animation_render(&animation);

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay
        SDL_framerateDelay(&fpsmanager);
    }

    Animation_destroy(&animation);

    return true;
}
bool Animation_load(Animation *animation)
{

    animation->start=false;
    // Load SoundEffects

    animation->menu.menusong=Mix_LoadWAV("assets/Menu.wav");
    if(!animation->menu.menusong)
    {
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }

    animation->bullet.bulletsound=Mix_LoadWAV("assets/Bullet.wav");
    if(!animation->bullet.bulletsound)
    {
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }

    animation->bullet.enemydeathsound=Mix_LoadWAV("assets/Explosion.wav");
    if(!animation->bullet.enemydeathsound)
   {
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
   }

    animation->bullet2.bulletsound=Mix_LoadWAV("assets/Bullet.wav");
    if(!animation->bullet2.bulletsound)
    {
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }

    animation->bullet2.enemydeathsound=Mix_LoadWAV("assets/Explosion.wav");
    if(!animation->bullet2.enemydeathsound)
   {
        printf("Mix_LoadWAV: %s\n", Mix_GetError());
   }

    animation->victory.bossdeath=Mix_LoadWAV("assets/BossDeath.wav");
     if(!animation->victory.bossdeath)
    {
         printf("Mix_LoadWAV: %s\n", Mix_GetError());
    }

     animation->boss.bossappear=Mix_LoadWAV("assets/BossAppear.wav");
      if(!animation->boss.bossappear)
     {
          printf("Mix_LoadWAV: %s\n", Mix_GetError());
     }

      animation->defeat.planedeathsound=Mix_LoadWAV("assets/PlaneDeath.wav");
       if(!animation->defeat.planedeathsound)
      {
           printf("Mix_LoadWAV: %s\n", Mix_GetError());
      }

      animation->ultimate.ultimatesound=Mix_LoadWAV("assets/Ultimate.wav");
       if(!animation->ultimate.ultimatesound)
       {
           printf("Mix_LoadWAV: %s\n", Mix_GetError());
       }

       animation->pause.pausesound=Mix_LoadWAV("assets/Pause.wav");
        if(!animation->pause.pausesound)
        {
            printf("Mix_LoadWAV: %s\n", Mix_GetError());
        }
    // Load the ocean image
    if(!Background_load(animation->renderer, &animation->background, OCEAN_IMG))
        return false;

    // Background move direction
    animation->background.direction = DIRECTION_DOWN;

    // Background speed in pixel/second
    animation->background.speed = OCEAN_SPEED;



    if(!Plane_load(animation->renderer, &animation->plane, PLANE_IMG))
    {
        Background_destroy(&animation->background);
        return false;
    }

    animation->plane.margin = PLANE_MARGIN;

    for (int i=0 ; i< ENEMY_NUM ; i++)
    {
    if(!Enemy_load(animation->renderer, &animation->enemy[i], ENEMY_IMG))
    {
        Background_destroy(&animation->background);
        return false;
    }

    animation->enemy[i].margin = ENEMY_MARGIN;
    }

    for (int j=0 ; j< HEART_NUM ; j++)
    {
    if(!Heart_load(animation->renderer, &animation->heart[j], HEART_IMG))
    {
        Background_destroy(&animation->background);
        return false;
    }

    animation->heart[j].margin = HEART_MARGIN;
    }



        if(!Bullet_load(animation->renderer, &animation->bullet, BULLET_IMG))
    {
        Background_destroy(&animation->background);
        return false;
    }

    animation->bullet.margin = BULLET_MARGIN;

    if(!Bullet2_load(animation->renderer, &animation->bullet2, BULLET2_IMG))
{
    Background_destroy(&animation->background);
    return false;
}

animation->bullet2.margin = BULLET2_MARGIN;
    if(!Bossattack_load(animation->renderer, &animation->bossattack, BOSSATTACK_IMG))
{
    Background_destroy(&animation->background);
    return false;
}

animation->bossattack.margin = BOSSATTACK_MARGIN;

    if(!Boss_load(animation->renderer, &animation->boss, BOSS_IMG))
{
    Background_destroy(&animation->background);
    return false;
}

animation->boss.margin = BOSS_MARGIN;

if(!Ultimate_load(animation->renderer, &animation->ultimate, ULTIMATE_IMG1, ULTIMATE_IMG2))
{
Background_destroy(&animation->background);
return false;
}

animation->ultimate.margin = ULTIMATE_MARGIN;

    if(!Victory_load(animation->renderer, &animation->victory, VICTORY_IMG))
    {
    Background_destroy(&animation->background);
    return false;
    }

    animation->victory.margin = VICTORY_MARGIN;

    if(!Defeat_load(animation->renderer, &animation->defeat, DEFEAT_IMG))
    {
    Background_destroy(&animation->background);
    return false;
    }

    animation->defeat.margin = DEFEAT_MARGIN;

    if(!Menu_load(animation->renderer, &animation->menu, MENU_IMG))
    {
    Background_destroy(&animation->background);
    return false;
    }

    animation->menu.margin = MENU_MARGIN;

    if(!Pause_load(animation->renderer, &animation->pause, PAUSE_IMG1, PAUSE_IMG2, PAUSE_IMG3))
    {
    Background_destroy(&animation->background);
    return false;
    }

    animation->defeat.margin = DEFEAT_MARGIN;

    // Set victory initial position
    Victory_setX(&animation->victory, (animation->width - animation->victory.image.rect.w) / 2);
    Victory_setY(&animation->victory, animation->height - animation->victory.image.rect.h - animation->victory.margin);

    // Set menu initial position
    Menu_setX(&animation->menu, 0);
    Menu_setY(&animation->menu, 0);

    // Set defeat initial position
    Defeat_setX(&animation->defeat, (animation->width - animation->defeat.image.rect.w) / 2);
    Defeat_setY(&animation->defeat, animation->height - animation->defeat.image.rect.h - animation->defeat.margin);

    // Set pause initial position

    Pause_setX(&animation->pause, 570);
    Pause_setY(&animation->pause, 480);

    // Set plane initial position
    Plane_setX(&animation->plane, (animation->width - animation->plane.image.rect.w) / 2);
    Plane_setY(&animation->plane, animation->height - animation->plane.image.rect.h - animation->plane.margin);
    animation->plane.hp=PLANE_HP;


    // Set boss initial position
    Boss_setX(&animation->boss, (animation->width - animation->boss.image.rect.w) / 2);
    Boss_setY(&animation->boss, animation->height - animation->boss.image.rect.h - animation->boss.margin);
    animation->boss.hp=BOSS_HP;
    animation->boss.aggro=false;

    // Set enemy initial position
    int adderx=0;
    int addery=0;
    int enemyspawn=0;
    for (int i=0 ; i< ENEMY_NUM ; i++)
    {
    int posx=25+adderx;
    Enemy_setX(&animation->enemy[i], posx );// Horiz. center
    animation->enemy[i].initialx=posx;
    int posy=(animation->height - animation->enemy[i].image.rect.h - animation->enemy[i].margin)+addery;
    Enemy_setY(&animation->enemy[i], posy );
    animation->enemy[i].initialy=posy;
    animation->enemy[i].addery=addery;

    adderx=adderx+130;
    enemyspawn++;
    if(enemyspawn % 10 == 0)
    {
       adderx=0;
       addery=addery+130;
    }
    }

    // Set heart initial position
    int heartx=0;
    int heartspawn=0;
    for (int j=0 ; j< HEART_NUM ; j++)
    {
    int poshx=1170+heartx;
    Heart_setX(&animation->heart[j], poshx );

    int poshy=15;
    Heart_setY(&animation->heart[j], poshy );

    heartx=heartx+30;
    heartspawn++;
    if(heartspawn % 5 == 0)
    {
        heartx=0;
    }
    }

    // Initiate system fixes
    animation->bossattack.fix=1;
    animation->counter=1;
    animation->bullet.first=0;
    animation->bullet2.first=0;
    animation->currentlevel=1;
    animation->currentstage=1;
    animation->bullet.wrongpress=false;
    animation->bullet2.wrongpress=false;


    // Plane move direction
    animation->plane.direction = DIRECTION_STOP;

    // Plane move speed in pixel/second
    animation->plane.speed = PLANE_SPEED;

    for(int i=0; i<ENEMY_NUM; i++)
    {
         // Enemy move direction
        if((animation->enemy[i].addery/10)%2==0)
        {
            animation->enemy[i].direction = DIRECTION_RIGHT;
        }
        else
        {
            animation->enemy[i].direction = DIRECTION_LEFT;
        }


         // Plane move speed in pixel/second
         animation->enemy[i].speed = ENEMY_SPEED;
    }

    // Boss follow plane direction
    animation->boss.direction = DIRECTION_STOP;

    // Boss move speed in pixel/second
    animation->boss.speed = 1200;

    // Ultimate follow boss direction
    animation->ultimate.direction = DIRECTION_STOP;

    // Ultimate move speed in pixel/second
    animation->ultimate.speed = PLANE_SPEED / BOSS_SPEED_RATIO;



    // Bullet move direction
    animation->bullet.direction = DIRECTION_STOP;

    // Bullet move speed in pixel/second
    animation->bullet.speed = BULLET_SPEED;

    // Bullet2 move direction
    animation->bullet2.direction = DIRECTION_STOP;

    // Bullet2 move speed in pixel/second
    animation->bullet2.speed = BULLET_SPEED;

    // Bossattack move direction
    animation->bossattack.direction = DIRECTION_STOP;

    // Bossattack move speed in pixel/second
    animation->bossattack.speed = BOSSATTACK_SPEED;



    return true;
}

void Animation_destroy(Animation *animation)
{
    Plane_destroy(&animation->plane);
    Enemy_destroy(&animation->enemy[ENEMY_NUM]);
    Heart_destroy(&animation->heart[HEART_NUM]);
    Background_destroy(&animation->background);
    Bullet_destroy(&animation->bullet);
    Bullet2_destroy(&animation->bullet2);
    Boss_destroy(&animation->boss);
    Victory_destroy(&animation->victory);
    Defeat_destroy(&animation->defeat);
    Bossattack_destroy(&animation->bossattack);
    Ultimate_destroy(&animation->ultimate);
    Pause_destroy(&animation->pause);
    SDL_CloseAudioDevice(animation->deviceId);
    SDL_FreeWAV(animation->wavBuffer);
    Menu_destroy(&animation->menu);

}

bool Animation_handleEvent(Animation *animation, SDL_Event *e)
{
    bool quit = false;
    // User requests quit
    if(e->type == SDL_QUIT)
    {
        quit = true;
    }
    else if(e->type == SDL_KEYDOWN)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_ESCAPE:
            quit = true;
            break;

        case SDLK_f:
            if(animation->start==false)
            {
                animation->start=true;
                SDL_PauseAudioDevice(animation->deviceId, 0);
                Mix_HaltChannel(7);
                Mix_FreeChunk(animation->menu.menusong);
            }
            break;

        case SDLK_p:
            if(animation->start==true)
            {
            if(animation->victory.shown==false&&animation->defeat.shown==false)
            {
            if(animation->pause.shown==false)
            {animation->pause.shown=true;
            SDL_PauseAudioDevice(animation->deviceId, 1);
            Mix_PlayChannel(4,animation->pause.pausesound,0);
            Mix_HaltChannel(5);
            }
            else
            {animation->pause.shown=false;
            if(animation->mute==false)
            {
            SDL_PauseAudioDevice(animation->deviceId, 0);
            }
            Mix_HaltChannel(4);
            Mix_HaltChannel(5);
            }
            }
            }
            break;

        case SDLK_m:
            if(animation->start==true)
            {
                if(animation->pause.shown==false)
                {
                if(animation->mute==false)
            {
                animation->mute=true;
                SDL_PauseAudioDevice(animation->deviceId, 1);
            }
            else
            {
                animation->mute=false;
                SDL_PauseAudioDevice(animation->deviceId, 0);
            }
            }
            }
            break;

        case SDLK_RIGHT:
        case SDLK_LEFT:
            if(animation->start==true)
            {
            if(animation->plane.destroyed==false)
        {
        Plane_setDirection(&animation->plane, e->key.keysym.sym);

        }
            }
        break;


        case SDLK_SPACE:
            if(animation->start==true)
            {
            if(animation->plane.destroyed==false)
            {
                if(animation->pause.shown==false)
                {


                if (animation->counter==3)
                {
                    animation->counter=1;
                }
                if (animation->counter==1)
               {
                   if(210>animation->bullet.image.rect.y || animation->bullet.first==0)
                  {
                   animation->bullet.shown=true;
                   Mix_PlayChannel(-1,animation->bullet.bulletsound,0);
                   Bullet_setX(&animation->bullet , animation->plane.image.rect.x - animation->bullet.image.rect.w /2 + animation->plane.image.rect.w /2);
                   Bullet_setY(&animation->bullet, animation->plane.image.rect.y);
                   Bullet_setDirection(&animation->bullet, e->key.keysym.sym);
                   animation->bullet.first++;
                   animation->bullet.wrongpress=false;
                   }
                   else{
                       if(animation->bullet.first!=1)
                       {animation->bullet.wrongpress=true;}}

               }
               if(animation->counter==2)
               {

                   if(210>animation->bullet2.image.rect.y || animation->bullet2.first==0)
                  {
                   animation->bullet2.shown=true;
                   Mix_PlayChannel(-1,animation->bullet2.bulletsound,0);
                   Bullet2_setX(&animation->bullet2 , animation->plane.image.rect.x - animation->bullet2.image.rect.w /2 + animation->plane.image.rect.w /2);
                   Bullet2_setY(&animation->bullet2, animation->plane.image.rect.y);
                   Bullet2_setDirection(&animation->bullet2, e->key.keysym.sym);
                   animation->bullet2.first++;
                   animation->bullet2.wrongpress=false;
                   }
                   else{if(animation->bullet2.first!=1)
                       {animation->bullet2.wrongpress=true;}}


               }
               if((animation->bullet.shown==true)||(animation->bullet2.shown==true))
               {
                   animation->counter=animation->counter+2;

                   if((animation->bullet.wrongpress=true)||(animation->bullet2.wrongpress=true))
                   {animation->counter=animation->counter-1;}

               }



            }
            }
            }
            break;

        }
    }
    else if(e->type == SDL_KEYUP)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_RIGHT:
        case SDLK_LEFT:
            if(animation->start==true)
            {
            if(animation->plane.destroyed==false)
            {
            Plane_unsetDirection(&animation->plane, e->key.keysym.sym);
            }
            }
            break;

        }
    }

    return quit;
}

int Animation_song(Animation *animation)
{


    // Load .WAV sound
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;

    if(!SDL_LoadWAV(WAVES_SOUND, &wavSpec, &animation->wavBuffer, &wavLength))
    {
        printf(".WAV sound '%s' could not be loaded!\n"
               "SDL_Error: %s\n", WAVES_SOUND, SDL_GetError());
        return 0;
    }

    // Open audio device
    animation->deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if(!animation->deviceId)
    {
        printf("Audio device could not be opened!\n"
               "SDL_Error: %s\n", SDL_GetError());
        SDL_FreeWAV(animation->wavBuffer);
        return 0;
    }

    // Queue audio (~ Add to playlist)
    if(SDL_QueueAudio(animation->deviceId, animation->wavBuffer, wavLength) < 0)
    {
        printf("Audio could not be queued!\n"
               "SDL_Error: %s\n", SDL_GetError());
        SDL_CloseAudioDevice(animation->deviceId);
        SDL_FreeWAV(animation->wavBuffer);
        return 0;
    }



return 0;

}

void Animation_update(Animation *animation, int framerate)
{


    if(animation->start==true)
    {
    if(animation->pause.shown==false)
    {
    // Move ocean
    Background_move(&animation->background, framerate);

    // Move plane
    Plane_move(&animation->plane, &animation->ultimate, &animation->defeat, animation->width, framerate, animation);

    // Move enemy
    for(int i=0; i<ENEMY_NUM; i++)
    {

        Enemy_roaming(&animation->enemy[i]);
        Enemy_move(&animation->enemy[i], framerate);

    }
    // Move bullet
//    if(animation->counter==1)
//    {
    Bullet_move(&animation->bullet,framerate, animation);
//    }
//    if(animation->counter==2)
//    {
    Bullet2_move(&animation->bullet2,framerate, animation);
//    }


    // Boss follows plane
    Boss_followDirection(&animation->boss, &animation->plane);
    Boss_move(&animation->boss, animation->width, framerate, &animation->plane);

    Ultimate_setCoordinates(&animation->ultimate, animation->boss.image.rect.x+(animation->boss.image.rect.w/2)-38, animation->boss.image.rect.y+(animation->boss.image.rect.h/2)+100);
    // Bossattack-Ultimate coordination
    Ultimate_followDirection(&animation->ultimate, &animation->boss, &animation->plane);
    Ultimate_move(&animation->ultimate, &animation->boss/*, animation->width*/, framerate);



    // Move bossattack
    Bossattack_move(&animation->bossattack, &animation->plane, framerate, animation);

    // Boss AI behaviour
    Boss_AI(&animation->boss, &animation->bullet, &animation->plane, &animation->bossattack, &animation->victory, &animation->defeat, &animation->ultimate);
    Boss_AI2(&animation->boss, &animation->bullet2, &animation->plane);

    // Plane AI death check
    Plane_AI(&animation->plane, &animation->defeat);

    // Bossattack limits check
    Bossattack_limits(&animation->bossattack, &animation->plane, animation->boss.image.rect.x, animation->boss.image.rect.x + animation->boss.image.rect.w, animation->boss.image.rect.y+(animation->boss.image.rect.h/2), &animation->ultimate, &animation->victory, &animation->defeat);
}
}
}

void Animation_render(Animation *animation)
{

    if(animation->start==true)
    {
    // Render ocean
    Background_render(animation->renderer, &animation->background, animation->width, animation->height);

    // Render score and level
    const SDL_Color COLOR_WHITE = {255, 255, 255, 255};
    char board[30];
    char level[30];
    sprintf(board, "Score: %d", animation->plane.score);
    stringRGBA(animation->renderer, 60, 25, board, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a);
    if(animation->boss.stage==false)
    {
    sprintf(level, "LEVEL: %d-%d", animation->currentlevel , animation->currentstage);
    stringRGBA(animation->renderer, 160, 25, level, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a);
    }
    if(animation->boss.stage==true)
    {
    sprintf(level, "LEVEL: %d-BOSS", animation->currentlevel);
    stringRGBA(animation->renderer, 160, 25, level, COLOR_WHITE.r, COLOR_WHITE.g, COLOR_WHITE.b, COLOR_WHITE.a);
    }
    // Render plane
    Plane_render(animation->renderer, &animation->plane);

    // Render enemy
    for (int i=0 ; i< ENEMY_NUM ; i++)
    {
    Enemy_render(animation->renderer, &animation->enemy[i]);
    }
    // Render heart
    for (int j=0 ; j< HEART_NUM ; j++)
    {
    Heart_render(animation->renderer, &animation->heart[j]);
    }

    // Render bullet
    Bullet_render(animation->renderer, &animation->bullet);

    // Render bullet2
    Bullet2_render(animation->renderer, &animation->bullet2);

    // Render boss
    Boss_render(animation->renderer, &animation->boss);

    // Render victory
    Victory_render(animation->renderer, &animation->victory);

    // Render defeat
    Defeat_render(animation->renderer, &animation->defeat);

    // Render bossattack
    Bossattack_render(animation->renderer, &animation->bossattack);

    // Render ultimate


    Pause_render(animation->renderer, &animation->pause);

    if(animation->ultimate.shown==true)
    {



    Ultimate_render(animation->renderer, &animation->ultimate);

    }



}
    Menu_render(animation->renderer,&animation->menu, animation);
}

