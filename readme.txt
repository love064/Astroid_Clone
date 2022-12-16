
Group 11
	- Krystof Hadrousek, Lingxiu Li, Love Fried

Repository Link
	https://github.com/love064/Astroid_Clone 

Codebase Oversight
	- File Contents
		- main.cpp
			-> this file contains the state codes which switches between the main_menu and the level,
			-> it also contains the code for the main menu,
			-> as well as the Initialization for the window (including init. for textures and sound)
		- Level.h
			-> this file contains classes for the Level as well as the Player, Asteroid, and, Projectile
			-> as well as the initialization of their functions
		- Level.cpp
			-> this file contains all of the functions with-in the classes (eg. Player(update), Level(spawn_projectile))
			-> as well as a supporting function for these functions (distance_sq()) (ps. there is only 1 supprting function like this therefore its in the same file and not a new "math" file)
		- Constants.h
			-> this file contains the constant values (const "float")

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
		- Asteroids
			- Asteroid interaction with screen borders
		- constants
			- PLAYER_SPEED
			- PLAYER_SIZE
			- ship_height
		- :)


	Lingxiu (left group)
		- Asteroid(update)
			-> movement


	Love
		- Game states
			- do_main_menu()
			- do_game()
		- Textures
			- Initialization
			- Level(render)
			- Projectile(render)
			- Asteroid(render)
		- Sounds
			- Initialization 
			- Thrust
			- Explsoion
			- Pew
		- Player(update) (only parts bellow)
			-> shooting
			-> damage
		- Projectile class
			- Projectile(update)
			- Projectile(render)
		- Level class
			- Level(update)
			- Level(render)
			- Level(spawn_projectile)
			- Level(spawn_asteroid)
			- Level(closest_asteroid)
			- Level(reset)
		- distance_sq
		- constants
			- DELTA
			- PROJECTILE_SPEED
		- Organization
			- Header, and cpp files
