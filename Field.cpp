#pragma once
#include "Field.h"

void Field::create() {
	for (int i = 0; i < height; ++i) {
		tiles.push_back(std::deque<Tile*>());
		for (int j = 0; j < width; ++j)
			tiles[i].push_back(new Tile(Type::Floor, SnakePart::None, Color::Black, Color::Black, j, i));
	}
	for (int i = 0; i < width; ++i) {
		tiles[0][i] = new Tile(Type::Wall, SnakePart::None, Color::White, Color::White, i, 0);
		tiles[height - 1][i] = new Tile(Type::Wall, SnakePart::None, Color::White, Color::White, i, height - 1);
	}
	for (int i = 0; i < height; ++i) {
		tiles[i][0] = new Tile(Type::Wall, SnakePart::None, Color::White, Color::White, 0, i);
		tiles[i][width - 1] = new Tile(Type::Wall, SnakePart::None, Color::White, Color::White, width - 1, i);
	}
}

void Field::render() {
	initscr();
	clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	resize_term(height + 10, width + 30);
	start_color();

	renderWalls();
	renderSnake();
	renderFood();
	renderStatistics();

	refresh();
}

void Field::render(Tile* t) {
	char tile;
	switch (t->type) {
	case Type::Food: tile = SNAKE_FOOD_SYMBOL; break;
	case Type::Snake: tile = (t->part == SnakePart::Head) ? '*' : '+'; break;
	case Type::Wall: tile = SNAKE_WALL_SYMBOL; break;
	default: tile = ' '; break;
	}
	init_pair(tile, (int)t->color, (int)t->foreground);
	attron(COLOR_PAIR(tile));
	mvaddch(t->y + 5, t->x + 15, tile);
	attroff(COLOR_PAIR(tile));
}

void Field::renderFood() {
	render(tiles[food_y][food_x]);
	refresh();
}

void Field::renderSnake() {
	for (size_t i = 0; i < snake.tail.size(); ++i)
		render(&snake.tail[i]);
}

void Field::renderWalls() {
	for (int i = 0; i < width; ++i) {
		render(tiles[0][i]);
		render(tiles[height - 1][i]);
	}
	for (int i = 0; i < height; ++i) {
		render(tiles[i][0]);
		render(tiles[i][width - 1]);
	}
}

void Field::renderStatistics() {
	mvprintw(2, 15, "Score: %d", snake.length - SNAKE_DEFAULT_LENGTH);
	mvprintw(3, 15, "Speed level: %d", speed_level);
}

void Field::generateFood() {
	srand(time(0));
	int x, y;
	Type dest_tile_type = getObject(x = rand() % (width - 10) + 5, y = rand() % (height - 10) + 5)->type;
	while (dest_tile_type == Type::Snake || dest_tile_type == Type::Wall)
		dest_tile_type = getObject(x = rand() % (width - 10) + 5, y = rand() % (height - 10) + 5)->type;;
	tiles[y][x] = new Tile(Type::Food, SnakePart::None, Color::Yellow, Color::Yellow, x, y);
	food_x = x;
	food_y = y;
}

Tile* Field::getObject(int x, int y) {
	return tiles[y][x];
}

void Field::removeObject(int x, int y) {
	delete tiles[y][x];
	tiles[y][x] = new Tile(Type::Floor, SnakePart::None, Color::Black, Color::Black, x, y);
}

void Field::increaseEatenFoodCount() {
	++eaten;
}

void Field::swap(Tile* t1, Tile* t2) {
	int dest_x = t2->x;
	int dest_y = t2->y;
	tiles[t1->y][t1->x] = t2;
	tiles[t2->y][t2->x] = t1;
	t2->x = t1->x;
	t2->y = t1->y;
	t1->x = dest_x;
	t1->y = dest_y;
	render(t1);
	render(t2);
	refresh();
}

void Field::suffer() {
	clear();
	mvprintw(height / 2, width / 2 + 8, "Bet it was tasty");
	mvprintw(height / 2 + 1, width / 2 + 5, "Press R to start again");
	mvprintw(height / 2 + 2, width / 2 + 6, "Press Q to exit game");
	refresh();
}