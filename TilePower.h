/**
* \file TilePower.h
*
* \author Chiyu Song
*
* \brief Class that implements a Power tile
*/

#pragma once

#include "Tile.h"


/**
* \brief A Power tile
*/
class CTilePower : public CTile
{
public:
	CTilePower(CCity *city);

	/// \brief Default constructor (disabled)
	CTilePower() = delete;

	/// \brief Copy constructor (disabled)
	CTilePower(const CTilePower &) = delete;

	~CTilePower();

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitPower(this); }

	/** Set direction of a power grid
	* \param direction */
	void SetDirection(int direction) { mDirection = direction; }

	/** Update the direction of a power grid
	*/
	void Update();

	/** Change the direction of a power grid
	*/
	void ChangeDirection();

private:
	/// The Direction of a power grid
	int mDirection = 0;
};
