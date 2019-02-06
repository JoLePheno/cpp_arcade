/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** Snake.cpp
*/

#include <chrono>
#include "Snake.hpp"
#include <utility>
#include <iostream>
#include <time.h>
#include "../../include/PixelBox.hpp"

Arcade::IGameLib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new Arcade::Snake;
}

__attribute__((destructor))
void out()
{
	delete ret;
}

extern "C" Arcade::IGameLib *entryPoint()
{
	return ret;
}

Arcade::Snake::Snake()
{
	srand(static_cast<unsigned int>(time(nullptr)));
}

Arcade::Vect<size_t> Arcade::Snake::getNbrRand(size_t x, size_t y)
{
	Arcade::Vect<size_t> tmp(rand()%x, rand()%y);

	if (_map[tmp.getY()][tmp.getX()] == '1') {
		while (_map[tmp.getY()][tmp.getX()] == '1') {
			tmp = {rand()%x, rand()%y};
		}
	}
	return tmp;
}

bool Arcade::Snake::init()
{
	Arcade::Vect<size_t> tmp;
	_snakePos.clear();
	_snakePos.emplace_back(
		Arcade::Vect<size_t>(static_cast<size_t>(_map[0].size() / 2 - 2),
		                     static_cast<size_t>(_map.size() / 2 + 8)));
	_food = getNbrRand(_map[0].size() - 1, _map.size() - 1);
	_score = 0;
	return true;
}

bool Arcade::Snake::stop()
{

}

const std::string Arcade::Snake::getName() const
{
	return std::__cxx11::string("Nibbler");
}

bool Arcade::Snake::applyEvent(Arcade::Keys key)
{
	if (key != NONE)
		_key = key;
}

bool Arcade::Snake::update()
{
	return true;
}

void Arcade::Snake::moveUp()
{
	Arcade::Vect<size_t> last(_snakePos.back());
	last.setY(last.getY() - 1);
	if (_map[last.getY()][last.getX()] != '1') {
		_snakePos.pop_back();
		_snakePos.push_back(last);
	}
}

void Arcade::Snake::moveDown()
{
	Arcade::Vect<size_t> last(_snakePos.back());
	last.setY(last.getY() + 1);
	if (_map[last.getY()][last.getX()] != '1') {
		_snakePos.pop_back();
		_snakePos.push_back(last);
	}
}

void Arcade::Snake::moveLeft()
{
	Arcade::Vect<size_t> last(_snakePos.back());
	last.setX(last.getX() - 1);
	if (_map[last.getY()][last.getX()] != '1') {
		_snakePos.pop_back();
		_snakePos.push_back(last);
	}
}

void Arcade::Snake::moveRight()
{
	Arcade::Vect<size_t> last(_snakePos.back());
	last.setX(last.getX() + 1);
	if (_map[last.getY()][last.getX()] != '1') {
		_snakePos.pop_back();
		_snakePos.push_back(last);
	}
}

void Arcade::Snake::moveSnake()
{
	switch (_key)
	{
		case Arcade::Keys::Q :
			moveLeft();
			break;
		case Arcade::Keys::D :
			moveRight();
			break;
		case Arcade::Keys::Z :
			moveUp();
			break;
		case Arcade::Keys::S :
			moveDown();
			break;
		default:
			break;
	}
}

void Arcade::Snake::lookFood()
{
	auto tmp = _snakePos.end()[-2];

	tmp.setX(tmp.getX() - 1);
	tmp.setY(tmp.getY() - 1);
	if (_snakePos.front().getX() == _food.getX() && _snakePos.front().getY() == _food.getY()) {
		_food = getNbrRand(_map[0].size() - 1, _map.size() - 1);
		_score += 10;
	}
}

void Arcade::Snake::setPlayerName(std::string &name)
{
	if (name.size() > 14)
		name.erase(14, name.size());
	_playerName = name;
}

void Arcade::Snake::refresh(Arcade::IGraphicLib &graphicLib)
{
	graphicLib.clearWindow();
	printMap(graphicLib);
	printOthers(graphicLib);
	moveSnake();
	printSnake(graphicLib);
	lookFood();
	printFood(graphicLib);
	graphicLib.refreshWindow();
	_key = NONE;
}

