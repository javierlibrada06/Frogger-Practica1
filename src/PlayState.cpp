#include "PlayState.h"
#include "EndState.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "Frog.h"
#include "Vehicle.h"
#include "Log.h"
#include "Wasp.h"
#include "TurtleGroup.h"
#include "InfoBar.h"
#include "HomeFrog.h"

#include "FileFormatError.h"
#include "FileNotFoundError.h"
#include "SceneObject.h"
#include "SDLApplication.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <format>
#include <random>

constexpr const char* const MAP_FILE = "../assets/maps/";

PlayState::PlayState(SDLApplication* g, const std::string& map, std::list<SceneObject*> list)
    : GameState(g), mapFile(map) {
    sceneObjects = list;
    loadMap();
    nextWasp = getRandomRange(MIN_WASP_GENERATOR, MAX_WASP_GENERATOR);
    waspSpawn = SDL_GetTicks();
}

PlayState::~PlayState() {
    for (SceneObject* s : sceneObjects) {
        delete s;
    }
    for (GameObject* g : gameObjects) {
        delete g;
    }
}

void PlayState::update() {

    if ((static_cast<Frog*>(*frog))->getHomesReached() == PlayState::NUM_HOMEFROGS)
    {
        game->replaceState(new EndState(game, true));
    }
    else if ((static_cast<Frog*>(*frog))->getLives() == 0)
    {
        game->replaceState(new EndState(game, false));
    }
    waspUpdate(); // Se actualizan las avispas (creación)
    for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) (*it)->update(); //Update de todos los sceneObjects
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) (*it)->update();
    delayedCallBack();
}

void PlayState::render() const {
    getGame()->textures[SDLApplication::BACKGROUND]->render();
    for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) (*it)->render();
    for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) (*it)->render();
}

void
PlayState::waspDelete(It it)
{
    delete* it;         // Libera memoria
    sceneObjects.erase(it); // Elimina del vector
}

void
PlayState::waspUpdate() {
    
    if (SDL_GetTicks() - waspSpawn >= nextWasp)
    {
        waspSpawn = SDL_GetTicks();
        if ((static_cast<Frog*>(*frog))->getHomesReached() != NUM_HOMEFROGS - 1)
        {
            // Genera nueva avispa
            nextWasp = (float)getRandomRange(MIN_WASP_GENERATOR, MAX_WASP_GENERATOR);
            float lifeTime = (float)getRandomRange(MIN_WASP_LIFE, MAX_WASP_LIFE);
            bool encontrado = false;
            int hf = getRandomRange(0, NUM_HOMEFROGS - 1);

            while (!encontrado)
            {
                if (!homeFrogsPos[hf].second) encontrado = true;
                else {
                    hf++;
                    if (hf > NUM_HOMEFROGS - 1) hf = 0;
                }
            }
            Point2D<float> pos = homeFrogsPos[hf].first;

            pos = pos + Point2D<float>(PlayState::WASP_OFFSET_X, PlayState::WASP_OFFSET_Y);

            std::string wasp = std::format("{} {} {} {} {}", pos.getX(), pos.getY(), 0, 0, lifeTime);
            std::istringstream inputString(wasp);
            sceneObjects.push_back(nullptr);  // reserva un hueco
            PlayState::It it = --sceneObjects.end();
            *it = new Wasp(inputString, this, it, "Avispa Update");
        }
    }
}

void 
PlayState::loadMap() {
    if (sceneObjects.empty()) {
        std::ifstream inputMap;
        inputMap.open(std::string(MAP_FILE) + mapFile);
        if (!inputMap.is_open()) throw FileNotFoundError(mapFile);
        else
        {
            ArchiveLine = 1;
            std::string l;
            while (std::getline(inputMap, l)) {
                std::istringstream inputString(l);
                char c;
                if (!(inputString >> c)) throw FileFormatError(mapFile, ArchiveLine, "Error de lectura sobre el tipo de elemento");
                else
                {
                    if (c == 'V') sceneObjects.push_back(new Vehicle(inputString, this, mapFile));
                    else if (c == 'L') sceneObjects.push_back(new Log(inputString, this, mapFile));
                    else if (c == 'T') sceneObjects.push_back(new TurtleGroup(inputString, this, mapFile));
                    else if (c == 'F') {
                        Frog* f = new Frog(inputString, this, mapFile);
                        sceneObjects.push_back(f);
                        addEventListener(f);
                        frog = --sceneObjects.end();
                    }
                    else if (c == 'W') {
                        sceneObjects.push_back(nullptr);
                        PlayState::It it = --sceneObjects.end();
                        *it = new Wasp(inputString, this, it, mapFile);
                    }
                    else if (c == '#');
                    else throw FileFormatError(mapFile, ArchiveLine, "Error de lectura sobre el tipo de elemento");
                }
                ArchiveLine++;
            }
        }
        inputMap.close();

        // Load InfoBar
        //infoBar = new InfoBar(this, ((static_cast<Frog*>(*frog))));
        gameObjects.push_back(new InfoBar(this, ((static_cast<Frog*>(*frog)))));

        //Load HomeFrogs
        for (int i = 0; i < PlayState::NUM_HOMEFROGS; i++)
        {
            HomeFrog* homeFrog = new HomeFrog(this, homeFrogsPos[i].first, (static_cast<Frog*>(*frog)));
            sceneObjects.push_back(homeFrog);
        }
        //frog = sceneObjects.end();
    }
}

PlayState::Collision
PlayState::checkCollision(const SDL_FRect& rect) const
{
    Collision collision;
    collision.type = NONE;
    auto it = sceneObjects.begin();
    while (it != sceneObjects.end() && collision.type == NONE) {
        collision = (*it)->checkCollision(rect);
        it++;
    }
    return collision;

}

// Condicion de victoria
void
PlayState::homeReached(Point2D<float> position) {
    int hf = position.getX() / PlayState::SEPARATION_HOMEFROG;
    homeFrogsPos[hf].second = true;
}

// Random (wasps)
int
PlayState::getRandomRange(int min, int max) {
    static std::random_device rd;
    static std::mt19937 randomGenerator(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(randomGenerator);
}

void
PlayState::pause() {
    game->pushState(new PauseState(game, mapFile, sceneObjects));
}

