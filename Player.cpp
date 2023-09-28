#include "Player.h"

bool Player::OnMove(string& input)
{
	if (cin >> input)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::OnPromote(char& input)
{
	cin >> input;
}