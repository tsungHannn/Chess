#pragma once
#include <iostream>
#include <string>
using namespace std;
class Player
{
public:
	
	virtual bool OnMove(string &input);
	virtual void OnPromote(char&);
};

