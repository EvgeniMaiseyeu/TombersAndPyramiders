#pragma once
/*#include "Vector2.h"
#include <vector>
#include <SearchCell.h>

class PathFinding
{
public:
	PathFinding(void);
	~PathFinding(void);

	void FindPath(Vector2 currentPos, Vector2 targetPos);
	Vector2 NextPathPos();
	void ClearOpenList() { monster_openList.clear(); }
	void ClearVisitedList() { monster_visitedList.clear(); }
	void ClearPathToGoal() {
		monster_pathToGoal.clear();
	}
	bool monster_intializedStartGoal;
	bool monster_foundGoal;

Private:
	void SetStartAndGoal(searchCell start, SearchCell goal);
	void pathOpened(int x, int y, float newCoast, SearchCell * parent);
	SearchCell * GetNextCell();
	void ContinuePath();


	SearchCell * monster_startCell;
	SearchCell *monster_goalCell;
	std::vector<SearchCell*> monster_openList;
	std::vector<SearchCell*> monster_visitedList;
	std::vector<Vector2*> monster_pathToGoal;

};
*/