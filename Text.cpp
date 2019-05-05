SDL_Surface* text_surface = NULL;
SDL_Color text_color;
SDL_Color Score_num;
SDL_Surface* screen = SDL_SetVideoMode(570, 650, 32, SDL_ANYFORMAT);

class Text
{
public:
    char textbuf[100];
    int coord_x, coord_y;
    Text(){};
    ~Text(){};
    void draw_text(TTF_Font *);
    void set_text(char*, int, int);
};

void Text::draw_text(TTF_Font *fnu)
{
    text_surface = TTF_RenderUTF8_Solid(fnu, textbuf, text_color);
    SDL_Rect coord;
    coord.x=coord_x;
    coord.y=coord_y;
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &coord);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
}

void Text::set_text(char* txt, int x, int y)
{
    strcpy(textbuf, txt);
    coord_x=x;
    coord_y=y;
}

class Button:public Text
{
public:
    Button(){};
    ~Button(){};
    void change_click(TTF_Font *);
};

void Button::change_click(TTF_Font *fnu)
{
    Score_num.r=255;
    Score_num.b=0;
    Score_num.g=0;
    text_surface = TTF_RenderUTF8_Solid(fnu, textbuf, Score_num);
    SDL_Rect coord;
    coord.x=coord_x;
    coord.y=coord_y;
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &coord);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
    Sleep(250);
    text_surface = TTF_RenderUTF8_Solid(fnu, textbuf, text_color);
    coord.x=coord_x;
    coord.y=coord_y;
    if(text_surface){
    SDL_BlitSurface(text_surface, NULL, screen, &coord);
    SDL_FreeSurface(text_surface); text_surface = NULL;
    }
    SDL_Flip(screen);
}

Text textline;
Button Play;
Button Change_player;
Button Rules;
Button Exit;
Button Scores;
Button Delete;
Button Print;
