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
    SDL_Window* win = SDL_CreateWindow("Animacao orientada a eventos",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         500, 500, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);


    /* EXECUÇÃO */
    SDL_bool event = SDL_TRUE;
    SDL_Event evt;
    Uint32 espera = 500;
    SDL_Rect r = { 100,100, 30,30 };
    while(event){
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0x00,0x00,0xFF,0x00);
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        
        if (isevt) {
            switch (evt.type) {
                case SDL_KEYDOWN:
                    switch (evt.key.keysym.sym) {
                        case SDLK_UP:
                            if(r.y == 0){
                                break;
                            }
                            r.y -= 10;
                            break;
                        case SDLK_DOWN:
                            if(r.y == 470){
                                break;
                            }
                            r.y += 10;
                            break;
                        case SDLK_LEFT:
                            if(r.x == 0){
                                break;
                            }
                            r.x -= 10;
                            break;
                        case SDLK_RIGHT:
                            if(r.x == 470){
                                break;
                            }
                            r.x += 10;
                            break;
                    }
                break;
                case SDL_WINDOWEVENT:
                    switch(evt.window.event){
                        case SDL_WINDOWEVENT_CLOSE:
                        event = SDL_FALSE;
                        break;
                    }
                break;
            }
        }else{
            espera = 500;
            r.x += 10;
            r.y += 10;
            if(r.x >= 470){
            r.x = 0;
            }
            if(r.y >= 470){
                r.y = 0;
            }
        }
    }
    /* FINALIZACAO */
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}T
