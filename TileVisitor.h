/**
* \file TileVisitor.h
*
* \author Jonathan Dowdall
*
* Tile visitor base class.
*/


#pragma once

// Forward references to all tile types
class CTileBuilding;
class CTileCoalmine;
class CTileLandscape;
class CTileRoad;
class CTilePower;
class CTileConstruction;

/** Tile visitor base class */
class CTileVisitor
{
public:
	CTileVisitor();
	virtual ~CTileVisitor();

	/** Visit a CTileBuilding object
	* \param building Building we are visiting */
	virtual void VisitBuilding(CTileBuilding *building) { }

	/** Visit a CTileCoalmine object
	* \param coalmine Coal mine we are visiting */
	virtual void VisitCoalmine(CTileCoalmine *coalmine) { }

	/** Visit a CTileLandscape object
	* \param landscape Landscape tile we are visiting */
	virtual void VisitLandscape(CTileLandscape *landscape) { }

	/** Visit a CTilePower object
	* \param power Power we are visiting */
	virtual void VisitPower(CTilePower *power) { }

	/** Visit a CTileRoad object
	* \param road Road we are visiting */
	virtual void VisitRoad(CTileRoad *road) { }

	/** Visit a CTileRoad object
	* \param construction Road we are visiting */
	virtual void VisitConstruction(CTileConstruction *construction) { }

private:
	/// Tiles counter
	int mNumTiles = 0;

};
