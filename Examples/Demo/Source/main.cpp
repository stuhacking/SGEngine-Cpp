//
// A Basic Test that simple engine features are working.
//
#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include <cmath>

#include "Engine.h"
#include "Game.h"

using namespace sge;

struct AppSettings {
    u32 width = 320;
    u32 height = 240;
    float fov = 50.0f;
    bool fullscreen = false;
};

static AppSettings settings;
static std::unique_ptr<Game> game;

static bool ReadAppSettings () {
    JSONFile initFile("data/init.json");
    const json::Document &doc = *(initFile.GetRootDocument());

    if (!doc.HasParseError()) {
        for (const auto &prop : doc.GetObject()) {
            if (strncmp("width", prop.name.GetString(), 5) == 0 && prop.value.IsInt()) {
                settings.width = static_cast<u32>(prop.value.GetInt());
            }
            if (strncmp("height", prop.name.GetString(), 6) == 0 && prop.value.IsInt()) {
                settings.height = static_cast<u32>(prop.value.GetInt());
            }
            if (strncmp("fullscreen", prop.name.GetString(), 10) == 0 && prop.value.IsBool()) {
                settings.fullscreen = prop.value.GetBool();
            }
            if (strncmp("fov", prop.name.GetString(), 3) == 0 && prop.value.IsNumber()) {
                settings.fov = prop.value.GetFloat();
            }
        }

        return true;
    }

    return false;
}

int main (int argc, char *argv[]) {
    ReadAppSettings();
    InitSGEApplication("Lighting Demo", settings.width, settings.height, settings.fullscreen);

    if (!window->IsInitialized()) {
        console.Error("Error initializing SGE Window.\n");
        return 1;
    }

    game = std::unique_ptr<Game>(new Game(window->GetWidth(), window->GetHeight()));
    if (!game->Init()) {
        console.Error("Failure during game init!\n");
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
