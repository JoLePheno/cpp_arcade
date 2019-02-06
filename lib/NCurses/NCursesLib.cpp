//
// EPITECH PROJECT, 2018
// arcade
// File description:
// arcade
//

#include <unistd.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <ncurses.h>
#include "NCursesLib.hpp"

Arcade::IGraphicLib *ret = nullptr;

Arcade::NCursesLib::NCursesLib()
{
	_keys.push_back(Arcade::Keys::NONE);
	_win = nullptr;
	_open = false;
}

std::string Arcade::NCursesLib::getName() const
{
	return "NCURSES";
}

bool Arcade::NCursesLib::isOpen() const
{
	return _open;
}

void Arcade::NCursesLib::closeRenderer()
{
	delwin(_win);
	endwin();
	_open = false;
}

void Arcade::NCursesLib::openRenderer()
{
	int h = 0;
	int w = 0;

	initscr();
	start_color();
	noecho();
	cbreak();
	timeout(0);
	curs_set(0);
	keypad(stdscr, true);
	getmaxyx(stdscr, h, w);
	keypad(stdscr, true);
	_win = newwin(h, w, 0, 0);
	_open = true;
}

void Arcade::NCursesLib::clearWindow()
{
	wclear(_win);
}

void Arcade::NCursesLib::refreshWindow()
{
	wrefresh(_win);
}

Arcade::Vect<int> Arcade::NCursesLib::searchColor(Color col,
						  Color bg)
{
	Vect<int> ret(-1, -1);

	col.setAlpha(0);
	bg.setAlpha(0);
	for (int i = 0; i < static_cast<int>(_color.size()); i++) {
		if (col == _color[i])
			ret.setX(i + 1);
		if (bg == _color[i])
			ret.setY(i + 1);
	}
	if (ret.getX() == -1)
		ret.setX(createColor(col));
	if (ret.getY() == -1 && col != bg)
		ret.setY(createColor(bg));
	if (col == bg)
		ret.setY(ret.getX());
	return ret;
}

int Arcade::NCursesLib::createColor(Color col)
{
	short r;
	short g;
	short b;
	double rDble = (col.getRed() / 255) * 1000.0;
	double gDble = (col.getGreen() / 255) * 1000.0;
	double bDble = (col.getBlue() / 255) * 1000.0;

	r = rDble;
	g = gDble;
	b = bDble;
	_color.push_back(col);
	init_color(_color.size(), r, g, b);
	return _color.size();
}


int Arcade::NCursesLib::getPairIndex(int x, int y)
{
	std::pair<int, int> pair(x, y);
	int index = static_cast<int>(_pColor.size() + 1);
	auto it = std::find(_pColor.begin(), _pColor.end(), pair);

	if (it == _pColor.end()) {
		init_pair(static_cast<short>(index), static_cast<short>(x),
		          static_cast<short>(y));
		_pColor.push_back(pair);
	} else
		index = static_cast<int>(it - _pColor.begin() + 1);
	return index;
}

int Arcade::NCursesLib::getColorIndex(Arcade::Color &color)
{
	auto tab = (unsigned char *)color;
	auto iter = std::find(_sColor.begin(), _sColor.end(), color);
	int idx = static_cast<int>(_sColor.size() + 1);

	if (iter == _sColor.end()) {
		init_color(static_cast<short>(_sColor.size() + 1),
		           static_cast<short>(tab[0] * 3.92),
		           static_cast<short>(tab[1] * 3.92),
		           static_cast<short>(tab[2] * 3.92));
		_sColor.emplace_back(color);
	} else
		idx = static_cast<int>(iter - _sColor.begin() + 1);
	return idx;
}

void Arcade::NCursesLib::drawPixelBox(Arcade::PixelBox &box)
{
	size_t x = 0;
	size_t y = 0;

	for (; x < box.getHeight(); x++) {
		for (; y < box.getWidth(); y++) {
			Arcade::Color pixelColor =
				box.getPixel(Arcade::Vect<size_t>(y, x));
			auto id = getPairIndex(getColorIndex(pixelColor),
			                           getColorIndex(pixelColor));
			wattron(_win, COLOR_PAIR(id));
			mvwprintw(_win, static_cast<int>(box.getY() + x),
			          static_cast<int>(box.getX() + y), " ");
			wattroff(_win, COLOR_PAIR(id));
		}
	}
}

void Arcade::NCursesLib::drawText(TextBox &box)
{
	if (!isOpen() || box.getValue().empty())
		return ;
	Arcade::Color pixelColor = box.getColor();
	Arcade::Color background = box.getBackgroundColor();
	auto id = getPairIndex(getColorIndex(pixelColor),
	                       getColorIndex(background));
	wattron(_win, COLOR_PAIR(id));
	mvwprintw(_win, static_cast<int>(box.getY()),
	          static_cast<int>(box.getX()), "%s", box.getValue().c_str());
	wattroff(_win, COLOR_PAIR(id));
}

bool Arcade::NCursesLib::pollEvents()
{
	int c = getch();
	bool ret = false;

	if (c == ERR)
		return ret;
	try
	{
		_keys.push_back(_keyMap.at(c));
	}
	catch(const std::out_of_range)
	{
	}
	return true;
}

Arcade::Keys Arcade::NCursesLib::getLastEvent()
{
	Arcade::Keys key = _keys.back();
	if (!_keys.empty())
		_keys.pop_back();
	return key;
}

void Arcade::NCursesLib::clearEvents()
{
	_keys.clear();
}

Arcade::Vect<size_t> Arcade::NCursesLib::getScreenSize() const
{
	Vect<size_t> ret;
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	ret.setXY(w.ws_col, w.ws_row);
	return ret;
}

int Arcade::NCursesLib::getMaxY() const
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	return w.ws_row;
}

int Arcade::NCursesLib::getMaxX() const
{
	struct winsize w;

	ioctl(0, TIOCGWINSZ, &w);
	return w.ws_col;
}

__attribute__((constructor))
void enter()
{
        ret = new Arcade::NCursesLib;
}

__attribute__((destructor))
void out()
{
        delete ret;
}

extern "C" Arcade::IGraphicLib *entryPoint()
{
        return ret;
}