#include "PlayState.h"
#include "EndState.h"
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

constexpr const char* const MAP_FILE = "../assets/maps/";

PlayState::PlayState(SDLApplication* g, const std::string& map)
    : GameState(g), mapFile(map) {
    loadMap();
}

PlayState::~PlayState() {
    for (SceneObject* s : sceneObjects) {
        delete s;
    }
    delete infoBar;
}

void PlayState::update() {

    //waspUpdate(); // Se actualizan las avispas (creación)
    for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) (*it)->update(); //Update de todos los sceneObjects
    if ((static_cast<Frog*>(*frog))->getHomesReached() == PlayState::NUM_HOMEFROGS)
    {
       game->replaceState(new EndState(game, true));
    }
    else if ((static_cast<Frog*>(*frog))->getLives() == 0)
    {
        game->replaceState(new EndState(game, false));
    }
    infoBar->update();
    //processPendingDeletes();; // Aqui se eliminan todas las avispas muertas
}

void PlayState::render() const {
    getGame()->textures[SDLApplication::BACKGROUND]->render();
    for (auto it = sceneObjects.begin(); it != sceneObjects.end(); ++it) (*it)->render();
    infoBar->render();
    //frog->render();
}

//void PlayState::addObject(SceneObject* obj) {
//    sceneObjects.push_back(obj);
//}

//void PlayState::deleteAfter(It it) {
//    toDelete = it;
//}

//void PlayState::processPendingDeletes() {
//    if (pendingDelete) {
//        delete* toDelete;
//        objects.erase(toDelete);
//        pendingDelete = false;
//    }
//}

//void
//PlayState::waspUpdate() {
//    
//    if (SDL_GetTicks() - waspSpawn >= nextWasp)
//    {
//        waspSpawn = SDL_GetTicks();
//        if ((static_cast<Frog*>(*frog))->getHomesReached() != Game::NUMBER_HFROGS - 1)
//        {
//            // Genera nueva avispa
//            nextWasp = (float)getRandomRange(MIN_WASP_GENERATOR, MAX_WASP_GENERATOR);
//            float lifeTime = (float)getRandomRange(MIN_WASP_LIFE, MAX_WASP_LIFE);
//            bool encontrado = false;
//            int hf = getRandomRange(0, Game::NUMBER_HFROGS - 1);
//
//            while (!encontrado)
//            {
//                if (!homeFrogsPos[hf].second) encontrado = true;
//                else {
//                    hf++;
//                    if (hf > Game::NUMBER_HFROGS - 1) hf = 0;
//                }
//            }
//            Point2D<float> pos = homeFrogsPos[hf].first;
//
//            pos = pos + Point2D<float>(Game::WASP_OFFSET_X, Game::WASP_OFFSET_Y);
//            Vector2D<float> speed(0, 0);
//
//            sceneObjects.push_back(nullptr);  // reserva un hueco
//            PlayState::It it = --sceneObjects.end();
//            *it = new Wasp(this, pos, lifeTime, speed, it);
//        }
//    }
//}

void 
PlayState::loadMap() {
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
                        sceneObjects.push_back(new Frog(inputString, this, mapFile));
                        frog = --sceneObjects.end();
                    }
                    else if (c == '#');
                    else throw FileFormatError(mapFile, ArchiveLine, "Error de lectura sobre el tipo de elemento");
                }
                ArchiveLine++;
            }
        }
        inputMap.close();

    // Load InfoBar
    infoBar = new InfoBar(this, ((static_cast<Frog*>(*frog))));

    //Load HomeFrogs
    for (int i = 0; i < PlayState::NUM_HOMEFROGS; i++)
    {
        HomeFrog* homeFrog = new HomeFrog(this, homeFrogsPos[i].first, (static_cast<Frog*>(*frog)));
        sceneObjects.push_back(homeFrog);
    }
    //frog = sceneObjects.end();
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


void 
PlayState::handleEvent(SDL_Event& event) {
   (static_cast<Frog*>(*frog))->handleEvent(event);
}

// Condicion de victoria
void
PlayState::homeReached(Point2D<float> position) {
    int hf = position.getX() / Game::SEPARATION_HOMEFROG;
    homeFrogsPos[hf].second = true;
}

