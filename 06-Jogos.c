#include <assert.h>
#include <SDL2/SDL.h>

int AUX_WaitEventTimeoutCount(SDL_Event* evt, Uint32* espera) {
    Uint32 ms = SDL_GetTicks();
	int event = SDL_WaitEventTimeout(evt, *espera);
	if (event){
		*espera -= (SDL_GetTicks() - ms);
		if(*espera <= 0) {
			*espera = 0;
		}
		return event;
	}else{
		return event;
	}
}

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("3 retangulos",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);

    /* EXECUÇÃO */
    Uint32 espera = 500;
    SDL_bool event = SDL_TRUE;
    SDL_Rect Tempo = { 100,100, 50,50 };
    SDL_Rect Teclado = { 300,200, 50,50 };
    SDL_Rect Mouse = { 500,500, 50,50 };
    while (event) {
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &Tempo);
        SDL_SetRenderDrawColor(ren, 0xFF,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &Teclado);
        SDL_SetRenderDrawColor(ren, 0x00,0xFF,0xFF,0x00);
        SDL_RenderFillRect(ren, &Mouse);
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
                switch (evt.key.keysym.sym) {
                    case SDLK_UP:
                        if(Teclado.y == 0){
                            break;
                        }
                        Teclado.y -= 5;
                        break;
                    case SDLK_DOWN:
                        if(Teclado.y == 450){
                            break;
                        }
                        Teclado.y += 5;
                        break;
                    case SDLK_LEFT:
                        if(Teclado.x == 0){
                            break;
                        }
                        Teclado.x -= 5;
                        break;
                    case SDLK_RIGHT:
                        if(Teclado.x == 450){
                            break;
                        }
                        Teclado.x += 5;
                        break;
                    break;
                }
                case SDL_MOUSEMOTION:
                    int x,y;
                    SDL_GetMouseState(&x,&y);
                    if(x >= 450){
                        Mouse.x = 450;
                    }else{
                        Mouse.x = x;
                    }
                    if(y >= 450){
                        Mouse.y = 450;
                    }else{
                        Mouse.y = y;
                    }
                break;
            }
        } else {
            espera = 500;
            Tempo.x += 5;
            Tempo.y += 5;
            if(Tempo.x >= 455){
                Tempo.x = 0;
            }
            if(Tempo.y >= 455){
                Tempo.y = 0;
            }
        }

    }
    

    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
