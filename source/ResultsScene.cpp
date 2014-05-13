/*
 * (C) 2014 Search for a Star
 * 
 */

#include "ResultsScene.h"
#include "IwGx.h"
#include "resources.h"
#include "input.h"
#include "GameSceneManager.h"

using namespace SFAS2014;

//
//
// ResultsScene class
//
//
ResultsScene::ResultsScene( GameSceneManager& sceneManager )
        : m_SceneManager( sceneManager )
{

}

ResultsScene::~ResultsScene()
{
}

void ResultsScene::Init()
{
	Scene::Init();

    m_IsActive = false;

	// Create background sprite
	m_Background = new CSprite();
	m_Background->m_X = (float)IwGxGetScreenWidth() / 2;
	m_Background->m_Y = (float)IwGxGetScreenHeight() / 2;
	m_Background->SetImage(g_pResources->getResultsBackground());
	m_Background->m_W = m_Background->GetImage()->GetWidth();
	m_Background->m_H = m_Background->GetImage()->GetHeight();
	m_Background->m_AnchorX = 0.5;
	m_Background->m_AnchorY = 0.5;
 
	// Fit background to screen size
	m_Background->m_ScaleX = (float)IwGxGetScreenWidth() / m_Background->GetImage()->GetWidth();
	m_Background->m_ScaleY = (float)IwGxGetScreenHeight() / m_Background->GetImage()->GetHeight();
	AddChild(m_Background);

	// Create the title text
	m_GameOver = new CLabel();
	m_GameOver->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_GameOver->m_Y = (float)IwGxGetScreenHeight() * 0.15f;
	m_GameOver->SetFont(g_pResources->getFont());
	m_GameOver->SetText("GAME OVER!");
	m_GameOver->m_AnchorX = 0.5;
	m_GameOver->m_AnchorY = 0.5;
	m_GameOver->m_Color = CColor(255,255,255,255);
	AddChild(m_GameOver);

	// Create the title text
	m_TapContinue = new CLabel();
	m_TapContinue->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_TapContinue->m_Y = (float)IwGxGetScreenHeight() * 0.65f;
	m_TapContinue->SetFont(g_pResources->getFont());
	m_TapContinue->SetText("TAP TO CONTINUE");
	m_TapContinue->m_AnchorX = 0.5;
	m_TapContinue->m_AnchorY = 0.5;
	m_TapContinue->m_Color = CColor(0,0,0,255);
	AddChild(m_TapContinue);
}

void ResultsScene::Update(float deltaTime, float alphaMul)
{
    // Don't update if the scene isn't active.
    if( !m_IsActive )
    {
        return;
    }

	Scene::Update(deltaTime, alphaMul);

    if( g_pInput->m_Pressed )
    {
        m_SceneManager.SwitchTo( GameSceneManager::keBoardState );
        return;
    }
}

void ResultsScene::Render()
{
	Scene::Render();
}

