/**
* \file TilePower.cpp
*
* \author Chiyu Song
*/

#include "stdafx.h"
#include "TilePower.h"
#include <vector>

using namespace std;
using namespace Gdiplus;

/// Image when the coalmine production is empty
const vector<wstring> Directions = { L"powerlhd.png", L"powerlvd.png", L"powerllud.png",
L"powerlludrd.png", L"powerllurd.png", L"powerlrdd.png", L"powerlrud.png", L"powerlldd.png" };

/** Constructor
* \param city The city this is a member of
*/
CTilePower::CTilePower(CCity *city) : CTile(city)
{
}

/**
* \brief Destructor
*/
CTilePower::~CTilePower()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTilePower::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTile::XmlSave(node);

	itemNode->SetAttribute(L"type", L"power");
	itemNode->SetAttribute(L"file", GetFile());
	itemNode->SetAttribute(L"direction", mDirection);

	return itemNode;
}


/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTilePower::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);
	SetImage(node->GetAttributeValue(L"file", L""));
	mDirection = node->GetAttributeIntValue(L"direction", 0);
}

/**
* Called before the image is drawn
*/
void CTilePower::Update()
{
	if (mDirection != 0)
	{
		SetImage(Directions[mDirection - 1]);
	}
}


/**
* Change the direction of a power grid
*/
void CTilePower::ChangeDirection()
{
	if (mDirection >= Directions.size())
	{
		mDirection = 1;
	}
	else if (mDirection != 0)
	{
		mDirection++;
	}
	Update();
}
