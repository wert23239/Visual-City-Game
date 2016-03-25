/**
* \file TileCounter.h
*
* \author Jonathan Dowdall
*
* \brief Class that implements the Tile counter concrete visitor
*/

#pragma once
#include "TileVisitor.h"
#include "Tile.h"

/** Tile visitor counts tiles*/
class CTileCounter :
	public CTileVisitor
{
public:

	CTileCounter();
	virtual ~CTileCounter();

	/** Visit a CTileBuilding object
	* \param building Building we are visiting */
	virtual void VisitBuilding(CTileBuilding *building) { mNumTiles++; }

	/** Visit a CTileCoalmine object
	* \param coalmine Coal mine we are visiting */
	virtual void VisitCoalmine(CTileCoalmine *coalmine) { mNumTiles++; }

	/** Visit a CTileLandscape object
	* \param landscape Landscape tile we are visiting */
	virtual void VisitLandscape(CTileLandscape *landscape) { mNumTiles++; }

	/** Visit a CTilePower object
	* \param power Power we are visiting */
	virtual void VisitPower(CTileRoad *power) { mNumTiles++; }

	/** Visit a CTileRoad object
	* \param road Road we are visiting 
	*/
	virtual void VisitRoad(CTileRoad *road) { mNumTiles++; }

	/** Get the number of Tiles
	* \returns Number of Tiles */
	int GetNumTiles() const { return mNumTiles; }

	/** Get the number of partially overlapped Tiles
	* \returns Number of Tiles */
	int GetNumPartOverlap() const { return mNumPartOverlap; }

	/** Get the number of partially overlapped Tiles
	* \returns Number of Tiles */
	int GetNumOverlap() const { return mNumOverlap; }

private:
	/// Tiles counter
	int mNumTiles = 0;

	/// Partially overlapped tiles counter
	int mNumPartOverlap = 0;
	
	/// Total overlaps
	int mNumOverlap = 0;
};
