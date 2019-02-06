/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** Core.hpp
*/

#ifndef ARCADE_CORE_HPP
#define ARCADE_CORE_HPP

#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include "IGraphicLib.hpp"
#include "IGameLib.hpp"

class Core {
public:
	explicit Core(const std::string &lib);
	~Core();
	Arcade::IGraphicLib *load_gfx();
	Arcade::IGameLib *load_game();
	Arcade::IGraphicLib *next_lib();
	Arcade::IGraphicLib *prev_lib();
	bool loadMenu(Arcade::IGraphicLib **lib, Arcade::Keys keys);
	bool launchGame(Arcade::IGraphicLib **Lib);
	void loopGame(Arcade::IGraphicLib **lib, Arcade::IGameLib *game);
	void loopCore(Arcade::IGraphicLib *lib);
	bool setPlayerName(Arcade::IGraphicLib **lib, Arcade::Keys key);

	Arcade::IGraphicLib *manageEvent(Arcade::Keys key, Arcade::IGraphicLib *lib);
private:
	void showLibs(Arcade::IGraphicLib *lib, Arcade::Vect<size_t> &pos, int pix);
	void showGames(Arcade::IGraphicLib *lib, Arcade::Vect<size_t> &pos, int pix);
	void *_open_lib;
	void *_open_game;
	std::string _game;
	std::string _lib;
	bool _menu;
	std::string _playerName;
	std::vector<std::string> _gph_path;
	std::vector<std::string> _game_path;
};

#endif /* !ARCADE_CORE_HPP */
