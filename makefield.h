#pragma once
#include"structs.h"
class MakeField
{
private:
	Vector2 size;
public:
	MakeField(bool sizeRand,Vector2 &s);
	FieldV2 make();
};

