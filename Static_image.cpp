SDL_Surface* image = NULL;
SDL_Surface* image_phon = NULL;
SDL_Surface* download=NULL;
SDL_Surface* temp = SDL_SetVideoMode(80, 120, 32, SDL_ANYFORMAT);

SDL_Event event;
SDL_Rect irect;
SDL_Rect frame_tmp, frame_dst;
SDL_Rect dest;

TTF_Font *fnt;
TTF_Font *fnt_1;
TTF_Font *fnt_2;
TTF_Font *fnt_3;

int KILL=0;
int PLAY=0;
int DESTROY=0;
int SCORE=0;
int looser=0;
int global_x=0;
int global_y=0;
int global_speed=0;
int coord_x;

int save_me_x=0;
int save_me_y=0;
int save_enemy_x=0;
int save_enemy_y=0;
int save_speed=0;
char save_name[30];
int SAVE=0;

class Static_image
{
public:
    char name_of_image[30];
    int coord_x;
    int coord_y;
    Static_image(){};
    ~Static_image(){};
    void set_image(char*, int, int);
    void draw_image(SDL_Surface*);
};

void Static_image::set_image(char* txt, int x, int y)
{
    strcpy(name_of_image, txt);
    download=SDL_LoadBMP(name_of_image);
    coord_x=x;
    coord_y=y;
}

void Static_image::draw_image(SDL_Surface *scrscrscr)
{
    SDL_Rect coord;
    coord.x=coord_x;
    coord.y=coord_y;
    SDL_BlitSurface(download, NULL, scrscrscr, &coord);
    SDL_Flip(screen);
}

class Me:public Static_image
{
public:
    Me(){};
    ~Me(){};
    int do_me();
};

class Enemy:public Static_image
{
public:
    int speed;
    int number;
    Enemy(){};
    ~Enemy(){};
    void do_enemy();
};

Static_image my;

int Me::do_me()
{
    char str[100];
    char Score_f[]={"Score_f.dat"};
    char Print_f[]={"Print_f.txt"};
    char textbuf[]={"Press space to shoot, press Esc to pause the game"};
    fnt = TTF_OpenFont("3d.ttf", 50);
    fnt_1 = TTF_OpenFont("3d.ttf", 30);
    fnt_2 = TTF_OpenFont("3d.ttf", 20);
    fnt_3 = TTF_OpenFont("3d.ttf", 70);
    text_color.r = 0; text_color.g = 255; text_color.b = 0;
    if(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT || ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            {
                save_me_x=irect.x;
                save_me_y=irect.y;
                return 1;
            }
        while(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT)
            {
                if(irect.x<490)
                {
                    irect.x++;
                    //save_me_x=irect.x;
                    //save_me_y=irect.y;
                    frame_dst.x=irect.x-1;
                    frame_dst.y=irect.y;
                    frame_dst.h=120;
                    frame_dst.w=80;
                    SDL_BlitSurface(image_phon, &frame_dst, temp, &frame_dst);
                    SDL_BlitSurface(temp, &frame_dst, screen, &frame_dst);
                    SDL_BlitSurface(image, NULL, screen, &irect);
                    SDL_Flip(screen);
                    Sleep(2);
                }
                if(SDL_PollEvent(&event)) if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT) break;
            }
            while(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT)
            {
                irect.x--;
                frame_dst.x=irect.x+1;
                frame_dst.y=irect.y;
                frame_dst.h=120;
                frame_dst.w=80;
                SDL_BlitSurface(image_phon, &frame_dst, temp, &frame_dst);
                SDL_BlitSurface(temp, &frame_dst, screen, &frame_dst);
                SDL_BlitSurface(image, NULL, screen, &irect);
                SDL_Flip(screen);
                Sleep(2);
                if(SDL_PollEvent(&event)) if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT) break;
            }
            while(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
            {
                Draw_FillRect(screen, irect.x+40, 80, 3, 450, 0x00FF00);
                SDL_Flip(screen);
                frame_tmp.x=irect.x+40;
                frame_tmp.y=80;
                frame_tmp.h=450;
                frame_tmp.w=3;
                SDL_BlitSurface(image_phon, &frame_tmp, temp, &frame_tmp);
                SDL_BlitSurface(temp, &frame_tmp, screen, &frame_tmp);
                if(irect.x+40>global_x && irect.x+40<global_x+70)
                {
                    DESTROY=irect.x+40;
                    looser=1;
                    SCORE++;
                    SDL_Rect score;
                    score.x=520; score.y=5+20+5+20+5;
                    Draw_FillRect(screen, 520, 5+2+5+20+5+15, 40, 25, 0x000000);
                    sprintf(str, "%d", SCORE);
                    text_surface = TTF_RenderUTF8_Solid(fnt_2, str, Score_num);
                    if(text_surface){
                    SDL_BlitSurface(text_surface, NULL, screen, &score);
                    SDL_FreeSurface(text_surface); text_surface = NULL;
                    }
                    SDL_Flip(screen);
                    break;
                }
                if(SDL_PollEvent(&event)) if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE) break;
                }
    }
        if(PLAY==1) //GAME OVER
        {
            //SDL_KillThread( thread );
            SAVE=0;
            frame_dst.x=irect.x-1;
            frame_dst.y=irect.y;
            frame_dst.h=120;
            frame_dst.w=80;
            SDL_BlitSurface(image_phon, &frame_dst, temp, &frame_dst);
            SDL_BlitSurface(temp, &frame_dst, screen, &frame_dst);
            SDL_BlitSurface(image, NULL, screen, &irect);
            SDL_Flip(screen);
            image=SDL_LoadBMP("bam.bmp");
            SDL_BlitSurface(image, NULL, screen, &irect);
            SDL_Flip(screen);
            dest.x = 100; dest.y = 340;
            text_surface = TTF_RenderUTF8_Solid(fnt_3, "GAME OVER", text_color);
            if(text_surface){
            SDL_BlitSurface(text_surface, NULL, screen, &dest);
            SDL_FreeSurface(text_surface); text_surface = NULL;
            }
            SDL_Flip(screen);
            //edit(Score_f);
            //nextstep=0;
        }
        return 0;
}

