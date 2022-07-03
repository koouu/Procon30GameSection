#include "AOutside.h"
#include "Calculation.h"

#define INF (1<<20)//‚Å‚©‚¢’l

AOutside::AOutside(int teamID) :Algorithm(teamID)
{
	for (int i = 0; i < database.width; i++) {
		for (int j = 0; j < database.height; j++)
			fieldDP[j][i] = -INF;
	}
	int point[4] = {};
	for (int i = 0; i < database.width;i++) {
		point[0] += database.points[0][i] + database.points[1][i];
		point[1] += database.points[database.width - 2][i] + database.points[database.width-1][i];
	}
	for (int i = 0; i < database.width; i++) {
		point[2] += database.points[i][0] + database.points[i][1];
		point[3] += database.points[i][database.height - 2] + database.points[i][database.height - 1];
	}
	point[0] /= database.width;
	point[1] /= database.width;
	point[2] /= database.height;
	point[3] /= database.height;
	if (point[0] == point[1]) { status += (1 << 3); }
	else {
		if (point[1] > point[0]) { status += (1 << 1); }
	}
	if (point[2] == point[3]) { status += (1 << 2); }
	else {
		if (point[3] > point[2]) { status += (1 << 0); }
	}
	if (status == 0b1100 && point[1] == point[3]) {
		status += (1 << 4); 
	}
	
}

void AOutside::execute(int ahead)
{

}

int AOutside::explore(Vector2 v, int x, int y)
{
	v.x += x;
	v.y += y;

	if (fieldDP[v.y][v.x] != -INF)return fieldDP[v.y][v.x];
	if (v.x == -1)return -INF;
	if (v.y == -1)return -INF;
	if (v.x == database.width)return -INF;
	if (v.y == database.height)return -INF;
	
	return tree(v);
}

int AOutside::tree(Vector2 v)
{
	int point=-INF;
	switch (destination) {
	case 0b00:
		max(point,explore(v, -1, -1));
		max(point, explore(v, -1, 0));
		max(point, explore(v, -1, 1));
		break;
	case 0b01:
		max(point, explore(v, -1, -1));
		max(point, explore(v, 0, -1));
		max(point, explore(v, 1, -1));
		break;
	case 0b10:
		max(point, explore(v, 1, -1));
		max(point, explore(v, 1, 0));
		max(point, explore(v, 1, 1));
		break;
	case 0b11:
		max(point, explore(v, -1, 1));
		max(point, explore(v, 0, 1));
		max(point, explore(v, 1, 1));
		break;
	}

	fieldDP[v.y][v.x] = point;

	if (database.tiled[v.y][v.x] == teamID)return point;
	else if (database.tiled[v.y][v.x] == 0)point + database.points[v.y][v.x];
	return point + (database.points[v.y][v.x] * 2);

}
