#include "ThreadingMutex.h"

//SDL_mutex* mtx = SDL_CreateMutex();

SDL_sem* sem = SDL_CreateSemaphore(1);