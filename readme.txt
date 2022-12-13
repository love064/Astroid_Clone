
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
		- Player
			- Player movement forward and rotation
			- Player interaction with screen borders
			- Function to render the player ship texture
			- Applying drag to the ship (not yet implemented)
		- constants
			- PLAYER_SPEED
			- PLAYER_SIZE
			- ship_height
		- :)


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
		- Organization
			- Header, and cpp files
