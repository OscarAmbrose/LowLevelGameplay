#pragma once
#include <GameObject.h>

class PlayerCharacter : public GameObject
{
public:
	PlayerCharacter();
	PlayerCharacter(int playerNumber);
	~PlayerCharacter() {}

	//Initialise the character, this sets up all of the default information for the character
	PlayerCharacter* InitialiseCharacter();

	int GetPlayerNumber() const { return m_PlayerNumber; }
	void SetPlayerNumber(int newPlayerNum) { m_PlayerNumber = newPlayerNum; }

protected:

	//Player number should equal the controller which is controlling the character
	int m_PlayerNumber;
};
