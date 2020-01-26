#pragma once
#include<SFML/Graphics.hpp>
#include <iostream>

// class which checks collision
class Collider
{
	public:
		bool collision(sf::Sprite first_sprite, sf::Sprite second_sprite);
};