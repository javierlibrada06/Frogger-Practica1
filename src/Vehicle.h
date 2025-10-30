#pragma once
#include "game.h"
#include "vector2D.h"
#include "texture.h"
#include "Crosser.h"
class Vehicle : public Crosser
{
public:
	Vehicle();
	void loadVehicle(std::istream& entrada, Game* g);
	~Vehicle();
	void update();
	void render() const;
};

