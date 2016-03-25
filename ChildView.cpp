/**
 * \file ChildView.cpp
 *
 * \author Charles B. Owen
 */

#include "stdafx.h"
#include "DoubleBufferDC.h"
#include "CityApp.h"
#include "ChildView.h"
#include "Tile.h"
#include "TileLandscape.h"
#include "TileBuilding.h"
#include "TileRoad.h"
#include "TileCoalmine.h"
#include "BuildingCounter.h"
#include "CoalCounter.h"
#include "CoalTrumper.h"
#include "RoadChanger.h"
#include "TileCounter.h"
#include "TileStadium.h"
#include "TileOremine.h"
#include "TilePower.h"
#include "DirectionChanger.h"
#include "ConstructionWorker.h"
#include "AnimeSwitch.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>
#include <cmath>
#include <iomanip>
#include <Windows.h>
#include <MMSystem.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;
using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 100;

/// Initial tile X location
const int InitialX = CCity::GridSpacing * 5;

/// Initial tile Y location
const int InitialY = CCity::GridSpacing * 3;

/// Margin of trashcan from side and bottom in pixels
const int TrashcanMargin = 5;

/// Margin of shuffle button
const int ShuffleMargin = 15;

/// The directory containing the file images
const std::string SoundChime = "sounds/navopen.wav";


/// offset x position while moving mouse
int offsetX = 0;
/// offset y position while moving mouse
int offsetY = 0;

/**
 * Constructor
 */
CChildView::CChildView()
{
    srand((unsigned int)time(nullptr));

    // Load the trash can image
    mTrashcan = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/trashcan.png"));
    if (mTrashcan->GetLastStatus() != Ok)
    {
        AfxMessageBox(L"Failed to open images/trashcan.png");
    }

	// Load the navigation image
	mNavigation = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/nav1.png"));
	if (mNavigation->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/nav1.png");
	}

	// Load the shuffle button
	mShuffleButton = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/shuffle.png"));
	if (mNavigation->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/shuffle.png");
	}
}

/**
 * Destructor
 */
CChildView::~CChildView()
{
}

