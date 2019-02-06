/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** Core.cpp
*/

#include <stdlib.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <regex>
#include <unistd.h>
#include <cstdlib>
#include <bits/dlfcn.h>
#include "../include/Core.hpp"
#include "../include/Vect.hpp"

Core::Core(const std::string &lib)
{
	DIR *libs = nullptr;
	DIR *games = nullptr;
	struct dirent *libsPath;
	struct dirent *gamesPath;

	libs = opendir("./lib");
	games = opendir("./games");
	if (libs == NULL || games == NULL) {
		std::cout << "Error opening libs directory" << std::endl;
		exit(84);
	} while ((libsPath = readdir(libs)) != NULL) {
		std::string file = libsPath->d_name;
		if (std::regex_match(file, std::regex("lib_arcade_[a-zA-z]*.so")))
			_gph_path.push_back("./lib/" + file);
	}
	while ((gamesPath = readdir(games)) != NULL) {
		std::string file = gamesPath->d_name;
		if (std::regex_match(file, std::regex("lib_arcade_[a-zA-z]*.so")))
			_game_path.push_back("./games/" + file);
	}
	this->_lib = lib;
	if (!_game_path.empty())
		this->_game = _game_path[0];
	this->_open_lib = nullptr;
	_menu = true;
	_playerName = "";
}

Core::~Core()
= default;

Arcade::IGraphicLib *Core::next_lib()
{
	std::vector<std::string>::iterator it;

	it = std::find(_gph_path.begin(), _gph_path.end(), _lib);
	if (it.operator*() == _gph_path.back()) {
		_lib = _gph_path.front();
	}
	else if (it != _gph_path.end()) {
		auto nx = std::next(it, 1);
		_lib = *nx;
	} else
		_lib = *_gph_path.begin();
	return load_gfx();
}

Arcade::IGraphicLib * Core::prev_lib()
{
	std::vector<std::string>::iterator it;

	it = std::find(_gph_path.begin(), _gph_path.end(), _lib);
	if (it.operator*() == _gph_path.front()) {
		_lib = _gph_path.back();
	}
	else if (it !=  _gph_path.end()) {
		auto nx = std::prev(it, 1);
		_lib = *nx;
	}
	else
		_lib = _gph_path.end().operator*();
	return load_gfx();
}

Arcade::IGraphicLib *Core::load_gfx()
{
	Arcade::IGraphicLib *(*entryPoint)();

	if (this->_open_lib)
		dlclose(this->_open_lib);
	_open_lib = dlopen(this->_lib.c_str(), RTLD_NOW);
	if (_open_lib == NULL) {
		std::cout << dlerror() << std::endl;
		exit(84);
	}
	entryPoint = (Arcade::IGraphicLib *(*)())dlsym(_open_lib, "entryPoint");
	return (*entryPoint)();
}

Arcade::IGameLib *Core::load_game()
{
	Arcade::IGameLib *(*entryPoint)();

	if (this->_open_game)
		dlclose(this->_open_game);
	_open_game = dlopen(this->_game.c_str(), RTLD_NOW);
	if (_open_game == NULL) {
		std::cout << dlerror() << std::endl;
		exit(84);
	}
	entryPoint = (Arcade::IGameLib *(*)())dlsym(_open_game, "entryPoint");
	return (*entryPoint)();
}

void Core::showLibs(Arcade::IGraphicLib *lib, Arcade::Vect<size_t> &pos, int pix)
{
	Arcade::Vect<Arcade::Color> colors;
	std::string name;

	pos.setY(((lib->getMaxY() / 100 + 1) * 10) - 3);
	colors.setXY(Arcade::Color(0, 0, 0, 255), Arcade::Color(0, 255, 0, 255));
	Arcade::TextBox gfx("Graphical Libraries : (change with left and right arrows)", pos,
			    25, colors.getY(), colors.getX());
	lib->drawText(gfx);

	pos.setX(pos.getX() + 4 * pix);
	colors.setY(Arcade::Color(255, 255, 255, 255));
	gfx.setPos(pos);
	gfx.setColor(colors.getY());
	gfx.setFontSize(20);
	for (int i = 0; i < static_cast<int>(_gph_path.size()); i++) {
		if (_lib == _gph_path[i])
			gfx.setBackgroundColor(Arcade::Color(0, 0, 255, 255));
		else
			gfx.setBackgroundColor(colors.getX());
		pos.setY(pos.getY() + 2 * pix);
		gfx.setPos(pos);
		name = &_gph_path[i].c_str()[17];
		name = name.substr(0, name.find("."));
		gfx.setValue(name);
		lib->drawText(gfx);
	}
}

