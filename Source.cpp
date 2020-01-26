#include<iostream>
#include<thread>
#include <chrono>
#include<SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Tank.h"
#include"Rocket.h"
#include"Enemy.h"
#include"Collider.h"
#include"Background.h"

// checks collision for player's_bullet with enemy tank
void enem_bullet_collsion(Collider *local_collider,Enemy *enem, Rocket *shell)
{
	sf::Sprite shell_sprite = shell->get_sprite();
	if (local_collider->collision(enem->get_sprite(), shell_sprite))
	{
		enem->take_dmg(shell->deal_dmg());
		shell->mark_to_destroy();
	}
}

// checks collision for enemy's bullet with player tank
void player_bullet_collsion(Collider* local_collider, Tank* player, Rocket* shell)
{
	sf::Sprite shell_sprite = shell->get_sprite();
	if (local_collider->collision(player->get_sprite(), shell_sprite))
	{
		player->take_dmg(shell->deal_dmg());
		shell->mark_to_destroy();
	}
}


int main()
{	
	//all necessary declarations
	Collider global_collider = Collider(); //use this to check collisions 
	sf::Music engine; //simply to play engine sound
	engine.openFromFile("Sounds/tank_engine.wav");
	sf::RenderWindow window(sf::VideoMode(800, 600), "TANK GAME", sf::Style::Titlebar | sf::Style::Close);
	Tank* player_tank = new Tank(50, 50);
	Enemy* enemy_tank;
	enemy_tank = new Enemy(500, 250);
	engine.setLoop(true);
	engine.play();
	Rocket* shell; // this is going to keep shell object for both player and enemy
	sf::Time time_search = sf::seconds(3.0f); // how much time enemy need to make decision
	sf::Clock clock;
	Background bg(window.getSize().x, window.getSize().y);

	while (window.isOpen())
	{	
		// checking collisions with bullets
		if (player_tank->get_bullet_status())
		{
			shell = player_tank->get_shell();
			enem_bullet_collsion(&global_collider, enemy_tank, shell);
		}
		if (enemy_tank->get_bullet_status())
		{
			shell = enemy_tank->get_shell();
			player_bullet_collsion(&global_collider, player_tank, shell);
		}
		//
		sf::Event event;
		// main game loop
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		// this if check if both player and enemy are alive if they are it ends game
		if (enemy_tank->check_life() && player_tank->check_life())
		{
			if (clock.getElapsedTime() >= time_search)
			{
				enemy_tank->search_player(player_tank->get_position());
				clock.restart();
			}

			player_tank->get_move();
			window.clear();
			window.draw(bg);
			enemy_tank->update(player_tank->get_position(), window);
			player_tank->update(window);
			window.draw(*player_tank);
			window.draw(*enemy_tank);
			window.display();
		}
		else
		{
			engine.stop();
			// cas we loose
			if (!player_tank->check_life())
			{
				
				bg.change_texture("loose");
				
			}
			// case we win
			else if (!enemy_tank->check_life())
			{
				bg.change_texture("won");
			}
			window.clear();
			window.draw(bg);
			window.display();
			std::this_thread::sleep_for(std::chrono::seconds(2));

			delete player_tank;
			delete enemy_tank;
			window.close();
		}
		
	}

	return 0;
}