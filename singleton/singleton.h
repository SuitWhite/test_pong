#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Singleton{
    static Singleton *instance;
    Singleton();
public:
    SDL_Renderer* renderer;
    static Singleton* getInstance();

    static const int WINDOW_WIDTH = 640;
    static const int WINDOW_HEIGHT = 640;
    static const int BALL_SPEED = 16;
    static const int SPEED = 9;
    static const int SIZE = 8;
    static constexpr double PI = 3.14159265358979323846;
};