/**
* \file BuildingCounter.h
*
* \author Jonathan Dowdall
*
* \brief Class that implements the building counter concrete visitor
*/

#pragma once
#include "TileVisitor.h"
/** Visitor Building Counter */
class CBuildingCounter :
	public CTileVisitor
{
public:

	CBuildingCounter();
	virtual ~CBuildingCounter();

	/** Get the number of buildings
	* \returns Number of buildings */
	int GetNumBuildings() const { return mNumBuildings; }

	void VisitBuilding(CTileBuilding *building);

private:
	/// Buildings counter
	int mNumBuildings = 0;

};

