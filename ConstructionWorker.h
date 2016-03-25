/**
* \file ConstructionWorker.h
*
* \author Jonathan Dowdall
*
* \brief Class that implements the construction visitor
*/
#pragma once
#include "TileVisitor.h"
#include "TileConstruction.h"

/** Tile visitor Construction */
class CConstructionWorker :
	public CTileVisitor
{
public:
	CConstructionWorker();
	virtual ~CConstructionWorker();

	/** Visit a CTileCoalmine object
	* \param site Site we are visiting */
	virtual void VisitConstruction(CTileConstruction *site) override { site->Build(); }
};

