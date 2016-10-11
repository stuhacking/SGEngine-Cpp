//
// Input Implementation
//
#include "../../Engine.h"

#include <SDL2/SDL.h>
#include <map>

namespace sge {

static SDL_Keycode sdlKeyMap[24] = {
    SDLK_SPACE, SDLK_ESCAPE, SDLK_BACKSPACE, SDLK_RETURN, SDLK_KP_ENTER,
    SDLK_INSERT, SDLK_DELETE, SDLK_END, SDLK_HOME, SDLK_PAGEUP, SDLK_PAGEDOWN,
    SDLK_PAUSE, SDLK_PRINTSCREEN, SDLK_LCTRL, SDLK_RCTRL, SDLK_LALT, SDLK_RALT,
    SDLK_LSHIFT, SDLK_RSHIFT, SDLK_TAB, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT
};

// Map of Keycodes which are currently down.
static std::map<SDL_Keycode, bool> keyMap;
static std::map<SDL_Keycode, bool> keysReleased;
static std::map<SDL_Keycode, bool> keysPressed;

// Mouse Stuff
static constexpr u32 MOUSE_BUTTONS = 3;

struct mouse_state {
    bool buttons[MOUSE_BUTTONS];
    bool locked;
    // Cache SDL Mouse position each update.
    Vec2f pos;
    Vec2f delta;
};

static struct mouse_state mouse;
static struct mouse_state lastMouse;

// Other signalled Events caught. These should be flagged and
// handled by the caller.
static bool quit;

// Poll SDL_Event queue and update input state. Should be
// called once per interval before calling other input
// queries.
void Input::Update () {
    keysReleased.clear();
    keysPressed.clear();

    // Reset Mouse buttons
    lastMouse = mouse;
    mouse.delta.Zero();

    SDL_Event evt;
    while (SDL_PollEvent(&evt)) {
        switch (evt.type) {
        // TODO(smh): Maybe split input polling from window event polling.
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            keysPressed[evt.key.keysym.sym] = !keyMap[evt.key.keysym.sym];
            keyMap[evt.key.keysym.sym] = true;
            break;
        case SDL_KEYUP:
            keysReleased[evt.key.keysym.sym] = keyMap[evt.key.keysym.sym];
            keyMap[evt.key.keysym.sym] = false;
            break;
        case SDL_MOUSEMOTION:
            i32 x, y, dx, dy;

            SDL_GetMouseState(&x, &y);
            SDL_GetRelativeMouseState(&dx, &dy);

            mouse.pos.x = static_cast<float>(x);
            mouse.pos.y = static_cast<float>(y);
            mouse.delta.x += static_cast<float>(dx);
            mouse.delta.y += static_cast<float>(dy);
            break;
        case SDL_MOUSEBUTTONDOWN:
            mouse.buttons[evt.button.button] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            mouse.buttons[evt.button.button] = false;
            break;
        default:
            break;
        }
    }
}

//--------------------------
// Keyboard Queries
//--------------------------

bool Input::KeyDown (const Key keyCode) {
    return keyMap[sdlKeyMap[keyCode]];
}

bool Input::KeyDown (const char keyCode) {
    return keyMap[keyCode];
}

bool Input::KeyPressed (const Key keyCode) {
    return keysPressed[sdlKeyMap[keyCode]];
}

bool Input::KeyPressed (const char keyCode) {
    return keysPressed[keyCode];
}

bool Input::KeyReleased (const Key keyCode) {
    return keysReleased[sdlKeyMap[keyCode]];
}

bool Input::KeyReleased (const char keyCode) {
    return keysReleased[keyCode];
}

//--------------------------
// Mouse Queries
//--------------------------


void Input::LockMouse () {
    i32 x, y;
    SDL_SetRelativeMouseMode(SDL_TRUE);
    // Throw away any current accumulated mouse delta. Avoids sudden
    // jerk when entering locked mouse state.
    SDL_GetRelativeMouseState(&x, &y);
    mouse.locked = true;
}

void Input::ReleaseMouse () {
    SDL_SetRelativeMouseMode(SDL_FALSE);
    mouse.locked = false;
}

bool Input::MouseLocked () {
    return mouse.locked;
}

Vec2f Input::GetMousePosition () {
    return mouse.pos;
}

Vec2f Input::GetMouseDelta () {
    return mouse.delta;
}

bool Input::MouseDown (const u32 button) {
    return mouse.buttons[button];
}

bool Input::MousePressed (const u32 button) {
    return mouse.buttons[button] && !lastMouse.buttons[button];
}

bool Input::MouseReleased (const u32 button) {
    return !mouse.buttons[button] && lastMouse.buttons[button];
}

//--------------------------
// Misc Event Queries
//--------------------------

bool Input::SignalQuit () {
    return quit;
}

} /* namespace sge */
