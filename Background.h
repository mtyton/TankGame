#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>

class Background:public::sf::Drawable
{
public:
	Background(int x, int y);
	void change_texture(std::string name);
private:
	sf::Texture texture;
	sf::Sprite sprite;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

};

