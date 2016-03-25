/**
* \file TileConstruction.h
*
* \author Jonathan Dowdall
*
* \brief Class that implements a Landscape tile
*/

#pragma once

#include "Tile.h"

/**
* \brief A Construction tile
*/
class CTileConstruction : public CTile
{
public:
	CTileConstruction(CCity *city);

	/// \brief Default constructor (disabled)
	CTileConstruction() = delete;

	/// \brief Copy constructor (disabled)
	CTileConstruction(const CTileConstruction &) = delete;

	~CTileConstruction();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitConstruction(this); }

	virtual void Update(double elapsed);

	/** \Sets mbuild to true */
	virtual void Build() { mBuild = true; }

	/// \brief Get to see if building
	/// \returns mBuild bool
	virtual bool IsBuilding(){ return mBuild; }

	virtual void PropertiesDlg() override;
	
	/** Virtual func that switches oremine mUpdate*/
	virtual void SwitchUpdate(){};

private:

	/// How long its been clearing
	double mDuration = 0;

	/// Flag to start building
	bool mBuild = false;
};

