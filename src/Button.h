#pragma once
#include "Label.h"
#include "EventHandler.h"
#include <functional>
class Button :
    public Label, public EventHandler
{
public: using Callback = std::function<void()>;
private:
    Callback callback;
    bool hover = false;
    bool selected = false;
public:
    void render() const override;
    using Callback = std::function<void()>;
    Button(GameState*, Point2D<float>, SDLApplication::TextureName, std::function<void()> callback, bool b=true);
    void handleEvent(const SDL_Event&) override;
    void connect(Callback);
    bool isInside(float, float);
    void setSelected();
};

