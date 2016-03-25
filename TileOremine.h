/**
* \file TileOremine.h
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
class CTileOremine : public CTileConstruction
{
public:
	CTileOremine(CCity *city);

	/// \brief Default constructor (disabled)
	CTileOremine() = delete;

	/// \brief Copy constructor (disabled)
	CTileOremine(const CTileOremine &);

	~CTileOremine();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	virtual void Mine();

	void Update(double elapsed) override;

	/** Switches oremine mUpdate*/
	virtual void SwitchUpdate(){ mUpdate = !mUpdate; }
	
private:
	/// Duration of time elapsed
	double mDuration = 0;
	/// Reversal of image traversal
	bool mReverseImage = false;
	/// Flag to trigger animation for oremine
	bool mIsBuilt = false;
	/// Current image in animation
	int mImageIndex = 0;
	/// Flag to trigger animation for oremine
	bool mUpdate = true;
};

