/**
* \file TileRoad.h
*
* \author Charles B. Owen
*
* \brief Class that implements a Road tile
*/

#pragma once

#include "Tile.h"


/**
* \brief A Road tile
*/
class CTileRoad : public CTile
{
public:
    CTileRoad(CCity *city);

    /// \brief Default constructor (disabled)
    CTileRoad() = delete;

    /// \brief Copy constructor (disabled)
    CTileRoad(const CTileRoad &) = delete;

    ~CTileRoad();

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

    void SetAdjacencies(bool ul, bool ur, bool ll, bool lr);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitRoad(this); }

	/**  Set the Orinetaiton of the road
	* \param Orient the int of the Orientation */
	void SetOrientation(int Orient){ mOrientation = Orient; }
	void Rotate();
private:
    
	/// The current adjacency integer or -1 if none
    int mCurrentAdj = -1;
	/// The Road direction
	int mOrientation = 0;
};

