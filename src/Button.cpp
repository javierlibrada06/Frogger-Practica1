#include "Button.h"
#include <SDL3/SDL.h>
Button::Button(GameState* g, Point2D<float> p, SDLApplication::TextureName t, Callback c, bool b)
	: Label(g, p, t)
{
    connect(c);
    selected = b;
}

void
Button::render() const
{
    if (!texture) return;
    else if (selected) {
        if (hover) {
            SDL_Color magenta = { 255, 0, 255, 1 };
            texture->render(getBoundingBox(), magenta);
        }
        else texture->render(getBoundingBox());
    }
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
        if (hover && selected && event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
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
void
Button::setSelected() { selected = !selected; }