/// \cond
/// This doxygen switch tells it to ignore this block of code
BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_LBUTTONUP()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_TIMER()
    ON_COMMAND(ID_FILE_OPEN, &CChildView::OnFileOpen)
    ON_COMMAND(ID_FILE_SAVEAS, &CChildView::OnFileSaveas)
    ON_COMMAND(ID_BUILDINGS_FARMHOUSE, &CChildView::OnBuildingsFarmhouse)
    ON_COMMAND(ID_LANDSCAPING_GRASS, &CChildView::OnLandscapingGrass)
    ON_COMMAND(ID_LANDSCAPING_SPARTYSTATUE, &CChildView::OnLandscapingSpartystatue)
    ON_COMMAND(ID_BUILDINGS_BLACKSMITHSHOP, &CChildView::OnBuildingsBlacksmithshop)
    ON_COMMAND(ID_LANDSCAPING_TALLGRASS, &CChildView::OnLandscapingTallgrass)
    ON_COMMAND(ID_BUILDINGS_BROWNHOUSE, &CChildView::OnBuildingsBrownhouse)
    ON_COMMAND(ID_BUILDINGS_YELLOWHOUSE, &CChildView::OnBuildingsYellowhouse)
    ON_COMMAND(ID_BUILDINGS_F, &CChildView::OnBuildingsF)
    ON_COMMAND(ID_BUILDINGS_HOSPITAL, &CChildView::OnBuildingsHospital)
    ON_COMMAND(ID_BUILDINGS_MARKET, &CChildView::OnBuildingsMarket)
    ON_COMMAND(ID_BUILDINGS_CONDOS, &CChildView::OnBuildingsCondos)
    ON_COMMAND(ID_LANDSCAPING_TREE, &CChildView::OnLandscapingTree)
    ON_COMMAND(ID_LANDSCAPING_TREES, &CChildView::OnLandscapingTrees)
    ON_COMMAND(ID_LANDSCAPING_BIGTREES, &CChildView::OnLandscapingBigtrees)
    ON_COMMAND(ID_LANDSCAPING_ROAD, &CChildView::OnLandscapingRoad)
    ON_COMMAND(ID_BUSINESSES_COALMINE, &CChildView::OnBusinessesCoalmine)
    ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_ZONING_RESIDENTIAL, &CChildView::OnZoningResidential)
	ON_COMMAND(ID_ZONING_INDUSTRIAL, &CChildView::OnZoningIndustrial)
	ON_COMMAND(ID_ZONING_AGRICULTURAL, &CChildView::OnZoningAgricultural)
	ON_UPDATE_COMMAND_UI(ID_ZONING_RESIDENTIAL, &CChildView::OnUpdateZoningResidential)
	ON_UPDATE_COMMAND_UI(ID_ZONING_INDUSTRIAL, &CChildView::OnUpdateZoningIndustrial)
	ON_UPDATE_COMMAND_UI(ID_ZONING_AGRICULTURAL, &CChildView::OnUpdateZoningAgricultural)
	ON_COMMAND(ID_ZONING_NONE, &CChildView::OnZoningNone)
	ON_UPDATE_COMMAND_UI(ID_ZONING_NONE, &CChildView::OnUpdateZoningNone)
	ON_COMMAND(ID_BUILDINGS_COUNT, &CChildView::OnBuildingsCount)
	ON_COMMAND(ID_BUSINESSES_HAULCOAL, &CChildView::OnBusinessesHaulcoal)
	ON_COMMAND(ID_BUSINESSES_TRUMP, &CChildView::OnBusinessesTrump)
	ON_UPDATE_COMMAND_UI(ID_BUSINESSES_TRUMP, &CChildView::OnUpdateBusinessesTrump)
	ON_COMMAND(ID_VIEW_CITYSPECS, &CChildView::OnViewCityspecs)
	ON_COMMAND(ID_BUSINESSES_CONSTRUCTION, &CChildView::OnBusinessesConstruction)
	ON_COMMAND(ID_POWER_POWERPLANT, &CChildView::OnPowerPowerplant)
	ON_COMMAND(ID_POWER_SUBSTATION, &CChildView::OnPowerSubstation)
	ON_COMMAND(ID_POWER_SOLARPOWERSTATION, &CChildView::OnPowerSolarpowerstation)
	ON_COMMAND(ID_POWER_POWERGRID, &CChildView::OnPowerPowergrid)
	ON_COMMAND(ID_POWER_CHANGEDIRECTION, &CChildView::OnPowerChangedirection)
	ON_UPDATE_COMMAND_UI(ID_POWER_CHANGEDIRECTION, &CChildView::OnUpdatePowerChangedirection)
	ON_COMMAND(ID_CURVEDROADS_ROADUL, &CChildView::OnCurvedroadsRoadul)
	ON_COMMAND(ID_CURVEDROADS_ROADUR, &CChildView::OnCurvedroadsRoadur)
	ON_COMMAND(ID_CURVEDROADS_ROADLL, &CChildView::OnCurvedroadsRoadll)
	ON_COMMAND(ID_CURVEDROADS_ROADLR, &CChildView::OnCurvedroadsRoadlr)
	ON_COMMAND(ID_LONGROADS_ROADUD, &CChildView::OnLongroadsRoadud)
	ON_COMMAND(ID_LONGROADS_ROADLR, &CChildView::OnLongroadsRoadlr)
	ON_COMMAND(ID_INTERSECTIONS_FULL, &CChildView::OnIntersectionsFull)
	ON_COMMAND(ID_INTERSECTIONS_NORIGHT, &CChildView::OnIntersectionsNoright)
	ON_COMMAND(ID_INTERSECTIONS_NODOWN, &CChildView::OnIntersectionsNodown)
	ON_COMMAND(ID_INTERSECTIONS_NOUP, &CChildView::OnIntersectionsNoup)
	ON_COMMAND(ID_INTERSECTIONS_NOLEFT, &CChildView::OnIntersectionsNoleft)
	ON_COMMAND(ID_OTHERROADS_ROTATE, &CChildView::OnOtherroadsRotate)
	ON_UPDATE_COMMAND_UI(ID_OTHERROADS_ROTATE, &CChildView::OnUpdateOtherroadsRotate)
END_MESSAGE_MAP()
/// \endcond



/** 
* This function is called before the window is created.
* \param cs A structure with the window creation parameters
* \returns TRUE
*/
BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

