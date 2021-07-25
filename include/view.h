#ifndef _VIEW_H_
#define _VIEW_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include <GL/glew.h>
#include <signal.h>
#include <stdbool.h>

typedef struct {
    SDL_Window* handle;
    SDL_GLContext context;
    bool isclosed;
} Display;

#define display_clear(r, g, b, a) {glClearColor(r, g, b, a); glClear(GL_COLOR_BUFFER_BIT);}

extern Display display(const int, const int, const char*);
extern void display_delete(Display*);
extern void display_update(Display*);

#endif