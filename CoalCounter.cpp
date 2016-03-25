/**
* \file CoalCounter.cpp
*
* \author Jonathan Dowdall
*/

#include "stdafx.h"
#include "CoalCounter.h"

/// Constructor
CCoalCounter::CCoalCounter()
{
}

/// Destructor
CCoalCounter::~CCoalCounter()
{
}

/** Visit a CTileCoalmine object
* \param coalmine Coalmine we are visiting */
void CCoalCounter::VisitCoalmine(CTileCoalmine *coalmine)
{
	mCoalTons += coalmine->CountCoal();
}