/** 
* This function is called to draw in the window.
*
* This function is called in response to a drawing message
* whenever we need to redraw the window on the screen.
* It is responsible for painting the window.
*/
void CChildView::OnPaint()
{
    CPaintDC paintDC(this);     // device context for painting
    CDoubleBufferDC dc(&paintDC); // device context for painting

    Graphics graphics(dc.m_hDC);
    graphics.Clear(Color(0, 0, 0));

    if (mFirstDraw)
    {
        mFirstDraw = false;
        SetTimer(1, FrameDuration, nullptr);

        /*
        * Initialize the elapsed time system
        */
        LARGE_INTEGER time, freq;
        QueryPerformanceCounter(&time);
        QueryPerformanceFrequency(&freq);

        mLastTime = time.QuadPart;
        mTimeFreq = double(freq.QuadPart);
    }

    /*
    * Compute the elapsed time since the last draw
    */
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    long long diff = time.QuadPart - mLastTime;
    double elapsed = double(diff) / mTimeFreq;
    mLastTime = time.QuadPart;
	
	if (mShuffleTime) mGameTimer += elapsed;

    mCity.Update(elapsed);

    // Get the size of the window
    CRect rect;
    GetClientRect(&rect);

	/*
	* Actually Draw the city
	*/
	graphics.SetPageUnit(UnitPixel);
	graphics.SetPageScale(mScale);		// of type double    
	mCity.OnDraw(&graphics, mOffsetX, mOffsetY);
	graphics.SetPageScale(1);

    /*
     * Draw the trash can
     */
    
    // Bottom minus image size minus margin is top of the image
    mTrashcanTop = rect.Height() - mTrashcan->GetHeight() - TrashcanMargin;
    mTrashcanRight = TrashcanMargin + mTrashcan->GetWidth();

	graphics.DrawImage(mTrashcan.get(), TrashcanMargin, mTrashcanTop,
		mTrashcan->GetWidth(), mTrashcan->GetHeight());

	
	/*
	* Draw the navigation bar
	*/
	if (mNavigationFlag)
	{
		mNavigation = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/nav2.png"));
	}
	else 
	{
		mNavigation = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/nav1.png"));
	}
	graphics.DrawImage(mNavigation.get(), 
		rect.Width() - TrashcanMargin - mNavigation->GetWidth(), // x pos
		TrashcanMargin, // y pos
		mNavigation->GetWidth(), mNavigation->GetHeight());

	/*
	* Draw the shuffle button
	*/
	graphics.DrawImage(mShuffleButton.get(),
		TrashcanMargin, // x pos
		ShuffleMargin, // y pos
		mShuffleButton->GetWidth(), mShuffleButton->GetHeight());
	
	/*
	* Draw the clock
	*/
	FontFamily fontFamily(L"Arial");
	Gdiplus::Font font(&fontFamily, 16);
	SolidBrush white(Color(255, 255, 255));
	wstring clock = Clock();
	graphics.DrawString(clock.c_str(),  // String to draw
		-1,         // String length, -1 means it figures it out on its own
		&font,      // The font to use
		PointF(TrashcanMargin, TrashcanMargin + mShuffleButton->GetHeight()),   // Where to draw (top left corner)
		&white);    // The brush to draw the text with

	//for (auto tile : mCity.GetZoning(mTileZone))
	//{
	//	tile->DrawBorder(&graphics, &pen, mOffsetX, mOffsetY);
	//}
	if (mDraw == true)
	{
		for (auto tile : mCity)
		{
			Gdiplus::Pen pen(Gdiplus::Color::Red, 2);
			int mChoice = rand() % 7;
			if (mChoice == 7)
				pen.SetColor(Color::Red);
		    else if(mChoice == 1)
				pen.SetColor(Color::Blue);
			else if (mChoice == 2)
				pen.SetColor(Color::Yellow);
			else if (mChoice == 3)
				pen.SetColor(Color::Orange);
			else if (mChoice == 4)
				pen.SetColor(Color::Green);
			else if (mChoice == 5)
				pen.SetColor(Color::Purple);
			else if (mChoice == 6)
				pen.SetColor(Color::Violet);

			tile->DrawBorder(&graphics, &pen, mOffsetX, mOffsetY);
		}
		mDraw = true;
	}

}


