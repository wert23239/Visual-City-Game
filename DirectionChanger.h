/**
* \file DirectionChanger.h
*
* \author Chiyu Song
*
* \brief Class that Change the direction of a power grid
*/

#pragma once
#include "TileVisitor.h"
#include "TilePower.h"

/** Tile visitor change power directions */
class CDirectionChanger :
	public CTileVisitor
{
public:

	CDirectionChanger();
	virtual ~CDirectionChanger();

	/**
	* \param power  Change the direction of a power grid*/
	void VisitPower(CTilePower *power) { power->ChangeDirection(); }
};
