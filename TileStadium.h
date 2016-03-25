/**
* \file TileStadium.h
*
* \author Jonathan Dowdall
*
* \brief Class that implements a Landscape tile
*/

#pragma once

#include "Tile.h"
#include "TileConstruction.h"

/**
* \brief A Landscape tile
*/
class CTileStadium : public CTileConstruction
{
public:
	CTileStadium(CCity *city);

	/// \brief Default constructor
	CTileStadium();

	/// \brief Copy constructor
	CTileStadium(const CTileStadium &);

	~CTileStadium();

	void Update(double elapsed) override;
	
	bool HitTest(int x, int y) override;

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);
	
private:
	/// Duration of time elapsed
	double mDuration = 0;

};