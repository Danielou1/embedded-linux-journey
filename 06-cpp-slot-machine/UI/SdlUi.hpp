#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h> // Include SDL_ttf header
#include <string>
#include <vector>
#include "../GameEngine.hpp"

class SdlUi {
public:
    SdlUi();
    ~SdlUi();

    void run();

private:
    bool init();
    void handleEvents();
    void update();
    void render();
    void clean();

    bool m_isRunning;
    GameEngine m_engine;
    std::vector<std::string> m_lastResult;
    int m_lastWin;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    TTF_Font* m_font; // Add font member variable
};
