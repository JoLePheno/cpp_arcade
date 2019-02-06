/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** main.cpp
*/

#include <stdlib.h>
#include <iostream>
#include "include/Core.hpp"
#include "include/IGraphicLib.hpp"

int arcade(const std::string s1)
{
	Core *core = new Core(s1);
	Arcade::IGraphicLib *lib = core->load_gfx();
	std::cout << lib->getName() << std::endl;
	core->loopCore(lib);
	return (0);
}

int main(int ac, char **av)
{
	if (ac != 2) {
		std::cout << "Usage: ./arcade {path to a gfx library}" << std::endl;
		return 1;
	}
	else
		return arcade(std::string(av[1]));
}
