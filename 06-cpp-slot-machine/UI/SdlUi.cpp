#include "SdlUi.hpp"
#include <iostream>

SdlUi::SdlUi() : m_isRunning(false), m_window(nullptr), m_renderer(nullptr) {}

SdlUi::~SdlUi() {
    clean();
}

bool SdlUi::init() {
    // SDL3: SDL_Init returns true on success
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // SDL3: SDL_CreateWindow(title, width, height, flags)
    m_window = SDL_CreateWindow("Slot Machine", 800, 600, 0);
    if (!m_window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // SDL3: SDL_CreateRenderer(window, name)
    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    m_isRunning = true;
    return true;
}

void SdlUi::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // SDL3: SDL_QUIT is now SDL_EVENT_QUIT
        if (event.type == SDL_EVENT_QUIT) {
            m_isRunning = false;
        }
    }
}

void SdlUi::render() {
    // SDL3: Still returns true/false
    SDL_SetRenderDrawColor(m_renderer, 30, 30, 30, 255); // Dark grey
    SDL_RenderClear(m_renderer);

    // TODO: Render reels

    SDL_RenderPresent(m_renderer);
}

void SdlUi::run() {
    if (!init()) {
        return;
    }

    while (m_isRunning) {
        handleEvents();
        render();
    }
}

void SdlUi::clean() {
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if (m_window) {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    SDL_Quit();
}
