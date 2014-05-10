/*
 * (C) 2014 Search for a Star
 * 
 */

#include "BoardScene.h"
#include "IwGx.h"
#include "resources.h"
#include "input.h"
#include "GameSceneManager.h"
#include "GameData.h"
#include <iostream>

using namespace SFAS2014;

//
//
// BoardScene class
//
//
BoardScene::BoardScene( GameSceneManager& sceneManager )
        : m_SceneManager( sceneManager )
{

}

BoardScene::~BoardScene()
{
    delete m_pTitle;
    for( unsigned int i = 0; i < 10; i++ )
    {
        delete m_pScoreValues[i];
    }
}

void BoardScene::Init()
{
	Scene::Init();

    m_IsActive = false;

	// Create the title text
	m_pTitle = new CLabel();
	m_pTitle->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pTitle->m_Y = (float)IwGxGetScreenHeight() * 0.10f;
	m_pTitle->SetFont(g_pResources->getFont());
	m_pTitle->SetText("High Scores");
	m_pTitle->m_AnchorX = 0.5;
	m_pTitle->m_AnchorY = 0.5;
	m_pTitle->m_Color = CColor(255,255,255,255);
	AddChild(m_pTitle);

    for( unsigned int i = 0; i < 10; i++ )
    {
	    m_pScoreValues[i] = new CLabel();
	    m_pScoreValues[i]->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	    m_pScoreValues[i]->m_Y = (float)IwGxGetScreenHeight() * (0.15f + 0.06f * i);
	    m_pScoreValues[i]->SetFont(g_pResources->getFont());
	    m_pScoreValues[i]->SetText("Bar");
	    m_pScoreValues[i]->m_AnchorX = 0.5;
    	m_pScoreValues[i]->m_AnchorY = 0.5;
	    m_pScoreValues[i]->m_Color = CColor(255,255,255,255);
	    AddChild(m_pScoreValues[i]);
    }
}

void BoardScene::Update(float deltaTime, float alphaMul)
{
    // Don't update if the scene isn't active.
    if( !m_IsActive )
    {
        return;
    }

	Scene::Update(deltaTime, alphaMul);
    
	char scoreBuffer[9];
    for( unsigned int i = 0; i < 10; i++ )
    {
	    sprintf(scoreBuffer, "%d", g_pGameData->GetScore(i) );
	    m_pScoreValues[i]->SetText(scoreBuffer);
        // Add a few extra pixels to the width, because the function underestimates.
        m_pScoreValues[i]->m_W = (float)Iw2DGetStringWidth(scoreBuffer) + 5;
    }

    if( g_pInput->m_Pressed )
    {
        m_SceneManager.SwitchTo( GameSceneManager::keTitleState );
        return;
    }
}

void BoardScene::Render()
{
	Scene::Render();
}

