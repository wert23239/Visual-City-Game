#include "stdafx.h"
#include "TileStadium.h"

using namespace std;
using namespace Gdiplus;

// Time to set to stadium image
double StadiumDuration = 4.5;
// Image to use for stadium
const wstring StadiumImage = L"stadium.png";
/// How much we offset drawing the tile to the left of the center
int OffsetLeft = 64;
/// How much we offset drawing the tile above the center
int OffsetDown = 32;

/**
* \brief Distance from center for inside of tiles.
*/
const int InsideTolerance = 128;

/** Constructor
* \param city The city this is a member of
*/
CTileStadium::CTileStadium(CCity *city) : CTileConstruction(city)
{
}

/**
* \brief Destructor
*/
CTileStadium::~CTileStadium()
{
}

/**
* Called before the image is drawn
* \param elapsed Time since last draw
*/
void CTileStadium::Update(double elapsed)
{
	if (IsBuilding())
	{
		CTileConstruction::Update(elapsed);
		mDuration += elapsed;

		if (mDuration >= StadiumDuration)
			SetImage(StadiumImage);
	}
}

/** \brief Test to see if we hit this object with a mouse.
* \param x X position to test
* \param y Y position to test
* \return true if hit.
*/
bool CTileStadium::HitTest(int x, int y)
{
	// Simple manhattan distance 
	return (abs(x - GetX()) + abs(y - GetY()) * 2) <= InsideTolerance;
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Created XML node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileStadium::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTileConstruction::XmlSave(node);

	itemNode->SetAttribute(L"type", L"stadium");
	itemNode->SetAttribute(L"duration", mDuration);

	return itemNode;
}

/**
* brief Load the attributes for an item node.
*
* This is the  base class version that loads the attributes
* common to all items. Override this to load custom attributes
* for specific items.
*
* \param node The Xml node we are loading the item from
*/
void CTileStadium::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTileConstruction::XmlLoad(node);
	mDuration = node->GetAttributeDoubleValue(L"duration", 0);
}