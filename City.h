/**
 * \file City.h
 *
 * \author Jonathan Dowdall
 *
 * \brief Class that implements a simple city with tiles we can manipulate
 */

#pragma once

#include <memory>
#include <vector>
#include <map>
#include <utility>

#include "XmlNode.h"
#include "Tile.h"
#include "BlankTile.h"

/**
 * \brief Implements a simple city with tiles we can manipulate
 */
class CCity
{
public:
    CCity();
    virtual ~CCity();

    /// The spacing between grid locations
    static const int GridSpacing = 32;


    void Add(std::shared_ptr<CTile> item);
	void AddBlank(std::shared_ptr<CBlankTile> blankTile);
    std::shared_ptr<CTile> HitTest(int x, int y);
    void MoveToFront(std::shared_ptr<CTile> item);
    void DeleteItem(std::shared_ptr<CTile> item);

    void OnDraw(Gdiplus::Graphics *graphics, int offsetX, int offsetY);

    void Save(const std::wstring &filename);
    void Load(const std::wstring &filename);
    void Clear();

    void Update(double elapsed);
    void SortTiles();

    std::shared_ptr<CTile> GetAdjacent(std::shared_ptr<CTile> tile, int dx, int dy);
    std::shared_ptr<CTile> GetAdjacent(CTile *tile, int dx, int dy);

	void Accept(CTileVisitor *visitor);

	bool IsComplete() { return mBlankTiles.size() == 0; }

	/** Iterator that iterates over the city tiles */
	class Iter
	{
	public:
		/** Constructor
		* \param city The city we are iterating over 
		* \param pos The position we start at
		*/
		Iter(CCity *city, int pos) : mCity(city), mPos(pos) {}

		/** Test for end of the iterator
		* \param other The other iter were comparing to
		* \returns True if we this position equals not equal to the other position */
		bool operator!=(const Iter &other) const
		{
			return mPos != other.mPos;
		}

		/** Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CTile> operator *() const { return mCity->mTiles[mPos]; }

		/** Increment the iterator
		* \returns Reference to this iterator */
		const Iter& operator++()
		{
			mPos++;
			return *this;
		}

	private:
		CCity *mCity;   ///< City we are iterating over
		int mPos;       ///< Position in the collection
	};

	/** Get an iterator for the beginning of the collection
	* \returns Iter object at position 0 */
	Iter begin() { return Iter(this, 0); }

	/** Get an iterator for the end of the collection
	* \returns Iter object at position past the end */
	Iter end() { return Iter(this, mTiles.size()); }

	/// Zoning iterator
	class ZoningIter
	{
	public:
		/** Constructor
		* \param zone The zone we are iterating over 
		* \param pos The position we start at
		*/
		ZoningIter(std::vector<std::shared_ptr<CTile>> zone, int pos) : mZone(zone), mPos(pos) {}

		/** Test for end of the iterator
		* \param other is other iter
		* \returns True if this position is not equal to the other position */
		bool operator!=(const ZoningIter &other) const
		{
			return mPos != other.mPos;
		}

		/** Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CTile> operator *() const { return mZone[mPos]; }

		/** Increment the iterator
		* \returns Reference to this iterator */
		const ZoningIter& operator++()
		{
			mPos++;
			return *this;
		}

	private:
		std::vector<std::shared_ptr<CTile>> mZone; ///< the zone of the iter
		int mPos;       ///< Position in the collection
	};

	/** A class we return to support iterating over
	* only specific zonings in the collection */
	class ZoningIterSupport
	{
	public:
		/** Constructor
		* \param city The city we are iteratoring over
		* \param zoning The zoning we are interested in */
		ZoningIterSupport(CCity *city, CTile::Zonings zoning) : mCity(city), mZoning(zoning) 
		{
			for (auto tile : mCity->mTiles)
			{
				if (tile->GetZoning() == zoning)
				{
					mZone.push_back(tile);
				}
			}
		}

		/** Get an iterator for the beginning of the collection
		* \returns Iter object at position 0 */
		ZoningIter begin() { return ZoningIter(mZone, 0); }

		/** Get an iterator for the end of the collection
		* \returns Iter object at position past the end */
		ZoningIter end() { return ZoningIter(mZone, mZone.size()); }

	private:
		CCity *mCity; ///< The City we iterate through
		CTile::Zonings mZoning; ///< The zone we iterate through
		/// Vector of all the tiles with the specific zoning
		std::vector<std::shared_ptr<CTile>> mZone;
	};

	/** Get a zoning iterator support object
	* \param zoning The zoning we are interested in
	* \returns ZoningIterSupport object
	*/
	ZoningIterSupport GetZoning(CTile::Zonings zoning) { return ZoningIterSupport(this, zoning); }

	bool MatchTest(std::shared_ptr<CTile> tile);

private:
    void XmlTile(const std::shared_ptr<xmlnode::CXmlNode> &node);
    void BuildAdjacencies();

    /// All of the tiles that make up our city
    std::vector<std::shared_ptr<CTile> > mTiles;

	/// All of the blank tiles that are used in the game
	std::vector<std::shared_ptr<CBlankTile> > mBlankTiles;

    /// Adjacency lookup support
    std::map<std::pair<int, int>, std::shared_ptr<CTile> > mAdjacency;
};

