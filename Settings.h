#pragma once
#include <curses.h>

enum class Type  { Snake, Food, Floor, Wall };
enum class SnakePart { Head, Tail, None };
enum class Color { Black = 0, Yellow = 6, White, Green = 10 };
enum class Direction { Up, Down, Left, Right };
enum class SnakeState { MovingUp, MovingDown, MovingLeft, MovingRight, Still };

static const int SNAKE_HEAD_SYMBOL = '*';
static const int SNAKE_TAIL_SYMBOL = '+';
static const int SNAKE_FOOD_SYMBOL = 'O';
static const int SNAKE_WALL_SYMBOL = '#';

static const int SNAKE_DEFAULT_FIELD_HEIGHT = 50;
static const int SNAKE_DEFAULT_FIELD_WIDTH  = 50;
static const int SNAKE_DEFAULT_POS_X = 25;
static const int SNAKE_DEFAULT_POS_Y = 25;
static const int SNAKE_DEFAULT_LENGTH = 3;
static const int SNAKE_DEFAULT_SPEED = 70;
static const int SNAKE_DEFAULT_SPEED_LEVEL = 1;
static const int SNAKE_MAX_SPEED = 10;
