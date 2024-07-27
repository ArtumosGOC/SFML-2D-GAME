#include "WinClass.h"

falling_square fallingSquare;

void WinClass::falling_square()
{
	while (fallingSquare.getWinIsOpen() && !fallingSquare.getEndGame())
	{
		fallingSquare.update();
		fallingSquare.render();
	}
}
