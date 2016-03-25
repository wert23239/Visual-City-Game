/**
* \file CoalTrumper.cpp
*
* \author Jonathan Dowdall */

#include "stdafx.h"
#include "CoalTrumper.h"

/// Constructor
CCoalTrumper::CCoalTrumper()
{
}

/// Destructor
CCoalTrumper::~CCoalTrumper()
{
}

/** Visit a CTileCoalmine object
* \param coalmine Coalmine we are visiting */
void CCoalTrumper::VisitCoalmine(CTileCoalmine *coalmine)
{
	coalmine->Trump();
}