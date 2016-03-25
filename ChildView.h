/**
* \file ChildView.h
*
* \author Charles B. Owen
*
* \brief Class that implements the child window our program draws in.
*
* The window is a child of the main frame, which holds this
* window, the menu bar, and the status bar.
*/

#pragma once

#include "City.h"
#include <string>

class CTile;

/** \brief The child window our program draws in. */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
    void AddBuilding(const std::wstring &file);
    void AddLandscape(const std::wstring &file);
	void AddPower(const std::wstring &file);
	void AddRoad(const std::wstring &file,int Orient);
	void TileCounter();

    /// The city
    CCity   mCity;

	/// The zoom scale of the city
	double mScale = 1;

    /// True until the first time we draw
    bool mFirstDraw = true;

    long long mLastTime;    ///< Last time we read the timer
    double mTimeFreq;       ///< Rate the timer updates

    /// Any item we are currently dragging
    std::shared_ptr<CTile> mGrabbedItem;

    std::unique_ptr<Gdiplus::Bitmap> mTrashcan; ///< Trashcan image to use
    int mTrashcanTop = 0;           ///< Top line of the trashcan in pixels
    int mTrashcanRight = 0;         ///< Right side of the trashcan in pixels

	std::unique_ptr<Gdiplus::Bitmap> mNavigation; ///< Navigation image to use
	int mNavTop = 0;           ///< Top line of the navigation hand in pixels
	int mNavBottom = 0;         ///< Right side of the navigation hand in pixels

	std::unique_ptr<Gdiplus::Bitmap> mShuffleButton; ///< Shuffle image to use
	/// Possible zoning options for check mark
	enum Zoning { None, Residential, Industrial, Agricultural };
	
	/// Current zoning option
	Zoning mZoning = None;
	
	/// Current Color option
	bool mDraw = false;

	/// Zoning of the tile
	CTile::Zonings mTileZone = CTile::Zonings::NONE;

	/// Flag that sets if trump is enabled;
	bool mTrumpFlag = false;

	/// Flag that sets if navigation is enabled;
	bool mNavigationFlag = false;

	/// Flag that sets if change direction is enabled;
	bool mDirectionFlag = false;

	/// Flag that sets if roatation is enabled;
	bool mRotateFlag= false;
	/// X click point used in scrolling
	int mClickX = 0;
	/// Y Click point used in scrolling
	int mClickY = 0;
	/// Offset x for scrolling
	int mOffsetX = 0;
	/// Offset y for scrolling
	int mOffsetY = 0;

	/// Tile counter
	int mTileCnt = 0;
	/// Partially overlaping tile counter
	int mPartCnt = 0;
	/// Fully overlaping tile counter
	int mOverCnt = 0;
	
	/// Flag that indicates if the game in going
	bool mShuffleTime = false;

	double mGameTimer = 0.0;
public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnFileOpen();
    afx_msg void OnFileSaveas();
	/** \cond */
    afx_msg void OnBuildingsFarmhouse();
    afx_msg void OnLandscapingGrass();
    afx_msg void OnLandscapingSpartystatue();
    afx_msg void OnBuildingsBlacksmithshop();
    afx_msg void OnLandscapingTallgrass();
    afx_msg void OnBuildingsBrownhouse();
    afx_msg void OnBuildingsYellowhouse();
    afx_msg void OnBuildingsF();
    afx_msg void OnBuildingsHospital();
    afx_msg void OnBuildingsMarket();
    afx_msg void OnBuildingsCondos();
    afx_msg void OnLandscapingTree();
    afx_msg void OnLandscapingTrees();
    afx_msg void OnLandscapingBigtrees();
    afx_msg void OnLandscapingRoad();
    afx_msg void OnBusinessesCoalmine();
	/** \endcond */
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnZoningResidential();
	afx_msg void OnZoningIndustrial();
	afx_msg void OnZoningAgricultural();
	afx_msg void OnUpdateZoningResidential(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZoningIndustrial(CCmdUI *pCmdUI);
	afx_msg void OnUpdateZoningAgricultural(CCmdUI *pCmdUI);
	afx_msg void OnZoningNone();
	afx_msg void OnUpdateZoningNone(CCmdUI *pCmdUI);
	afx_msg void OnBuildingsCount();
	afx_msg void OnBusinessesHaulcoal();
	afx_msg void OnBusinessesTrump();
	afx_msg void OnUpdateBusinessesTrump(CCmdUI *pCmdUI);
	afx_msg void OnViewCityspecs();
	afx_msg void OnBusinessesConstruction();
	afx_msg void OnPowerPowerplant();
	afx_msg void OnPowerSubstation();
	afx_msg void OnPowerSolarpowerstation();
	afx_msg void OnPowerPowergrid();
	afx_msg void OnPowerChangedirection();
	afx_msg void OnUpdatePowerChangedirection(CCmdUI *pCmdUI);
	afx_msg void OnCurvedroadsRoadul();
	afx_msg void OnCurvedroadsRoadur();
	afx_msg void OnCurvedroadsRoadll();
	afx_msg void OnCurvedroadsRoadlr();
	afx_msg void OnLongroadsRoadud();
	afx_msg void OnLongroadsRoadlr();
	afx_msg void OnIntersectionsFull();
	afx_msg void OnIntersectionsNoright();
	afx_msg void OnIntersectionsNodown();
	afx_msg void OnIntersectionsNoup();
	afx_msg void OnIntersectionsNoleft();
	afx_msg void OnOtherroadsRotate();
	afx_msg void OnUpdateOtherroadsRotate(CCmdUI *pCmdUI);

	void Shuffle();
	void EndGame();
	std::wstring Clock();
};

