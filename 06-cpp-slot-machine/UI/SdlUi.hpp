/**
 * @file SdlUi.hpp
 * @brief User Interface and Rendering layer using SDL3.
 * @author Danielou Mounsande
 */

#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <vector>
#include "../GameEngine.hpp"

/**
 * @class SdlUi
 * @brief Handles the graphics, input events, and the main application loop.
 * 
 * This class is responsible for initializing the SDL3 environment, 
 * handling KMSDRM/OpenGL ES rendering, and processing touch/mouse inputs.
 */
class SdlUi {
public:
    /**
     * @brief Constructor initializing default values.
     */
    SdlUi();

    /**
     * @brief Destructor ensuring proper cleanup of SDL resources.
     */
    ~SdlUi();

    /**
     * @brief Starts and manages the main game loop.
     */
    void run();

private:
    /**
     * @brief Initializes SDL3, TTF, Window, and Renderer.
     * @return true if initialization was successful, false otherwise.
     */
    bool init();

    /**
     * @brief Processes system and user input events (touch, mouse, keyboard).
     */
    void handleEvents();

    /**
     * @brief Updates the game state (placeholder for future logic).
     */
    void update();

    /**
     * @brief Renders the current frame to the screen using OpenGL ES.
     */
    void render();

    /**
     * @brief Releases all allocated SDL and TTF resources.
     */
    void clean();

    bool m_isRunning;             /**< Loop control flag. */
    GameEngine m_engine;          /**< Core game logic instance. */
    std::vector<std::string> m_lastResult; /**< Latest spin results for rendering. */
    int m_lastWin;                /**< Score of the last spin. */

    SDL_Window* m_window;         /**< SDL Window pointer. */
    SDL_Renderer* m_renderer;     /**< SDL Renderer pointer. */
    TTF_Font* m_font;             /**< Loaded font for text rendering. */
};
