#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../writer/writer.h"
#include "../singleton/singleton.h"

class Game{
private:
    SDL_Renderer* renderer;
    Writer *writer;
    SDL_Window* window;
    SDL_Color color;
    bool running;
    int frameCount, timerFPS, lastFrame, fps;

    SDL_Rect l_paddle, r_paddle, ball;
    std::pair<float, float> vel;
    std::pair<int, int> score_values;
    bool turn;

    void update();
    void base();
    void input();
    void render();
public:
    Game();
    void game();
    virtual ~Game();
};