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
}
MainMenuState::~MainMenuState() {

}

std::string path2string(const std::filesystem::path& p) {
	return reinterpret_cast<const char*>(p.u8string().c_str());
}

void MainMenuState::LoadMaps()
{
    leftArrow = new Button(this, Point2D<float>(100, 300), game->getMapTexture("texts/left.png"), [this]() { selectPreviousButton(); });
    rightArrow = new Button(this, Point2D<float>(350, 300), game->getMapTexture("texts/right.png"), [this]() { selectNextButton(); });
    rightArrow->selected = true;
    leftArrow->selected = true;


    for (auto& entry : filesystem::directory_iterator("../assets/maps/"))
    {
        std::string mapPath = entry.path().string();
        std::string name = entry.path().filename().string();
        auto textPath = TEXTS_ROOT / entry.path().filename().replace_extension(".png");
        std::string textPathString = path2string(textPath);

        Button::Callback cb = [this, name]() {
            game->replaceState(std::make_shared<PlayState>(game, name));
        };
        Button* b = new Button(this, Point2D<float>(225, 300), game->getMapTexture(textPathString), cb);

        maps.push_back({ b, name });
    }
    if (!maps.empty())
    {
        for (int i = 0; i < maps.size(); i++) {
            if (maps[i].second == "Original.txt") { 
                selectedButton = maps[i].first;
                maps[i].first->selected = true;
                selectedIndex = i;
            }
            cout << maps[i].second << endl;
        }
    }

    for (auto& pair : maps)
    {
        addEventListener(pair.first); //se añaden todos los botones
    }

    addEventListener(leftArrow);
    addEventListener(rightArrow);
}


//void
//MainMenuState::handleEvent(SDL_Event& event)
//{
//    // Pasar el evento a los botones de mapas
//    for (auto& pair : maps)
//        pair.first->handleEvent(event);
//
//    // Pasar el evento a las flechas
//    if (leftArrow) leftArrow->handleEvent(event);
//    if (rightArrow) rightArrow->handleEvent(event);
//}
void
MainMenuState::update()
{

}
void 
MainMenuState::render() const
{
    game->textures[SDLApplication::MENU_BACKGROUND]->render();
   
    // render botones de mapas
    for (auto& pair : maps) {
        pair.first->render();
    }
    // render flechas
    if (leftArrow) leftArrow->render();
    if (rightArrow) rightArrow->render();
}

void 
MainMenuState::selectNextButton()
{
    if (maps.empty()) return;
    selectedButton->selected = false;
    if (selectedIndex < maps.size()-1) selectedIndex++;
    else selectedIndex = 0;    selectedButton = maps[selectedIndex].first;
    selectedButton->selected = true;
}

void 
MainMenuState::selectPreviousButton()
{
    if (maps.empty()) return;
    selectedButton->selected = false;
    if (selectedIndex > 0) selectedIndex--;
    else selectedIndex = maps.size()-1;
    selectedButton = maps[selectedIndex].first;
    selectedButton->selected = true;
}
