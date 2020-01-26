#include "Collider.h"

bool Collider::collision(sf::Sprite first_sprite, sf::Sprite second_sprite)
{
	if (first_sprite.getGlobalBounds().intersects(second_sprite.getGlobalBounds()))
	{
		return true;
	}
	return false;
}