void Core::showGames(Arcade::IGraphicLib *lib, Arcade::Vect<size_t> &pos, int pix)
{
	Arcade::Vect<Arcade::Color> colors;
	std::string name;

	pos.setY(pos.getY() + 2 * pix);
	pos.setX(pos.getX() - 4 * pix);
	colors.setXY(Arcade::Color(0, 0, 0, 255), Arcade::Color(0, 255, 0, 255));
	Arcade::TextBox gms("Games : (Change with up and down arrows)", pos, 25,
			    colors.getY(), colors.getX());
	lib->drawText(gms);

	pos.setX(pos.getX() + 4 * pix);
	colors.setY(Arcade::Color(255, 255, 255, 255));
	gms.setPos(pos);
	gms.setColor(colors.getY());
	gms.setFontSize(20);
	for (int i = 0; i < static_cast<int>(_game_path.size()); i++) {
		if (_game == _game_path[i])
			gms.setBackgroundColor(Arcade::Color(0, 0, 255, 255));
		else
			gms.setBackgroundColor(colors.getX());
		pos.setY(pos.getY() + 2 * pix);
		gms.setPos(pos);
		name = &_game_path[i].c_str()[19];
		name = name.substr(0, name.find("."));
		gms.setValue(name);
		lib->drawText(gms);
	}
}

bool Core::setPlayerName(Arcade::IGraphicLib **lib, Arcade::Keys key)
{
	Arcade::TextBox namePlayer("", {120, 20}, 30, Arcade::Color(255, 255, 255, 255), Arcade::Color(0, 0, 0, 255));
	Arcade::TextBox nameFix("NAME: ", {20, 20}, 30, Arcade::Color(255, 255, 255, 255), Arcade::Color(0, 0, 0, 255));

	(*lib)->drawText(nameFix);
	if (key == Arcade::Keys::ENTER) {
		launchGame(lib);
		return true;
	}
	else if (key + 96 >= 'a' && key + 96 <= 'z') {
		_playerName.push_back(static_cast<char>(key + 96));
		namePlayer.setValue(_playerName);
	}
	else if (key == Arcade::Keys::BACKSPACE && !_playerName.empty()) {
		_playerName.pop_back();
		namePlayer.setValue(_playerName);
	}
	if (!_playerName.empty()) {
		namePlayer.setValue(_playerName);
		(*lib)->drawText(namePlayer);
	}
	return false;
}

Arcade::IGraphicLib *Core::manageEvent(Arcade::Keys key, Arcade::IGraphicLib *lib)
{
	if (key == Arcade::Keys::RIGHT) {
		lib->closeRenderer();
		lib = this->next_lib();
		lib->openRenderer();
		std::cout << lib->getName() << std::endl;
	}
	else if (key == Arcade::Keys::LEFT) {
		lib->closeRenderer();
		lib = this->prev_lib();
		lib->openRenderer();
		std::cout << lib->getName() << std::endl;
	}
	return lib;
}

bool Core::loadMenu(Arcade::IGraphicLib **lib, Arcade::Keys keys)
{
	Arcade::Color white(Arcade::Color(255, 255, 255, 255));
	Arcade::Color black(Arcade::Color(0, 0, 0, 0));

	int pix = 1;
	if ((*lib)->getName() == "SFML" || (*lib)->getName() == "SDL") {
		pix = 30;
	}
	Arcade::Vect<size_t> pos(0, 0);
	pos.setXY(2 * pix,
	          static_cast<size_t>((((*lib)->getMaxY() / 100 + 1) * 5) / 2));
	Arcade::TextBox title("ARCADE", pos, 30, white, black);
	(*lib)->drawText(title);
	showLibs(*lib, pos, pix);
	showGames(*lib, pos, pix);
	if (keys == Arcade::Keys::ENTER) {
		(*lib)->clearEvents();
		return false;
	}
	else
		return true;
}

void Core::loopCore(Arcade::IGraphicLib *lib)
{
	Arcade::Keys key;
	_menu = true;

	lib->openRenderer();
	while (lib->isOpen()) {
		lib->clearWindow();
		lib->pollEvents();
		key = lib->getLastEvent();
		if (key == Arcade::Keys::ESC)
			lib->closeRenderer();
	lib = this->manageEvent(key, lib);
		if (_menu) {
			_menu = loadMenu(&lib, key);
		}
		else if (!_menu) {
			_menu = setPlayerName(&lib, key);
		}
	lib->refreshWindow();
	}
}

void Core::loopGame(Arcade::IGraphicLib **lib, Arcade::IGameLib *game)
{
	Arcade::Keys key = Arcade::Keys::NONE;

	game->setPlayerName(_playerName);
	game->init();
	while ((*lib)->isOpen() && key != Arcade::Keys::ESC) {
		(*lib) = this->manageEvent(key, *lib);
		(*lib)->pollEvents();
		key = (*lib)->getLastEvent();
		game->applyEvent(key);
		game->refresh(**lib);
	}
}

bool Core::launchGame(Arcade::IGraphicLib **lib)
{
	Arcade::IGameLib *game;

	game = this->load_game();
	(*lib)->clearWindow();
	(*lib)->clearEvents();
	if (game == nullptr)
		return false;
	else
		loopGame(lib, game);
	return true;
}