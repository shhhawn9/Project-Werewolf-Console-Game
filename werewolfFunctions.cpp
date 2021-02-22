/*
 * Group Members: Haley Goldlist
                  Adrian Maceiras
                  Shawn Gu
 */
// DO NOT CHANGE OR REMOVE THE FOLLOWING LINES
#ifndef __DEFINE_WEREWOLF_FUNCTIONS_CPP__
#define __DEFINE_WEREWOLF_FUNCTIONS_CPP__

#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include "mapFunctions.cpp"
#include "utilityFunctions.cpp"
// DO NOT CHANGE OR REMOVE THE PRECEDING LINES

/*
 * WEREWOLF CONSTANTS
 */
const char WEREWOLF_SYMBOL_NORMAL = 'W';
const char WEREWOLF_SYMBOL_STUNNED = 'w';
const char WEREWOLF_SYMBOL_DEAD = 'm';
const int WEREWOLF_MAX_DAMAGE = 5;
const int WEREWOLF_POST_DAMAGE_TELEPORT_DISTANCE = 6;
const int WEREWOLF_PICTURE_WIDTH = 36;
const int WEREWOLF_PICTURE_HEIGHT = 12;
const string WEREWOLF_PICTURE[WEREWOLF_PICTURE_HEIGHT] = {
	"             /\\",
	"            ( ;`~v/~~~ ;._",
	"         ,/'\"/^) ' < o\\  '\".~'\\\\\\--,",
	"       ,/\",/W  u '`. ~  >,._..,   )'",
	"      ,/'  w  ,U^v  ;//^)/')/^\\;~)'",
	"   ,/\"'/   W` ^v  W |;         )/'",
	" ;''  |  v' v`\" W }  \\\\",
	"\"    .'\\    v  `v/^W,) '\\)\\.)\\/)",
	"         `\\   ,/,)'   ''')/^\"-;'",
	"              \\",
	"               '\". _",
	"                    \\" };

/*
 * WEREWOLF STATE
 */
int werewolfX;
int werewolfY;
int werewolfHealth = 0;
int werewolfStunnedCount = 0;
bool skipWerewolfsTurn = false;

/*
 * FUNCTION PROTOTYPES
 */
bool isOpenSpaceForWerewolf(const int, const int);
//the werewolf can also walk over key, pebble, pebbles, plank, plank_set, and rope squares. The werewolf cannot walk over tied ropes.

bool werewolfIsAlive() // EREZ: correct
{
	/* GOOD CODE */
	// return True only if the werewolf has health greater than zero.
	if (werewolfHealth > 0)
	{
		return true;
	}
    else
    {
        return false;
    }
}

bool werewolfIsStunned() // EREZ: correct
{
	/* GOOD CODE */
	// return true only if the werewolf's stun count is greater than zero
	if (werewolfStunnedCount > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

char getWerewolfSymbol() // EREZ: correct
{
	/* GOOD CODE */
	//return a different symbol depending on whether the werewolf is alive but not stunned, alived and stunned, or dead.
	if (werewolfIsStunned() && werewolfIsAlive())
	{
		return WEREWOLF_SYMBOL_STUNNED;
	}
	else if (werewolfIsAlive() && !werewolfIsStunned())
	{
		return WEREWOLF_SYMBOL_NORMAL;
	}
	else
	{
		return WEREWOLF_SYMBOL_DEAD;
	}
}

int doWerewolfHit(const int hitpoints) // EREZ: correct
{
	/* GOOD CODE */
	//a. Subtract hitpoints from werewolfHealth.
	//b.Make sure werewolfHealth is never below zero.
	//c.Add 2 to werewolfStunnedCount.
	//d. return werewolfHealth
	if (werewolfHealth > 0)
	{
		werewolfHealth = werewolfHealth - hitpoints;
        werewolfStunnedCount = werewolfStunnedCount + 2;
        if (werewolfHealth <=0)
        {
            werewolfHealth = 0;
            werewolfStunnedCount = 0;
        }
    }
	return werewolfHealth;
}

void doWerewolfNextMove(const int playerX, const int playerY)
{
	//a. If the werewolf is not alive, stop executing this function.
	//b.If the werewolf's turn should be skipped this round, reset the flag and stop executing this function.
	//c.If werewolfStunnedCount is greater than zero, subtract one from werewolfStunnedCount and stop executing this function.

	/* GOOD CODE */
	if (!werewolfIsAlive()) // EREZ: correct
	{
		return;
	}
    else if (skipWerewolfsTurn) // EREZ: correct
    {
        skipWerewolfsTurn = false; // EREZ: correct
        return;
    }
	else if (werewolfIsStunned())  // EREZ: correct
	{
		werewolfStunnedCount--;
        return;
	}

	int deltaX = playerX - werewolfX; // distance from werewolf to player in X direction
	int deltaY = playerY - werewolfY; // distance from werewolf to player in Y direction

	int possibleNextX = werewolfX + sign(deltaX); // one square closer to player in X direction
	int possibleNextY = werewolfY + sign(deltaY); // one square closer to player in Y direction

	bool xDirectionMovePossible = (deltaX != 0 && isOpenSpaceForWerewolf(possibleNextX, werewolfY));
	bool yDirectionMovePossible = (deltaY != 0 && isOpenSpaceForWerewolf(werewolfX, possibleNextY));

	if (xDirectionMovePossible && !yDirectionMovePossible)
	{
		werewolfX = possibleNextX;
	}
	else if (!xDirectionMovePossible && yDirectionMovePossible)
	{
		werewolfY = possibleNextY;
	}
	else if (xDirectionMovePossible && yDirectionMovePossible)
	{
		if (abs(deltaX) > abs(deltaY))
		{
			werewolfX = possibleNextX;
		}
		else if (abs(deltaX) < abs(deltaY))
		{
			werewolfY = possibleNextY;
		}
		else
		{
            //On the line bool randomlyPickX = (true /* MISSING CODE */);replace the truewith code that will randomly return true or falsewith equal probability. Make sure your code does not produce any errors nor warnings for this line.
            /* Good Code */
            bool randomlyPickX = rand() % 2;
            if (randomlyPickX)
            {
                werewolfX = possibleNextX;
            }
            else
            {
                werewolfY = possibleNextY;
            }
            
		}
	}
}

bool isOpenSpaceForWerewolf(const int x, const int y)
{
    char mapSquare = getMapSquare(x, y);
    return (mapSquare == MAP_SQUARE_EMPTY     || // EREZ: correct
            mapSquare == MAP_SQUARE_KEY       || // EREZ: correct
            mapSquare == MAP_SQUARE_PEBBLE    || // EREZ: correct
            mapSquare == MAP_SQUARE_PEBBLES   || // EREZ: correct
            mapSquare == MAP_SQUARE_PLANK     || // EREZ: correct
            mapSquare == MAP_SQUARE_PLANK_SET || // EREZ: correct
            mapSquare == MAP_SQUARE_ROPE      ); // EREZ: correct
		// fixed EREZ: no, you MUST remove this part of the condition for it to work correctly
}

// DO NOT CHANGE OR REMOVE THE FOLLOWING LINE
#endif
// DO NOT CHANGE OR REMOVE THE PRECEDING LINE
