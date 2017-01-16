#pragma once
#include "Settings.h"
#include <ctime>
#include <typeinfo>
#include <deque>

static int x_increment;
static int y_increment;

class Tile;
class Snake;

class FieldInterface {
public:
	virtual void swap(Tile*, Tile*) = 0;
	virtual Tile* getObject(int x, int y) = 0;
	virtual void removeObject(int x, int y) = 0;
	virtual void render() = 0;
	virtual void renderWalls() = 0;
	virtual void renderSnake() = 0;
	virtual void renderFood() = 0;
	virtual void renderStatistics() = 0;
	virtual void generateFood() = 0;
	virtual void increaseEatenFoodCount() = 0;

	int width;
	int height;
};
static FieldInterface* field;
void setField(FieldInterface* actual_field);

class Tile {
public:
	Tile(Type t, SnakePart p, Color c, Color f, int x, int y) : type(t), part(p), color(c), foreground(f), x(x), y(y) {};
	~Tile() {};

	int x;
	int y;
	Type type;
	Color color;
	Color foreground;
	SnakePart part;
};

class Snake {
public:
	Snake();
	~Snake() {};

	void move(Direction);
	void grow();

	int speed;
	int length;
	SnakeState state;
	SnakeState previous_state;
	std::deque<Tile> tail;
};