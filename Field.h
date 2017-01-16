#pragma once
#include "GameObjects.h"

class Field : public FieldInterface {
public:
	Field() : width(SNAKE_DEFAULT_FIELD_WIDTH), height(SNAKE_DEFAULT_FIELD_HEIGHT), snake(Snake()), eaten(0), speed_level(SNAKE_DEFAULT_SPEED_LEVEL) { setField(this); };
	~Field() {};

	void create();
	void render();
	void render(Tile*);
	void renderWalls();
	void renderSnake();
	void renderFood();
	void renderStatistics();
	void swap(Tile*, Tile*);
	Tile* getObject(int x, int y);
	void removeObject(int x, int y);
	void generateFood();
	void increaseEatenFoodCount();

	void suffer();

	int width;
	int height;

	int food_x;
	int food_y;

	int eaten;
	Snake snake;
	int speed_level;
	std::deque<std::deque<Tile*>> tiles;
};