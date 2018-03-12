#pragma once
/* #include <PathFinding.h>

#define WORLD_SIZE 10;
struct SearchCell
{
public:
	int monster_x, monster_y;
	int monster_id;
	SearchCell *parent;
	float G;
	float H;

	SearchCell() : parent(0) {}
	SearchCell(int x, int y, SearchCell *_parent = 0) :monster_x(x), monster_y(y),
		parent(_parent), monster_id(y * WORLD_SIZE + y), G(0), H(0) {};
	float GetF() {
		return G + H;
	}
	float Distance(SearchCell * nodeEnd)
	{
		float x = (float)(fabs(this->monster_x - nodeEnd->monster_x));
		float y = (float)(fabs(this->monster_y - nodeEnd->monster_y));
		return x + y;

	}


};
#pragma once
*/