/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__GRIDITEM_H__)
#define __GRIDITEM_H__

#include "Iw2DSceneGraph.h"

namespace SFAS2014
{

/**
 * @class GridItem
 *
 * @brief Manages the GridItem items position and the state of the GridItem.
 *
 */
class GridItem 
{

public:	
	
	enum Shape
	{
		Circle,
		Square,
		Triangle,
		Star,

		NumberOfShapes
	};

    static unsigned int* Values; // Array of valid values
    static unsigned int TotalValues; // Total number of valid values

    GridItem( float x, float y, Shape shape);
    ~GridItem();

    /**
     * @fn    const CSprite * GridItem::GetSprite();
     *
     * @brief Returns the sprite for this GridItem
     *
     */
	Iw2DSceneGraph::CSprite * GetSprite() { return mSprite; }

    /**
     * @fn    const CSprite * GridItem::GetSprite();
     *
     * @brief Returns the label for this GridItem
     *
     */
	Iw2DSceneGraph::CLabel * GetLabel() { return m_Label; }

    /**
     * @fn    void GridItem::Highlight();
     *
     * @brief Highlights the Item
     *
     */
	void Highlight();

    /**
     * @fn    void GridItem::Reset();
     *
     * @brief Resets the Item to non-highlighted.
     *
     */
	void Reset();
    
    /**
     * @fn    bool GridItem::Toggle();
     *
     * @brief Toggles the Item between highlighted and unhighlighted.
     *
     */
    bool Toggle();
    
    /**
     * @fn    unsigned int GridItem::GetValue();
     *
     * @brief Returns the number value associated with the Item.
     *
     */
    unsigned int GetValue();
    
    /**
     * @fn    Shape GridItem::GetShape();
     *
     * @brief Returns the shape of the Item.
     *
     */
    Shape GetShape() { return mShape; }
    
    /**
     * @fn    bool GridItem::IsHighlighted();
     *
     * @brief Returns true if the Item is highlighted.
     *
     */
    bool IsHighlighted();
    
    /**
     * @fn    void GridItem::FallDistance( float y );
     *
     * @brief Makes the GridItem fall on-screen by the given amount.
     *
     */
    void FallDistance( float y );
    
    /**
     * @fn    void GridItem::FallToPosition( float y );
     *
     * @brief Makes the GridItem fall on-screen to the given position.
     *
     */
    void FallToPosition( float y );
    
    /**
     * @fn    void GridItem::Update( float deltaTime );
     *
     * @brief If the Item is falling, updates its position.
     *
     */
    void Update( float deltaTime );
    
    /**
     * @fn    void GridItem::SetPosition( float x, float y );
     *
     * @brief Sets the item's position to the given x and y.
     *
     */
    void SetPosition( float x, float y );

private: 

    static const float FallSpeed;
	Iw2DSceneGraph::CSprite * mSprite;
    Iw2DSceneGraph::CLabel* m_Label;
	Shape mShape;
    unsigned int mValue;
    bool mHighlighted;
    // The position to which the GridItem is falling.
    float m_TargetY;
	
	static Iw2DSceneGraph::CColor mShapeColours[NumberOfShapes];
	static Iw2DSceneGraph::CColor mHighlightColour;
};
}

#endif  // __GRIDITEM_H__