/**
* \brief Erase the background prior to drawing.
*
* We return true so this does nothing. This prevents the flicker
* of a repaint of white before actual drawing.
*
* \param pDC A device context to draw on
* \returns TRUE
*/
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
    // This disabled the default background erase
    return TRUE;
}

/** \brief Handle a left button double-click on a tile
* \param nFlags Mouse flags
* \param point Where we clicked
*/
void CChildView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    auto tile = mCity.HitTest(point.x / mScale - mOffsetX, point.y / mScale - mOffsetY);
    if (tile != nullptr) 
		if (!mShuffleTime)
		{
			{
				// We double-clicked on a tile

				// Bring up the tile editing dialog box
				if (!mTrumpFlag && !mRotateFlag && !mDirectionFlag)
				{
					tile->PropertiesDlg();
				}

				// Build construction site
				CConstructionWorker worker;
				tile->Accept(&worker);

				Invalidate();
			}
		}
}



/** \brief Called when there is a left mouse button press
* \param nFlags Flags associated with the mouse button press
* \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (mNavigationFlag)
	{
		// Set click point for scrolling 
		mClickX = point.x;
		mClickY = point.y;
	}
	// Get the size of the window
	CRect rect;
	GetClientRect(&rect);

	// Click tile
	mGrabbedItem = mCity.HitTest((point.x) / mScale - mOffsetX, (point.y) / mScale - mOffsetY);
	if (mGrabbedItem != nullptr && !mNavigationFlag)
	{
		if (mShuffleTime){
			if (mGrabbedItem->GetMatchFlage() == true){
				mGrabbedItem = nullptr;
			}
			else
			{
				// We grabbed something
				// Move it to the front
				mCity.MoveToFront(mGrabbedItem);
				Invalidate();
			}
		}
		else{
			if (!mTrumpFlag && !mDirectionFlag && !mRotateFlag)
			{
				// We grabbed something
				// Move it to the front
				mCity.MoveToFront(mGrabbedItem);
				Invalidate();
			}
			else if (mDirectionFlag)
			{
				CDirectionChanger visitor;
				mGrabbedItem->Accept(&visitor);
				mGrabbedItem = false;
			}
			else if (mRotateFlag)
			{
				// Instantiate the visitor
				CRoadChanger roadC;

				// Send to JUST this one time
				mGrabbedItem->Accept(&roadC);

				// Clear this since we don't want to then drag
				mGrabbedItem = false;
			}
			else if (mTrumpFlag)
			{
				// Instantiate the visitor
				CCoalTrumper trumper;

				// Send to JUST this one time
				mGrabbedItem->Accept(&trumper);

				// Clear this since we don't want to then drag
				mGrabbedItem = false;
			}
		}
	}

	if (!mShuffleTime)
	{
		// Click shuffle
		if (point.x < TrashcanMargin + mShuffleButton->GetWidth() &&
			point.x > TrashcanMargin &&
			point.y > TrashcanMargin &&
			point.y < TrashcanMargin + mShuffleButton->GetHeight())
		{
			Shuffle();
		}
	}
	// Click scrolling navigation
	if (point.x < rect.Width() - TrashcanMargin &&
		point.x > rect.Width() - TrashcanMargin - mNavigation->GetWidth() / 2 &&
		point.y > TrashcanMargin &&
		point.y < TrashcanMargin + mNavigation->GetHeight())
	{
		mNavigationFlag = !mNavigationFlag;
	}

	// Click zoom in
	if (point.x < rect.Width() - TrashcanMargin - mNavigation->GetWidth() / 2 &&
		point.x > rect.Width() - TrashcanMargin - mNavigation->GetWidth() &&
		point.y > TrashcanMargin &&
		point.y < TrashcanMargin + mNavigation->GetHeight() / 2)
	{
		if (mScale < 4)
		{
			mScale *= 2;
		}
	}
	// Click zoom out
	if (point.x < rect.Width() - TrashcanMargin - mNavigation->GetWidth() / 2 &&
		point.x > rect.Width() - TrashcanMargin - mNavigation->GetWidth() &&
		point.y > TrashcanMargin + mNavigation->GetHeight() / 2 &&
		point.y < TrashcanMargin + mNavigation->GetHeight())
	{
		if (mScale > .25)
		{
			mScale /= 2;
		}
	}
}

/** \brief Called when the left mouse button is released
* \param nFlags Flags associated with the mouse button release
* \param point Where the button was pressed
*/
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{

	OnMouseMove(nFlags, point);
	mGrabbedItem = mCity.HitTest((point.x) / mScale - mOffsetX, (point.y) / mScale - mOffsetY);
	if (mGrabbedItem != nullptr && !mNavigationFlag)
	{
		bool match;
		match = mCity.MatchTest(mGrabbedItem);
		if (match){
			//play sound
			PlaySound(TEXT("sounds/navopen.wav"), NULL, SND_ASYNC);
			mGrabbedItem->SetMatchFlage(true);
		}
	}
	
	// Check for game completion
	if (mShuffleTime)
	{
		if (mCity.IsComplete()) EndGame();
	}
}



