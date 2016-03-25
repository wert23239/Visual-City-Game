#include "stdafx.h"
#include "TileConstruction.h"

using namespace std;
using namespace Gdiplus;

/// Image for empty construction site
const wstring Clearing0 = L"construction-empty.png";

/// Image for first clearing
const wstring Clearing1 = L"clearing1.png";
/// Production time for first clearing
const double ProductionTime1 = 0.5;

/// Image for second clearing
const wstring Clearing2 = L"clearing2.png";
/// Production time for second clearing
const double ProductionTime2 = 1;

/// Image for third clearing
const wstring Clearing3 = L"clearing3.png";
/// Production time for third clearing
const double ProductionTime3 = 1.5;

/// Image for fourth clearing
const wstring Clearing4 = L"clearing4.png";
/// Production time for fourth clearing
const double ProductionTime4 = 2;

/// Image for fifth clearing
const wstring Clearing5 = L"clearing5.png";
/// Production time for fifth clearing
const double ProductionTime5 = 2.5;

/// Image for sixth clearing
const wstring Clearing6 = L"clearing6.png";
/// Production time for sixth clearing
const double ProductionTime6 = 3;

/// Image for seventh clearing
const wstring Clearing7 = L"clearing7.png";
/// Production time for seventh clearing
const double ProductionTime7 = 3.5;

/// Image for eigth clearing
const wstring Clearing8 = L"clearing8.png";
/// Production time for eigth clearing
const double ProductionTime8 = 4;


/** Constructor
* \param city The city this is a member of
*/
CTileConstruction::CTileConstruction(CCity *city) : CTile(city)
{
	SetImage(Clearing0);
}

/**
* \brief Destructor
*/
CTileConstruction::~CTileConstruction()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileConstruction::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTile::XmlSave(node);
	itemNode->SetAttribute(L"file", GetFile());
	itemNode->SetAttribute(L"building", mBuild);
	return itemNode;
}

/** \brief Save this item to an XML node
* \param node The node we are a child of
*/
void CTileConstruction::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);
	SetImage(node->GetAttributeValue(L"file", L""));
	mBuild = node->GetAttributeIntValue(L"building", false);
	mDuration = node->GetAttributeDoubleValue(L"duration", 0);
}

/**
* Called before the image is drawn
* \param elapsed Time since last draw
*/
void CTileConstruction::Update(double elapsed)
{
	CTile::Update(elapsed);

	mDuration += elapsed;

	if (mDuration >= ProductionTime1)
		SetImage(Clearing1);
	if (mDuration >= ProductionTime2)
		SetImage(Clearing2);
	if (mDuration >= ProductionTime3)
		SetImage(Clearing3);
	if (mDuration >= ProductionTime4)
		SetImage(Clearing4);
	if (mDuration >= ProductionTime5)
		SetImage(Clearing5);
	if (mDuration >= ProductionTime6)
		SetImage(Clearing6);
	if (mDuration >= ProductionTime7)
		SetImage(Clearing7);
	if (mDuration >= ProductionTime8)
		SetImage(Clearing8);
}

/**
* Called to change the properties dialog
*/
void CTileConstruction::PropertiesDlg()
{
	if (mBuild)
	{
		CTile::PropertiesDlg();
	}

}