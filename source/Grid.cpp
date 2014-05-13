/*
 * (C) 2014 Search for a Star
 * 
 */

#include "Grid.h"
#include "TargetNumberGenerator.h"

using namespace SFAS2014;

//
//
// Grid class
//
//
Grid::Grid( int gridWidth, int gridHeight, Scene& scene ) : m_Scene( scene )
{
    m_GridWidth = gridWidth;
    m_GridHeight = gridHeight;

    // Allocate array space.
    m_pGrid = new GridItem* [m_GridWidth * m_GridHeight];

    PopulateGrid();
}

Grid::~Grid()
{
    // Delete all the GridItems.
    for( int i = 0; i < ( m_GridWidth * m_GridHeight ); i++ )
    {
        // Remove sprites from the GameScene, because the GridItem destructor 
        // will clean them up.
        m_Scene.RemoveChild(m_pGrid[i]->GetSprite());
        m_Scene.RemoveChild(m_pGrid[i]->GetLabel());
        delete m_pGrid[i];
    }
    // Not responsible for deleting the TargetNumberGenerator.
}

GridItem* Grid::GetItem( int row, int col )
{ 
    return m_pGrid[( row * m_GridWidth ) + col]; 
}

GridItem* Grid::GetTouchedItem( int x, int y )
{ 
    for( int i = 0; i < ( m_GridWidth * m_GridHeight ); i++ )
    {
        if( m_pGrid[i]->GetSprite()->HitTest( x, y ) )
        {
            return m_pGrid[i];
        }
    }
    return NULL;
}

void Grid::PopulateGrid()
{
	float x = 32.0f;
	float y = 32.0f;
	for( int row = 0; row < m_GridHeight; row++ )
	{
		x = 32.0f;
		for( int column = 0; column < m_GridWidth; column++ )
		{
			int shape = IwRand() % 4;
			GridItem* item = new GridItem( x, y, (GridItem::Shape)shape );

			m_pGrid[( row * m_GridWidth ) + column] = item; 
			m_Scene.AddChild( item->GetSprite() );
			m_Scene.AddChild( item->GetLabel() );

			x += 64.0f;
		}

		y += 64.0f;
	}
}

void Grid::ClearGrid()
{
    for( int i = 0; i < ( m_GridWidth * m_GridHeight ); i++ )
    {
        m_Scene.RemoveChild( m_pGrid[i]->GetSprite() );
	    m_Scene.RemoveChild( m_pGrid[i]->GetLabel() );
        delete m_pGrid[i];
    }
}

void Grid::ClearHighlightedItems()
{
    GridItem** newGridItems = m_pTNG->GetNextGridItems();
    unsigned int newGridItemsIndex = 0;
    for( int column = 0; column < m_GridWidth; column++ )
    {
        // Iterate from the lowest rows on the screen to the highest.
        int nextFreeRow = m_GridHeight-1;
        for( int row = m_GridHeight-1; row >= 0; row-- )
        {
            if( GetItem( row, column )->IsHighlighted() )
            {
                // Delete highlighted item.
                m_Scene.RemoveChild( GetItem( row, column )->GetSprite() );
			    m_Scene.RemoveChild( GetItem( row, column )->GetLabel() );
                delete GetItem( row, column );
            }
            else
            {
                // Or make non-highlighted item fall.
                GetItem( row, column )->FallDistance(
                        64.0f * ( nextFreeRow - row ) );
                m_pGrid[( nextFreeRow * m_GridWidth ) + column] = 
                        GetItem( row, column );
                nextFreeRow--;
            }
        }
        // Fill gaps at the top with GridItems from the TNG.
        unsigned int itemsSpawnedThisCol = 0;
        for( ; nextFreeRow >= 0; nextFreeRow-- )
        {
            // Position the item.
            newGridItems[newGridItemsIndex]->SetPosition( 
                    32.0f + ( 64.0f * column ), 
                    -64.0f * (itemsSpawnedThisCol + 1) );
            newGridItems[newGridItemsIndex]->FallToPosition(
                    32.0f + ( 64.0f * nextFreeRow ) );
            // Add it to the Grid.
            m_pGrid[( nextFreeRow * m_GridWidth ) + column] = 
                    newGridItems[newGridItemsIndex];
            m_Scene.AddChild( GetItem( nextFreeRow, column )->GetSprite() );
            m_Scene.AddChild( GetItem( nextFreeRow, column )->GetLabel() );
            itemsSpawnedThisCol++;
            newGridItems[newGridItemsIndex] = NULL;
            newGridItemsIndex++;
        }
    }
    delete[] newGridItems;
}

void Grid::Reset()
{
    ClearGrid();
    PopulateGrid();
}

bool Grid::LineBonus()
{
    pair** highlighted;
    highlighted = new pair* [m_GridWidth*m_GridHeight];
    int totalHighlighted = 0;
    for( int col = 0; col < m_GridWidth; col++ )
    {
        for( int row = 0; row < m_GridHeight; row++ )
        {
            if( GetItem( row, col )->IsHighlighted() )
            {
                highlighted[totalHighlighted] = new pair();
                highlighted[totalHighlighted]->row = row;
                highlighted[totalHighlighted]->col = col;
                totalHighlighted++;
            }
        }
    }
    return HorizontalLineBonus( highlighted, totalHighlighted ) ||
            VerticalLineBonus( highlighted, totalHighlighted );
}

bool Grid::HorizontalLineBonus( pair** highlighted, int totalHighlighted )
{
    for( int i = 1; i < totalHighlighted; i++ )
    {
        if( highlighted[i]->row != highlighted[i-1]->row || 
                highlighted[i]->col != highlighted[i-1]->col + 1 )
        {
            return false;
        }
    }
    return true;
}

bool Grid::VerticalLineBonus( pair** highlighted, int totalHighlighted )
{
    for( int i = 1; i < totalHighlighted; i++ )
    {
        if( highlighted[i]->row != highlighted[i-1]->row + 1 || 
                highlighted[i]->col != highlighted[i-1]->col )
        {
            return false;
        }
    }
    return true;
}

bool Grid::SameShapeBonus()
{
    GridItem::Shape shape = GridItem::NumberOfShapes;
    for( int i = 0; i < m_GridWidth*m_GridHeight; i++ )
    {
        if( m_pGrid[i]->IsHighlighted() )
        {
            // If this is the first highlighted item, note its shape.
            if( GridItem::NumberOfShapes == shape )
            {
                shape = m_pGrid[i]->GetShape();
            }
            // Otherwise, compare with the required shape.
            else if( m_pGrid[i]->GetShape() != shape )
            {
                return false;
            }
        }
    }
    return true;
}

void Grid::Update( float deltaTime )
{
    for( int i = 0; i < m_GridWidth * m_GridHeight; i++ )
    {
        m_pGrid[i]->Update( deltaTime );
    }
}

void Grid::SetTargetNumberGenerator( TargetNumberGenerator* tng )
{
    m_pTNG = tng;
}

unsigned int Grid::GetWidth()
{
    return m_GridWidth;
}

unsigned int Grid::GetHeight()
{
    return m_GridHeight;
}
