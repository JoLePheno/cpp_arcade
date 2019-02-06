//
// EPITECH PROJECT, 2018
// arcade
// File description:
// arcade
//

#include "../include/PixelBox.hpp"

Arcade::PixelBox::PixelBox(Vect<size_t> size, Vect<size_t> pos, Color col)
{
	_size = size;
	_pos = pos;
	for (unsigned i = 0; i < size.getY() * size.getX(); ++i)
		_colorFrame.push_back(col);
}

size_t Arcade::PixelBox::getHeight() const
{
	return _size.getY();
}

size_t Arcade::PixelBox::getY() const
{
	return _pos.getY();
}

void Arcade::PixelBox::setHeight(size_t height)
{
	_size.setY(height);
}

void Arcade::PixelBox::setY(size_t y)
{
	_pos.setY(y);
}

size_t Arcade::PixelBox::getWidth() const
{
	return _size.getX();
}

size_t Arcade::PixelBox::getX() const
{
	return _pos.getX();
}

void Arcade::PixelBox::setWidth(size_t width)
{
	_size.setX(width);
}

void Arcade::PixelBox::setX(size_t x)
{
	_pos.setX(x);
}

Arcade::Vect<size_t> Arcade::PixelBox::getSize() const
{
	return _size;
}

void Arcade::PixelBox::setSize(Vect<size_t> size)
{
	_size = size;
}

Arcade::Vect<size_t> Arcade::PixelBox::getPos() const
{
	return _pos;
}

void Arcade::PixelBox::setPos(Vect<size_t> pos)
{
	_pos = pos;
}

void Arcade::PixelBox::putPixel(Vect<size_t> pos, Color col)
{
	if (pos.getX() >= _size.getX() ||
	    pos.getY() >= _size.getY())
		return;
	_colorFrame[pos.getY() * _size.getX() + pos.getX()] = col;
}

Arcade::Color Arcade::PixelBox::getPixel(Vect<size_t> pos) const
{
	if (pos.getX() >= _size.getX() ||
	    pos.getY() >= _size.getY())
		exit(84);
	return _colorFrame[pos.getY() * _size.getX() + pos.getX()];
}

void Arcade::PixelBox::putRect(Vect<size_t> pos, Vect<size_t> size, Color col)
{
	for (unsigned i = 0; i < size.getY(); ++i)
		for (unsigned j = 0; j < size.getX(); ++j)
			putPixel(Arcade::Vect<size_t>(pos.getX() + j,
			                              pos.getY() + i), col);
}

std::vector<Arcade::Color> &Arcade::PixelBox::getPixelArray()
{
	return _colorFrame;
}