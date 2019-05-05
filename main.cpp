#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <math.h>
#include <SDL.h>
#include <SDL_draw.h>
#include <windows.h>
#include "SDL_ttf.h"
#include <fstream>
#include <iostream>
#include <SDL_thread.h>
#include "Text.cpp"
#include "Static_image.cpp"

using namespace std;

SDL_Surface* sh1 = NULL;
SDL_Surface* animation =SDL_SetVideoMode(570, 650, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
SDL_Thread *thread=NULL;
SDL_Rect TEXT_LOCATE;

int ONLY_EDIT=0;
int count=0;
char NOW_NAME[30];
int Res_Score_y=50;
int zzz=0;

void add(char*);
void edit(char*);
void show(char*);
void search(char*);
void print1(struct players data);
void input_name();
void play();
void draw_menu_s();
void draw_input_name();
void draw_score();
void draw_change_player(char*);
void draw_beginning();
void logi(char *text);
void do_menu_s();
void draw_rules();
int Draw_Shuttle();
void save(int, int, int, int, int, int);
void delete_file(char*);
void print_file(char*, char*);
void check_save();

struct players
{
    char name[30];
    int score;
};

struct players input_player(void)
{
    struct players new_pl;
    memcpy( new_pl.name, NOW_NAME, sizeof(char)*30 );
    new_pl.score=SCORE;
    return new_pl;
};

int main ( int argc, char** argv )
{
    check_save();
    char Score_f[]={"Score_f.dat"};
    char Print_f[]={"Print_f.txt"};
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    if (TTF_Init())
    {
        fprintf(stderr,"?????? ? TTF_Init: %s\n",SDL_GetError());
        return 1;
    }
    atexit(SDL_Quit);
    fnt = TTF_OpenFont("3d.ttf", 50);
    fnt_1 = TTF_OpenFont("3d.ttf", 25);
    fnt_2 = TTF_OpenFont("3d.ttf", 15);
    fnt_3 = TTF_OpenFont("3d.ttf", 70);
    printf("fnt = %p\n", fnt);
    if(!fnt)
    return 3;
    if(!fnt_1)
    return 3;
    if(!fnt_2)
    return 3;
    if(!fnt_3)
    return 3;
    draw_beginning();
    if (zzz==1)
    {
        TTF_Quit();
        SDL_Quit();
        return 0;
    }
    input_name();
    if (zzz==1)
    {
        TTF_Quit();
        SDL_Quit();
        return 0;
    }
    search(Score_f);
    if(ONLY_EDIT==0) add(Score_f);
    FILE * pFile;
    long size;
    pFile = fopen ("game.txt","rb");
    if (pFile==NULL) perror ("Error opening file");
    else
    {
        fseek (pFile, 0, SEEK_END);
        size=ftell (pFile);
        fclose (pFile);
    }
    if(size==0)
    {
        do_menu_s();
    }
    if(size!=0)
    {
        do_menu_s();
    }
    TTF_Quit();
    SDL_Quit();
    return 0;

}

int h=10;

void logi(char *text)
{

    dest.x = 500;
    dest.y = h;
    h+=10;
    SDL_Color Print_C;
    Print_C.r=255; Print_C.g=255; Print_C.b=255;
    fnt_2 = TTF_OpenFont("arial.ttf", 15);
    text_surface = TTF_RenderUTF8_Solid(fnt_2, text, Print_C);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
}

int Draw_Shuttle(void *data)
{
    check_save();
    if(SAVE==1)
    {
        char file[]={"game.dat"};
        delete_file(file);
    }
    WannaCry.do_enemy();
    return 0;

}

void input_name()
{
    fnt_1 = TTF_OpenFont("3d.ttf", 30);
    SDL_Event event;
    memset(NOW_NAME,0,30);
    char now[2];
    SDL_Rect text;
    SDL_Color text_c;
    text_c.r=0; text_c.g=255; text_c.b=0;
    SDL_Surface *text1;
    text.x=60;
    text.y=240;
    text.h=50;
    text.w=670;
    while ( SDL_WaitEvent(&event) )
        {
            if(event.type == SDL_QUIT || ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            {
                zzz=1;
                return;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <=SDLK_9)
                {
                    int digitsym = (char) event.key.keysym.sym;
                    sprintf(now, "%c", digitsym);
                    text1 = TTF_RenderUTF8_Solid(fnt_1, now, text_c);
                    SDL_BlitSurface(text1, NULL, screen, &text);
                    SDL_Flip(screen);
                    NOW_NAME[count]=digitsym;
                    count++;
                    text.x+=20;
                    continue;
                }
                if(event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <=SDLK_z)
                {
                    char digitsym = (char) event.key.keysym.sym;
                    sprintf(now, "%c", digitsym);
                    text1 = TTF_RenderUTF8_Solid(fnt_1, now, text_c);
                    SDL_BlitSurface(text1, NULL, screen, &text);
                    SDL_Flip(screen);
                    NOW_NAME[count]=digitsym;
                    count++;
                    if(digitsym=='i') text.x+=10;
                    else text.x+=20;
                    continue;
                }
                if(event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    count--;
                    Draw_FillRect(screen,text.x-20, text.y, 30, 30,0x000000);
                    SDL_Flip(screen);
                    text.x=text.x-20;
                    continue;
                }
                if(event.key.keysym.sym == SDLK_SPACE)
                {
                    char digitsym = ' ';
                    sprintf(now, "%c", digitsym);
                    text1 = TTF_RenderUTF8_Solid(fnt_1, now, text_c);
                    SDL_BlitSurface(text1, NULL, screen, &text);
                    SDL_Flip(screen);
                    NOW_NAME[count]=digitsym;
                    count++;
                    text.x+=20;
                    continue;
                }
                if(event.key.keysym.sym == SDLK_RETURN)
                {
                    NOW_NAME[count]='\0';
                    break;
                }
            }
        }
}

void add (char* file)
{
    FILE *f;
    int pos, k=0;
    struct players new_pl;
    system("CLS");
    if((f=fopen(file, "ab"))==NULL)
    {
        perror("Error open file");
        system("pause");
        return;
    }
    new_pl=input_player();
    fwrite(&new_pl, sizeof(new_pl), 1, f);
fclose(f);
}

void print1(struct players data)
{
    char str1[30];
    fnt = TTF_OpenFont("3d.ttf", 30);
    TEXT_LOCATE.x=50;
    TEXT_LOCATE.y=Res_Score_y;
    SDL_Color Print_C;
    Print_C.r=0; Print_C.g=255; Print_C.b=0;
    sprintf(str1, "%d", data.score);
    text_surface = TTF_RenderUTF8_Solid(fnt, data.name, Print_C);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &TEXT_LOCATE);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    TEXT_LOCATE.x=512;
    text_surface = TTF_RenderUTF8_Solid(fnt, str1, Print_C);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &TEXT_LOCATE);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    Res_Score_y+=35;
    TEXT_LOCATE.x=50;
}

