#include "SdlUi.hpp"
#include <iostream>
#include <SDL3_ttf/SDL_ttf.h>


SdlUi::SdlUi() : m_isRunning(false), m_lastWin(0), m_window(nullptr), m_renderer(nullptr), m_font(nullptr) {}

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

    // Initialize SDL_ttf
    if (!TTF_Init()) {
        SDL_Log("TTF_Init failed: %s", SDL_GetError());
        return false;
    }

    // Load font
    // We use a standard vector font for stability.
    m_font = TTF_OpenFont("/usr/share/fonts/truetype/roboto/Roboto-Regular.ttf", 40); 
    if (m_font) {
        SDL_Log("Loaded Roboto successfully.");
    } else {
        SDL_Log("Roboto not found, trying DejaVu...");
        m_font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 40);
        if (m_font) SDL_Log("Loaded DejaVu successfully.");
    }

    if (!m_font) {
        SDL_Log("CRITICAL: No standard fonts found!");
        return false;
    }


    // Diagnostic des entrées (Souris et Tactile)
    int num_mice;
    SDL_MouseID* mice = SDL_GetMice(&num_mice);
    std::cout << "Number of mice detected: " << num_mice << std::endl;
    SDL_free(mice);

    int num_touch;
    SDL_TouchID* touch_devices = SDL_GetTouchDevices(&num_touch);
    std::cout << "Number of touch devices: " << num_touch << std::endl;
    for(int i=0; i<num_touch; ++i) {
        std::cout << "Touch Device " << i << ": " << SDL_GetTouchDeviceName(touch_devices[i]) << std::endl;
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
        SDL_RenderFillRect(m_renderer, &rect); // Draw white background for the reel

        if (i < (int)m_lastResult.size()) {
            std::string sym = m_lastResult[i];
            
            // Render text
            SDL_Surface* textSurface = TTF_RenderText_Blended(m_font, sym.c_str(), 0, {0, 0, 0, 255}); // Black text
            
            if (textSurface == nullptr) {
                static bool loggedOnce = false;
                if (!loggedOnce) {
                    SDL_Log("Emoji render failed, falling back to '?'. Error: %s", SDL_GetError());
                    loggedOnce = true;
                }
                // Fallback to a simple character that is guaranteed to exist in standard fonts
                textSurface = TTF_RenderText_Blended(m_font, "?", 0, {0, 0, 0, 255});
            }

            if (textSurface != nullptr) {
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
                if (textTexture == nullptr) {
                    SDL_Log("Unable to create texture from rendered text! SDL Error: %s", SDL_GetError());
                } else {
                    float textW, textH;
                    SDL_GetTextureSize(textTexture, &textW, &textH);
                    SDL_FRect renderQuad = { 
                        rect.x + (reelW - textW) / 2, 
                        rect.y + (reelH - textH) / 2, 
                        textW, 
                        textH 
                    };
                    SDL_RenderTexture(m_renderer, textTexture, nullptr, &renderQuad);
                    SDL_DestroyTexture(textTexture);
                }
                SDL_DestroySurface(textSurface);
            }
        }
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
    if (m_font) TTF_CloseFont(m_font);
    TTF_Quit();
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);
    SDL_Quit();
}
