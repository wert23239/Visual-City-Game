#include "stdafx.h"
#include "TileRoad.h"
#include <vector>
using namespace std;
using namespace Gdiplus;

const vector<wstring> RoadOrientation = { L"roadludr.png",L"roaddr.png", L"roadld.png", L"roadlu.png",
L"roadur.png", L"roadlr.png", L"roadud.png", L"roadudr.png", L"roadldr.png", L"roadlud.png", L"roadlur.png" };
/** Constructor
* \param city The city this is a member of
*/
CTileRoad::CTileRoad(CCity *city) : CTile(city)
{
    SetAdjacencies(false, false, false, false);
}

/**
* \brief Destructor
*/
CTileRoad::~CTileRoad()
{
}

/** \brief Save this item to an XML node
 * \param node The node we are going to be a child of
 * \returns Pointer to the crated node
 */
std::shared_ptr<xmlnode::CXmlNode> CTileRoad::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
    auto itemNode = CTile::XmlSave(node);

    itemNode->SetAttribute(L"type", L"road");
	itemNode->SetAttribute(L"file", GetFile());
	itemNode->SetAttribute(L"direction", mOrientation);
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
void CTileRoad::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);
	SetImage(node->GetAttributeValue(L"file", L""));
	mOrientation = node->GetAttributeIntValue(L"direction", 0);
}
/**
 * \brief Indicate the road tiles adjacent to this one
 *
 * The road time image chosen is dependent on the tiles around
 * it. This is where the adjacency of road tiles is indicated.
 * 
 * \param ul True if road tile to upper left
 * \param ur True if road tile to upper right
 * \param ll True if road tile to lower left
 * \param lr True if road tile to lower right
 */
void CTileRoad::SetAdjacencies(bool ul, bool ur, bool ll, bool lr)
{
    // Create the adjacency code
    int code = (ul ? 1 : 0) | (ur ? 2 : 0) | (ll ? 4 : 0) | (lr ? 8 : 0);
    if (mCurrentAdj == code)
    {
        // We are already set. Do nothing
        return;
    }

    static wstring files[] = {
        L"roadlr.png",      // 0
        L"roadlr.png",      // 1
        L"roadud.png",      // 2
        L"roadlu.png",      // 3
        L"roadud.png",      // 4
        L"roadld.png",      // 5
        L"roadud.png",      // 6
        L"roadlud.png",     // 7
        L"roadlr.png",      // 8
        L"roadlr.png",      // 9
        L"roadur.png",      // 10
        L"roadlur.png",     // 11
        L"roaddr.png",      // 12
        L"roadldr.png",     // 13
        L"roadudr.png",     // 14
        L"roadludr.png"    // 15
    };

    // Select the appropriate image
    mCurrentAdj = code;
    SetImage(files[code]);
}

/**  Rotates tiles the apporiate amount of degrees. also stops properites */
void CTileRoad::Rotate()
{
	//if (mOrientation != 0)
	mOrientation++;
	if (mOrientation == 5)
		mOrientation = 1;
	else if (mOrientation==7)
		mOrientation=5;
	else if (mOrientation == 11)
		mOrientation = 7;
	
	if (mOrientation != 0)
	{
		SetImage(RoadOrientation[mOrientation]);
	}
}