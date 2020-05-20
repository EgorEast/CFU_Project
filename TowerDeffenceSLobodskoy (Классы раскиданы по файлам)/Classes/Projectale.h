#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"

class Projectale :public Entity {
public:
	int direction;//направление снарядов

	Projectale(Image& image, String Name, Vector2f startPos, int Width, int Height);
	void update(float time);
	void move();
	void collision();
};