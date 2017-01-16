#pragma once
#include "GameObjects.h"
#include <iterator>

Snake::Snake() : state(SnakeState::Still), previous_state(SnakeState::MovingRight), speed(SNAKE_DEFAULT_SPEED), length(SNAKE_DEFAULT_LENGTH) {
	tail = { 
		Tile(Type::Snake, SnakePart::Head, Color::White, Color::White, SNAKE_DEFAULT_POS_X, SNAKE_DEFAULT_POS_Y),
		Tile(Type::Snake, SnakePart::Tail, Color::Green, Color::Green, SNAKE_DEFAULT_POS_X - 1, SNAKE_DEFAULT_POS_Y),
		Tile(Type::Snake, SnakePart::Tail, Color::Green, Color::Green, SNAKE_DEFAULT_POS_X - 2, SNAKE_DEFAULT_POS_Y) 
	};
}

void setField(FieldInterface* actual_field) {
	field = actual_field;
}

void Snake::move(Direction dir) {
	int previous_x_inc = x_increment;
	int previous_y_inc = y_increment;

	switch (dir) {
	case Direction::Up: state = SnakeState::MovingUp; x_increment = 0; y_increment = -1; break;
	case Direction::Down: state = SnakeState::MovingDown; x_increment = 0; y_increment = 1; break;
	case Direction::Left: state = SnakeState::MovingLeft; x_increment = -1; y_increment = 0; break;
	case Direction::Right: state = SnakeState::MovingRight; x_increment = 1; y_increment = 0; break;
	}

	bool backwards_movement = previous_state == SnakeState::MovingDown && state == SnakeState::MovingUp ||
							  previous_state == SnakeState::MovingUp && state == SnakeState::MovingDown ||
							  previous_state == SnakeState::MovingLeft && state == SnakeState::MovingRight ||
							  previous_state == SnakeState::MovingRight && state == SnakeState::MovingLeft;
	if (backwards_movement) {
		state = previous_state; 
		x_increment = previous_x_inc;
		y_increment = previous_y_inc;
		//return;
	};

	int new_x = tail.front().x + x_increment;
	int new_y = tail.front().y + y_increment;

	switch (field->getObject(new_x, new_y)->type) {
	case Type::Food: 
		field->removeObject(new_x, new_y); 
		grow(); 
		field->generateFood();  
		break;
	case Type::Snake: state = SnakeState::Still; break;
	case Type::Wall: state = SnakeState::Still; break;
	default:
		int initial_x = tail.begin()->x;
		int initial_y = tail.begin()->y;
		field->swap(&tail[0], field->getObject(new_x, new_y));
		tail[0].x = initial_x;
		tail[0].y = initial_y;
		for (int i = tail.size() - 1; i > 0; --i)
			field->swap(&tail[i], field->getObject(tail[i - 1].x, tail[i - 1].y));
		tail[0].x = initial_x + x_increment;
		tail[0].y = initial_y + y_increment;
		break;
	}
	field->renderSnake();
	field->renderFood();
	previous_state = state;
}

void Snake::grow() {
	tail.begin()->part = SnakePart::Tail;
	tail.begin()->color = Color::Green;
	tail.begin()->foreground = Color::Green;
	tail.push_front(Tile(Type::Snake, SnakePart::Head, Color::White, Color::White, tail.front().x + x_increment, tail.front().y + y_increment));
	++length;
	field->increaseEatenFoodCount();
	field->renderStatistics();
}