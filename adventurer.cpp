#include "adventurer.h"


/* setters */
void Adventurer::set_map_size(int map_size)
{
	this->map_size = map_size;
}

void Adventurer::set_num_arrows(int num_arrows) 
{
	this->num_arrows = num_arrows;
}

void Adventurer::set_has_gold(bool has_gold)
{
	this->has_gold = has_gold;
}

void Adventurer::set_x(int x)
{
	this->x = x;
}

void Adventurer::set_y(int y)
{
	this->y = y;
}

void Adventurer::set_x_y(int x, int y)
{
	this->x = x;
	this->y = y;
}


/* getters */
int Adventurer::get_map_size() const
{
	return this->map_size;
}

int Adventurer::get_num_arrows() const
{
	return this->num_arrows;
}

bool Adventurer::get_has_gold() const
{
	return this->has_gold;
}

int Adventurer::get_x() const
{
	return this->x;
}

int Adventurer::get_y() const
{
	return this->y;
}


/* mutators */
void Adventurer::fire_arrow()
{
	this->num_arrows--;
}

void Adventurer::pick_up_gold()
{
	this->has_gold = true;
}

void Adventurer::move_north()
{
	//check if adventurer is already at top
	(y == 0) ? stay() : change_y(-1);
}

void Adventurer::move_south()
{
	//check if adventurer is already at bottom of cave
	(y == (map_size - 1)) ? stay() : change_y(1);
}

void Adventurer::move_east()
{	
	//check if adventurer is already at right side of cave
	(x == map_size - 1) ? stay() : change_x(1);
}

void Adventurer::move_west()
{
	//check if adventurer is already at left side of cave
	(x == 0) ? stay() : change_x(-1);
}

void Adventurer::stay()
{
	return;
}

void Adventurer::change_x(int change)
{
	this->x += change;
}

void Adventurer::change_y(int change)
{
	this->y += change;
}