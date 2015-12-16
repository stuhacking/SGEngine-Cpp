//
// Input Implementation
//
#include "../Engine.h"

#include <unordered_map>

namespace sge {

// Map of Keycodes which are currently down.
static std::unordered_map<SDL_Keycode, bool> keyMap;
static std::unordered_map<SDL_Keycode, bool> keysReleased;
static std::unordered_map<SDL_Keycode, bool> keysPressed;

// Mouse Stuff
static std::unordered_map<u32, bool> mouseMap;
static std::unordered_map<u32, bool> mouseReleased;
static std::unordered_map<u32, bool> mousePressed;

static bool mouseLocked;
static Vector2 mousePos;
static Vector2 mouseDelta;

// Other signalled Events caught. These should be flagged and
// handled by the caller.
static bool quit;

// Poll SDL_Event queue and update input state. Should be
// called once per interval before calling other input
// queries.
void Input::Update () {
    keysReleased.clear();
    keysPressed.clear();
    mouseReleased.clear();
    mousePressed.clear();

    mouseDelta.x = mouseDelta.y = 0.0f;

    SDL_Event evt;
    while (SDL_PollEvent(&evt)) {
        switch (evt.type) {
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
            s32 x, y;
            s32 dx, dy;
            SDL_GetMouseState(&x, &y);
            SDL_GetRelativeMouseState(&dx, &dy);

            mousePos.x = static_cast<float>(x);
            mousePos.y = static_cast<float>(y);
            mouseDelta.x += static_cast<float>(dx);
            mouseDelta.y += static_cast<float>(dy);
            break;
        case SDL_MOUSEBUTTONDOWN:
            mousePressed[evt.button.button] = !mouseMap[evt.button.button];
            mouseMap[evt.button.button] = true;
            break;
        case SDL_MOUSEBUTTONUP:
            mouseReleased[evt.button.button] = mouseMap[evt.button.button];
            mouseMap[evt.button.button] = false;
            break;
        default:
            break;
        }
    }
}

//--------------------------
// Keyboard Queries
//--------------------------

bool Input::KeyDown (const SDL_Keycode keyCode) {
    return keyMap[keyCode];
}

bool Input::KeyPressed (const SDL_Keycode keyCode) {
    return keysPressed[keyCode];
}

bool Input::KeyReleased (const SDL_Keycode keyCode) {
    return keysReleased[keyCode];
}

//--------------------------
// Mouse Queries
//--------------------------


void Input::LockMouse () {
    SDL_SetRelativeMouseMode(SDL_TRUE);
    mouseLocked = true;
}

void Input::ReleaseMouse () {
    SDL_SetRelativeMouseMode(SDL_FALSE);
    mouseLocked = false;
}

bool Input::MouseLocked () {
    return mouseLocked;
}

Vector2 Input::GetMousePosition () {
    return mousePos;
}

Vector2 Input::GetMouseDelta () {
    return mouseDelta;
}

bool Input::MouseDown (const u32 button) {
    return mouseMap[button];
}

bool Input::MousePressed (const u32 button) {
    return mousePressed[button];
}

bool Input::MouseReleased (const u32 button) {
    return mouseReleased[button];
}

//--------------------------
// Misc Event Queries
//--------------------------

bool Input::SignalQuit () {
    return quit;
}

} /* namespace sge */