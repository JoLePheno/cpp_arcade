/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** SFML.cpp
*/

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "SFML.hpp"

Arcade::IGraphicLib *ret = nullptr;

__attribute__((constructor))
void enter()
{
	ret = new Arcade::SFML;
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

Arcade::SFML::SFML()
{
	_window.setFramerateLimit(30);
	_texture.create(800, 600);
	_sprite.setTexture(_texture);
	if (!_font.loadFromFile("fonts/arial.ttf")) {
		std::cout << "error fonts" << std::endl;
	}
}

void Arcade::SFML::drawText(Arcade::TextBox &textBox)
{
	if (!isOpen() || textBox.getValue().empty())
		return ;
	_text.setFont(_font);
	_text.setString(textBox.getValue());
	_text.setCharacterSize(static_cast<unsigned int>(textBox.getFontSize()));
	_text.setColor(*(sf::Color *)((unsigned char *)textBox.getColor()));
	_text.setPosition(textBox.getPos().getX(), textBox.getPos().getY());
	_window.draw(_text);
}

bool Arcade::SFML::isOpen() const
{
	return _window.isOpen();
}

void Arcade::SFML::clearWindow()
{
	_window.clear();
}

void Arcade::SFML::refreshWindow()
{
	_window.display();
}

void Arcade::SFML::closeRenderer()
{
	_window.close();
}

std::string Arcade::SFML::getName() const
{
	return std::__cxx11::string("SFML");
}

void Arcade::SFML::openRenderer()
{
	_window.create(sf::VideoMode(800, 600), "Arcade: \"les barres du "
		"zoo\"");
}

void Arcade::SFML::drawPixelBox(Arcade::PixelBox &pixelBox)
{
	_texture.update((unsigned char *)&pixelBox.getPixelArray()[0],
	                static_cast<unsigned int>(pixelBox.getWidth()),
	                static_cast<unsigned int>(pixelBox.getHeight()),
	                static_cast<unsigned int>(pixelBox.getX()),
	                static_cast<unsigned int>(pixelBox.getY()));
	_sprite.setTextureRect(sf::Rect<int>(static_cast<int>(pixelBox.getX()),
	                                     static_cast<int>(pixelBox.getY()),
	                                     static_cast<int>(pixelBox.getWidth()),
	                                     static_cast<int>(pixelBox.getHeight())));
	_sprite.setPosition(pixelBox.getX(), pixelBox.getY());
	_window.draw(_sprite);

}

bool Arcade::SFML::pollEvents()
{
	sf::Event event{};
	bool value = false;

	while (this->isOpen() && _window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed) {
			try
			{
				this->_events.push_back(_keyMap.at(event.key.code));
			}
			catch(const std::out_of_range)
			{
			}
			value = true;
		}
	}
	return value;
}

Arcade::Keys Arcade::SFML::getLastEvent()
{
	Arcade::Keys key = _events.back();
	if (!_events.empty())
		_events.pop_back();
	return key;
}

void Arcade::SFML::clearEvents()
{
	this->_events.clear();
}

Arcade::Vect<size_t> Arcade::SFML::getScreenSize() const
{
	Arcade::Vect<size_t> size;

	size.setX(_window.getSize().x);
	size.setY(_window.getSize().y);
	return size;
}

int Arcade::SFML::getMaxY() const
{
	return (_window.getSize().y);
}

int Arcade::SFML::getMaxX() const
{
	return (_window.getSize().x);
}
