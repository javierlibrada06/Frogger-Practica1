#pragma once
#include "GameObject.h"
#include "vector2D.h"
#include "PlayState.h"
#include "SDL3/SDL.h"
class SceneObject : public GameObject
{
protected:
	Point2D<float> position;
	Texture* texture;
	PlayState* play;
	SDL_FRect getBoundingBox() const;

public:	
	static constexpr int ANGLE_LEFT = -90;
	static constexpr int ANGLE_RIGHT = 90;
	static constexpr int ANGLE_UPSIDEDOWN = 180;

	SceneObject();
	SceneObject(std::istream&, PlayState*, std::string);
	virtual ~SceneObject() = default;
	void render() const;
	virtual PlayState::Collision checkCollision(const SDL_FRect& other) = 0;
};

