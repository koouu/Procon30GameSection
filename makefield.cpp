#include "makefield.h"
#include "DxLib.h"




MakeField::MakeField(bool sizeRand,Vector2 &size)
{
	
	if (sizeRand) {
		size.x = GetRand(10) + 10;
		size.y = GetRand(10) + 10;
	}
	
	this->size = size;
	

}

FieldV2 MakeField::make()
{
	FieldV2 v2;
	int pattern=1,center_y=size.y%2,center_x=0;
	while (1) {
		if (GetRand(1)) {
			pattern = 2;
			center_x = size.x % 2;
		}
		for (int i = 0; i < center_y + (size.y / 2); i++) {
			for (int j = 0; j < center_x + (size.x / pattern); j++) {
				v2.field[i][j] = GetRand(32) - 16;
			}
		}
		if (pattern - 1) {
			for (int i = 0; i < center_y + (size.y / 2); i++) {
				for (int j = 0; j < (size.x / pattern); j++) {
					v2.field[i][size.x - 1 - j] = v2.field[i][j];
				}
			}
		}
		for (int i = 0; i < (size.y / 2); i++) {
			for (int j = 0; j < (size.x); j++) {
				v2.field[size.y - 1 - i][j] = v2.field[i][j];
			}
		}
		int point = 0;
		for (int i = 0; i < size.y; i++) {
			for (int j = 0; j < size.x; j++) {
				point += v2.field[i][j];
			}
		}
		if(point>=0)
		return v2;
	}
	
}


