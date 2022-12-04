#include <assert.h>
#include <SDL2/SDL.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, int* espera) {
    int ms = SDL_GetTicks();
	int event = SDL_WaitEventTimeout(evt, *espera);
	if (event){
		*espera -= (SDL_GetTicks() - ms);
		if(*espera <= 0) {
			*espera = 0;
		}
	}
    return event;
}

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("1.6.1",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         600, 600, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    int x,y;
    int espera = 500;
    SDL_bool event = SDL_TRUE;
    SDL_Rect Tempo = { 0,100, 50,50 };
    SDL_Rect Teclado = { 0,300, 50,50 };
    SDL_Rect Mouse = { 0,500, 50,50 };
    int x1 = 500;
    int y1 = 0;
    int x2 = 10;
    int y2 = 600;
    SDL_Rect LinhaChegada = { x1,y1, x2,y2 };
    SDL_bool colisaoTeclado, colisaoMouse, colisaoTempo, ganhador;
    int QualRet = 0;
    ganhador = SDL_FALSE;
    while (event) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &Tempo);
        SDL_SetRenderDrawColor(ren, 0xFF,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &Teclado);
        SDL_SetRenderDrawColor(ren, 0x00,0xFF,0xFF,0x00);
        SDL_RenderFillRect(ren, &Mouse);
        SDL_SetRenderDrawColor(ren, 0xFF,0x00,0x00,0x00);
        SDL_RenderFillRect(ren, &LinhaChegada);
        SDL_RenderPresent(ren);

        SDL_Event evt;
        if (evt.type == SDL_WINDOWEVENT) {
            switch(evt.window.event){
            case SDL_WINDOWEVENT_CLOSE:
            event = SDL_FALSE;
            break;
            }
        }

        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if (isevt) {
            switch (evt.type) {
                case SDL_KEYDOWN:
                colisaoTeclado = SDL_HasIntersection(&Teclado,&LinhaChegada);
                switch (evt.key.keysym.sym) {
                    case SDLK_LEFT:
                        if(Teclado.x == 0){
                            break;
                        }
                        Teclado.x -= 5;
                    break;
                    case SDLK_RIGHT:
                        if(!colisaoTeclado){
                            Teclado.x += 5;
                        }else{    
                            if(!ganhador){
                                ganhador = SDL_TRUE;
                                QualRet = 1;
                            }
                        }
                    break;
                }
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&x,&y);
                    colisaoMouse = SDL_HasIntersection(&Mouse,&LinhaChegada);
                    if(!colisaoMouse){
                        Mouse.x = x;
                    }else{    
                            if(!ganhador){
                                ganhador = SDL_TRUE;
                                QualRet = 2;
                            }
                        }
                break;
            }
        } else {
            espera = 500;
            colisaoTempo = SDL_HasIntersection(&Tempo,&LinhaChegada);
            if(!colisaoTempo){
                Tempo.x += 20;
            }else{    
                if(!ganhador){
                    ganhador = SDL_TRUE;
                    QualRet = 3;
                }
            }
        }
    if(colisaoMouse && colisaoTeclado && colisaoTempo){
        if (QualRet == 1){
            SDL_Log("Teclado ganhou");
        }
        if (QualRet == 2){
            SDL_Log("Mouse ganhou");
        }
        if (QualRet == 3){
            SDL_Log("Tempo ganhou");
        }

        // reinicialização 
        ganhador = SDL_FALSE;
        colisaoMouse = SDL_FALSE;
        colisaoTeclado = SDL_FALSE;
        colisaoTempo = SDL_FALSE;
        Teclado.x = 0;
        Mouse.x = 0;
        Tempo.x = 0;
    }

    }
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

