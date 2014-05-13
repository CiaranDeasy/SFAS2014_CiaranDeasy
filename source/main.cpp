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

#include "Iw2D.h"
#include "input.h"
#include "audio.h"
#include "resources.h"
#include "GameData.h"

#include "TitleScene.h"
#include "GameScene.h"
#include "GameSceneManager.h"
#include "ResultsScene.h"

// FRAME_TIME is the amount of time that a single frame should last in seconds
#define FRAME_TIME  (30.0f / 1000.0f)

int main()
{
    // Initialise the 2D graphics system
    Iw2DInit();

    // Set up audio systems
    g_pAudio = new Audio();

    // Create resources
    g_pResources = new Resources();

    // Set up input systems
    g_pInput = new Input();

    // Load or create game data
    g_pGameData = SFAS2014::GameData::LoadGameData();

    // Create scene manager
    SFAS2014::GameSceneManager * pSceneManager = new SFAS2014::GameSceneManager();

    // Initialise the time
    uint64 currentTime = 0;
    uint64 lastTime = s3eTimerGetMs();
    float deltaTime = 0;

    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {
        // Compute the change in time.
        currentTime = s3eTimerGetMs();
        deltaTime = ((float)(currentTime - lastTime))/1000.f;
        lastTime = currentTime;

        // Update input system
        g_pInput->Update();

        // Update audio system
        g_pAudio->Update();

        // Update scene manager
        pSceneManager->Update(deltaTime);

        // Clear the drawing surface
        Iw2DSurfaceClear(0xffff0000);

        // Render scene manager
        pSceneManager->Render();

        // Show the drawing surface
        Iw2DSurfaceShow();

        // Yield to the OS
        s3eDeviceYield(0);
    }

    // Clean-up
    SFAS2014::GameData::SaveGameData( g_pGameData );
    delete g_pAudio;
    delete g_pInput;
    delete g_pResources;
    delete pSceneManager;
    Iw2DTerminate();

    return 0;
}
