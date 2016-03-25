#include "stdafx.h"
#include "TileOremine.h"
#include <vector>
using namespace std;
using namespace Gdiplus;

/// Time that the oremine is built
const double OremineDuration = 4.5;

/// Image for first Oremine
const wstring Oremine1 = L"oremine1.png";
/// Production time for first Oremine
const double ProductionTime1 = 0.5;

/// Image for second Oremine
const wstring Oremine2 = L"oremine2.png";
/// Production time for second Oremine
const double ProductionTime2 = 1;

/// Image for third Oremine
const wstring Oremine3 = L"oremine3.png";
/// Production time for third Oremine
const double ProductionTime3 = 1.5;

/// Image for fourth Oremine
const wstring Oremine4 = L"oremine4.png";
/// Production time for fourth Oremine
const double ProductionTime4 = 2;

/// Image for fifth Oremine
const wstring Oremine5 = L"oremine5.png";
/// Production time for fifth Oremine
const double ProductionTime5 = 2.5;

/// Image for sixth Oremine
const wstring Oremine6 = L"oremine6.png";
/// Production time for sixth Oremine
const double ProductionTime6 = 3;

/// Image for seventh Oremine
const wstring Oremine7 = L"oremine7.png";
/// Production time for seventh Oremine
const double ProductionTime7 = 3.5;

/// Image for eigth Oremine
const wstring Oremine8 = L"oremine8.png";
/// Production time for eigth Oremine
const double ProductionTime8 = 4;

/// Vector of images
vector<wstring> fileVector = { Oremine1,
Oremine2,
Oremine3,
Oremine4,
Oremine5,
Oremine6,
Oremine7,
Oremine8 };

/** Constructor
* \param city The city this is a member of
*/
CTileOremine::CTileOremine(CCity *city) : CTileConstruction(city)
{
}

/**
* \brief Destructor
*/
CTileOremine::~CTileOremine()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileOremine::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTileConstruction::XmlSave(node);

	itemNode->SetAttribute(L"type", L"oremine");
	itemNode->SetAttribute(L"imageIndex", mImageIndex);
	itemNode->SetAttribute(L"duration", mDuration);
	itemNode->SetAttribute(L"built", mIsBuilt);
	itemNode->SetAttribute(L"reverse", mReverseImage);
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
void CTileOremine::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTileConstruction::XmlLoad(node);
	mImageIndex = node->GetAttributeIntValue(L"imageIndex", 0);
	mDuration = node->GetAttributeDoubleValue(L"duration", 0);
	mIsBuilt = node->GetAttributeIntValue(L"built", 0);
	mReverseImage = node->GetAttributeIntValue(L"reverse", 0);

}
/**
* Called before the image is drawn
* \param elapsed Time since last draw
*/
void CTileOremine::Update(double elapsed)
{
	if (IsBuilding() && mUpdate)
	{
		mDuration += elapsed;
		if (mDuration >= OremineDuration)
		{
			mIsBuilt = true;
		}
		if (mIsBuilt == true)
			Mine();
		else CTileConstruction::Update(elapsed);
	}
}

/** 
* Used to control the Mines
*/
void CTileOremine::Mine()
{	
	if (mDuration >= 0.1)
	{
		SetImage(fileVector[mImageIndex]);

		if (!mReverseImage)
			mImageIndex++;
		else mImageIndex--;

		if (mImageIndex == 7 || mImageIndex == 0)
			mReverseImage = !mReverseImage;

		mDuration = 0;
	}
}

