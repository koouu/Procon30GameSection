#pragma once
#include"structs.h"
class Field
{
	FieldV2 field;
	std::string action[16];
public:
	Field(FieldV2 field);
	FieldV2 getMove(Vector2 move[]);
	void draw();
	std::string *getAgentAction();
};

