#include "Tank.h"

Tank::Tank(float x, float y)
{	
	texture.loadFromFile("Sprites/first_tank.png");
	sprite = new sf::Sprite();
	sprite->setTexture(texture);
	sprite->setPosition(sf::Vector2f(x, y));
	sprite->setOrigin(50, 50);
	shot = false;
	
	if (!tank_buffer.loadFromFile("Sounds/tank_fire.wav"))
	{
		throw std::invalid_argument("File doesn't exists or there was an error while reading");
	}
	this->tank_sound.setBuffer(tank_buffer);
	hp = 10;
	// text
	font.loadFromFile("Fonts/legacycyborg.ttf");
	text.setFont(font);
	text.setPosition(10, 10);
	text.setFillColor(sf::Color::Green);
}

Tank::~Tank()
{
	delete sprite;
}

void Tank::get_move()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		curr_velocity = -y_velocity;
		sprite->setRotation(0.0f);
		sprite->move(curr_velocity);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		curr_velocity = x_velocity;
		sprite->setRotation(90.0f);
		sprite->move(curr_velocity);
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		curr_velocity = -x_velocity;
		sprite->setRotation(270.0f);
		sprite->move(curr_velocity);
	}
	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		curr_velocity = y_velocity;;
		sprite->setRotation(180.0f);
		sprite->move(curr_velocity);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) 
		&& !shot)
	{
		tank_sound.play();
		sf::Vector2f* position = new sf::Vector2f;
		*position = sprite->getPosition();
		shot = true;
		shell = new Rocket(curr_velocity, *position, sprite->getRotation());
		delete position;
	}
	
}
void Tank::shoot(sf::RenderWindow& window)
{
	window.draw(*shell);
}

void Tank::update(sf::RenderWindow& window)
{
	show_hp(window);
	if (shot)
	{
		if (shell->get_status() == 1)
		{
			delete shell;
			shot = false;
		}
		else
		{
			shell->update();
			window.draw(*shell);
			if (shell->out_of_screen())
			{
				delete shell;
				shot = false;
			}
		}
		
	}
}

void Tank::show_hp(sf::RenderWindow& window)
{
	text.setString(std::to_string(hp));
	window.draw(text);
}


Rocket* Tank::get_shell()
{
	if (shot)
	{
		return shell;
	}
}

bool Tank::get_bullet_status()
{
	return shot;
}

sf::Vector2f Tank::get_position()
{
	return sprite->getPosition();
}

sf::Sprite Tank::get_sprite()
{
	return *sprite;
}

void Tank::take_dmg(int dmg)
{
	hp -= dmg;
}

bool Tank::check_life()
{
	return hp;
}



void Tank::draw(sf::RenderTarget &target, sf::RenderStates state) const
{
	target.draw(*sprite, state);
}