/** \brief Called when the mouse is moved
* \param nFlags Flags associated with the mouse movement
* \param point Where the button was pressed
*/
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{

    // See if an item is currently being moved by the mouse
	if ((mGrabbedItem != nullptr && !mNavigationFlag) && !mGrabbedItem->GetMatchFlage())
    {

        // If an item is being moved, we only continue to 
        // move it while the left button is down.
        if (nFlags & MK_LBUTTON)
        {
			mGrabbedItem->SetLocation((point.x) / mScale - mOffsetX, (point.y) / mScale - mOffsetY);
        }
        else
        {
            // When the left button is released we release
            // the item. If we release it on the trashcan,
            // delete it.
            if (point.x < mTrashcanRight && point.y > mTrashcanTop)
            {
                // We have clicked on the trash can
                mCity.DeleteItem(mGrabbedItem);
            }
            else
            {
                mGrabbedItem->QuantizeLocation();
            }
            mCity.SortTiles();
            mGrabbedItem = nullptr;
        }
		// Force the screen to redraw
		Invalidate();
    }

	// if mouse is clicked and navigation is on
	if ((mNavigationFlag && nFlags & MK_LBUTTON) && !mGrabbedItem->GetMatchFlage())
	{
		// change x offset
		offsetX = point.x - mClickX;
		mOffsetX += offsetX;
		mClickX = point.x;

		// change y offset
		offsetY = point.y - mClickY;
		mOffsetY += offsetY;
		mClickY = point.y;
	}

}

/**
* \brief Handle timer events
* \param nIDEvent The timer event ID
*/
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
    Invalidate();
    CWnd::OnTimer(nIDEvent);
}



/**
* \brief Handler for the File/Save As menu option
*/
void CChildView::OnFileSaveas()
{
    CFileDialog dlg(false,  // false = Save dialog box
        L".city",           // Default file extension
        nullptr,            // Default file name (none)
        OFN_OVERWRITEPROMPT,    // Flags
        L"City Files (*.city)|*.city|All Files (*.*)|*.*||");    // Filter
    if (dlg.DoModal() != IDOK)
        return;

    wstring filename = dlg.GetPathName();

    mCity.Save(filename);
}


/** \brief This function is called when an File Open menu item is selected.
*
* It loads the city from a file.
*/
void CChildView::OnFileOpen()
{
    CFileDialog dlg(true,  // true = Open dialog box
        L".city",           // Default file extension
        nullptr,            // Default file name (none)
        0,    // Flags
        L"City Files (*.city)|*.city|All Files (*.*)|*.*||");    // Filter
    if (dlg.DoModal() != IDOK)
        return;

    wstring filename = dlg.GetPathName();
    mCity.Load(filename);
	mDraw = false;
	mGameTimer = false;
	mShuffleTime = false;
    Invalidate();
}



/**
 * \brief Add a CTileBuilding tile to the drawing.
 * \param file The file for the building image
 */
void CChildView::AddBuilding(const std::wstring &file)
{
    auto tile = make_shared<CTileBuilding>(&mCity);
    tile->SetImage(file);
    tile->SetLocation(InitialX, InitialY);
    mCity.Add(tile);
    Invalidate();
}


