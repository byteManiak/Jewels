#pragma once

#include <functional>
#include <SDL2/SDL.h>

/**
 * @brief Register a callback to the given event type. The parameter in the callback
 * will be used as a copy of the triggered event, to be used within the callback's context.
 * @param eventType Type of the event to register the callback to.
 * @param cb Callback to register to the event type.
 */
void registerToSDLEvent(SDL_EventType eventType, std::function<void(SDL_Event)> cb);

/**
 * @brief Processes all SDL events through SDL_PollEvent and SDL_PumpEvents.
 */
void processSDLEvents();

/**
 * @brief Process SDL events.
 */
void updateEvents();