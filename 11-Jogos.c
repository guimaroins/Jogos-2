#include <SDL2/SDL.h>
#include <assert.h>
#include <SDL2/SDL_image.h>

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

int main (int argc, char* args[])
{
    /* INICIALIZACAO */
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(0);
    SDL_Window* win = SDL_CreateWindow("Recorte",
                         SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED,
                         600, 600, SDL_WINDOW_SHOWN
                      );
    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, 0);
    SDL_Texture* img = IMG_LoadTexture(ren, "auxilio/mario.png");
    assert(img != NULL);

    /* EXECUÇÃO */
    int isup = 1;
    SDL_bool event = SDL_TRUE;
    SDL_Event evt;
    int espera = 300;
    SDL_Rect r = { 400,100, 100,150 };
    SDL_Rect c;
    while(event){
        SDL_SetRenderDrawColor(ren, 0xFF,0xFF,0xFF,0x00);
        SDL_RenderClear(ren);
        if (isup) {
            c = (SDL_Rect) {   800,0, 900,150 };
        } else {
            c = (SDL_Rect) { 150,0, 250,150 };
        }
        SDL_RenderCopy(ren, img, &c, &r);
        SDL_RenderPresent(ren);
        isup = !isup;
        int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
        if (!isevt) {
            espera = 300;
            if(r.y == 100 && r.x > 100){
                r.x -= 10;
            }
            if(r.x == 100 && r.y < 400){
                r.y += 10;
            }
            if(r.y == 400 && r.x < 400){
                r.x += 10;
            }
            if(r.x == 400 && r.y > 100){
                r.y -= 10;
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
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
