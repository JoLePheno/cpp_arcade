/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** GTK.hpp
*/

#ifndef ARCADE_GTK_HPP
#define ARCADE_GTK_HPP

#include <iostream>
#include <map>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_test_font.h>
#include "../../include/Keys.hpp"
#include "../../include/IGraphicLib.hpp"

namespace Arcade {
	class SDL2 : public Arcade::IGraphicLib {
		public:
		SDL2();
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
		SDL_Texture *_texture = nullptr;
		TTF_Font *_font = nullptr;
		std::map<SDL_Keycode , Arcade::Keys> _keyMap {
			{SDLK_a, Arcade::Keys::A},
			{SDLK_b, Arcade::Keys::B},
			{SDLK_c, Arcade::Keys::C},
			{SDLK_d, Arcade::Keys::D},
			{SDLK_e, Arcade::Keys::E},
			{SDLK_f, Arcade::Keys::F},
			{SDLK_g, Arcade::Keys::G},
			{SDLK_h, Arcade::Keys::H},
			{SDLK_i, Arcade::Keys::I},
			{SDLK_j, Arcade::Keys::J},
			{SDLK_k, Arcade::Keys::K},
			{SDLK_l, Arcade::Keys::L},
			{SDLK_m, Arcade::Keys::M},
			{SDLK_n, Arcade::Keys::N},
			{SDLK_o, Arcade::Keys::O},
			{SDLK_p, Arcade::Keys::P},
			{SDLK_q, Arcade::Keys::Q},
			{SDLK_r, Arcade::Keys::R},
			{SDLK_s, Arcade::Keys::S},
			{SDLK_t, Arcade::Keys::T},
			{SDLK_u, Arcade::Keys::U},
			{SDLK_v, Arcade::Keys::V},
			{SDLK_w, Arcade::Keys::W},
			{SDLK_x, Arcade::Keys::X},
			{SDLK_y, Arcade::Keys::Y},
			{SDLK_z, Arcade::Keys::Z},
			{SDLK_LEFT, Arcade::Keys::LEFT},
			{SDLK_RIGHT, Arcade::Keys::RIGHT},
			{SDLK_UP, Arcade::Keys::UP},
			{SDLK_DOWN, Arcade::Keys::DOWN},
			{SDLK_RETURN, Arcade::Keys::ENTER},
			{SDLK_SPACE, Arcade::Keys::SPACE},
			{SDLK_DELETE, Arcade::Keys::DELETE},
			{SDLK_BACKSPACE, Arcade::Keys::BACKSPACE},
			{SDLK_TAB, Arcade::Keys::TAB},
			{SDLK_ESCAPE, Arcade::Keys::ESC}
		};
		std::list<Arcade::Keys> _events;
		SDL_Window *_window;
		SDL_Renderer *_renderer;
		std::string _libName;
	};
}

#endif /* !ARCADE_GTK_HPP */