/**
* \brief Add a CTileLandscaping tile to the drawing.
* \param file The file for the landscape image
*/
void CChildView::AddLandscape(const std::wstring &file)
{
    auto tile = make_shared<CTileLandscape>(&mCity);
    tile->SetImage(file);
    tile->SetLocation(InitialX, InitialY);
    mCity.Add(tile);
    Invalidate();
}


/**
* \brief Add a CTilePower tile to the drawing.
* \param file The file for the power image
*/
void CChildView::AddPower(const std::wstring &file)
{
	auto tile = make_shared<CTilePower>(&mCity);
	tile->SetImage(file);
	tile->SetLocation(InitialX, InitialY);
	mCity.Add(tile);
	Invalidate();
}


/**
* \brief Add a CTileRoad tile to the drawing.
* \param file The file for the power image
* \param Orient The Orientation of the road
*/
void CChildView::AddRoad(const std::wstring &file,int Orient)
{
	auto tile = make_shared<CTileRoad>(&mCity);
	tile->SetImage(file);
	tile->SetLocation(InitialX, InitialY);
	tile->SetOrientation(Orient);
	mCity.Add(tile);
	Invalidate();
}

/**
* \brief Counte overlaping tiles
*/
void CChildView::TileCounter()
{
	mTileCnt = 0;
	mOverCnt = 0;
	mPartCnt = 0;
	const double tileDist = 3 * 32;
	for (auto tile : mCity)
	{
		bool overlaping = false;
		mTileCnt++;
		for (auto compTile : mCity)
		{
			if (tile != compTile)
			{
				double tX = tile->GetX();
				double tY = tile->GetY();
				double cptX = compTile->GetX();
				double cptY = compTile->GetY();
				if ((tX == cptX) && (tY == cptY))
				{
					mOverCnt++;
					break;
				}
				double dx = tX - cptX;
				double dy = tY - cptY;
				dx = abs(dx);
				dy = abs(dy);
				double len = (dy * 2 + dx);
				if ((0 < len) && (len <= tileDist)){
					overlaping = true;
				}
			}
		}
		if (!overlaping)
		{
			mPartCnt++;
		}
	}
	mPartCnt = mTileCnt - mPartCnt;
}


/**
 * \cond
 *
 * I'm not going to document these menu handlers, since what they 
 * so is obvious. I'm using a Doxygen feature to ignore the functions
 */

/** \brief Menu handler that creates a power plant*/
void CChildView::OnPowerPowerplant()
{
	AddPower(L"powercoal0.png");
}

/** \brief Menu handler that creates power lines*/
void CChildView::OnPowerSubstation()
{
	AddPower(L"substation.png");
}

/** \brief Menu handler that creates power stations */
void CChildView::OnPowerSolarpowerstation()
{
	AddPower(L"powerssolar.png");
}

/** \brief Menu handler that creates power grids */
void CChildView::OnPowerPowergrid()
{
	auto tile = make_shared<CTilePower>(&mCity);
	tile->SetImage(L"powerlhd.png");
	tile->SetLocation(InitialX, InitialY);
	tile->SetDirection(1);
	mCity.Add(tile);
	Invalidate();
}


void CChildView::OnBuildingsFarmhouse()
{
    AddBuilding(L"farm0.png");
}


void CChildView::OnLandscapingGrass()
{
    AddLandscape(L"grass.png");
}


void CChildView::OnLandscapingSpartystatue()
{
    AddLandscape(L"sparty.png");
}


void CChildView::OnBuildingsBlacksmithshop()
{
    AddBuilding(L"blacksmith.png");
}

void CChildView::OnLandscapingTallgrass()
{
    AddLandscape(L"tallgrass.png");
}

/** Menu handler that creates a brownhouse */
void CChildView::OnBuildingsBrownhouse()
{
    AddBuilding(L"house.png");
}

/** Menu handler that creates a yellowhouse */
void CChildView::OnBuildingsYellowhouse()
{
    AddBuilding(L"yellowhouse.png");
}

/** Menu handler that creates a firestation */
void CChildView::OnBuildingsF()
{
    AddBuilding(L"firestation.png");
}

/** Menu handler that creates a hospital */
void CChildView::OnBuildingsHospital()
{
    AddBuilding(L"hospital.png");
}

/** Menu handler that creates a market */
void CChildView::OnBuildingsMarket()
{
    AddBuilding(L"market.png");
}

