/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__GRID_H__)
#define __GRID_H__

#include "GridItem.h"
#include "scene.h"

namespace SFAS2014
{
    class TargetNumberGenerator;

/**
 * @class Grid
 *
 * @brief Container for a grid of GridItems, with methods for manipulating them.
 *
 */
class Grid
{

public:	

    Grid( int gridWidth, int gridHeight, Scene& scene );
    ~Grid();

    /**
     * @fn    GridItem* Grid::GetItem();
     *
     * @brief Returns the GridItem at the given position.
     *
     */
	 GridItem* GetItem( int row, int col );

    /**
     * @fn    GridItem* Grid::GetItem();
     *
     * @brief Returns the item at the given point on the screen, or NULL if
     *        there isn't one.
     *
     */
	 GridItem* GetTouchedItem( int x, int y );

    /**
     * @fn    void Grid::Reset();
     *
     * @brief Deletes all the GridItems and creates new ones.
     *
     */
	void Reset();

    /**
     * @fn    void ClearHighlightedItems();
     *
     * @brief Deletes all the GridItems and creates new ones.
     *
     */
	void ClearHighlightedItems();

    /**
     * @fn    bool LineBonus();
     *
     * @brief Returns true if the currently highlighted GridItems are in a line.
     */
    bool LineBonus();

    /**
     * @fn    bool SameShapeBonus();
     *
     * @brief Returns true if the currently highlighted GridItems are the same 
              shape as each other.
     */
    bool SameShapeBonus();

    /**
     * @fn    void Update( float deltaTime );
     *
     * @brief 
     */
    void Update( float deltaTime );

    /**
     * @fn    unsigned int GetWidth();
     *
     * @brief 
     */
    unsigned int GetWidth();

    /**
     * @fn    unsigned int GetHeight();
     *
     * @brief 
     */
    unsigned int GetHeight();

    /**
     * @fn    void Grid::SetTargetNumberGenerator();
     *
     * @brief Sets the TNG from which the Grid gets replacement GridItems for
     *        those the player clears.
     */
    void SetTargetNumberGenerator( TargetNumberGenerator* tng );

private: 
    
    // Internal structure for testing relative Item positions.
    struct pair { int row; int col; };

    int m_GridWidth;
    int m_GridHeight;
	GridItem ** m_pGrid; // Array of GridItems
    Scene& m_Scene;       // Reference to scene for adding and removing sprites.
    TargetNumberGenerator* m_pTNG;
	
    // Fills each space in the grid with a new GridItem.
    void PopulateGrid();
    // Delete all GridItems in the grid.
    void ClearGrid();
    
    // Takes an array of (row, col) positions and returns true if they are in
    // a line.
    bool HorizontalLineBonus( pair** highlighted, int totalHighlighted );
    bool VerticalLineBonus( pair** highlighted, int totalHighlighted );

};
}

#endif  // __GRID_H__


