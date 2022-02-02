#include "engine/event.h"
#include "engine/input.h"

#include <unordered_map>
#include <vector>
#include <SDL2/SDL.h>

std::unordered_map<SDL_EventType, std::vector<std::function<void(SDL_Event)>>> eventRegistry = {};

void registerToSDLEvent(SDL_EventType eventType, std::function<void(SDL_Event)> cb)
{
    if (eventRegistry.find(eventType) == eventRegistry.end())
    {
        eventRegistry[eventType] = std::vector<std::function<void(SDL_Event)>>();
    }

    eventRegistry[eventType].push_back(cb);
}

void processSDLEvents()
{
    SDL_PumpEvents();

    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        if (eventRegistry.find((SDL_EventType)ev.type) != eventRegistry.end())
        {
            for(auto &i : eventRegistry[(SDL_EventType)ev.type]) i(ev);
        }
    }
}

void updateEvents()
{
	updateKeyboard();
	processSDLEvents();
}