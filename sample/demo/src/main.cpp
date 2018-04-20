//
// A Basic test that simple engine features are working.
//
#include <SDL2/SDL.h>
#include <memory>
#include <iostream>
#include <cmath>

#include "engine.h"
#include "game.h"

using namespace sge;

struct AppSettings {
    u32 width = 320;
    u32 height = 240;
    float fov = 50.0f;
    bool fullscreen = false;
};

static AppSettings settings;
static std::unique_ptr<Game> game;

static bool readAppSettings () {
    JSONFile initFile("data/init.json");
    const json::Document &doc = *(initFile.rootDocument());

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
    readAppSettings();
    initSGEApplication("Lighting Demo", settings.width, settings.height,
                       settings.fullscreen);

    if (!gWindow->isInitialized()) {
        gConsole.error("Error initializing SGE Window.\n");
        return 1;
    }

    game = std::unique_ptr<Game>(new Game(gWindow->width(), gWindow->height()));
    if (!game->init()) {
        gConsole.error("Failure during game init!\n");
        return 1;
    }

    gWindow->clear();

    float clockSpeed = 1.0f;
    Clock gameClock = Clock(clockSpeed);
    while (!Input::signalQuit() && !Input::keyReleased(Input::Key::Escape)) {
        gameClock.update();
        Input::update();

        if (Input::keyReleased(Input::Key::Space)) {
            gameClock.pause(!gameClock.isPaused());
        }

        if (Input::keyReleased(Input::Key::PageUp)) {
            clockSpeed *= 2.0f;
            gameClock.setScale(clockSpeed);
        }

        if (Input::keyReleased(Input::Key::PageDown)) {
            if (clockSpeed >= 2.0f) {
                clockSpeed /= 2.0f;
            }
            gameClock.setScale(clockSpeed);
        }

        game->input();
        game->update(gameClock.deltaSeconds());

        gWindow->clear();

        game->render();

        gWindow->update();
    }

    return 0;
}
