#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include"Rocket.h"
#include"Collider.h"


class Tank:public sf::Drawable
{
public:
	Tank(float x, float y);
	~Tank();
	void get_move();
	void update(sf::RenderWindow& window);
	Rocket* get_shell();
	bool get_bullet_status(); // returns shot variable
	sf::Vector2f get_position();
	sf::Sprite get_sprite();
	void take_dmg(int dmg);
	bool check_life();
	
private:
	// font and text use to show hp on screen
	sf::Text text;
	sf::Font font;
	//
	sf::SoundBuffer tank_buffer;
	sf::Sound tank_sound;
	bool shot; // keeps state of bullet shot=1 - bullet in the air
	int hp; // health points
	sf::Sprite *sprite;
	sf::Texture texture;
	float speed = 0.015F; // speed of moving the vehicle
	// all possible velocities
	sf::Vector2f y_velocity = {0, speed};
	sf::Vector2f x_velocity = { speed, 0 };
	// current velocity
	sf::Vector2f curr_velocity = { 0,0 };
	Rocket *shell;
	void shoot(sf::RenderWindow& window);
	void draw(sf::RenderTarget &target, sf::RenderStates state) const override;
	void show_hp(sf::RenderWindow& window);
};

