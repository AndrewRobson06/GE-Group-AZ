#pragma once
#include <SFML/Graphics/.hpp>

struct Parameters {

	static constexpr int tile_size = 64;
	static constexpr int grid_cols = 13;
	static constexpr int grid_rows = 5;

	static constexpr int game_width = grid_cols * tile_size;
	static constexpr int game_height = grid_rows * tile_size;

	//main menu sprite sheet, background and button background
	static inline const sf::IntRect menu_bg_rect{ 0,0,64,64 };

	//player sprite sheet currently just a singular sprite as the player has no animation yet
	static inline const st::IntRect player_rect{ 0,0,64,64 };

		
}
