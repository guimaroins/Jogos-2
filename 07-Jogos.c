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
/*
int espera = 500;
int isevt = AUX_WaitEventTimeoutCount(&evt, &espera);
*/
