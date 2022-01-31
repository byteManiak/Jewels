#include "engine/input.h"
#include "engine/event.h"

static const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
static Uint8 prevState[SDL_NUM_SCANCODES];
static int mouseX, mouseY;
static int mouseButtons;

std::pair<int,int> getMouseCoords()
{
	return std::make_pair(mouseX, mouseY);
}

bool isMouseButtonPressed(int button)
{
	return mouseButtons & button;
}

static void getMousePos(SDL_Event ev)
{
	mouseX = ev.motion.x;
	mouseY = ev.motion.y;
}

static void getMouseButtons(SDL_Event ev)
{
	if (ev.button.state == SDL_PRESSED) mouseButtons |= ev.button.button;
	else mouseButtons &= ~(ev.button.button);
}

void initInput()
{
	registerToSDLEvent(SDL_MOUSEMOTION, getMousePos);
	registerToSDLEvent(SDL_MOUSEBUTTONDOWN, getMouseButtons);
	registerToSDLEvent(SDL_MOUSEBUTTONUP, getMouseButtons);
}

void updateKeyboard()
{
	memcpy(prevState, keyboardState, sizeof(Uint8)*SDL_NUM_SCANCODES);
}

bool isKeyPressed(SDL_Scancode scancode)
{
	return keyboardState[scancode] && !prevState[scancode];
}

bool isKeyDown(SDL_Scancode scancode)
{
	return keyboardState[scancode] && prevState[scancode];
}

bool isKeyReleased(SDL_Scancode scancode)
{
	return prevState[scancode] && !keyboardState[scancode];
}