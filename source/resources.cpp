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

#include "resources.h"
#include "Iw2D.h"
#include "audio.h"

Resources::Resources()
{
    // Load images
    Circle = Iw2DCreateImage("textures/Circle.png");
    Square = Iw2DCreateImage("textures/Square.png");
    Triangle= Iw2DCreateImage("textures/Triangle.png");
    Star = Iw2DCreateImage("textures/Star.png");
    Button = Iw2DCreateImage("textures/Button.png");
    Pause = Iw2DCreateImage("textures/Pause.png");
    Super = Iw2DCreateImage("textures/Super.png");
	TitleBackground = Iw2DCreateImage( "textures/TitleBackground.png" );
	ResultsBackground = Iw2DCreateImage( "textures/ResultBackground.png" );
    TutorialPages[0] = Iw2DCreateImage( "textures/Help0.png" );
    TutorialPages[1] = Iw2DCreateImage( "textures/Help1.png" );
    TutorialPages[2] = Iw2DCreateImage( "textures/Help2.png" );
    TutorialPages[3] = Iw2DCreateImage( "textures/Help3.png" );
    TutorialPages[4] = Iw2DCreateImage( "textures/Help4.png" );
    TutorialPages[5] = Iw2DCreateImage( "textures/Help5.png" );

	// Load fonts
    Font = Iw2DCreateFont("fonts/arial8.gxfont");

    // Load sound effects
    TilesCleared = g_pAudio->PreloadSound("audio/gem_destroyed.wav");
}

Resources::~Resources()
{
    delete Circle;
    delete Square;
    delete Triangle;
    delete Star;
    delete Button;
    delete Pause;
    delete Super;
    delete TitleBackground;
    delete ResultsBackground;
    for( unsigned int i = 0; i < 6; i++ )
    {
        delete TutorialPages[i];
    }

	delete Font;
    delete TilesCleared;
}

// Global resources
Resources* g_pResources = 0;



