/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** SFML.hpp
*/

#ifndef ARCADE_SFML_HPP
#define ARCADE_SFML_HPP

#include "../../include/Keys.hpp"
#include <iostream>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../../include/TextBox.hpp"
#include "../../include/IGraphicLib.hpp"

namespace Arcade {
	class SFML: public Arcade::IGraphicLib {
	public:
		SFML();
		void drawText(TextBox &text) override;
		bool isOpen() const override;
		void clearWindow() override;
		void refreshWindow() override;
		void closeRenderer() override;
		std::string getName() const override;
		void openRenderer() override;
		void drawPixelBox(PixelBox &) override;
		bool pollEvents() override;
		Keys getLastEvent() override;
		void clearEvents() override;

		/* Context Info */
		// get the X and Y max of the windows
		Vect<size_t> getScreenSize() const override;

		// get the Y max of the windows
		int getMaxY() const override;

		// get the X max of the windows
		int getMaxX() const override;
	private:
		sf::Text _text;
		std::map<sf::Keyboard::Key, Keys> _keyMap {
			{sf::Keyboard::Key::A, Keys::A},
			{sf::Keyboard::Key::B, Keys::B},
			{sf::Keyboard::Key::C, Keys::C},
			{sf::Keyboard::Key::D, Keys::D},
			{sf::Keyboard::Key::E, Keys::E},
			{sf::Keyboard::Key::F, Keys::F},
			{sf::Keyboard::Key::G, Keys::G},
			{sf::Keyboard::Key::H, Keys::H},
			{sf::Keyboard::Key::I, Keys::I},
			{sf::Keyboard::Key::J, Keys::J},
			{sf::Keyboard::Key::K, Keys::K},
			{sf::Keyboard::Key::L, Keys::L},
			{sf::Keyboard::Key::M, Keys::M},
			{sf::Keyboard::Key::N, Keys::N},
			{sf::Keyboard::Key::O, Keys::O},
			{sf::Keyboard::Key::P, Keys::P},
			{sf::Keyboard::Key::Q, Keys::Q},
			{sf::Keyboard::Key::R, Keys::R},
			{sf::Keyboard::Key::S, Keys::S},
			{sf::Keyboard::Key::T, Keys::T},
			{sf::Keyboard::Key::U, Keys::U},
			{sf::Keyboard::Key::V, Keys::V},
			{sf::Keyboard::Key::W, Keys::W},
			{sf::Keyboard::Key::X, Keys::X},
			{sf::Keyboard::Key::Y, Keys::Y},
			{sf::Keyboard::Key::Z, Keys::Z},
			{sf::Keyboard::Key::Left, Keys::LEFT},
			{sf::Keyboard::Key::Right, Keys::RIGHT},
			{sf::Keyboard::Key::Up, Keys::UP},
			{sf::Keyboard::Key::Down, Keys::DOWN},
			{sf::Keyboard::Key::Return, Keys::ENTER},
			{sf::Keyboard::Key::Space, Keys::SPACE},
			{sf::Keyboard::Key::Delete, Keys::DELETE},
			{sf::Keyboard::Key::BackSpace, Keys::BACKSPACE},
			{sf::Keyboard::Key::Tab, Keys::TAB},
			{sf::Keyboard::Key::Escape, Keys::ESC},
			{sf::Keyboard::Key::Unknown, Keys::NONE}
		};
		sf::Font _font;
		sf::Sprite _sprite;
		sf::Texture _texture;
		std::list<Arcade::Keys> _events;
		sf::RenderWindow _window;
	};
}

#endif /* !ARCADE_SFML_HPP */
