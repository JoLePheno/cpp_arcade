//
// EPITECH PROJECT, 2018
// arcade
// File description:
// arcade
//

#pragma once

#include <map>
#include <ncurses.h>
#include <curses.h>
#include <sys/ioctl.h>
#include "../../include/Color.hpp"
#include "../../include/IGraphicLib.hpp"

namespace Arcade {

	class NCursesLib : public IGraphicLib {
	public:
		NCursesLib();
		std::string getName() const;
                bool isOpen() const override;
                void closeRenderer() override;
                void openRenderer() override;
                void clearWindow() override;
                void refreshWindow() override;
                void drawPixelBox(PixelBox &) override;
                void drawText(TextBox &) override;
		bool pollEvents() override;
                Keys getLastEvent() override;
                void clearEvents() override;
                Vect<size_t> getScreenSize() const override;
                int getMaxY() const override;
                int getMaxX() const override;
	private:
		Vect<int> searchColor(Color col, Color bg);
		std::vector<std::pair<int, int>> _pColor;
		int createColor(Color col);
		int getPairIndex(int x, int y);
		int getColorIndex(Arcade::Color &color);
		std::vector<Arcade::Color> _sColor;
		WINDOW *_win = nullptr;
		std::map<int, Keys> _keyMap {
			{ERR, Keys::NONE},
			{'a', Keys::A},
			{'b', Keys::B},
			{'c', Keys::C},
			{'d', Keys::D},
			{'e', Keys::E},
			{'f', Keys::F},
			{'g', Keys::G},
			{'h', Keys::H},
			{'i', Keys::I},
			{'j', Keys::J},
			{'k', Keys::K},
			{'l', Keys::L},
			{'m', Keys::M},
			{'n', Keys::N},
			{'o', Keys::O},
			{'p', Keys::P},
			{'q', Keys::Q},
			{'r', Keys::R},
			{'s', Keys::S},
			{'t', Keys::T},
			{'u', Keys::U},
			{'v', Keys::V},
			{'w', Keys::W},
			{'x', Keys::X},
			{'y', Keys::Y},
			{'z', Keys::Z},
			{KEY_UP, Keys::UP},
			{KEY_DOWN, Keys::DOWN},
			{KEY_LEFT, Keys::LEFT},
			{KEY_RIGHT, Keys::RIGHT},
			{10, Keys::ENTER},
			{' ', Keys::SPACE},
			{KEY_DC, Keys::DELETE},
			{KEY_BACKSPACE, Keys::BACKSPACE},
			{'\t', Keys::TAB},
			{27, Keys::ESC}
		};
		std::vector<Arcade::Keys> _keys;
		std::vector<Arcade::Color> _color;
		std::vector<Vect<int>> _pairs;
		bool _open;
	};
};
