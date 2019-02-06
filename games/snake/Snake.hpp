/*
** EPITECH PROJECT, 2018
** Arcade
** File description:
** Snake.hpp
*/

#ifndef ARCADE_SNAKE_HPP
#define ARCADE_SNAKE_HPP

#include <vector>
#include "../../include/IGameLib.hpp"
#include "../../include/Vect.hpp"

namespace Arcade {
	class Snake : public Arcade::IGameLib {
	public:
		Snake();

		const std::string getName() const;

		/* Resources handling */
		// Initializes the library
		bool init() override;

		// Unloads the library
		bool stop() override;

		// Processes the key obtained by the IGraphicLib from the user to update the game state
		bool applyEvent(Keys key) override;

		// Updates the game state. (Move the player forward and/or move the NPCs)
		bool update() override;

		// Renders the game state to the screen. This should call IGraphicLib::refresh() to display content to the user.
		void refresh(IGraphicLib &graphicLib) override;

		// To call at the end of the execution of the game (after the player loose or win) for getting his score
		size_t getScore() override;
		bool printMap(IGraphicLib &graphicLib);
		bool printSnake(Arcade::IGraphicLib &graphicLib);
		void setPlayerName(std::string &name);
		void moveSnake();
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();
		void lookFood();
	private:
		int _mapHeight;
		int _mapWidth;
		int _score;
		const std::vector<std::string> _map = {
			"11111111111111111111111111111111111111111",
			"111111                             111111",
			"111                                   111",
			"1                                       1",
			"1                                       1",
			"1                                       1",
			"1                  1111                 1",
			"1   1              1111                 1",
			"1   1              1111                 1",
			"1   1      11111111111111111111         1",
			"1   1      11111111111111111111         1",
			"1   1              1111       1         1",
			"1   1              1111                 1",
			"1                  1111111              1",
			"1                                       1",
			"1                                   11  1",
			"1         11111                     11  1",
			"1                                       1",
			"11111111111111111111111111111111111111111"};

		std::vector<Arcade::Vect<size_t >> _snakePos;
		Arcade::Keys _key;
		Arcade::Vect<size_t> _food;
		std::string _playerName;

		bool printFood(IGraphicLib &graphicLib);

		Vect <size_t> getNbrRand(size_t x, size_t y);

		void printOthers(IGraphicLib &graphicLib);
	};
};

#endif /* !ARCADE_SNAKE_HPP */
