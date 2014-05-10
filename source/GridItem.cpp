/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GridItem.h"

#include "resources.h"

using namespace Iw2DSceneGraphCore;
using namespace Iw2DSceneGraph;
using namespace SFAS2014;

//
//
// GridItem class
//
//
// Initialised in the GameScene initialiser.
unsigned int GridItem::TotalValues = 0;
unsigned int* GridItem::Values = NULL;
const float GridItem::FallSpeed = 512.0f;

CColor GridItem::mShapeColours[GridItem::NumberOfShapes] = 
{
		CColor( 128, 255, 154, 255 ),
		CColor( 255, 181, 255, 255 ),
		CColor( 128, 255, 232, 255 ),
		CColor( 240, 255, 140, 255 )
};

CColor GridItem::mHighlightColour = CColor( 255, 128, 128, 255 );

GridItem::GridItem( float x, float y, Shape shape )
{
	mSprite = new CSprite();
	mSprite->m_X = x;
	mSprite->m_Y = y;
    m_TargetY = y;
	
	mShape = shape;
    mValue = Values[IwRand() % TotalValues];

	if( mShape == Circle )
	{
		mSprite->SetImage(g_pResources->getCircle());
	}
	else if( mShape == Square )
	{
		mSprite->SetImage(g_pResources->getSquare());
	}
	else if( mShape == Triangle )
	{
		mSprite->SetImage(g_pResources->getTriangle());
	}
	else if( mShape == Star )
	{
		mSprite->SetImage(g_pResources->getStar());
	}

    mHighlighted = false;

	mSprite->m_Color = mShapeColours[mShape];

	mSprite->m_W = mSprite->GetImage()->GetWidth();
	mSprite->m_H = mSprite->GetImage()->GetHeight();
	mSprite->m_AnchorX = 0.0f;
	mSprite->m_AnchorY = 0.0f;
 
	// Fit grid to screen size
	mSprite->m_ScaleX = 1.0f;
	mSprite->m_ScaleY = 1.0f;
    
	// Create the number label
	m_Label = new CLabel();
	char labelBuffer[4];
	sprintf(labelBuffer, "%d", mValue );
	m_Label->SetText(labelBuffer);
    // Add a few extra pixels to the width, because the function underestimates.
    Iw2DSetFont(m_Label->m_Font);
    //m_Label->m_W = (float)Iw2DGetStringWidth(labelBuffer) + 2;
	m_Label->m_AnchorX = 0.5;
	m_Label->m_AnchorY = 0.5;
	m_Label->m_X = x + mSprite->m_W / 2;
	m_Label->m_Y = y + mSprite->m_H / 2;
	m_Label->SetFont(g_pResources->getFont());
    m_Label->m_ScaleX *= 2.0f;
    m_Label->m_ScaleY *= 2.0f;
	m_Label->m_Color = CColor(0,0,0,255);
}

GridItem::~GridItem()
{
    delete mSprite;
    delete m_Label;
}

bool GridItem::Toggle()
{
    if( mHighlighted ) {
        Reset();
    }
    else
    {
        Highlight();
    }
    return mHighlighted;
}

void GridItem::Highlight()
{
	mSprite->m_Color = mHighlightColour;
    mHighlighted = true;
}

void GridItem::Reset()
{
	mSprite->m_Color = mShapeColours[mShape];
    mHighlighted = false;
}


unsigned int GridItem::GetValue()
{
    return mValue;
}

bool GridItem::IsHighlighted() 
{
    return mHighlighted;
}

void GridItem::FallDistance( float y )
{
    m_TargetY += y;
}

void GridItem::FallToPosition( float y )
{
    m_TargetY = y;
}

void GridItem::Update( float deltaTime )
{
    if( mSprite->m_Y < m_TargetY )
    {
        float deltaY = FallSpeed * deltaTime;
        if( mSprite->m_Y + deltaY > m_TargetY )
        {
            deltaY = m_TargetY - mSprite->m_Y;
        }
        mSprite->m_Y += deltaY;
        m_Label->m_Y += deltaY;
    }
}

void GridItem::SetPosition( float x, float y )
{
    mSprite->m_X = x;
    mSprite->m_Y = y;
	m_Label->m_X = x + mSprite->m_W / 2;
	m_Label->m_Y = y + mSprite->m_H / 2;
    m_TargetY = y;
}