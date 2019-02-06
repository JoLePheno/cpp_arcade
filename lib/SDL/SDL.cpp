/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** SDL.cpp
*/

#include <iostream>
#include <list>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cstdint>
#include <stdint-gcc.h>
#include "SDL.hpp"

Arcade::IGraphicLib *ret = nullptr;

Arcade::SDL2::SDL2(): _events(),
                      _window(nullptr),
                      _renderer(nullptr),
                      _libName("SDL")
{
	TTF_Init();
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
}

void Arcade::SDL2::openRenderer()
{
	this->_window = SDL_CreateWindow(
		"Arcade : \"Les barres du zoo\"",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_OPENGL
	);
	if (!this->_window) {
		std::cout << "Could not create window: %s\n" << SDL_GetError
			() << std::endl;
	}
	this->_renderer = SDL_CreateRenderer(this->_window, -1, SDL_RENDERER_ACCELERATED);
	_texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA32,
	                             SDL_TEXTUREACCESS_STREAMING, 800, 600);
}

std::string Arcade::SDL2::getName() const
{
	return _libName;
}

void Arcade::SDL2::closeRenderer()
{
	SDL_DestroyRenderer(this->_renderer);
	SDL_DestroyTexture(_texture);
	SDL_DestroyWindow(this->_window);
	SDL_Quit();
	TTF_Quit();
	_window = nullptr;
}

bool Arcade::SDL2::isOpen() const
{
	return _window != nullptr;
}

void Arcade::SDL2::clearWindow()
{
	if (this->_window) {
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 0);
		SDL_RenderClear(this->_renderer);
	}
}

void Arcade::SDL2::drawText(Arcade::TextBox &text)
{
	if (text.getValue().empty())
			return;
	auto *tab = (unsigned char *)text.getColor();
	SDL_Color figure = {tab[0], tab[1], tab[2], tab[3]};
	tab = (unsigned char *)text.getBackgroundColor();
	SDL_Color background = {tab[0], tab[1], tab[2], tab[3]};
	_font = TTF_OpenFont("fonts/arial.ttf", static_cast<int>(text.getFontSize()));
	if (!_font)
		std::cout << "can't load font" << std::endl;
	auto surface = TTF_RenderText_Shaded(_font, text.getValue().c_str(), figure, background);
	_texture = SDL_CreateTextureFromSurface(_renderer, surface);
	SDL_Rect pos = {static_cast<int>(text.getX()), static_cast<int>(text.getY()), surface->w, surface->h};
	SDL_RenderCopy(_renderer, _texture, nullptr, &pos);
	SDL_FreeSurface(surface);
	TTF_CloseFont(_font);
}

void Arcade::SDL2::refreshWindow()
{
	if (this->_window)
		SDL_RenderPresent(this->_renderer);
}

void Arcade::SDL2::drawPixelBox(Arcade::PixelBox &pixelBox)
{
	SDL_Rect draw{};

	draw.x = static_cast<int>(pixelBox.getX());
	draw.y = static_cast<int>(pixelBox.getY());
	draw.w = static_cast<int>(pixelBox.getWidth());
	draw.h = static_cast<int>(pixelBox.getHeight());
	SDL_UpdateTexture(_texture, &draw, &pixelBox.getPixelArray()[0],
	                  static_cast<int>(pixelBox.getWidth() * 4));
	SDL_RenderCopy(_renderer, _texture, &draw, &draw);
}

bool Arcade::SDL2::pollEvents()
{
	SDL_Event event{};
	bool value = false;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN &&
		    _keyMap.count(event.key.keysym.sym)) {
			_events.push_back(_keyMap[event.key.keysym.sym]);
			value = true;
		}
	}
	return value;
}

Arcade::Keys Arcade::SDL2::getLastEvent()
{
	Arcade::Keys key = _events.back();
	if (!_events.empty())
		_events.pop_back();
	return key;
}

void Arcade::SDL2::clearEvents()
{
	this->_events.clear();
}

Arcade::Vect<size_t> Arcade::SDL2::getScreenSize() const
{
	int h;
	int w;
	SDL_GetWindowSize(_window, &w, &h);
	Arcade::Vect<size_t> size;

	size.setXY(static_cast<size_t>(w), static_cast<size_t>(h));
	return size;
}

int Arcade::SDL2::getMaxY() const
{
	int h;
	int w;
	SDL_GetWindowSize(_window, &w, &h);

	return h;
}

int Arcade::SDL2::getMaxX() const
{
	int h;
	int w;
	SDL_GetWindowSize(_window, &w, &h);

	return w;
}

__attribute__((constructor))
void enter()
{
	ret = new Arcade::SDL2;
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
