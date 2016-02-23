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

static std::unique_ptr<SGEWindow> win;

static std::unique_ptr<Game> game;

int main (int argc, char *argv[]) {

    win = std::unique_ptr<SGEWindow>(new SGEWindow("Hello World", 1024, 576));

    if (!win->IsInitialized()) {
        std::cerr << "Error initializing SGE Window.\n";
        return 1;
    }

    game = std::unique_ptr<Game>(new Game(win->GetWidth(), win->GetHeight()));
    if (!game->Init()) {
        std::cerr << "Failure during game init!\n";
        return 1;
    }

    win->Clear();

    float clockSpeed = 1.0f;
    Clock gameClock = Clock(clockSpeed);
    while (!Input::SignalQuit() && !Input::KeyReleased(Input::Key::Escape)) {
        gameClock.Update();
        Input::Update();

        if (Input::KeyReleased(Input::Key::Space)) {
            gameClock.Pause(!gameClock.IsPaused());
        }

        game->Input();
        game->Update(gameClock.DeltaSeconds());

        win->Clear();

        game->Render();

        win->Delay(33);
        win->Update();
    }

    return 0;
}
