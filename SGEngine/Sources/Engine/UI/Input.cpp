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
static Vector2 mousePos;

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

    SDL_Event evt;
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT) {
            quit = true;
        } else if (evt.type == SDL_KEYDOWN) {
            keysPressed[evt.key.keysym.sym] = !keyMap[evt.key.keysym.sym];
            keyMap[evt.key.keysym.sym] = true;
        } else if (evt.type == SDL_KEYUP) {
            keysReleased[evt.key.keysym.sym] = keyMap[evt.key.keysym.sym];
            keyMap[evt.key.keysym.sym] = false;
        } else if (evt.type == SDL_MOUSEMOTION) {
            int x, y;
            SDL_GetMouseState(&x, &y);

            mousePos.x = static_cast<float>(x);
            mousePos.y = static_cast<float>(y);
        } else if (evt.type == SDL_MOUSEBUTTONDOWN) {
            mousePressed[evt.button.button] = !mouseMap[evt.button.button];
            mouseMap[evt.button.button] = true;
        } else if (evt.type == SDL_MOUSEBUTTONUP) {
            mouseReleased[evt.button.button] = mouseMap[evt.button.button];
            mouseMap[evt.button.button] = false;
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

Vector2 Input::GetMousePosition () {
    return Vector2(mousePos);
}

//--------------------------
// Mouse Queries
//--------------------------

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
