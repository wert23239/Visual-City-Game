/**
* \file BlankTile.h
*
* \author Chiyu Song
*/

#include "stdafx.h"
#include "City.h"
#include "BlankTile.h"

using namespace std;

/**
* Brief Constructor
* \param x
* \param y
* \param file
*/
CBlankTile::CBlankTile(int x, int y, std::wstring file)
{
	mX = x;
	mY = y;
	mFile = file;
}

/**
* Brief Destructor
*/
CBlankTile::~CBlankTile()
{
}