Static_image en;

void Enemy::do_enemy()
{
    SDL_Rect Ship, frame_tmp, frame_dst;
    Score_num.r=0xFF; Score_num.g=0xD7; Score_num.b=0x00;
    image_phon = SDL_LoadBMP( "phon.bmp" );
    if( image_phon == NULL ) printf( "Unable to load image %s! SDL Error: %s\n", "unnamed.bmp", SDL_GetError() );
    while(KILL==0)
    {
        number=rand() % 23 + 1;
        coord_x=rand() % 480;
        //save_enemy_x=coord_x;
        global_x=coord_x;
        speed=rand() % 3 + 1;
        if(SAVE==1)
        {
            Ship.x=save_enemy_x;
            Ship.y=save_enemy_y;
            speed=save_speed;
            coord_x=save_enemy_x;
            global_x=save_enemy_x;

        }
        else save_enemy_y=120;
        SAVE=0;
        switch(number)
        {
           case 1: en.set_image("1.bmp", Ship.x, save_enemy_y);break;
           case 2: en.set_image("2.bmp", coord_x, save_enemy_y);break;
           case 3: en.set_image("3.bmp", coord_x, save_enemy_y);break;
           case 4: en.set_image("4.bmp", coord_x, save_enemy_y);break;
           case 5: en.set_image("5.bmp", coord_x, save_enemy_y);break;
           case 6: en.set_image("6.bmp", coord_x, save_enemy_y);break;
           case 7: en.set_image("7.bmp", coord_x, save_enemy_y);break;
           case 8: en.set_image("8.bmp", coord_x, save_enemy_y);break;
           case 9: en.set_image("9.bmp", coord_x, save_enemy_y);break;
           case 10: en.set_image("10.bmp", coord_x, save_enemy_y);break;
           case 11: en.set_image("11.bmp", coord_x, save_enemy_y);break;
           case 12: en.set_image("12.bmp", coord_x, save_enemy_y);break;
           case 13: en.set_image("13.bmp", coord_x, save_enemy_y);break;
           case 14: en.set_image("14.bmp", coord_x, save_enemy_y);break;
           case 15: en.set_image("15.bmp", coord_x, save_enemy_y);break;
           case 16: en.set_image("16.bmp", coord_x, save_enemy_y);break;
           case 17: en.set_image("17.bmp", coord_x, save_enemy_y);break;
           case 18: en.set_image("18.bmp", coord_x, save_enemy_y);break;
           case 19: en.set_image("19.bmp", coord_x, save_enemy_y);break;
           case 20: en.set_image("20.bmp", coord_x, save_enemy_y);break;
           case 21: en.set_image("21.bmp", coord_x, save_enemy_y);break;
           case 22: en.set_image("22.bmp", coord_x, save_enemy_y);break;
           case 23: en.set_image("23.bmp", coord_x, save_enemy_y);break;
       }
       if( download == NULL ) printf( "Unable to load image %s! SDL Error: %s\n", "unnamed.bmp", SDL_GetError() );
       switch(speed)
       {
           case 1: speed=3;break;
           case 2: speed=5;break;
           case 3: speed=8;break;
       }
       save_speed=speed;
       if(looser==0)
       {
           frame_tmp.x=0;
           frame_tmp.y=0;
           frame_tmp.h=100;
           frame_tmp.w=80;
           Ship.x=coord_x;
           Ship.y=save_enemy_y;
           Ship.h=100;
           Ship.w=80;
           int nextstep=1;
           //????? ??????????
           //
           en.draw_image(screen);
           //SDL_BlitSurface(download,NULL,screen,&Ship);
           //SDL_Flip(screen);
           save_enemy_x=coord_x;
           global_speed=speed;
           //
           while(Ship.y!=455 && looser==0)
           {
               Ship.y++;
               save_enemy_y=Ship.y;
               frame_dst.x=Ship.x;
               frame_dst.y=Ship.y-1;
               frame_dst.h=100;
               frame_dst.w=70;
               SDL_BlitSurface(image_phon, &frame_dst, temp, &frame_dst);
               SDL_BlitSurface(temp, &frame_dst, screen, &frame_dst);
               SDL_BlitSurface(download, NULL, screen, &Ship);
               SDL_Flip(screen);
               Sleep(speed);
           }
           if (Ship.y==455)
           {
               frame_dst.x=Ship.x;
           frame_dst.y=Ship.y;
           frame_dst.h=100;
           frame_dst.w=70;
           SDL_BlitSurface(image_phon, &frame_dst, temp, &frame_dst);
           SDL_BlitSurface(temp, &frame_dst, screen, &frame_dst);
           SDL_Flip(screen);
           PLAY=1;
           looser=0;
           }
            //looser=1;
       }
       if(looser==1)
       {
            Draw_FillRect(screen, DESTROY, 80, 3, 450, 0x00FF00);
            SDL_Flip(screen);
            Sleep(30);
            frame_dst.x=DESTROY;
            frame_dst.y=80;
            frame_dst.h=450;
            frame_dst.w=3;
            SDL_BlitSurface(image_phon, &frame_dst, temp, &frame_dst);
            SDL_BlitSurface(temp, &frame_dst, screen, &frame_dst);
            frame_dst.x=Ship.x;
            frame_dst.y=Ship.y;
            frame_dst.h=100;
            frame_dst.w=70;
            SDL_BlitSurface(image_phon, &frame_dst, temp, &frame_dst);
            SDL_BlitSurface(temp, &frame_dst, screen, &frame_dst);
            download = SDL_LoadBMP( "boom.bmp" );
            SDL_BlitSurface(download, NULL, screen, &frame_dst);
            SDL_Flip(screen);
            Sleep(250);
            frame_dst.h=65;
            frame_dst.w=95;
            SDL_BlitSurface(image_phon, &frame_dst, temp, &frame_dst);
            SDL_BlitSurface(temp, &frame_dst, screen, &frame_dst);
            SDL_Flip(screen);
            looser=0;
       }
       if(Ship.y==455)
       {
           frame_dst.x=Ship.x;
           frame_dst.y=Ship.y;
           frame_dst.h=100;
           frame_dst.w=70;
           SDL_BlitSurface(image_phon, &frame_dst, temp, &frame_dst);
           SDL_BlitSurface(temp, &frame_dst, screen, &frame_dst);
           SDL_Flip(screen);
           PLAY=1;
           looser=0;
       }
    }
}

Static_image MB1;
Static_image MB2;
Static_image MB3;
Static_image MB4;
Static_image MB5;

Me MyShuttle;
Enemy WannaCry;
