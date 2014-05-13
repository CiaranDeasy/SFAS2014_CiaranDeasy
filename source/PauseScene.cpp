/*
 * (C) 2014 Search for a Star
 * 
 */

#include "PauseScene.h"
#include "IwGx.h"
#include "resources.h"
#include "input.h"
#include "GameSceneManager.h"

using namespace SFAS2014;

//
//
// PauseScene class
//
//
PauseScene::PauseScene( GameSceneManager& sceneManager )
        : m_SceneManager( sceneManager )
{
    
}

PauseScene::~PauseScene()
{
}

void PauseScene::Init()
{
	Scene::Init();

    m_IsActive = false;

    m_pResumeSprite = new CSprite();
	m_pResumeSprite->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pResumeSprite->m_Y = (float)IwGxGetScreenHeight() * 0.4f;
	m_pResumeSprite->SetImage(g_pResources->getButton());
	m_pResumeSprite->m_W = m_pResumeSprite->GetImage()->GetWidth();
	m_pResumeSprite->m_H = m_pResumeSprite->GetImage()->GetHeight();
	m_pResumeSprite->m_AnchorX = 0.5;
	m_pResumeSprite->m_AnchorY = 0.5;
    m_pResumeSprite->m_Color = CColor( 255, 0, 0, 255 );
    AddChild( m_pResumeSprite );

	m_pResumeText = new CLabel();
	m_pResumeText->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pResumeText->m_Y = (float)IwGxGetScreenHeight() * 0.4f;
	m_pResumeText->SetFont(g_pResources->getFont());
	m_pResumeText->SetText("Resume Game");
	m_pResumeText->m_AnchorX = 0.5;
	m_pResumeText->m_AnchorY = 0.5;
	m_pResumeText->m_Color = CColor(0,0,0,255);
	AddChild(m_pResumeText);
}

void PauseScene::Update(float deltaTime, float alphaMul)
{
    // Don't update if the scene isn't active.
    if( !m_IsActive )
    {
        return;
    }

	Scene::Update(deltaTime, alphaMul);

    // Test for button presses.
    if( g_pInput->m_Pressed )
    {
        if( m_pResumeSprite->HitTest( g_pInput->m_X, g_pInput->m_Y ) )
        {
            m_SceneManager.SwitchTo( GameSceneManager::keGameState );
            return;
        }
    }
}

void PauseScene::Render()
{
	Scene::Render();
}
