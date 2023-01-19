#include <assert.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#define MIN(x,y) (((x) < (y)) ? (x) : (y))

int AUX_WaitEventTimeoutCount(SDL_Event* evt, int* espera) {
    int ms = SDL_GetTicks();
	int event = SDL_WaitEventTimeout(evt, *espera);
	if (event){
		*espera -= (SDL_GetTicks() - ms);
		if(*espera < 0) {
			*espera = 0;
		}
    }
    return event;
}

struct objetos{
    SDL_Rect r;
    SDL_bool IsCollind;
    SDL_Rect Sprite;
};

typedef struct {
    char * text;
    TTF_Font * font;
    SDL_Color color;
    SDL_Rect r;
} screenTex;

enum tela {menu=0,jogo,fim,morte};
/*
int ShowMenu(SDL_Surface* screen,TTF_Font* fonte){
    //Inicialização
    //int MouseX,MouseY;
    
    //SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0x00);
    //SDL_RenderClear(ren);
    Uint32 espera;
    const int NUMMENU = 2;
    const char* Labels[NUMMENU];
    Labels[0] = "Jogar";
    Labels[1] = "Sair";
    SDL_Surface* Menus[NUMMENU];
    bool selected[NUMMENU];
    for(int i = 0; i< NUMMENU;i++){
        selected[i] = 0;
    }
    SDL_Color color[2] = {{255,255,255},{255,0,0}};
    //Construção
    Menus[0] = TTF_RenderText_Solid(fonte,Labels[0],color[0]);
    Menus[1] = TTF_RenderText_Solid(fonte,Labels[1],color[1]);
    //Posição do menu na tela
    SDL_Rect posicao[NUMMENU];
    posicao[0].x = screen->clip_rect.w/2 - Menus[0]->clip_rect.w/2;
    posicao[0].y = screen->clip_rect.h/2 - Menus[0]->clip_rect.h;
    posicao[1].x = screen->clip_rect.w/2 - Menus[0]->clip_rect.w/2;
    posicao[1].y = screen->clip_rect.h/2 + Menus[0]->clip_rect.h;


    SDL_Event evt;
    SDL_Point Mouse;
    SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0x00,0x00,0x00));
    while(1){
        espera = SDL_GetTicks();
        while (SDL_PollEvent(&evt)){
            switch(evt.type){
                case SDL_QUIT:
                    for (int i = 0;i<NUMMENU;i++){
                        SDL_FreeSurface(Menus[i]);
                    }
                    return 1;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&Mouse.x,&Mouse.y);
                    for (int i = 0;i<NUMMENU;i++){
                        if(SDL_PointInRect(&Mouse, &posicao[i])){
                            if(!selected[i]){
                                selected[i] = 1;
                                SDL_FreeSurface(Menus[i]);
                                Menus[i] = TTF_RenderText_Solid(fonte,Labels[i],color[1]);
                            }
                        }else{
                                if(selected[i]){
                                    selected[i] = 0;
                                    SDL_FreeSurface(Menus[i]);
                                    Menus[i] = TTF_RenderText_Solid(fonte,Labels[i],color[0]);
                                }
                        }
                    }
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&Mouse.x,&Mouse.y);
                    for (int i = 0;i<NUMMENU;i++){
                        if(SDL_PointInRect(&Mouse, &posicao[i])){
                                SDL_FreeSurface(Menus[0]);
                                SDL_FreeSurface(Menus[1]);
                                return i;
                        }break;
                    }
                case SDL_KEYDOWN:
                    if(evt.key.keysym.sym == SDLK_ESCAPE){
                        return 0;
                    }
            }
        }
        for(int i = 0; i < NUMMENU; i++) {
            SDL_BlitSurface(Menus[i],NULL,screen,&posicao[i]);
        }
        //SDL_UpdateTexture(screen);
        if(1000/30 > (SDL_GetTicks() - espera)){
            SDL_Delay(1000/30 - (SDL_GetTicks() - espera));
        }
    }
}  
*/
void ShowMenu2 (SDL_Renderer* ren, int * screen, int * espera) {

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("auxilio/tiny.ttf",50);
    assert(font != NULL);

    SDL_Color Black = {0x00,0x00,0x00,0xFF};
    SDL_Color Grey = {125,125,125,125};
    
    screenTex * MenuTex = malloc(sizeof(*MenuTex) * 3);
    
    MenuTex[0].text = malloc(sizeof("Jogar"));
    MenuTex[0].text = "Jogar";
    MenuTex[0].font = font;
    MenuTex[0].color = Grey;
    MenuTex[0].r = (SDL_Rect) {250,100,100,100};
    
    MenuTex[1].text = malloc(sizeof("Sair"));
    MenuTex[1].text = "Sair";
    MenuTex[1].font = font;
    MenuTex[1].color = Grey;
    MenuTex[1].r = (SDL_Rect) {250,300,100,100};
    
    MenuTex[2].text = malloc(sizeof("Voce morreu"));
    MenuTex[2].text = "Voce morreu";
    MenuTex[2].font = font;
    MenuTex[2].color = Grey;
    MenuTex[2].r = (SDL_Rect) {150,150,300,200};  
    
    Uint32 antes = SDL_GetTicks();
    if(*screen == morte){

        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);   
        struct SDL_Surface * Surface = TTF_RenderText_Solid(MenuTex[2].font,MenuTex[2].text,MenuTex[2].color);
        struct SDL_Texture * Texture = SDL_CreateTextureFromSurface(ren,Surface);
        SDL_RenderCopy(ren,Texture,NULL,&(MenuTex[2].r));
        SDL_FreeSurface(Surface); 
        SDL_DestroyTexture(Texture);
    
    }
    while (*screen == menu){
    
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);   
        
        int i;
        for (i = 0; i < 2; i++){
            struct SDL_Surface * Surface = TTF_RenderText_Solid(MenuTex[i].font,MenuTex[i].text,MenuTex[i].color);
            struct SDL_Texture * Texture = SDL_CreateTextureFromSurface(ren,Surface);
            SDL_RenderCopy(ren,Texture,NULL,&(MenuTex[i].r));
            SDL_FreeSurface(Surface); 
            SDL_DestroyTexture(Texture);
        }
        
        SDL_RenderPresent(ren);
        
        *espera = MAX(0, *espera - (int)(SDL_GetTicks() - antes));
        SDL_Event evt; 
        int isevt = AUX_WaitEventTimeoutCount(&evt, espera);
        antes = SDL_GetTicks();
        SDL_Point Mouse;
        if (isevt){
            switch (evt.type) {
                case SDL_WINDOWEVENT:
                    
                    if(SDL_WINDOWEVENT_CLOSE == evt.window.event){
                        *screen = fim;
                    }
                    break;
                
                case SDL_MOUSEMOTION:
                    MenuTex[0].color = Grey;
                    MenuTex[1].color = Grey;

                    SDL_GetMouseState(&Mouse.x,&Mouse.y);

                    if(SDL_PointInRect(&Mouse,&MenuTex[0].r)){
                            MenuTex[0].color = Black;
                    }else{
                        if(SDL_PointInRect(&Mouse,&MenuTex[1].r)){
                            MenuTex[1].color = Black;
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&Mouse.x,&Mouse.y);

                    if (SDL_PointInRect(&Mouse,&MenuTex[0].r)){
                        *screen = jogo;
                    }else{ 
                        if (SDL_PointInRect(&Mouse,&MenuTex[1].r)){
                            *screen = fim;
                        }
                    }
                    break;
            }
        } else *espera = 100;
        
    }
    
    TTF_CloseFont(font);
    free(MenuTex);
    TTF_Quit();
    
}
void EventsBomberman (SDL_Event* evt, struct objetos* bomberMan,struct objetos* Blocos,SDL_Rect* Bomba, int * sprites){
    SDL_Point mousePosition;
    int NumeroBlocos;
    SDL_Rect TesteColisao = bomberMan->r;
    int tamanho = 0;
    for(tamanho;tamanho<=74;tamanho++){
        Blocos[tamanho].IsCollind = SDL_FALSE;
    }
    switch(evt->type){
        case(SDL_KEYDOWN):
        SDL_PumpEvents();
            switch(evt->key.keysym.sym){
                case SDLK_UP:
                    if(*sprites == 0){
                        bomberMan->Sprite = (SDL_Rect) {50,16,12,16};
                    }
                    if(*sprites == 1){
                        bomberMan->Sprite = (SDL_Rect) {66,16,12,16};
                    }
                    if(*sprites == 2){
                        bomberMan->Sprite = (SDL_Rect) {82,16,12,16};
                    }
                    if(bomberMan->r.y <= 45){
                        break;
                    }
                    TesteColisao.y -=5;
                    for (NumeroBlocos=0;NumeroBlocos<2;NumeroBlocos++){
                        if((SDL_HasIntersection(&TesteColisao,&Blocos[NumeroBlocos].r))){
                            Blocos[NumeroBlocos].IsCollind = SDL_TRUE;
                        }
                    }
                    //SDL_Log("%d",Blocos[0].IsCollind);
                    if(!(Blocos[NumeroBlocos].IsCollind)){
                        bomberMan->r.y -= 5;
                    }
                    break;
                case SDLK_DOWN:
                    if(*sprites == 0){
                        bomberMan->Sprite = (SDL_Rect) {50,0,12,16};
                    }
                    if(*sprites == 1){
                        bomberMan->Sprite = (SDL_Rect) {66,0,12,16};
                    }
                    if(*sprites == 2){
                        bomberMan->Sprite = (SDL_Rect) {82,0,12,16};
                    }
                    if(bomberMan->r.y >= 520){
                        break;
                    }
                    TesteColisao.y += 5;
                    for (NumeroBlocos=0;NumeroBlocos<2;NumeroBlocos++){
                        if((SDL_HasIntersection(&TesteColisao,&Blocos[NumeroBlocos].r))){
                            Blocos[NumeroBlocos].IsCollind = SDL_TRUE;
                        }
                    }
                    //SDL_Log("%d",Blocos[0].IsCollind);
                    if(!(Blocos[NumeroBlocos].IsCollind)){
                        bomberMan->r.y += 5;
                    }
                    break;
                case SDLK_LEFT:
                    if(*sprites == 0){
                        bomberMan->Sprite = (SDL_Rect) {0,0,14,16};
                    }
                    if(*sprites == 1){
                        bomberMan->Sprite = (SDL_Rect) {17,0,11,16};
                    }
                    if(*sprites == 2){
                        bomberMan->Sprite = (SDL_Rect) {33,0,13,16};
                    }
                    if(bomberMan->r.x == 20){
                        break;
                    }
                    TesteColisao.x -= 5;
                    for (NumeroBlocos=0;NumeroBlocos<2;NumeroBlocos++){
                        if((SDL_HasIntersection(&TesteColisao,&Blocos[NumeroBlocos].r))){
                            Blocos[NumeroBlocos].IsCollind = SDL_TRUE;
                        }
                    }
                    //SDL_Log("%d",Blocos[NumeroBlocos].IsCollind);
                    if(!(Blocos[NumeroBlocos].IsCollind)){
                        bomberMan->r.x -= 5;
                    }
                    break;
                case SDLK_RIGHT:
                    if(*sprites == 0){
                        bomberMan->Sprite = (SDL_Rect) {2,16,14,16};
                    }
                    if(*sprites == 1){
                        bomberMan->Sprite = (SDL_Rect) {20,16,10,16};
                    }
                    if(*sprites == 2){
                        bomberMan->Sprite = (SDL_Rect) {33,16,14,16};
                    }
                    if(bomberMan->r.x >= 565){
                        break;
                    }
                    TesteColisao.x += 5;
                    for (NumeroBlocos=0;NumeroBlocos<2;NumeroBlocos++){
                        if((SDL_HasIntersection(&TesteColisao,&Blocos[NumeroBlocos].r))){
                            Blocos[NumeroBlocos].IsCollind = SDL_TRUE;
                        }
                    }
                    //SDL_Log("%d",Blocos[0].IsCollind);
                    if(!(Blocos[NumeroBlocos].IsCollind)){
                        bomberMan->r.x += 5;
                    }
                    break;
                case SDLK_z:
                    int contadorBomba = 0;
                    if(contadorBomba == 0){
                        *Bomba = (SDL_Rect) {bomberMan->r.x,bomberMan->r.y,15,25};
                    }
                    break;
                break;
            }

        default:
            break;
    }
}

