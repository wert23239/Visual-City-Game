/**
* \file CoalCounter.h
*
* \author Jonathan Dowdall
*
* \brief Class that implements the building counter concrete visitor
*/

#pragma once
#include "TileVisitor.h"
#include "TileCoalmine.h"

/** Tile visitor coal counter */
class CCoalCounter :
	public CTileVisitor
{
public:

	CCoalCounter();
	virtual ~CCoalCounter();

	/** Get the number of buildings
	* \returns Number of buildings */
	double GetCoalTons() const { return mCoalTons; }

	virtual void VisitCoalmine(CTileCoalmine *coalmine) override;

private:
	/// Total tons of coal that the visitor has collected
	double mCoalTons = 0;

};