void edit(char* file)
{
    FILE * f;
    int pos;
    struct players new_pl;
    if((f=fopen(file, "rb+"))==NULL)
    {
        perror("Error open file");
        system("pause");
        return;
    }
    while(fread(&new_pl, sizeof(new_pl), 1, f))
        if(!strcmp(new_pl.name, NOW_NAME))
        {
            pos=ftell(f);
            if(new_pl.score<SCORE)
            {
                new_pl.score=SCORE;
                fseek(f, pos-sizeof(new_pl), SEEK_SET);
                fwrite(&new_pl, sizeof(new_pl), 1, f);
                fclose(f);
            }
        }

}

void show (char* file)
{
    FILE* f;
    struct players new_pl;
    if((f=fopen (file, "rb"))==NULL)
    {
        perror("Error open file");
        system("pause");
        return;
    }
    while(fread(&new_pl, sizeof(new_pl), 1, f)==1) print1(new_pl);
    fclose(f);
    return;
}

void search(char* file)
{
    FILE *f;
    struct players new_pl;
    int size;
    system("CLS");
    if((f=fopen(file, "rb"))==NULL)
    {
        perror("Error open file");
        system("pause");
        return;
    }
    fseek (f, 0, SEEK_END);
    size=ftell (f);
    if(size==0) ONLY_EDIT=0;
        else
        {
            fseek(f, 0, SEEK_SET);
            while(fread(&new_pl, sizeof(new_pl), 1, f)==1)
            {
                if(strcmp(new_pl.name, NOW_NAME)==0) ONLY_EDIT=1;
            }
        }
    fclose(f);
}

