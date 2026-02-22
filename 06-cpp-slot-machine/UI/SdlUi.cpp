/**
 * @file SdlUi.cpp
 * @author Danielou Mounsande
 * @brief Implements the SdlUi class for the graphical user interface.
 */
#include "SdlUi.hpp"
#include <iostream>

/**
 * @brief Constructs a new SdlUi object.
 * 
 * Initializes member variables, setting pointers to nullptr and flags to their default state.
 */
SdlUi::SdlUi() : m_isRunning(false), m_lastWin(0), m_window(nullptr), m_renderer(nullptr) {}

/**
 * @brief Destroys the SdlUi object.
 * 
 * Calls the clean() method to ensure all SDL resources are properly released.
 */
SdlUi::~SdlUi() {
    clean();
}

/**
 * @brief Initializes the SDL library and creates the window and renderer.
 * 
 * Sets up SDL video drivers for a specific hardware target (KMS/DRM on Raspberry Pi),
 * initializes the video and event subsystems, creates a fullscreen window, and
 * prepares a renderer. It also logs diagnostic information about input devices.
 * 
 * @return True if initialization was successful, false otherwise.
 */
bool SdlUi::init() {
    // Enable debug logging for SDL
    SDL_SetLogPriorities(SDL_LOG_PRIORITY_DEBUG);

    // Hints for Raspberry Pi display drivers
    SDL_SetHint(SDL_HINT_VIDEO_DRIVER, "kmsdrm");
    SDL_SetHint(SDL_HINT_VIDEO_DISPLAY_PRIORITY, "DSI-1,DSI-2,HDMI-A-1");

    // Explicitly initialize VIDEO and EVENTS subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    // Diagnostics for Mouse and Touch inputs
    int num_mice;
    SDL_MouseID* mice = SDL_GetMice(&num_mice);
    if (mice) {
        std::cout << "Number of mice detected: " << num_mice << std::endl;
        SDL_free(mice);
    }

    int num_touch;
    SDL_TouchID* touch_devices = SDL_GetTouchDevices(&num_touch);
     if (touch_devices) {
        std::cout << "Number of touch devices: " << num_touch << std::endl;
        for(int i=0; i<num_touch; ++i) {
            const char* touch_name = SDL_GetTouchDeviceName(touch_devices[i]);
            if(touch_name)
                std::cout << "Touch Device " << i << ": " << touch_name << std::endl;
        }
        SDL_free(touch_devices);
    }

    // Create a fullscreen window
    m_window = SDL_CreateWindow("Slot Machine", 800, 480, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL);
    if (!m_window) {
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }

    // Create a renderer for the window
    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (!m_renderer) {
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        return false;
    }

    m_isRunning = true;
    return true;
}

/**
 * @brief Processes user input and other SDL events.
 * 
 * Polls for events such as quitting the application, mouse clicks, touch screen presses,
 * and key presses (Space or Enter). Any of these actions trigger a new spin of the reels.
 */
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

        // If a spin was triggered, update game state
        if (triggered) {
            m_lastResult = m_engine.spin();
            m_lastWin = m_engine.getPayout(m_lastResult);
            
            std::cout << "Action! Result: ";
            for(auto &s : m_lastResult) std::cout << s << " ";
            std::cout << " | Win: " << m_lastWin << std::endl;
        }
    }
}

/**
 * @brief Renders the current game state to the screen.
 * 
 * Clears the renderer with a background color (green for a win, purple otherwise).
 * It then draws placeholders for the three reels, coloring them based on the
 * symbol from the last spin. Finally, it draws a placeholder for a "spin" button.
 */
void SdlUi::render() {
    // Purple background for debug, changes to green on win
    if (m_lastWin > 0) {
        SDL_SetRenderDrawColor(m_renderer, 50, 200, 50, 255); // Green for win
    } else {
        SDL_SetRenderDrawColor(m_renderer, 100, 50, 150, 255); // Purple default
    }
    SDL_RenderClear(m_renderer);

    int w = 800;
    int h = 480;

    // Dimensions and layout for the reels
    int reelW = 150;
    int reelH = 200;
    int spacing = 50;
    int startX = (w - (3 * reelW + 2 * spacing)) / 2;
    int startY = 80;

    // Draw each reel placeholder
    for (int i = 0; i < 3; ++i) {
        SDL_FRect rect = { (float)startX + i * (reelW + spacing), (float)startY, (float)reelW, (float)reelH };
        SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255); // Default white
        
        // Color the reel based on the symbol
        if (i < (int)m_lastResult.size()) {
            std::string sym = m_lastResult[i];
            if (sym == "🍒") SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);       // Red
            else if (sym == "🍋") SDL_SetRenderDrawColor(m_renderer, 255, 255, 0, 255); // Yellow
            else if (sym == "🔔") SDL_SetRenderDrawColor(m_renderer, 255, 180, 0, 255); // Orange
            else if (sym == "7️⃣") SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);   // Blue
        }
        SDL_RenderFillRect(m_renderer, &rect);
    }

    // Draw the spin button placeholder
    SDL_FRect btnRect = { (float)(w - 240) / 2, (float)h - 100, 240.0f, 70.0f };
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255); // White
    SDL_RenderFillRect(m_renderer, &btnRect);

    // Update the screen
    SDL_RenderPresent(m_renderer);
}

/**
 * @brief Starts and manages the main game loop.
 * 
 * If initialization is successful, it enters a loop that repeatedly calls
 * handleEvents() and render(). A small delay is included to cap the frame rate.
 */
void SdlUi::run() {
    if (!init()) return;
    while (m_isRunning) {
        handleEvents();
        render();
        SDL_Delay(16); // ~60 FPS
    }
}

/**
 * @brief Frees resources and shuts down SDL.
 * 
 * Destroys the SDL renderer and window if they exist, and then quits
 * all SDL subsystems.
 */
void SdlUi::clean() {
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);
    SDL_Quit();
}
