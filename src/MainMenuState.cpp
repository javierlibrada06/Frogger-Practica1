#include "MainMenuState.h"
#include "SDLApplication.h"
#include "PlayState.h"
#include "Button.h"
#include "Label.h"
#include <filesystem>
#include <iostream>
using namespace std;
const std::filesystem::path TEXTS_ROOT = "texts/";

MainMenuState::MainMenuState(SDLApplication* g) 
    : GameState(g) {
    CreateMapButtons();
    CreateArrowButtons();

    Button* b = new Button(this, Point2D<float>(MAP_BUTTON_POS_X, MAP_BUTTON_POS_Y + MAP_BUTTON_SEPARATION_Y), SDLApplication::SALIR,
                           [this]() { game->exitGame(); });
    gameObjects.push_back(b);
    addEventListener(b);
}

std::string path2string(const std::filesystem::path& p) {
	return reinterpret_cast<const char*>(p.u8string().c_str());
}
void MainMenuState::CreateMapButtons()
{
    for (auto& entry : filesystem::directory_iterator("../assets/maps/"))
    {
        std::string mapPath = entry.path().string();
        std::string name = entry.path().filename().string();
        auto textPath = TEXTS_ROOT / entry.path().filename().replace_extension(".png");
        std::string textPathString = path2string(textPath);
        std::list<SceneObject*> list;
        Button::Callback cb = [this, name, list]() {
                game->replaceState(std::make_shared<PlayState>(game, name, list));
            };
        Button* b = new Button(this, Point2D<float>(MAP_BUTTON_POS_X, MAP_BUTTON_POS_Y), game->getMapTexture(textPathString), cb);
        gameObjects.push_back(b);

        maps.push_back({ b, name });
    }
    if (!maps.empty())
    {
        for (int i = 0; i < maps.size(); i++)
        {
            if (maps[i].second == "Original.txt")
            {
                selectedButton = maps[i].first;
                selectedIndex = i;
            }

            else maps[i].first->setSelected();
        }
    }

    for (auto& pair : maps)
    {
        addEventListener(pair.first); //se añaden todos los botones
    }
}
void MainMenuState::CreateArrowButtons()
{
    leftArrow = new Button(this, Point2D<float>(LEFT_ARROW_POS_X, MAP_BUTTON_POS_Y), game->getMapTexture("texts/left.png"), [this]() { selectPreviousButton(); });
    rightArrow = new Button(this, Point2D<float>(MAP_BUTTON_POS_Y + MAP_BUTTON_SEPARATION_Y, MAP_BUTTON_POS_Y), game->getMapTexture("texts/right.png"), [this]() { selectNextButton(); });

    gameObjects.push_back(leftArrow);
    gameObjects.push_back(rightArrow);

    gameObjects.push_back(new Label(this, Point2D<float>(MAP_BUTTON_POS_X, TITLE_ACTION_POS_Y), SDLApplication::ELEGIR));

    //se añaden las flechitas al event
    addEventListener(leftArrow);
    addEventListener(rightArrow);
}

void
MainMenuState::render() const
{
    game->getTexture(SDLApplication::MENU_BACKGROUND)->render();
    GameState::render();
}


void 
MainMenuState::selectNextButton()
{
    if (maps.empty()) return;
    selectedButton->setSelected();
    if (selectedIndex < maps.size()-1) selectedIndex++;
    else selectedIndex = 0;    selectedButton = maps[selectedIndex].first;
    selectedButton->setSelected();
}

void 
MainMenuState::selectPreviousButton()
{
    if (maps.empty()) return;
    selectedButton->setSelected();
    if (selectedIndex > 0) selectedIndex--;
    else selectedIndex = maps.size()-1;
    selectedButton = maps[selectedIndex].first;
    selectedButton->setSelected();
}

void
MainMenuState::handleEvent(const SDL_Event& event) {
    GameState::handleEvent(event);
    if (event.type == SDL_EVENT_KEY_DOWN ) {
       if (event.key.key == SDLK_RETURN) maps[selectedIndex].first->CallBack();
       if (event.key.key == SDLK_LEFT) selectPreviousButton();
       if (event.key.key == SDLK_RIGHT) selectNextButton();
    }

}
