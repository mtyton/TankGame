#include "Rocket.h"

Rocket::Rocket(sf::Vector2f speed, sf::Vector2f position, float rotation)
{	
	texture.loadFromFile("Sprites/Bullet.png");
	sprite.setTexture(texture);
	sprite.setScale(0.5f, 0.5f);
	velocity = speed;
	velocity.x *= 5;
	velocity.y *= 5;
	change_direction(rotation, position);
	sprite.setPosition(position);
	dmg = 2;
	destroyable = false;
}

Rocket::~Rocket()
{

}

void Rocket::update()
{
	sprite.move(velocity);
}

bool Rocket::out_of_screen()
{
	// TODO repare this
	sf::Vector2f* position = new sf::Vector2f;
	*position = sprite.getPosition();
	if (position->y < 0 ||
		position->y > 800||
		position->x > 800 ||
		position->x < 0)
	{
		delete position;
		return true;
	}
	delete position;
	return false;
}

void Rocket::explode()
{
	this->~Rocket();
}

sf::Sprite Rocket::get_sprite()
{
	return sprite;
}

void Rocket::mark_to_destroy()
{
	destroyable = true;
}

int Rocket::deal_dmg()
{
	return dmg;
}

bool Rocket::get_status()
{
	return destroyable;
}

void Rocket::change_direction(float rotation, sf::Vector2f &position)
{
	sprite.setRotation(rotation);

	if (rotation == 0.0f)
	{
		position.x -= 12.5;
		position.y -= 12.5;
	}
	else if (rotation == 90.0f)
	{
		position.x += 12.5;
		position.y -= 12.5;
	}
	else if (rotation == 180.0f)
	{
		position.x += 12.5;
		position.y += 12.5;
	}
	
	else if (rotation == 270.0f)
	{
		position.x -= 12.5;
		position.y += 12.5;
	}

}

void Rocket::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(sprite, state);
}
