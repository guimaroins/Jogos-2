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


void EventsBomberman (SDL_Event* evt, struct objetos* bomberMan,SDL_Rect Blocos,SDL_Rect* Bomba){
    SDL_Point mousePosition;
    SDL_Rect TesteColisao = bomberMan->r;
    switch(evt->type){
        case(SDL_KEYDOWN):
        SDL_PumpEvents();
            switch(evt->key.keysym.sym){
                case SDLK_UP:
                    if(bomberMan->r.y <= 45){
                        break;
                    }
                    TesteColisao.y -=5;
                    if(!(SDL_HasIntersection(&TesteColisao,&Blocos))){
                        bomberMan->r.y -= 5;
                    }
                    break;
                case SDLK_DOWN:
                    if(bomberMan->r.y >= 520){
                        break;
                    }
                    TesteColisao.y += 5;
                    if(!(SDL_HasIntersection(&TesteColisao,&Blocos))){
                        bomberMan->r.y += 5;
                    }
                    break;
                case SDLK_LEFT:
                    if(bomberMan->r.x == 20){
                        break;
                    }
                    TesteColisao.x -= 5;
                    if(!(SDL_HasIntersection(&TesteColisao,&Blocos))){
                        bomberMan->r.x -= 5;
                    }
                    break;
                case SDLK_RIGHT:
                    if(bomberMan->r.x >= 565){
                        break;
                    }
                    TesteColisao.x += 5;
                    if(!(SDL_HasIntersection(&TesteColisao,&Blocos))){
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
                         600, 600, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* IMGSprites = IMG_LoadTexture(ren, "auxilio/NES_Bomberman_GeneralSprites.png");
    SDL_Texture* IMGbackGround = IMG_LoadTexture(ren, "auxilio/NES_Bomberman_Playfield.png");
    assert(IMGSprites != NULL);
    assert(IMGbackGround != NULL);
    /* EXECUÇÃO */
    int espera = 100;
    
    // BackGRound
    SDL_Rect BackGround = (SDL_Rect) {0,0,600,600};
    SDL_Rect LimitacaoBackGround = (SDL_Rect) {0,0,496,208};
    
    // Criação do BomberMan
    struct objetos bomberMan;
    bomberMan.r = (SDL_Rect) {20,50,15,30};
    bomberMan.IsCollind = SDL_FALSE;
    SDL_Rect spriteFrenteParado = (SDL_Rect) { 67,0,10,16};
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
    //SDL_Rect Blocos[75];
    SDL_Rect Blocos = (SDL_Rect) {39,90,18,48};

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
        

        EventsBomberman(&evt, &bomberMan,Blocos,&Bomba);
        SDL_RenderCopy(ren, IMGSprites, &spriteBomba, &Bomba);
        //EventsInimigos(&evt,&Inimigos);
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if(!isevt){
            espera = 100;
            if(Inimigos[0].r.x <= 564 && Inimigos[0].r.y == 50){
                Inimigos[0].r.x += 4;
            }
            if(Inimigos[0].r.y <= 238 && Inimigos[0].r.x == 564){
                Inimigos[0].r.y += 4;
            }
            if(Inimigos[0].r.y == 238 && Inimigos[0].r.x >= 252){
                Inimigos[0].r.x -= 4;
            }
            if(Inimigos[0].r.y >= 50 && Inimigos[0].r.x == 252){
                Inimigos[0].r.y -= 4;
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
        SDL_RenderPresent(ren);

    }

    /* FINALIZACAO */
    SDL_DestroyTexture(IMGSprites);
    SDL_DestroyTexture(IMGbackGround);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}