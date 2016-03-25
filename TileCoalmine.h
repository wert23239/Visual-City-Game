/**
* \file TileCoalmine.h
*
* \author Charles B. Owen
*
* \brief Class that implements a Landscape tile
*/

#pragma once

#include "Tile.h"

/**
* \brief A Landscape tile
*/
class CTileCoalmine : public CTile
{
public:
    CTileCoalmine(CCity *city);

    /// \brief Default constructor (disabled)
    CTileCoalmine() = delete;

    /// \brief Copy constructor (disabled)
    CTileCoalmine(const CTileCoalmine &) = delete; 

    ~CTileCoalmine();

    virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitCoalmine(this); }

	void Update(double elapsed);

	/*
	* Count coal production
	* \returns currentCoal Total coal production
	*/
	double CountCoal();

	
	/*
	* Sets the coalmine to trump
	*/
	void Trump();

	/**Switches colemine mUpdate */
	virtual void SwitchUpdate() { mUpdate = !mUpdate; }

private:
	/// Production of coal in tons
	double mProduction = 0;

	/// How long it takes the production to increase
	double mDuration = 0;

	/// True if in trump mode
	bool mTrumpFlag = false;

	/// True if mine is destroyed
	bool mIsDestroyed = false;

	/// Flag to trigger animation for coalmine
	bool mUpdate = true;
};

