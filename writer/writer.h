#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define FONT_SIZE 32

class Writer{
private:
    TTF_Font* font;
    SDL_Color color;
    SDL_Rect score_board;
    SDL_Renderer* renderer;
public:
    void write(std::string text, int x, int y);
    Writer(SDL_Renderer* renderer);
    virtual ~Writer();
};