#include "Enemy.h"

Enemy::Enemy(float x, float y)
{
	texture.loadFromFile("Sprites/sec_tank.png");
	sprite = new sf::Sprite();
	sprite->setTexture(texture);
	sprite->setPosition(sf::Vector2f(x, y));
	hp = 10;
	direction = randomize_direction();
	offset = 40;
	sprite->setOrigin(50, 50);
	shot = false;
	velocity = new sf::Vector2f(0, 0.003F);
	// text
	font.loadFromFile("Fonts/legacycyborg.ttf");
	text.setFont(font);
	
	text.setFillColor(sf::Color::Magenta);
}

Enemy::~Enemy()
{
	delete sprite;
	delete velocity;
}

void Enemy::update(sf::Vector2f playerPos, sf::RenderWindow& window)
{
	show_hp(window);
	set_direction();
	move();
	avoid_wall_collision(window);
	logic(playerPos, window);
}

void Enemy::set_direction()
{
	switch (direction)
	{
	case UP:
		sprite->setRotation(0.0f);
		break;
	case DOWN:
		sprite->setRotation(180.0f);
		break;
	case RIGHT:
		sprite->setRotation(90.0f);
		break;
	case LEFT:
		sprite->setRotation(270.0f);
		break;
	}

}

void Enemy::move()
{
	
	if (direction == DOWN)
	{
		* velocity = sf::Vector2f(0, 0.01F);
		
	}
	else if (direction == UP)
	{
		*velocity = sf::Vector2f(0, -0.01F);

	}
	else if (direction == LEFT)
	{
		*velocity = sf::Vector2f(-0.01F, 0);

	}
	else if (direction == RIGHT)
	{
		*velocity = sf::Vector2f(0.01F, 0);

	}
	sprite->move(*velocity);
}

sf::Sprite Enemy::get_sprite()
{
	return *sprite;
}

void Enemy::set_position(float x, float y)
{
	sprite->setPosition(sf::Vector2f(x, y));
}

void Enemy::take_dmg(int dmg)
{
	hp -= dmg;
}

bool Enemy::check_life()
{
	return hp;
}

bool Enemy::get_bullet_status()
{
	return shot;
}

Rocket* Enemy::get_shell()
{
	if (shot)
	{
		return shell;
	}
}

void Enemy::search_player(sf::Vector2f player_position)
{
	float diffX, diffY;
	diffX = sprite->getPosition().x - player_position.x;
	diffY = sprite->getPosition().y - player_position.y;
	if(abs(diffY)<abs(diffX))
	{
		if (player_position.x < sprite->getPosition().x)
		{
			direction = LEFT;
		}
		else if(player_position.x > sprite->getPosition().x)
		{
			direction = RIGHT;
		}
	}
	else
	{
		if (player_position.y < sprite->getPosition().y)
		{
			direction = UP;
		}
		else if (player_position.y > sprite->getPosition().y)
		{
			direction = DOWN;
		}
	}
}

void Enemy::logic(sf::Vector2f playerPos, sf::RenderWindow& window)
{
	sf::Vector2f margin = get_check_margin(window);

	if (player_in_sight(playerPos, margin) && !shot)
	{
		shoot();
	}
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

void Enemy::shoot()
{
	shot = true;
	shell = new Rocket(*velocity, sprite->getPosition(), sprite->getRotation());
}

void Enemy::avoid_wall_collision(sf::RenderWindow& window)
{
	switch (direction)
	{
	case UP:
		if (this->sprite->getPosition().y - 70 <= 0)
		{
			direction = DOWN;
		}
		break;
	case DOWN:
		if (this->sprite->getPosition().y + 70 >= window.getSize().y)
		{
			direction = UP;
		}
		break;
	case LEFT:
		if (this->sprite->getPosition().x - 70 <= 0)
		{
			direction = RIGHT;
		}
		break;
	case RIGHT:
		if (this->sprite->getPosition().x + 70 >= window.getSize().x)
		{
			direction = LEFT;
		}
		break;
	}
}

void Enemy::show_hp(sf::RenderWindow& window)
{
	text.setPosition(window.getSize().x - 50, window.getSize().y - 50);
	text.setString(std::to_string(hp));
	window.draw(text);
}

bool Enemy::player_in_sight(sf::Vector2f playerPos, sf::Vector2f margin)
{
	sf::Vector2f enemPos = sprite->getPosition();
	//Collsion while looking up
	if (enemPos.y>=playerPos.y&&playerPos.y>=margin.y)
	{
		if (enemPos.x+offset>=playerPos.x && enemPos.x - offset<=playerPos.x)
		{
			return true;
		}	
	}
	// collistion while looking down
	if (enemPos.y <= playerPos.y && playerPos.y <= margin.y)
	{
		if (enemPos.x + offset >= playerPos.x && enemPos.x - offset <= playerPos.x)
		{
			return true;
		}
	}
	// collisiotn while looking right
	if (enemPos.x<= playerPos.x && playerPos.x <= margin.x)
	{
		if (enemPos.y + offset >= playerPos.y && enemPos.y - offset <= playerPos.y)
		{
			return true;
		}
	}
	// collisiton while looking left
	if (enemPos.x >= playerPos.x && playerPos.x >= margin.x)
	{
		if (enemPos.y + offset >= playerPos.y && enemPos.y - offset <= playerPos.y)
		{
			return true;
		}
	}
	return false;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(*sprite, state);
}

sf::Vector2f Enemy::get_check_margin(sf::RenderWindow& window)
{
	sf::Vector2f enemPos = sprite->getPosition();
	sf::Vector2f margin{};
	switch (direction)
	{
	case UP:
		margin.x = enemPos.x;
		margin.y = 0;
		break;
	case DOWN:
		margin.x = enemPos.x;
		margin.y = window.getSize().y;
		break;
	case LEFT:
		margin.x = 0;
		margin.y = enemPos.y;
		break;
	case RIGHT:
		margin.x = window.getSize().x;
		margin.y = enemPos.y;
		break;
	}
	return margin;
}


Directions Enemy::randomize_direction()
{
	std::srand(std::time(nullptr));
	int number = rand()%4+1;
	switch (number)
	{
	case 1:
		return UP;
	case 2:
		return DOWN;
	case 3: 
		return RIGHT;
	case 4:
		return LEFT;
	default:
		return UP;
	}
}
