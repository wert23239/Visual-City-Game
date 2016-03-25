/**
* \file BlankTile.h
*
* \author Chiyu Song
*
* \brief Base class for a blank tile which is not a derived class from CTile
*/

#pragma once

#include <string>
#include <memory>

class CCity;

class CBlankTile
{
public:
	CBlankTile(int x, int y, std::wstring file);
	virtual ~CBlankTile();

	/** \brief Get the file name for this tile image
	* \returns Filename or blank if none */
	std::wstring GetFile() { return mFile; }

	/** \brief The X location of the center of the tile
	* \returns X location in pixels */
	int GetX() const { return mX; }

	/** \brief The Y location of the center of the tile
	* \returns Y location in pixels */
	int GetY() const { return mY; }

private:
	// Item location in the aquarium
	int   mX = 0;     ///< X location for the center of the item
	int   mY = 0;     ///< Y location for the center of the item

	/// The file for this item
	std::wstring mFile;
};

