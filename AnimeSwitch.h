/**
* \file AnimeSwitch.h
*
* \author Chiyu Song
*
* \brief Visitor that switches animation on/off
*/

#pragma once
#include "TileVisitor.h"
#include "TileCoalmine.h"
#include "TileConstruction.h"
/** Visitor AnimeSwitch */
class CAnimeSwitch :
	public CTileVisitor
{
public:
	CAnimeSwitch();
	virtual ~CAnimeSwitch();

	/** Switches TileCoalmine::mUpdate
	* /param *coalmine
	*/
	virtual void VisitCoalmine(CTileCoalmine *coalmine) { coalmine->SwitchUpdate(); }

	/** Switches TileContruction::mBuild
	* /param *construction
	*/
	virtual void VisitConstruction(CTileConstruction *construction) { construction->SwitchUpdate(); }
};

