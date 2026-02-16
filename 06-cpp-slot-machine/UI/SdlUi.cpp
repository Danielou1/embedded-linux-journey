#include "SdlUi.hpp"
#include <iostream>

SdlUi::SdlUi() : m_isRunning(false), m_lastWin(0), m_window(nullptr), m_renderer(nullptr) {}

SdlUi::~SdlUi() {
    clean();
}

bool SdlUi::init() {
    SDL_SetLogPriorities(SDL_LOG_PRIORITY_DEBUG);

    SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "kmsdrm");
    SDL_SetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY, "DSI-1,DSI-2,HDMI-A-1");

    // Initialisation explicite de VIDEO et EVENTS
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    // Diagnostic des entrées (Souris et Tactile)
    int num_mice;
    SDL_MouseID* mice = SDL_GetMice(&num_mice);
    SDL_Log("Number of mice detected: %d", num_mice);
    SDL_free(mice);

    int num_touch;
    SDL_TouchID* touch_devices = SDL_GetTouchDevices(&num_touch);
    SDL_Log("Number of touch devices: %d", num_touch);
    for(int i=0; i<num_touch; ++i) {
        SDL_Log("Touch Device %d: %s", i, SDL_GetTouchDeviceName(touch_devices[i]));
    }
    SDL_free(touch_devices);

    m_window = SDL_CreateWindow("Slot Machine", 800, 480, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
    if (!m_window) {
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }

    m_isRunning = true;
    return true;
}

void SdlUi::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            m_isRunning = false;
        }
        
        bool triggered = false;
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            triggered = true;
            SDL_Log("Mouse click detected at %f, %f", event.button.x, event.button.y);
        } else if (event.type == SDL_EVENT_FINGER_DOWN) {
            triggered = true;
            SDL_Log("Finger down detected at x=%f, y=%f", event.tfinger.x, event.tfinger.y);
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
            if (event.key.key == SDLK_SPACE || event.key.key == SDLK_RETURN) {
                triggered = true;
            }
        }

        if (triggered) {
            m_lastResult = m_engine.spin();
            m_lastWin = m_engine.getPayout(m_lastResult);
            
            std::cout << "Action! Result: ";
            for(auto &s : m_lastResult) std::cout << s << " ";
            std::cout << " | Win: " << m_lastWin << std::endl;
        }
    }
}

void SdlUi::render() {
    // Fond violet pour le debug
    if (m_lastWin > 0) {
        SDL_SetRenderDrawColor(m_renderer, 50, 200, 50, 255);
    } else {
        SDL_SetRenderDrawColor(m_renderer, 100, 50, 150, 255);
    }
    SDL_RenderClear(m_renderer);

    int w = 800;
    int h = 480;

    int reelW = 150;
    int reelH = 200;
    int spacing = 50;
    int startX = (w - (3 * reelW + 2 * spacing)) / 2;
    int startY = 80;

    for (int i = 0; i < 3; ++i) {
        SDL_FRect rect = { (float)startX + i * (reelW + spacing), (float)startY, (float)reelW, (float)reelH };
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
        
        if (i < (int)m_lastResult.size()) {
            std::string sym = m_lastResult[i];
            if (sym == "🍒") SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
            else if (sym == "🍋") SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 255);
            else if (sym == "🔔") SDL_SetRenderDrawColor(m_renderer, 255, 180, 0, 255);
            else if (sym == "7️⃣") SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
        }
        SDL_RenderFillRect(m_renderer, &rect);
    }

    SDL_FRect btnRect = { (float)(w - 240) / 2, (float)h - 100, 240.0f, 70.0f };
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(m_renderer, &btnRect);

    SDL_RenderPresent(m_renderer);
}

void SdlUi::run() {
    if (!init()) return;
    while (m_isRunning) {
        handleEvents();
        render();
        SDL_Delay(16);
    }
}

void SdlUi::clean() {
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);
    SDL_Quit();
}
