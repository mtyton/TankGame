#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>

class Rocket:public sf::Drawable
{
public:
	Rocket(sf::Vector2f speed, sf::Vector2f position, float rotation);
	~Rocket();
	void update();
	bool out_of_screen();
	void explode();
	sf::Sprite get_sprite();
	void mark_to_destroy(); // sets destroybale
	int deal_dmg();
	bool get_status();
private:
	float *speed = new float(0.10F);
	sf::Vector2f velocity;
	sf::Sprite sprite;
	sf::Texture texture;
	void change_direction(float rotation, sf::Vector2f &position);
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	int dmg;
	bool destroyable; // keeps status if bullet should be destroyed or not
};

