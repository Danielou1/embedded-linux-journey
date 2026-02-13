#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <vector>

class SdlUi {
public:
    SdlUi();
    ~SdlUi();

    void run();

private:
    bool init();
    void handleEvents();
    void render();
    void clean();

    bool m_isRunning;

    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
};
