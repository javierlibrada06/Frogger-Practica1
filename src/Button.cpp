#include "Button.h"
#include <SDL3/SDL.h>
Button::Button(GameState* g, Point2D<float> p, SDLApplication::TextureName t, Callback c)
	: Label(g, p, t)
{
    connect(c);
}

void 
Button::render() const {

    texture->render(getBoundingBox());
    SDL_Color magenta = { 255, 0, 255 };
    if (hover) texture->render(getBoundingBox(), magenta);
}
void 
Button::connect(Callback cb) {
    callback = cb;
}
void 
Button::handleEvent(const SDL_Event& event) {

    if (event.type == SDL_EVENT_MOUSE_MOTION || event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        int x = event.motion.x;
        int y = event.motion.y;

        hover = isInside(x, y); // hover es un booleano de la clase Button
        if (hover && event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (callback) callback(); // Ejecuta la función
        }
    }
}
bool
Button::isInside(float x, float y) {
    SDL_FRect rect = getBoundingBox();

   return   x >= rect.x &&
            x <= rect.x + rect.w &&
            y >= rect.y &&
            y <= rect.y + rect.h;
}
