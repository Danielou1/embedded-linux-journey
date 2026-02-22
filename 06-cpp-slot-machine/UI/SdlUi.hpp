/**
 * @file SdlUi.hpp
 * @author Danielou Mounsande
 * @brief Defines the SdlUi class for the graphical user interface.
 * 
 * This class uses the SDL3 library to create a graphical window,
 * render the slot machine, and handle user input.
 */
#pragma once
#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include "../GameEngine.hpp"

/**
 * @class SdlUi
 * @brief Manages the SDL-based graphical user interface for the slot machine.
 * 
 * This class encapsulates all SDL-related functionality, including window creation,
 * rendering, event handling, and managing the main game loop.
 */
class SdlUi {
public:
    /**
     * @brief Constructs a new SdlUi object.
     * 
     * Initializes member variables to their default states.
     */
    SdlUi();

    /**
     * @brief Destroys the SdlUi object.
     * 
     * Ensures that all SDL resources are properly cleaned up.
     */
    ~SdlUi();

    /**
     * @brief Starts the main game loop.
     * 
     * This method initializes the UI, and then enters a loop to handle events,
     * update game state, and render the graphics until the user quits.
     */
    void run();

private:
    /**
     * @brief Initializes the SDL library and creates the window and renderer.
     * @return True if initialization was successful, false otherwise.
     */
    bool init();

    /**
     * @brief Processes user input and other events.
     * 
     * Handles events like closing the window or pressing a key.
     */
    void handleEvents();

    /**
     * @brief Updates the game logic.
     * 
     * This is where the game state changes, e.g., after a spin.
     */
    void update();

    /**
     * @brief Renders the current game state to the screen.
     * 
     * Clears the screen and draws all visual elements of the slot machine.
     */
    void render();

    /**
     * @brief Frees resources and shuts down SDL.
     * 
     * Called when the game loop ends to clean up allocated resources.
     */
    void clean();

    bool m_isRunning;  ///< Flag to control the main game loop.
    GameEngine m_engine; ///< The core game engine instance.
    std::vector<std::string> m_lastResult; ///< Stores the result of the last spin.
    int m_lastWin; ///< Stores the payout from the last spin.

    SDL_Window* m_window;     ///< Pointer to the main SDL window.
    SDL_Renderer* m_renderer; ///< Pointer to the SDL renderer for drawing.
};
