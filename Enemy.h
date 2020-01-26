#pragma once
#include<SFML/Graphics.hpp>
#include"Player.h"
#include<random>
#include<math.h>
#include <ctime>
#include"Rocket.h"

enum Directions{ UP, DOWN, LEFT, RIGHT }; // all possible tank directions


class Enemy:public sf::Drawable
{
public:
	Enemy(float x, float y);
	~Enemy();
	void update(sf::Vector2f playerPos, sf::RenderWindow& window);
	sf::Sprite get_sprite();
	void set_position(float x, float y);
	void take_dmg(int dmg);
	bool check_life();
	bool get_bullet_status(); // returns shot variable
	Rocket *get_shell();
	void search_player(sf::Vector2f player_position);
	
private:
	// font and text use to show hp on screen
	sf::Text text;
	sf::Font font;
	//checks if there is player in sight
	bool player_in_sight(sf::Vector2f playerPos, sf::Vector2f selfMod);
	int hp;
	int offset; // offset to detect player
	sf::Sprite *sprite;
	sf::Texture texture;
	void draw(sf::RenderTarget& target, sf::RenderStates state)const override;
	sf::Vector2f get_check_margin(sf::RenderWindow& window);
	Directions direction;
	Directions randomize_direction();
	bool shot; // variable says if the bullet was shot
	Rocket* shell{};
	void move();
	void logic(sf::Vector2f playerPos, sf::RenderWindow& window);
	void set_direction();
	void shoot();
	void avoid_wall_collision(sf::RenderWindow& window);
	sf::Vector2f* velocity;
	void show_hp(sf::RenderWindow& window);
};