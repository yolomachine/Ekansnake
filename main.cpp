#include "Field.h"
#include <Windows.h>

void game_begin() {
	Field field;
	field.create();
	field.render();
	field.generateFood();
	field.renderFood();

	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	bool lost = false;
	bool paused = false;
	bool init_phase = true;
	while (true) {
		if (lost) break;
		if (GetAsyncKeyState(VK_LEFT)) field.snake.state = SnakeState::MovingLeft;
		else if (GetAsyncKeyState(VK_RIGHT)) field.snake.state = SnakeState::MovingRight;
		else if (GetAsyncKeyState(VK_UP)) field.snake.state = SnakeState::MovingUp;
		else if (GetAsyncKeyState(VK_DOWN)) field.snake.state = SnakeState::MovingDown;
		else if (GetAsyncKeyState(VK_SPACE)) {
			paused = true;
			mvprintw(field.height + 7, 15, "Paused");
			refresh();
			while (paused) {
				Sleep(150);
				if (GetAsyncKeyState(VK_SPACE))
					paused = false;
			}
			mvprintw(field.height + 7, 15, "      ");
			refresh();
		}

		switch (field.snake.state) {
		case SnakeState::Still: lost = (!init_phase) ? true : false; break;
		case SnakeState::MovingLeft: init_phase = false; field.snake.move(Direction::Left); break;
		case SnakeState::MovingRight: init_phase = false; field.snake.move(Direction::Right); break;
		case SnakeState::MovingUp: init_phase = false; field.snake.move(Direction::Up); break;
		case SnakeState::MovingDown: init_phase = false; field.snake.move(Direction::Down); break;
		}

		Sleep(field.snake.speed);
		if (field.eaten != 0 && field.eaten % 10 == 0 && field.snake.speed != SNAKE_MAX_SPEED) {
			field.snake.speed -= 10;
			field.eaten = 0;
			++field.speed_level;
			field.renderStatistics();
		}
	}

	for (int i = 0; i < 5; ++i) {
		clear();
		refresh();
		Sleep(200);
		field.renderWalls();
		field.renderSnake();
		field.renderFood();
		field.renderStatistics();
		refresh();
		Sleep(200);
	}

	field.suffer();
	while (field.snake.tail.size()) {
		field.snake.tail.back().~Tile();
		field.snake.tail.pop_back();
	}
	field.snake.~Snake();
	while (field.tiles.size()) {
		while (field.tiles.back().size()) field.tiles.back().pop_back();
		field.tiles.pop_back();
	}
	field.~Field();

	int key;
	while (key = getchar()) {
		if (key == 'r') {
			game_begin();
			break;
		}
		else if (key == 'q') break;
	}
}
int main() {
	game_begin();
}
