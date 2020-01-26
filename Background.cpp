#include "Background.h"

Background::Background(int x, int y)
{
	texture.loadFromFile("Sprites/background.png");
	sprite.setTexture(texture);
	
}

void Background::change_texture(std::string name)
{
	texture.loadFromFile("Sprites/" + name + ".png");
	sprite.setTexture(texture);
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(sprite);
}
