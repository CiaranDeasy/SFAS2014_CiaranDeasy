/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 *
 * Edited for the Search for a Star Competition 2014
 *
 */

#if !defined(__RESOURCES_H__)
#define __RESOURCES_H__

#define MAX_GEM_TYPES   5

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;

class AudioSound;

/**
 * @class Resources
 *
 * @brief Resources class
 *
 * The that manages the lifetime of the following types of resources:
 * - Images
 * - Fonts
 * - Sound Effects
 * - Atlases
 */
class Resources
{
protected:
    CIw2DImage*     Circle;
    CIw2DImage*     Square;
    CIw2DImage*     Triangle;
    CIw2DImage*     Star;
    CIw2DImage*     Button;
    CIw2DImage*     Pause;
    CIw2DImage*     Super;
	CIw2DImage*		TitleBackground;
	CIw2DImage*		ResultsBackground;
    CIw2DImage*     TutorialPages[6];
    CIw2DFont*      Font;
    AudioSound*     TilesCleared;

public:
    CIw2DImage*     getCircle()					{ return Circle; }
    CIw2DImage*     getSquare()					{ return Square; }
    CIw2DImage*     getTriangle()				{ return Triangle; }
    CIw2DImage*     getStar()					{ return Star; }
    CIw2DImage*     getButton()					{ return Button; }
    CIw2DImage*     getPause()					{ return Pause; }
    CIw2DImage*     getSuper()				    { return Super; }
    CIw2DImage*     getTitleBackground()		{ return TitleBackground; }
    CIw2DImage*     getResultsBackground()		{ return ResultsBackground; }
    CIw2DImage*     getTutorialPage( int i )    { return TutorialPages[i]; }
	CIw2DFont*		getFont()					{ return Font; }
    AudioSound*     getTilesCleared()           { return TilesCleared; }

public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;




#endif  // __RESOURCES_H__


