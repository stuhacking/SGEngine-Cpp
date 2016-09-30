//
// A Basic Test that SDL2 + OpenGL is working.
//
#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include <cmath>

#include "Engine.h"
#include "Game.h"

using namespace sge;

static std::unique_ptr<Game> game;

int main (int argc, char *argv[]) {
    InitSGEApplication("Test App", 1280, 800, false);

    if (!window->IsInitialized()) {
        std::cerr << "Error initializing SGE Window.\n";
        return 1;
    }

    game = std::unique_ptr<Game>(new Game(window->GetWidth(), window->GetHeight()));
    if (!game->Init()) {
        std::cerr << "Failure during game init!\n";
        return 1;
    }

    window->Clear();

    float clockSpeed = 1.0f;
    Clock gameClock = Clock(clockSpeed);
    while (!Input::SignalQuit() && !Input::KeyReleased(Input::Key::Escape)) {
        gameClock.Update();
        Input::Update();

        if (Input::KeyReleased(Input::Key::Space)) {
            gameClock.Pause(!gameClock.IsPaused());
        }

        if (Input::KeyDown(Input::Key::PageUp)) {
            clockSpeed *= 2.0f;
            gameClock.SetScale(clockSpeed);
        }

        if (Input::KeyDown(Input::Key::PageDown)) {
            if (clockSpeed >= 2.0f) {
                clockSpeed /= 2.0f;
            }
            gameClock.SetScale(clockSpeed);
        }

        game->Input();
        game->Update(gameClock.DeltaSeconds());

        window->Clear();

        game->Render();

        //window->Delay(33);
        window->Update();
    }

    return 0;
}