void check_save()
{
    FILE *f;
    system("CLS");
    int size;
    if((f=fopen("game.dat", "rb"))==NULL)
    {
        perror("Error open file");
        system("pause");
        return;
    }
    fseek (f, 0, SEEK_END);
    size=ftell (f);
    if(size==0)
    {
        SAVE=0;
        fclose(f);
        return;
    }
    else
    {
        fseek(f, 0, SEEK_SET);
        fread(&save_name, sizeof(char)*30, 1, f);
        if(strcmp(save_name, NOW_NAME)==0)
        {
            SAVE=1;
            fread(&save_me_x, sizeof(int), 1, f);
            fread(&save_me_y, sizeof(int), 1, f);
            fread(&save_enemy_x, sizeof(int), 1, f);
            fread(&save_enemy_y, sizeof(int), 1, f);
            fread(&save_speed, sizeof(int), 1, f);
            fread(&SCORE, sizeof(int), 1, f);
        }
    }
    fclose(f);
    return;
}

void draw_rules()
{
    image = SDL_LoadBMP( "phon.bmp" );
    if( image == NULL ) printf( "Unable to load image %s! SDL Error: %s\n", "unnamed.bmp", SDL_GetError() );
    SDL_BlitSurface(image, NULL, screen, NULL);
    SDL_Flip(screen);
    fnt = TTF_OpenFont("3d.ttf", 50);
    fnt_1 = TTF_OpenFont("3d.ttf", 30);
    fnt_2 = TTF_OpenFont("3d.ttf", 20);
    fnt_3 = TTF_OpenFont("3d.ttf", 70);
    dest.x = 200; dest.y = 50;
    text_surface = TTF_RenderUTF8_Solid(fnt, "Rules", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    dest.x = 50; dest.y = 140;
    text_surface = TTF_RenderUTF8_Solid(fnt_1, "While you are playing, use", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    dest.x = 50; dest.y = dest.y + 35;
    text_surface = TTF_RenderUTF8_Solid(fnt_1, "the keys <-- and --> to move", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    dest.x = 50; dest.y = dest.y + 35;
    text_surface = TTF_RenderUTF8_Solid(fnt_1, "and the key 'space' to shoot.", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    dest.x = 50; dest.y = dest.y + 35;
    text_surface = TTF_RenderUTF8_Solid(fnt_1, "You can use the key 'esc'", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    dest.x = 50; dest.y = dest.y + 35;
    text_surface = TTF_RenderUTF8_Solid(fnt_1, "to close this program", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    dest.x = 50; dest.y = dest.y + 35;
    text_surface = TTF_RenderUTF8_Solid(fnt_1, "or return to menu.", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    dest.x = 50; dest.y = dest.y + 35;
    text_surface = TTF_RenderUTF8_Solid(fnt_1, "You can save your game.", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    text_color.r=255; text_color.b=0; text_color.g=0;
    dest.x = 50; dest.y = dest.y + 50;
    text_surface = TTF_RenderUTF8_Solid(fnt, "WARNING!!!", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    text_color.r=0; text_color.b=0; text_color.g=255;
    dest.x = 50; dest.y = dest.y + 70;
    text_surface = TTF_RenderUTF8_Solid(fnt_1, "All rights reserved,", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    dest.x = 50; dest.y = dest.y + 35;
    text_surface = TTF_RenderUTF8_Solid(fnt_1, "whatever that means ...", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    while(SDL_WaitEvent(&event))
    {
        if(event.type == SDL_QUIT ||(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
        {
            return;
        }
    }
    return;
}

void play()
{
    char Score_f[]={"Score_f.dat"};
    char Print_f[]={"Print_f.txt"};
    char textbuf[]={"Press space to shoot, press Esc to pause the game"};
    check_save();
    fnt = TTF_OpenFont("3d.ttf", 50);
    fnt_1 = TTF_OpenFont("3d.ttf", 30);
    fnt_2 = TTF_OpenFont("3d.ttf", 20);
    fnt_3 = TTF_OpenFont("3d.ttf", 70);
    text_color.r = 0; text_color.g = 255; text_color.b = 0;
    char txtbuf[100];
    image = SDL_LoadBMP( "phon.bmp" );
    if( image == NULL ) printf( "Unable to load image %s! SDL Error: %s\n", "unnamed.bmp", SDL_GetError() );
    SDL_BlitSurface(image, NULL, screen, NULL);
    SDL_Flip(screen);
    Draw_FillRect(screen, 0, 0, 570, 80, 0x000000);
    SDL_Flip(screen);
    int x = 5, y = 5;
    textline.set_text(textbuf,x,y);
    textline.draw_text(fnt_2);
    x = 5; y = 5+20+5;
    strcpy(textbuf, "Use the keys <-- and --> to move left or right");
    textline.set_text(textbuf,x,y);
    textline.draw_text(fnt_2);
    x = 5; y = 5+20+5+20+5;
    strcpy(textbuf, "Destroy all enemy ships!");
    textline.set_text(textbuf,x,y);
    textline.draw_text(fnt_2);
    x=450;
    strcpy(textbuf,"score:");
    textline.set_text(textbuf,x,y);
    textline.draw_text(fnt_2);
    dest.x=520; dest.y=5+20+5+20+5;
    char str[5];
    sprintf(str, "%d", SCORE);
    text_surface = TTF_RenderUTF8_Solid(fnt_2, str, Score_num);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    irect.x=240; irect.y=530;
    if(SAVE==1)
    {
        irect.x=save_me_x;
        irect.y=save_me_y;
    }
    image = SDL_LoadBMP( "me.bmp" );
    if( image == NULL ) printf( "Unable to load image %s! SDL Error: %s\n", "unnamed.bmp", SDL_GetError() );
    SDL_BlitSurface(image, NULL, screen, &irect);
    SDL_Flip(screen);
    int nextstep=1;
    int count=1, number, rest, coord_x, speed;
    thread = SDL_CreateThread(Draw_Shuttle, NULL);
    while(nextstep!=0)
    {
        int z=MyShuttle.do_me();
        if (z==1)
        {
            save(save_me_x, save_me_y, save_enemy_x, save_enemy_y, save_speed, SCORE);
            SDL_KillThread( thread );
            nextstep=0;
        }
        if(PLAY==1) //GAME OVER
        {
            SDL_KillThread( thread );
            edit(Score_f);
            nextstep=0;
        }
    }
    Sleep(400);
    return;
}

void draw_menu_s()
{
    char Score_f[]={"Score_f.dat"};
    char Print_f[]={"Print_f.txt"};
    fnt = TTF_OpenFont("3d.ttf", 50);
    fnt_1 = TTF_OpenFont("3d.ttf", 30);
    fnt_2 = TTF_OpenFont("3d.ttf", 20);
    fnt_3 = TTF_OpenFont("3d.ttf", 70);
    char textbuf[50]={"Enter your gaming name and press Enter"};
    int x=60, y=200;
    textline.set_text(textbuf, x, y);
    textline.draw_text(fnt);
    SDL_Flip(screen);
    image = SDL_LoadBMP( "phon.bmp" );
    if( image == NULL ) printf( "Unable to load image %s! SDL Error: %s\n", "unnamed.bmp", SDL_GetError() );
    SDL_BlitSurface(image, NULL, screen, NULL);
    x=210; y=50;
    strcpy(textbuf,"Menu");
    textline.set_text(textbuf, x, y);
    textline.draw_text(fnt);
    x = 170; y = 140;
    strcpy(textbuf,"Play");
    Play.set_text(textbuf, x, y);
    Play.draw_text(fnt_1);
    x = 170; y = y + 105;
    strcpy(textbuf,"Change player");
    Change_player.set_text(textbuf, x, y);
    Change_player.draw_text(fnt_1);
    x = 170; y = y + 105;
    strcpy(textbuf,"Results");
    Scores.set_text(textbuf, x, y);
    Scores.draw_text(fnt_1);
    x = 170; y = y + 105;
    strcpy(textbuf,"Rules");
    Rules.set_text(textbuf, x, y);
    Rules.draw_text(fnt_1);
    x = 170; y = y + 105;
    strcpy(textbuf,"Exit");
    Exit.set_text(textbuf, x, y);
    Exit.draw_text(fnt_1);
    //images on buttons
    x=90; y=125;
    strcpy(textbuf,"3m.bmp");
    MB1.set_image(textbuf, x, y);
    MB1.draw_image(screen);
    x=90; y=y+105;
    strcpy(textbuf,"5m.bmp");
    MB2.set_image(textbuf, x, y);
    MB2.draw_image(screen);
    x=90; y=y+105;
    strcpy(textbuf,"21m.bmp");
    MB3.set_image(textbuf, x, y);
    MB3.draw_image(screen);
    x=90; y=y+105;
    strcpy(textbuf,"18m.bmp");
    MB4.set_image(textbuf, x, y);
    MB4.draw_image(screen);
    x=90; y=y+105;
    strcpy(textbuf,"23m.bmp");
    MB1.set_image(textbuf, x, y);
    MB1.draw_image(screen);
    return;
}

void do_menu_s()
{
    char Score_f[]={"Score_f.dat"};
    char Print_f[]={"Print_f.txt"};
    fnt = TTF_OpenFont("3d.ttf", 50);
    fnt_1 = TTF_OpenFont("3d.ttf", 30);
    fnt_2 = TTF_OpenFont("3d.ttf", 40);
    fnt_3 = TTF_OpenFont("3d.ttf", 70);
    draw_menu_s();
    while(SDL_WaitEvent(&event))
    {
        if(event.type == SDL_QUIT ||(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
        {
            TTF_CloseFont(fnt);
            SDL_Quit();
            return;
        }
        if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if( ( x >= 120 ) && ( x <= 120 + 510 ) && ( y >= 330 ) && ( y <= 330 + 70 ) )
            {
                Scores.change_click(fnt_1);
                draw_score();
                draw_menu_s();
                continue;
            }
        }
        //Play
        if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int x, y;
            SDL_GetMouseState(&x, &y); // ???????? ?????????? ????
            if( ( x >= 120 ) && ( x <= 120 + 510 ) && ( y >= 120 ) && ( y <= 120 + 70 ) )
            {
                Play.change_click(fnt_1);
                play();
                PLAY=0;
                looser=0;
                SCORE=0;
                if (SAVE==0) draw_menu_s();
                else draw_menu_s();
                continue;
            }
        }
        //Change player
        if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int x, y;
            SDL_GetMouseState(&x, &y); // ???????? ?????????? ????
            if( ( x >= 120 ) && ( x <= 120 + 510 ) && ( y >= 225 ) && ( y <= 225 + 70 ) )
            {
                Change_player.change_click(fnt_1);
                draw_change_player(Score_f);
                if (SAVE==0) draw_menu_s();
                else draw_menu_s();
                continue;

            }
        }
        //Rules
        if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int x, y;
            SDL_GetMouseState(&x, &y); // ???????? ?????????? ????
            if( ( x >= 120 ) && ( x <= 120 + 510 ) && ( y >= 435 ) && ( y <= 435 + 70 ) )
            {
                Rules.change_click(fnt_1);
                draw_rules();
                if (SAVE==0) draw_menu_s();
                else draw_menu_s();
                continue;

            }
        }
        //Exit
        if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int x, y;
            SDL_GetMouseState(&x, &y); // ???????? ?????????? ????
            if( ( x >= 120 ) && ( x <= 120 + 510 ) && ( y >= 540 ) && ( y <= 540 + 70 ) )
            {
                Exit.change_click(fnt_1);
                return;
            }
        }
        //
    }
}

void draw_beginning()
{
    text_color.r = 255; text_color.g = 255; text_color.b = 255;
    char textbuf[100];
    image_phon = SDL_LoadBMP( "phon.bmp" );
    if( image_phon == NULL ) printf( "Unable to load image %s! SDL Error: %s\n", "unnamed.bmp", SDL_GetError() );
    if ( !screen )
    {
        printf("Unable to set video: %s\n", SDL_GetError());
        return;
    }
    SDL_Rect dstarea;
    image = SDL_LoadBMP( "bestname.bmp" );
    if( image == NULL ) printf( "Unable to load image %s! SDL Error: %s\n", "unnamed.bmp", SDL_GetError() );
    SDL_BlitSurface(image, NULL, screen, NULL);
    SDL_Flip(screen);
    int x = 150; int y = 55;
    strcpy(textbuf,"I964");
    textline.set_text(textbuf,x,y);
    textline.draw_text(fnt);
    x = 150; y = y + 55;
    strcpy(textbuf,"Korolieva");
    textline.set_text(textbuf,x,y);
    textline.draw_text(fnt);
    x = 150; y = y + 55;
    strcpy(textbuf,"Julie");
    textline.set_text(textbuf,x,y);
    textline.draw_text(fnt);
    text_color.r = 0; text_color.g = 255; text_color.b = 0;
    x = 150; y = 265;
    strcpy(textbuf,"Press TAB");
    textline.set_text(textbuf,x,y);
    textline.draw_text(fnt);
    x = 150; y = 320;
    strcpy(textbuf,"to start");
    textline.set_text(textbuf,x,y);
    textline.draw_text(fnt);
    while(SDL_WaitEvent(&event))
    {
        if(event.type == SDL_QUIT ||(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
        {
           zzz=1;
           return;
        }
        if((event.type==SDL_KEYDOWN)&&(event.key.keysym.sym==SDLK_TAB))
        {
            Draw_FillRect(screen, 55, 195, 460, 80, 0x000000);
            SDL_Flip(screen);
            Draw_Rect(screen, 55, 195, 460, 80, 0x00FF00);
            SDL_Flip(screen);
            dest.x = 60; dest.y = 200;
            text_surface = TTF_RenderUTF8_Solid(fnt_2, "Enter your gaming name and press Enter", text_color);
            if(text_surface){
            SDL_BlitSurface(text_surface, NULL, screen, &dest);
            SDL_FreeSurface(text_surface); text_surface = NULL;
            }
            SDL_Flip(screen);
            return;
        }
    }
}

void draw_score()
{
    char Score_f[]={"Score_f.dat"};
    char Print_f[]={"Print_f.txt"};
    fnt = TTF_OpenFont("3d.ttf", 50);
    fnt_1 = TTF_OpenFont("3d.ttf", 30);
    fnt_2 = TTF_OpenFont("3d.ttf", 20);
    fnt_3 = TTF_OpenFont("3d.ttf", 70);
    image = SDL_LoadBMP( "phon.bmp" );
    if( image == NULL ) printf( "Unable to load image %s! SDL Error: %s\n", "unnamed.bmp", SDL_GetError() );
    SDL_BlitSurface(image, NULL, screen, NULL);
    dest.x = 210; dest.y = 50;
    text_surface = TTF_RenderUTF8_Solid(fnt, "Score", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    Res_Score_y=140;
    show(Score_f);
    //draw buttons
    dest.x = 440; dest.y = 590;
    text_surface = TTF_RenderUTF8_Solid(fnt_1, "Delete", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    dest.x = 25; dest.y = 590;
    text_surface = TTF_RenderUTF8_Solid(fnt_1, "Print", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    //
    int nextstep=1;
    while(nextstep!=0)
    {
        if(SDL_PollEvent(&event))
        {
            //Exit
            if(event.type == SDL_QUIT || ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            {
                nextstep = 0;
            }
            if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if( ( x >= 0 ) && ( x <= 0 + 150 ) && ( y >= 560 ) && ( y <= 560 + 60 ) )
                {
                    //print
                    print_file(Score_f, Print_f);
                    return;
                }
                if( ( x >= 415 ) && ( x <= 415 + 150 ) && ( y >= 560 ) && ( y <= 560 + 60 ) )
                {
                    //delete
                    delete_file(Score_f);
                    return;
                }
            }
        }
    }
return;
}

void delete_file(char* file)
{
    FILE * hhh;
    struct players new_pl;
    if((hhh=fopen(file, "wb"))==NULL)
    {
        logi("666");
        perror("Error open file");
        system("pause");
        return;
    }
    fclose(hhh);
    return;
}

void draw_change_player(char* file)
{
    image = SDL_LoadBMP( "phon.bmp" );
    if( image == NULL ) printf( "Unable to load image %s! SDL Error: %s\n", "unnamed.bmp", SDL_GetError() );
    SDL_BlitSurface(image, NULL, screen, NULL);
    fnt_1 = TTF_OpenFont("3d.ttf", 50);
    fnt = TTF_OpenFont("3d.ttf", 30);
    dest.x = 100; dest.y = 50;
    text_color.r=0; text_color.g=255; text_color.b=0;
    text_surface = TTF_RenderUTF8_Solid(fnt_1, "Change player", text_color);
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &dest);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    int res=0;
    int nnn=0;
    char str1[30];
    dest.x=100; dest.y=140; dest.h=40; dest.w=365;
    FILE* f;
    struct players new_pl;
    if((f=fopen (file, "rb"))==NULL)
    {
        perror("Error open file");
        system("pause");
        return;
    }
    while((fread(&new_pl, sizeof(new_pl), 1, f)==1)&&(nnn<=8))
    {
        text_surface = TTF_RenderUTF8_Solid(fnt, new_pl.name, text_color);
        if(text_surface){
        SDL_BlitSurface(text_surface, NULL, screen, &dest);
        SDL_FreeSurface(text_surface); text_surface = NULL;
        }
        SDL_Flip(screen);
        nnn++;
        dest.y+=30;
    }
    while(SDL_WaitEvent(&event))
    {
        if(event.type == SDL_QUIT ||(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
        {
            return;
        }
        if(event.type==SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            if( ( x >= 90 ) && ( x <= 90 + 400 ) && ( y >= 130 ) && ( y <= 160 ) ) res=1;
            if( ( x >= 90 ) && ( x <= 90 + 400 ) && ( y >= 160 ) && ( y <= 190 ) ) res=2;
            if( ( x >= 90 ) && ( x <= 90 + 400 ) && ( y >= 190 ) && ( y <= 120 ) ) res=3;
            if( ( x >= 90 ) && ( x <= 90 + 400 ) && ( y >= 120 ) && ( y <= 150 ) ) res=4;
            if( ( x >= 90 ) && ( x <= 90 + 400 ) && ( y >= 150 ) && ( y <= 180 ) ) res=5;
            if( ( x >= 90 ) && ( x <= 90 + 400 ) && ( y >= 180 ) && ( y <= 210 ) ) res=6;
            if( ( x >= 90 ) && ( x <= 90 + 400 ) && ( y >= 210 ) && ( y <= 240 ) ) res=7;
            if( ( x >= 90 ) && ( x <= 90 + 400 ) && ( y >= 240 ) && ( y <= 540 ) ) res=8;
            fseek(f, 0, SEEK_SET);   /* ??????? ? ?????? ????? */
            while(fread(&new_pl, sizeof(new_pl), 1, f)==1)
            {
                    res--;
                    if(res==0) memcpy( NOW_NAME, new_pl.name,sizeof(char)*30 );
            }
            fclose(f);
            return;
            break;
        }
    }
    fclose(f);
    return;
}

void print_file(char* file, char* file_out)
{
    char str1[30];
    char sp[]={"--"};
    char sp2[]={'\n'};
    FILE* f;
    FILE* g;
    struct players new_pl;
    if((f=fopen (file, "rb"))==NULL)
    {
        perror("Error open file");
        system("pause");
        return;
    }
    logi("11");
    delete_file(file_out);
    if((g=fopen (file_out, "wb"))==NULL)
    {
        perror("Error open file");
        system("pause");
        return;
    }
    while(fread(&new_pl, sizeof(new_pl), 1, f)==1)
    {
        fprintf(g, "%s %d\n", new_pl.name, new_pl.score);
    }
    fclose(f);
    return;
}

void save(int a, int b, int c, int d, int e, int g)
{
    FILE *f;
    int pos, k=0;
    struct players new_pl;
    system("CLS");
    if((f=fopen("game.dat", "ab"))==NULL)
    {
        perror("Error open file");
        system("pause");
        return;
    }
    fwrite(&NOW_NAME, sizeof(char)*30, 1, f);
    fwrite(&a, sizeof(int), 1, f);
    fwrite(&b, sizeof(int), 1, f);
    fwrite(&c, sizeof(int), 1, f);
    fwrite(&d, sizeof(int), 1, f);
    fwrite(&e, sizeof(int), 1, f);
    fwrite(&g, sizeof(int), 1, f);
    memcpy( save_name, NOW_NAME, sizeof(char)*30 );
    SAVE=1;
fclose(f);
return;
}

