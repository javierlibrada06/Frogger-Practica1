#pragma once

#include <list>
#include <string>
#include <SDL3/SDL.h>

#include "GameState.h"
#include "Game.h"

class Frog; // forward
class Texture;
class SDLApplication;
class SceneObject;

class PlayState : public GameState {
public:
    // Pos Y dE HomeFrogs
    static constexpr float POS_Y_HOMEFROG = 19;
    // Pos x del primer HomeFrogs
    static constexpr float POS_X_HOMEFROG = 13;
    // Separacion HomeFrogs
    static constexpr float SEPARATION_HOMEFROG = 96;
    // Fin juego fuera pantalla izquierda
    static constexpr float GAME_END_LEFT = -150.0f;

    enum Type
    {
        NONE, ENEMY, PLATFORM, HOME
    };

    struct Collision
    {
        Type type;
        Vector2D<float> speed;
    };

    using It = std::list<SceneObject*>::iterator;

private:
    std::list<SceneObject*> sceneObjects;
    It frog;
    int ArchiveLine;

    std::vector<std::pair<Point2D<float>, bool> > homeFrogsPos = {
        std::pair(Point2D<float>(POS_X_HOMEFROG,POS_Y_HOMEFROG), false),
        std::pair(Point2D<float>(POS_X_HOMEFROG + SEPARATION_HOMEFROG * 1,POS_Y_HOMEFROG), false),
        std::pair(Point2D<float>(POS_X_HOMEFROG + SEPARATION_HOMEFROG * 2,POS_Y_HOMEFROG), false),
        std::pair(Point2D<float>(POS_X_HOMEFROG + SEPARATION_HOMEFROG * 3,POS_Y_HOMEFROG), false),
        std::pair(Point2D<float>(POS_X_HOMEFROG + SEPARATION_HOMEFROG * 4,POS_Y_HOMEFROG), false),
    };

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
    void homeReached(Point2D<float>);

    //// Eliminar objetos (Wasp)
    //void deleteAfter(It it);
    //void waspDelete();

    //Acceso a Frog
    //Frog* getFrog() const { return frog; }

    PlayState::Collision checkCollision(const SDL_FRect& rect) const;


    // Lectura de archivo
    int getArchiveLine() const { return archiveLine; }
    void incArchiveLine() { archiveLine++; }
};


