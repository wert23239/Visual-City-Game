/**
* \file CoalTrumper.h
*
* \author Jonathan Dowdall
*
* \brief Class that implements the trump functionality
*/

#pragma once
#include "TileVisitor.h"
#include "TileCoalmine.h"

/** Tile visitor Trump*/
class CCoalTrumper :
	public CTileVisitor
{
public:

	CCoalTrumper();
	virtual ~CCoalTrumper();

	virtual void VisitCoalmine(CTileCoalmine *coalmine) override;
	
};

