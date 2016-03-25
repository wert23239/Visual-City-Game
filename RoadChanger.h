/**
* \file RoadChanger.h
*
* \author Jonathan Dowdall
*
* \brief Class that implements the trump functionality
*/

#pragma once
#include "TileVisitor.h"
#include "TileRoad.h"

/** Tile visitor change road direction */
class CRoadChanger :
	public CTileVisitor
{
public:

	CRoadChanger();
	virtual ~CRoadChanger();

	virtual void VisitRoad(CTileRoad *road) override;

};

