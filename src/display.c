#include <display.h>

Display display(const int width, const int height, const char* title){
    int check;
    if( (check = SDL_Init(SDL_INIT_EVERYTHING)) < 0 )
        fprintf(stderr, "[SDL ERROR]: %s\n", SDL_GetError());

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    SDL_Window* handle;
    if ( (handle = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, height, width, SDL_WINDOW_OPENGL)) == NULL)
        fprintf(stderr, "[SDL ERROR]: %s\n", SDL_GetError());
    
    
    SDL_GLContext context;
    if ( (context = SDL_GL_CreateContext(handle)) == NULL)
        fprintf(stderr, "[SDL ERROR]: %s\n", SDL_GetError());

    
    if (glewInit() != GLEW_OK) {
        puts("[CRITICAL] Glew failed to initialize!\n");
        kill(0, SIGABRT);
    }


    Display v = {.handle = handle, .context = context, .isclosed = false};
    return v;
}

void display_delete(Display* v){
    SDL_GL_DeleteContext(v->context);
    SDL_DestroyWindow(v->handle);
    SDL_Quit();
    memset(v, 0, sizeof(Display));
}

void display_update(Display* v){
    SDL_GL_SwapWindow(v->handle);

    SDL_Event e;

    while (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT)
            v->isclosed = true;
}
