#pragma once

#include <list>
#include <string>
#include <SDL3/SDL.h>

#include "GameState.h"
#include "SceneObject.h"
#include "Game.h"

class Frog; // forward
class Texture;
class SDLApplication;

class PlayState : public GameState {
public:
    using It = std::list<SceneObject*>::iterator;

private:
    std::list<SceneObject*> sceneObjects;
    It frog;
    int ArchiveLine;

    // Gestión del mapa
    std::string mapFile;
    int archiveLine = 1;

    // Eliminación segura
    It toDelete;

public:
    PlayState(SDLApplication* g, const std::string& map);
    ~PlayState();

    // Métodos principales
    void handleEvent(SDL_Event& event) override;
    void update() override;
    void render() const override;

    // Cargar mapa
    void loadMap();

    // Crear objetos
    //void addObject(SceneObject* obj);

    //void waspUpdate();

    // Eliminar objetos (Wasp)
    //void deleteAfter(It it);
    //void waspDelete();

    // Acceso a Frog
    //Frog* getFrog() const { return frog; }

    // Lectura de archivo
    int getArchiveLine() const { return archiveLine; }
    void incArchiveLine() { archiveLine++; }
};


