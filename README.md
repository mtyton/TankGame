# TankGame
This is a Simple Tank Game, to move your can use [W,A,S,D] to shoot you should press 'space'.
Your enemy will move at his own.
# How to run it?
To Run this code you need to configure sfml 2.5:
```https://www.sfml-dev.org/tutorials/2.5/start-vc.php````
After that you have to compile this code
# How does it works?
## Collision with bullets
```
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
```
## Enemy AI
### Declaration
  ```
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
  ```
  Enemy Simply searches player by getting his position and checking in which direction is better to go to player, if player is in
    sight of an enemy's tank it shoots.
### Call
```
if (clock.getElapsedTime() >= time_search)
			{
				enemy_tank->search_player(player_tank->get_position());
				clock.restart();
			}
```
Betweeen every call of player searching there is a small period of time ```time_search ```, you can find this variable inside Source.cpp

# TODO
 - Enemy shoots in a period of time
 - Enemy reacts getting a hit with some delay
