
Group 11
	- Krystof Hadrousek, Lingxiu Li, Love Fried

Repository Link
	https://github.com/love064/Astroid_Clone 

Codebase Oversight
	- 


Controls
	- Use the mouse to click the start button
	- Use left/right arrow keys to rotate the ship
	- Use up arrow to move forward
	- Use space bar to shoot


Contribution
	Krystof
		- 


	Lingxiu
		-


	Love
		- Game states
			- do_main_menu()
			- do_game()
		- Textures
		- Sounds
		- Player(update) (only parts bellow)
			-> shooting
			-> damage
		- Projectile class
			- Projectile(update)
			- Projectile(render)
		- Level class
			- Level(update)
			- Level(render)
			- Level(spawn_projectiles)
			- Level(closest_asteroid)
			- Level(reset)
		- distance_sq
		- constants
			- DELTA
			- PROJECTILE_SPEED