size_t Arcade::Snake::getScore()
{
}

bool Arcade::Snake::printFood(Arcade::IGraphicLib &graphicLib)
{
	auto pWidth = static_cast<size_t>(graphicLib.getMaxX() * 0.7 / _map[0].size());
	auto pHeight = static_cast<size_t>(graphicLib.getMaxY() * 0.7 / _map.size());
	auto offsetY = static_cast<size_t>(graphicLib.getMaxY() * 0.3);
	Arcade::PixelBox pixelBox(Arcade::Vect<size_t>(pWidth, pHeight),
	                          Arcade::Vect<size_t>(), Arcade::Color(0, 255,
	                                                                0, 100));;
	pixelBox.setX(_food.getX() * pWidth);
	pixelBox.setY(offsetY + _food.getY() * pHeight);
	graphicLib.drawPixelBox(pixelBox);
	return true;
}

void Arcade::Snake::printOthers(Arcade::IGraphicLib &graphicLib)
{
	int pix = 1;

	if (graphicLib.getName() == "SFML" || graphicLib.getName() == "SDL") {
		pix = 30;
	}
	Arcade::Vect<size_t> posName(2 * pix, static_cast<size_t>((graphicLib.getMaxY() / 100 + 1) * 5) / 2);
	Arcade::Vect<size_t> posScore(2 * pix, static_cast<size_t>((graphicLib.getMaxY() / 100 + 4) * 5) / 2);
	Arcade::TextBox score("Score: " + std::to_string(_score), posScore, 30, Arcade::Color(255, 255, 255, 255), Arcade::Color(0, 0, 0, 255));
	Arcade::TextBox nameFix(_playerName, posName, 30, Arcade::Color(255, 255, 255, 255), Arcade::Color(0, 0, 0, 255));
	if (graphicLib.getName() != "SDL") {
		graphicLib.drawText(score);
		graphicLib.drawText(nameFix);
	}
}

bool Arcade::Snake::printMap(Arcade::IGraphicLib &graphicLib)
{
	auto pWidth = static_cast<size_t>(graphicLib.getMaxX() * 0.7 / _map[0].size());
	auto pHeight = static_cast<size_t>(graphicLib.getMaxY() * 0.7 / _map.size());
	auto offsetY = static_cast<size_t>(graphicLib.getMaxY() * 0.3);
	Arcade::Color color(255, 0, 0, 100);
	Arcade::PixelBox pixelBox;

	for (int i = 0; i < _map.size(); i++) {
		for (int x = 0; x < _map[i].size(); x++) {
			if (_map[i][x] == '1')
				color.setColor(255, 255, 255, 255);
			else
				color.setColor(255, 0, 0, 100);
			pixelBox = Arcade::PixelBox(Arcade::Vect<size_t>(pWidth, pHeight), Arcade::Vect<size_t>(), color);
			pixelBox.setX(x * pWidth);
			pixelBox.setY(offsetY + i * pHeight);
			graphicLib.drawPixelBox(pixelBox);
		}
	}
	return false;
}

bool Arcade::Snake::printSnake(Arcade::IGraphicLib &graphicLib)
{
	auto pWidth = static_cast<size_t>(graphicLib.getMaxX() * 0.7 / _map[0].size());
	auto pHeight = static_cast<size_t>(graphicLib.getMaxY() * 0.7 / _map.size());
	auto offsetY = static_cast<size_t>(graphicLib.getMaxY() * 0.3);
	Arcade::PixelBox pixelBox(Arcade::Vect<size_t>(pWidth, pHeight),
	                          Arcade::Vect<size_t>(), Arcade::Color(0, 0,
	                                                                255, 100));;

	for (auto cell : _snakePos) {
		pixelBox.setX(cell.getX() * pWidth);
		pixelBox.setY(offsetY + cell.getY() * pHeight);
		graphicLib.drawPixelBox(pixelBox);
	}
	return false;
}
