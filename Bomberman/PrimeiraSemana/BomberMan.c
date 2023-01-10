#include <assert.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <math.h>

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
};


void EventsBomberman (SDL_Event* evt, struct objetos* bomberMan,SDL_Rect Blocos){
    SDL_Point mousePosition;
    SDL_Rect TesteColisao = bomberMan->r;
    switch(evt->type){
        case(SDL_KEYDOWN):
        SDL_PumpEvents();
            switch(evt->key.keysym.sym){
                case SDLK_UP:
                    if(bomberMan->r.y == 80){
                        break;
                    }
                    TesteColisao.y -=5;
                    if(!(SDL_HasIntersection(&TesteColisao,&Blocos))){
                        bomberMan->r.y -= 5;
                    }
                    break;
                case SDLK_DOWN:
                    if(bomberMan->r.y == 860){
                        break;
                    }
                    TesteColisao.y += 5;
                    if(!(SDL_HasIntersection(&TesteColisao,&Blocos))){
                        bomberMan->r.y += 5;
                    }
                    break;
                case SDLK_LEFT:
                    if(bomberMan->r.x == 35){
                        break;
                    }
                    TesteColisao.x -= 5;
                    if(!(SDL_HasIntersection(&TesteColisao,&Blocos))){
                        bomberMan->r.x -= 5;
                    }
                    break;
                case SDLK_RIGHT:
                    if(bomberMan->r.x == 945){
                        break;
                    }
                    TesteColisao.x += 5;
                    if(!(SDL_HasIntersection(&TesteColisao,&Blocos))){
                        bomberMan->r.x += 5;
                    }
                    break;
                break;
            }

        default:
            break;
    }
}
/*
void EventsInimigos (SDL_Event* evt,struct objetos* Inimigos){
    int espera = 500;
    int isevt = AUX_WaitEventTimeoutCount(evt, &espera);
    if(!isevt){
        int evento = 0;
        switch(evento){
            case 0:
                if(Inimigos->r.x == 935){
                    break;
                }
                Inimigos->r.x += 5;
        }
    }
}*/
int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    SDL_Window* win = SDL_CreateWindow("BomberMan NES",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         1000, 1000, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* IMGSprites = IMG_LoadTexture(ren, "auxilio/NES_Bomberman_GeneralSprites.png");
    SDL_Texture* IMGbackGround = IMG_LoadTexture(ren, "auxilio/NES_Bomberman_Playfield.png");
    assert(IMGSprites != NULL);
    assert(IMGbackGround != NULL);
    /* EXECUÇÃO */
    int espera = 100;
    
    // BackGRound
    SDL_Rect BackGround = (SDL_Rect) {0,0,1000,1000};
    SDL_Rect LimitacaoBackGround = (SDL_Rect) {0,0,496,208};
    
    // Criação do BomberMan
    struct objetos bomberMan;
    bomberMan.r = (SDL_Rect) {35,80,20,60};
    bomberMan.IsCollind = SDL_FALSE;
    SDL_Rect spriteFrenteParado = (SDL_Rect) { 67,0,10,16};
    
    // Criação dos inimigos 
    struct objetos Inimigos[3];
    Inimigos[0].r = (SDL_Rect) {700,90,30,40};
    Inimigos[1].r = (SDL_Rect) {400,100,30,40};
    Inimigos[2].r = (SDL_Rect) {100,800,30,40};
    SDL_Rect spriteInimigo = (SDL_Rect) {0,240,17,17};
    // Colisões com os blocos
    //SDL_Rect Blocos[75];
    SDL_Rect Blocos = (SDL_Rect) {65,150,30,60};

    SDL_bool event = SDL_TRUE;
    SDL_Event evt;
    while (event) {
        
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, IMGbackGround, &LimitacaoBackGround, &BackGround);
        SDL_RenderCopy(ren, IMGSprites, &spriteFrenteParado, &bomberMan.r);
        SDL_RenderCopy(ren, IMGSprites, &spriteInimigo, &Inimigos[1].r);
        SDL_RenderCopy(ren, IMGSprites, &spriteInimigo, &Inimigos[2].r);
        SDL_RenderCopy(ren, IMGSprites, &spriteInimigo, &Inimigos[0].r);
        SDL_RenderPresent(ren);


        EventsBomberman(&evt, &bomberMan,Blocos);
        //EventsInimigos(&evt,&Inimigos);
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if(!isevt){
            espera = 100;
            if(Inimigos[0].r.x <= 805 && Inimigos[0].r.y == 90){
                Inimigos[0].r.x += 5;
            }
            if(Inimigos[0].r.y <= 250 && Inimigos[0].r.x == 805){
                Inimigos[0].r.y += 5;
            }
            if(Inimigos[0].r.y == 255 && Inimigos[0].r.x >= 295){
                Inimigos[0].r.x -= 5;
            }
            if(Inimigos[0].r.y >= 90 && Inimigos[0].r.x == 290){
                Inimigos[0].r.y -= 5;
            }
        }else{
            switch(evt.type){
                case(SDL_WINDOWEVENT):
                    switch(evt.window.event){
                        case SDL_WINDOWEVENT_CLOSE:
                            event = SDL_FALSE;
                        break;
                    }
                    break;
                default:
                    break;
            }
        }

    }

    /* FINALIZACAO */
    SDL_DestroyTexture(IMGSprites);
    SDL_DestroyTexture(IMGbackGround);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}