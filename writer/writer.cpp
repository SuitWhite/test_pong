#include "writer.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void Writer::write(std::string text, int x, int y) {
    SDL_Surface *surface;
    SDL_Texture *texture;

    const char* t = text.c_str();

    surface = TTF_RenderText_Solid(font, t, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    score_board.w=surface->w;
    score_board.h=surface->h;
    score_board.x=x-score_board.w;
    score_board.y=y-score_board.h;

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &score_board);
    SDL_DestroyTexture(texture);
}

Writer::Writer(SDL_Renderer* renderer){
    this->renderer = renderer;

    TTF_Init();
    font = TTF_OpenFont("Peepo.ttf", FONT_SIZE);

    color.r=color.g=color.b=255;
}

Writer::~Writer(){
    TTF_CloseFont(font);
}
