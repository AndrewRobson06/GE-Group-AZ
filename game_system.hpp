#pragma once
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

class Scene {
public:
	virtual ~Scene() = default;
	virtual void load() = 0;
	virtual	void unload() {};
	virtual update(float dt) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};

class GameSystem {
public:
	static void start(unsigned int width, unsigned int height, const std::string& tile, std::shared_ptr<Scene> initial_scene);
	static void set_active_scene(std::shared_prt<Scene> scene);

	static sf::Texture& get_menu_sheet();
	static sf::Texture& get_lake_sheet();
	static sf::Texture& get_player_sheet();

private:
	static std::shared_ptr<Scene> _active_scene;
	static sf::Texture _menu_sheet;
	static sf::Texture _lake_sheet;
	static sf::Texture _player_sheet;
};