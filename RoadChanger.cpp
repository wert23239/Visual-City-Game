/**
* \file RoadChanger.cpp
*
* \author Jonathan Dowdall */

#include "stdafx.h"
#include "RoadChanger.h"

/// Constructor
CRoadChanger::CRoadChanger()
{
}

/// Destructor
CRoadChanger::~CRoadChanger()
{
}

/** Visit a CTileCoalmine object
* \param road Road we are visiting */
void CRoadChanger::VisitRoad(CTileRoad *road)
{
	road->Rotate();
}