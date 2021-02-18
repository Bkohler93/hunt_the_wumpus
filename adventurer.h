#ifndef ADVENTURER_H
#define ADVENTURER_H

#include <iostream>

class Adventurer 
{
private:
	int map_size;
	int num_arrows;
	bool has_gold;
	int x, y;

public:
	/* constructors */
	Adventurer(int map_size, int x, int y) : 
		map_size{map_size}, num_arrows{3}, has_gold{false}, x{x}, y{y} {}
	Adventurer() : map_size{0}, num_arrows{3}, has_gold{false}, x{0}, y{0} {}

	/* setters */
	void set_map_size(int);
	void set_num_arrows(int);
	void set_has_gold(bool);
	void set_x(int);
	void set_y(int);
	void set_x_y(int, int);

	/* getters */
	int get_map_size() const;
	int get_num_arrows() const;
	bool get_has_gold() const;
	int get_x() const;
	int get_y() const;

	/* mutators */
	void fire_arrow();	//decreases arrow count by 1
	void pick_up_gold();	//sets has_gold to true;
	void move_north();
	void move_south();
	void move_east();
	void move_west();
	void change_x(int);
	void change_y(int);
	void stay();


};

#endif