/** Menu handler that creates condos */
void CChildView::OnBuildingsCondos()
{
    AddBuilding(L"condos.png");
}

/** Menu handler that creates a tree */
void CChildView::OnLandscapingTree()
{
    AddLandscape(L"tree.png");
}

/** Menu handler that creates trees */
void CChildView::OnLandscapingTrees()
{
    AddLandscape(L"tree2.png");
}

/** \brief Menu handler that creates big trees */
void CChildView::OnLandscapingBigtrees()
{
    AddLandscape(L"tree3.png");
}

/** \brief Menu handler that creates a road */
void CChildView::OnLandscapingRoad()
{
    auto tile = make_shared<CTileRoad>(&mCity);
    tile->SetLocation(InitialX, InitialY);
    mCity.Add(tile);
    Invalidate();
}

/** \brief Menu handler that creates a coalmine */
void CChildView::OnBusinessesCoalmine()
{
    auto tile = make_shared<CTileCoalmine>(&mCity);
    tile->SetLocation(InitialX, InitialY);
    mCity.Add(tile);
    Invalidate();
}
/** \endcond */
/** \brief Menu handler that sets zoning to residential */
void CChildView::OnZoningResidential()
{
	mZoning = Residential;
	mTileZone = CTile::Zonings::RESIDENTIAL;
}

/** \brief Handler for updating Zoning>Residential menu option prior to display */
void CChildView::OnUpdateZoningResidential(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == Residential);
}

/** \brief Menu handler that sets zoning to industrial */
void CChildView::OnZoningIndustrial()
{
	mZoning = Industrial;
	mTileZone = CTile::Zonings::INDUSTRIAL;
}

/** \brief Handler for updating Zoning>Industrial menu option prior to display */
void CChildView::OnUpdateZoningIndustrial(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == Industrial);

}

/** \brief Menu handler that sets zoning to agricultural */
void CChildView::OnZoningAgricultural()
{
	mZoning = Agricultural;
	mTileZone = CTile::Zonings::AGRICULTURAL;
}

/** \brief Handler for updating Zoning>Agricultural menu option prior to display */
void CChildView::OnUpdateZoningAgricultural(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == Agricultural);
}

/** \brief Menu handler that sets zoning to none */
void CChildView::OnZoningNone()
{
	mZoning = None;
	mTileZone = CTile::Zonings::NONE;
}

/** \brief Handler for updating Zoning>None menu option prior to display */
void CChildView::OnUpdateZoningNone(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mZoning == None);
}


/** \brief Menu handler that counts the number of builds */
void CChildView::OnBuildingsCount()
{
	CBuildingCounter visitor;
	mCity.Accept(&visitor);
	int cnt = visitor.GetNumBuildings();

	wstringstream str;
	str << L"There are " << cnt << L" buildings.";
	AfxMessageBox(str.str().c_str());
}

/** \brief Menu handler that hauls coal */
void CChildView::OnBusinessesHaulcoal()
{
	if (!mShuffleTime){
		CCoalCounter visitor;
		mCity.Accept(&visitor);
		wstringstream str;
		str << L"The total production is " << visitor.GetCoalTons() << L" tons";
		AfxMessageBox(str.str().c_str());
	}
}

/** \brief Menu handler that sets trump mode */
void CChildView::OnBusinessesTrump()
{
	mTrumpFlag = !mTrumpFlag;
}

/** \brief Menu handler that sets trump check mark*/
void CChildView::OnUpdateBusinessesTrump(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mTrumpFlag);
}

/** \brief Menu handler that returns ViewCityspecs*/
void CChildView::OnViewCityspecs()
{
	TileCounter();

	wstringstream str;
	str << L"There are " << mTileCnt << L" tiles. \n"
		<< L"There are " << mPartCnt << L" partially overlapped tiles. \n"
		<< L"There are " << mOverCnt << L" fully overlapped tiles. \n";
	AfxMessageBox(str.str().c_str());
}