void EventsInimigos (int isevt,struct objetos* Inimigos,int* espera){
    int NumeroInimigos;
    if(!isevt){
        *espera = 600;
        for(NumeroInimigos = 0;NumeroInimigos<=2;NumeroInimigos++){
            if(Inimigos[NumeroInimigos].r.x <= 564 && Inimigos[NumeroInimigos].r.y == 50){
                Inimigos[NumeroInimigos].r.x += 4;
            }
        }
        for(NumeroInimigos = 0;NumeroInimigos<=2;NumeroInimigos++){
            if(Inimigos[NumeroInimigos].r.y <= 238 && Inimigos[NumeroInimigos].r.x == 564){
                Inimigos[NumeroInimigos].r.y += 4;
            }
        }
        for(NumeroInimigos = 0;NumeroInimigos<=2;NumeroInimigos++){
            if(Inimigos[NumeroInimigos].r.y == 238 && Inimigos[NumeroInimigos].r.x >= 252){
                Inimigos[NumeroInimigos].r.x -= 4;
            }
        }
        for(NumeroInimigos = 0;NumeroInimigos<=2;NumeroInimigos++){
            if(Inimigos[NumeroInimigos].r.y >= 50 && Inimigos[NumeroInimigos].r.x == 252){
                Inimigos[NumeroInimigos].r.y -= 4;
            }
        }

    }
}

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    TTF_Init();
    SDL_Window* win = SDL_CreateWindow("BomberMan NES",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         600, 600, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* IMGSprites = IMG_LoadTexture(ren, "auxilio/NES_Bomberman_GeneralSprites.png");
    SDL_Texture* IMGbackGround = IMG_LoadTexture(ren, "auxilio/NES_Bomberman_Playfield.png");
    assert(IMGbackGround != NULL);

    /* EXECUÇÃO */
    int espera = 600;
    int screen = menu;
    int sprites = 0;
    // BackGRound
    SDL_Rect BackGround = (SDL_Rect) {0,0,600,600};
    SDL_Rect LimitacaoBackGround = (SDL_Rect) {0,0,496,208};
    
    // Criação do BomberMan
    struct objetos bomberMan;
    //bomberMan.r = (SDL_Rect) {20,50,15,30};
    bomberMan.r = (SDL_Rect) {20,50,45,45};
    bomberMan.IsCollind = SDL_FALSE;
    bomberMan.Sprite = (SDL_Rect) {67,0,10,16};
    
    // Criação da bomba
    SDL_Rect Bomba;
    SDL_Rect spriteBomba = (SDL_Rect) {16,48,16,16};
    
    // Criação dos inimigos 
    struct objetos Inimigos[3];
    Inimigos[0].r = (SDL_Rect) {400,50,17,30};
    Inimigos[1].r = (SDL_Rect) {400,142,17,30};
    Inimigos[2].r = (SDL_Rect) {100,510,17,30};
    SDL_Rect spriteInimigo = (SDL_Rect) {0,240,17,17};
    // Colisões com os blocos
    struct objetos Blocos[75];
    Blocos[0].r = (SDL_Rect) {39,90,18,48};
    Blocos[1].r = (SDL_Rect) {66,90,18,48};


    SDL_bool event = SDL_TRUE;
    SDL_Event evt;
    int NumeroInimigos;
    
    // Inicializa o jogo no Menu
    ShowMenu2(ren,&screen,&espera);
    if(screen == fim){
        event = SDL_FALSE;
    }
    //
    SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, IMGbackGround, &LimitacaoBackGround, &BackGround);
    SDL_RenderCopy(ren, IMGSprites, &bomberMan.Sprite, &bomberMan.r);
    
    while (event) {
        screen = menu;
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, IMGbackGround, &LimitacaoBackGround, &BackGround);
        
        for(NumeroInimigos = 0; NumeroInimigos<=2;NumeroInimigos++){
            SDL_RenderCopy(ren, IMGSprites, &spriteInimigo, &Inimigos[NumeroInimigos].r);
        }
        if(sprites == 3){
            sprites = 0;
        }
        EventsBomberman(&evt, &bomberMan,Blocos,&Bomba,&sprites);
        sprites++;
        SDL_RenderCopy(ren, IMGSprites, &bomberMan.Sprite, &bomberMan.r);
        SDL_RenderCopy(ren, IMGSprites, &spriteBomba, &Bomba);
        //EventsInimigos(isevt,&Inimigos);
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        EventsInimigos(isevt,Inimigos,&espera);
        
        //Acabando o jogo
        if(SDL_HasIntersection(&bomberMan.r,&Inimigos[0].r)){
            bomberMan.Sprite = (SDL_Rect) {0,64,10,10};
            screen = morte;
            ShowMenu2(ren,&screen,&espera);
            int espera = 1500;
            int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
            if(!isevt){
                event = SDL_FALSE;
            }

        }
        switch(evt.type){
            case(SDL_WINDOWEVENT):
                switch(evt.window.event){
                    case SDL_WINDOWEVENT_CLOSE:
                        event = SDL_FALSE;
                    break;
                }
                break;
        
            case(SDL_KEYDOWN):
                switch(evt.key.keysym.sym){
                    case SDLK_ESCAPE:
                        ShowMenu2(ren,&screen,&espera);
                        if(screen == fim){
                            event = SDL_FALSE;
                        }
                }
            
            default:
            break;
        }
        SDL_RenderPresent(ren);
    }


    /* FINALIZACAO */
    SDL_DestroyTexture(IMGbackGround);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
