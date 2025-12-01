#pragma once

#include <list>
#include <string>
#include <SDL3/SDL.h>

#include "GameState.h"
#include "EventHandler.h"
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
    // Numero de nidos
    static constexpr float NUM_HOMEFROGS = 5;
    // Fin juego fuera pantalla izquierda
    static constexpr float GAME_END_LEFT = -150.0f;
    // WASP -- (tiempo en milisegundos)
// Avispas tiempo de vida max 
    static constexpr float MAX_WASP_LIFE = 7000.0f;
    // Avispas tiempo de vida max
    static constexpr float MIN_WASP_LIFE = 5000.0f;
    // Avispas tiempo de generacion max
    static constexpr float MIN_WASP_GENERATOR = 7500.0f;
    // Avispas tiempo de generacion min
    static constexpr float MAX_WASP_GENERATOR = 9500.0f;
    // WASP -- (wasp offset)
    static constexpr int WASP_OFFSET_X = 8;
    static constexpr int WASP_OFFSET_Y = 4;


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
    InfoBar* infoBar;
    int ArchiveLine;
    float nextWasp;
    Uint32 waspSpawn;

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

public:
    PlayState(SDLApplication* g, const std::string& map, std::list<SceneObject*> list);
    ~PlayState();

    // Métodos principales
    void update() override;
    void render() const override;

    // Cargar mapa
    void loadMap();


    //// Eliminar objetos (Wasp)
    //void deleteAfter(It it);
    void waspDelete(It);

    PlayState::Collision checkCollision(const SDL_FRect& rect) const;


    // Lectura de archivo
    int getArchiveLine() const { return archiveLine; }
    void incArchiveLine() { archiveLine++; }

    void homeReached(Point2D<float>);
    void pause();

private:
    void waspUpdate();
    int getRandomRange(int, int);
};


