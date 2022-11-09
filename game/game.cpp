#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void Game::base(){
    l_paddle.y=r_paddle.y=(Singleton::WINDOW_HEIGHT/2)-(l_paddle.h/2);
    if(turn) {
        ball.x=l_paddle.x+(l_paddle.w*4);
        vel.first=Singleton::BALL_SPEED/2;
    } else {
        ball.x=r_paddle.x-(r_paddle.w*4);
        vel.first=-Singleton::BALL_SPEED/2;
    }
    vel.second=0;
    ball.y=Singleton::WINDOW_HEIGHT/2-(Singleton::SIZE/2);
    turn=!turn;
}

void Game::update(){
    if(SDL_HasIntersection(&ball, &r_paddle)) {
        double rel = (r_paddle.y+(r_paddle.h/2))-(ball.y+(Singleton::SIZE/2));
        double norm = rel/(r_paddle.h/2);
        double bounce = norm * (5*Singleton::PI/12);
        vel.first=-Singleton::BALL_SPEED * cos(bounce);
        vel.second=Singleton::BALL_SPEED * -sin(bounce);
    }

    if(SDL_HasIntersection(&ball, &l_paddle)) {
        double rel = (l_paddle.y+(l_paddle.h/2))-(ball.y+(Singleton::SIZE/2));
        double norm = rel/(l_paddle.h/2);
        double bounce = norm * (5*Singleton::PI/12);
        vel.first=Singleton::BALL_SPEED*cos(bounce);
        vel.second=Singleton::BALL_SPEED*-sin(bounce);
    }

    if(ball.y > r_paddle.y+(r_paddle.h/2)) r_paddle.y+=Singleton::SPEED;
    if(ball.y < r_paddle.y+(r_paddle.h/2)) r_paddle.y-=Singleton::SPEED;

    if(ball.x<=0) {
        score_values.second++;
        base();
    }
    if(ball.x+Singleton::SIZE>=Singleton::WINDOW_WIDTH) {
        score_values.first++;
        base();
    }

    if(ball.y<=0 || ball.y+Singleton::SIZE>=Singleton::WINDOW_HEIGHT) vel.second=-vel.second;

    ball.x+=vel.first;
    ball.y+=vel.second;

    if(l_paddle.y<0)l_paddle.y=0;
    if(l_paddle.y+l_paddle.h>Singleton::WINDOW_HEIGHT)l_paddle.y=Singleton::WINDOW_HEIGHT-l_paddle.h;
    if(r_paddle.y<0)r_paddle.y=0;
    if(r_paddle.y+r_paddle.h>Singleton::WINDOW_HEIGHT)r_paddle.y=Singleton::WINDOW_HEIGHT-r_paddle.h;
}

void Game::input(){
    SDL_Event e;
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    while(SDL_PollEvent(&e)) if(e.type==SDL_QUIT) running=false;

    if(keystates[SDL_SCANCODE_ESCAPE]) running=false;
    if(keystates[SDL_SCANCODE_UP]) l_paddle.y-=Singleton::SPEED;
    if(keystates[SDL_SCANCODE_DOWN]) l_paddle.y+=Singleton::SPEED;
}

void Game::render(){
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
    SDL_RenderClear(renderer);

    frameCount++;
    timerFPS = SDL_GetTicks()-lastFrame;
    if(timerFPS<(1000/60)) {
        SDL_Delay((1000/60)-timerFPS);
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &l_paddle);
    SDL_RenderFillRect(renderer, &r_paddle);
    SDL_RenderFillRect(renderer, &ball);

    std::string score = std::to_string(score_values.first) + "   " + std::to_string(score_values.second);
    writer->write(score, Singleton::WINDOW_WIDTH/2+FONT_SIZE, FONT_SIZE*2);

    SDL_RenderPresent(renderer);
}

Game::Game(){
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cout << "Failed at SDL_Init()" << std::endl;
    if(SDL_CreateWindowAndRenderer(Singleton::WINDOW_WIDTH, Singleton::WINDOW_HEIGHT, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer())" << std::endl;

    running=1;
    static int lastTime = 0;

    score_values.first=score_values.second=0;
    l_paddle.x=32;
    l_paddle.h=Singleton::WINDOW_HEIGHT/4;
    l_paddle.y=(Singleton::WINDOW_HEIGHT/2)-(l_paddle.h/2);
    l_paddle.w=10;

    r_paddle=l_paddle;
    r_paddle.x=Singleton::WINDOW_WIDTH-r_paddle.w-32;

    ball.w=ball.h=Singleton::SIZE;

    writer = new Writer(renderer);

    base();
}

void Game::game(){
    running=1;
    static int lastTime = 0;

    while(running) {
        lastFrame=SDL_GetTicks();
        if(lastFrame>=(lastTime+1000)) {
            lastTime=lastFrame;
            fps=frameCount;
            frameCount=0;
        }

        update();
        input();
        render();
    }
}

Game::~Game(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}