/** \brief Menu handler that creates a construction zone */
void CChildView::OnBusinessesConstruction()
{
	// initialize random seed
	srand(time(NULL));
	// generate random number between 0 and 1
	int randomNum = rand() % 2;

	// create a stadium or oremine
	if (randomNum)
	{
		auto tile = make_shared<CTileOremine>(&mCity);
		tile->SetLocation(InitialX, InitialY);
		mCity.Add(tile);
	}
	else
	{
		auto tile = make_shared <CTileStadium>(&mCity);
		tile->SetLocation(InitialX, InitialY);
		mCity.Add(tile);
	}
	Invalidate();
}


/** \brief Menu handler that sets direction mode*/
void CChildView::OnPowerChangedirection()
{
	mDirectionFlag = !mDirectionFlag;
}


/** \brief Menu handler that sets direction check mark*/
void CChildView::OnUpdatePowerChangedirection(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mDirectionFlag);
}

/** Menu handler that creates upper left roads */
void CChildView::OnCurvedroadsRoadul()
{
	AddRoad(L"roadlu.png",3);

}

/** Menu handler that creates upper right roads */
void CChildView::OnCurvedroadsRoadur()
{
	AddRoad(L"roadur.png",4);
}



/** Menu handler that creates lower left roads */
void CChildView::OnCurvedroadsRoadll()
{
	AddRoad(L"roadld.png",2);
}



/** Menu handler that creates lower right roads roads */
void CChildView::OnCurvedroadsRoadlr()
{
	AddRoad(L"roaddr.png",1);
}


/** Menu handler that creates up and down roads */
void CChildView::OnLongroadsRoadud()
{
	AddRoad(L"roadud.png",6);
}



/** Menu handler that creates left and right roads */
void CChildView::OnLongroadsRoadlr()
{
	AddRoad(L"roadlr.png",5);
}


/** Menu handler that creates full roads */
void CChildView::OnIntersectionsFull()
{
	AddRoad(L"roadludr.png",0);
}

/** Menu handler that creates no right roads */
void CChildView::OnIntersectionsNoright()
{
	AddRoad(L"roadlud.png",9);
}


/** Menu handler that creates no down roads */
void CChildView::OnIntersectionsNodown()
{
	AddRoad(L"roadlur.png",10);
}

/** Menu handler that creates no up roads */
void CChildView::OnIntersectionsNoup()
{
	AddRoad(L"roadldr.png",8);
}



/** Menu handler that creates no left roads */
void CChildView::OnIntersectionsNoleft()
{
	AddRoad(L"roadudr.png",7);
}

/** Menu handler that adjust for rotations */
void CChildView::OnOtherroadsRotate()
{
	mRotateFlag = !mRotateFlag;
}

/** \brief Menu handler that sets trump check mark*/
void CChildView::OnUpdateOtherroadsRotate(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(mRotateFlag);
}


void CChildView::Shuffle()
{
	mDraw = true;
	wstringstream str;
	str << L"SHUFFLE TIME!";
	AfxMessageBox(str.str().c_str());
	mShuffleTime = true;
	for (auto tile : mCity)
	{
		CAnimeSwitch sw;
		tile->Accept(&sw);
		int x = tile->GetX();
		int y = tile->GetY();
		std::wstring file = tile->GetFile();
		auto blankTile = make_shared<CBlankTile>(x, y, file);
		mCity.AddBlank(blankTile);
		tile->SetLocation(rand() % 500 , rand() % 500 );
	}
	/*mScale = 1;
	mOffsetX = 0;
	mOffsetY = 0;*/
	mNavigationFlag = false;
	Invalidate();
}


void CChildView::EndGame()
{
	mShuffleTime = false;
	for (auto tile : mCity)
	{
		CAnimeSwitch sw;
		tile->Accept(&sw);
	}
	wstringstream str;
	str << L"Great job! Score: " << mGameTimer;
	AfxMessageBox(str.str().c_str());
	mGameTimer = 0;
}

wstring CChildView::Clock()
{
	double CurrentTime = mGameTimer;
	int hour = mGameTimer / 3600;
	CurrentTime = fmod(CurrentTime,3600);
	int min = CurrentTime / 60;
	CurrentTime = fmod(CurrentTime, 60);
	int sec = CurrentTime / 1;

	wstringstream str;
	str << setw(2) << setfill(L'0') << hour << ":";
	str << setw(2) << setfill(L'0') << min << ":";
	str << setw(2) << setfill(L'0') << sec << endl;
	wstring clock = str.str();
    return clock;
}