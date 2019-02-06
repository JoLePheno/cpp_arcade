/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#pragma once

namespace Arcade {
	class Color {
	public:
		Color(unsigned char red = 0, unsigned char green = 0,
			unsigned char blue = 0, unsigned char alpha = 0);
		void setColor(unsigned char red = 0, unsigned char green = 0,
			unsigned char blue = 0, unsigned char alpha = 0);
		unsigned char getRed() const;
		unsigned char getGreen() const;
		unsigned char getBlue() const;
		unsigned char getAlpha() const;
		void setRed(unsigned char red);
		void setGreen(unsigned char green);
		void setBlue(unsigned char blue);
		void setAlpha(unsigned char alpha);
		operator unsigned char *();
		bool operator==(const Arcade::Color &other) const
		{
			return _red == other.getRed() && _green == other.getGreen() &&
			       _blue == other.getBlue() && _alpha == other.getAlpha();
		}
		bool operator!=(const Color &other) const
		{
                 	return !(_red == other._red && _green == other._green &&
				_blue == other._blue && _alpha == other._alpha);
		}
	private:
		unsigned char _red;
		unsigned char _green;
		unsigned char _blue;
		unsigned char _alpha;
	};
};
