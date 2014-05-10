/*
 * (C) 2014 Search for a Star
 * 
 */

#include "TitleScene.h"
#include "IwGx.h"
#include "resources.h"
#include "input.h"
#include "GameSceneManager.h"
#include "GameData.h"

using namespace SFAS2014;

//
//
// TitleScene class
//
//
TitleScene::TitleScene( GameSceneManager& sceneManager )
        : m_SceneManager( sceneManager )
{
}

TitleScene::~TitleScene()
{
	delete m_pBackground;
    delete m_pStartSprite;
    delete m_pStartText;
    delete m_pTutorialSprite;
    delete m_pTutorialText;
    delete m_pBoardSprite;
    delete m_pBoardText;
    delete m_pWipeSprite;
    delete m_pWipeText;
}

void TitleScene::Init()
{
	Scene::Init();

    m_IsActive = false;

	// Create background sprite
	m_pBackground = new CSprite();
	m_pBackground->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pBackground->m_Y = (float)IwGxGetScreenHeight() * 0.5f;
	m_pBackground->SetImage(g_pResources->getTitleBackground());
	m_pBackground->m_W = m_pBackground->GetImage()->GetWidth();
	m_pBackground->m_H = m_pBackground->GetImage()->GetHeight();
	m_pBackground->m_AnchorX = 0.5;
	m_pBackground->m_AnchorY = 0.5;
 
	// Fit background to screen size
	m_pBackground->m_ScaleX = (float)IwGxGetScreenWidth() / m_pBackground->GetImage()->GetWidth();
	m_pBackground->m_ScaleY = (float)IwGxGetScreenHeight() / m_pBackground->GetImage()->GetHeight();
	m_pBackground->m_Color = CColor(255,255,255,255);
    AddChild( m_pBackground );

    m_pStartSprite = new CSprite();
	m_pStartSprite->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pStartSprite->m_Y = (float)IwGxGetScreenHeight() * 0.4f;
	m_pStartSprite->SetImage(g_pResources->getButton());
	m_pStartSprite->m_W = m_pStartSprite->GetImage()->GetWidth();
	m_pStartSprite->m_H = m_pStartSprite->GetImage()->GetHeight();
	m_pStartSprite->m_AnchorX = 0.5;
	m_pStartSprite->m_AnchorY = 0.5;
    m_pStartSprite->m_Color = CColor( 0, 0, 255, 255 );
    AddChild( m_pStartSprite );

	m_pStartText = new CLabel();
	m_pStartText->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pStartText->m_Y = (float)IwGxGetScreenHeight() * 0.4f;
	m_pStartText->SetFont(g_pResources->getFont());
	m_pStartText->SetText("Play");
	m_pStartText->m_AnchorX = 0.5;
	m_pStartText->m_AnchorY = 0.5;
	m_pStartText->m_Color = CColor(255,255,255,255);
	AddChild(m_pStartText);

    m_pTutorialSprite = new CSprite();
	m_pTutorialSprite->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pTutorialSprite->m_Y = (float)IwGxGetScreenHeight() * 0.5f;
	m_pTutorialSprite->SetImage(g_pResources->getButton());
	m_pTutorialSprite->m_W = m_pTutorialSprite->GetImage()->GetWidth();
	m_pTutorialSprite->m_H = m_pTutorialSprite->GetImage()->GetHeight();
	m_pTutorialSprite->m_AnchorX = 0.5;
	m_pTutorialSprite->m_AnchorY = 0.5;
    m_pTutorialSprite->m_Color = CColor( 0, 0, 255, 255 );
    AddChild( m_pTutorialSprite );

	m_pTutorialText = new CLabel();
	m_pTutorialText->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pTutorialText->m_Y = (float)IwGxGetScreenHeight() * 0.5f;
	m_pTutorialText->SetFont(g_pResources->getFont());
	m_pTutorialText->SetText("How To Play");
	m_pTutorialText->m_AnchorX = 0.5;
	m_pTutorialText->m_AnchorY = 0.5;
	m_pTutorialText->m_Color = CColor(255,255,255,255);
	AddChild(m_pTutorialText);

    m_pBoardSprite = new CSprite();
	m_pBoardSprite->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pBoardSprite->m_Y = (float)IwGxGetScreenHeight() * 0.6f;
	m_pBoardSprite->SetImage(g_pResources->getButton());
	m_pBoardSprite->m_W = m_pBoardSprite->GetImage()->GetWidth();
	m_pBoardSprite->m_H = m_pBoardSprite->GetImage()->GetHeight();
	m_pBoardSprite->m_AnchorX = 0.5;
	m_pBoardSprite->m_AnchorY = 0.5;
    m_pBoardSprite->m_Color = CColor( 0, 0, 255, 255 );
    AddChild( m_pBoardSprite );

	m_pBoardText = new CLabel();
	m_pBoardText->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pBoardText->m_Y = (float)IwGxGetScreenHeight() * 0.6f;
	m_pBoardText->SetFont(g_pResources->getFont());
	m_pBoardText->SetText("Leaderboards");
	m_pBoardText->m_AnchorX = 0.5;
	m_pBoardText->m_AnchorY = 0.5;
	m_pBoardText->m_Color = CColor(255,255,255,255);
	AddChild(m_pBoardText);

    m_pWipeSprite = new CSprite();
	m_pWipeSprite->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pWipeSprite->m_Y = (float)IwGxGetScreenHeight() * 0.7f;
	m_pWipeSprite->SetImage(g_pResources->getButton());
	m_pWipeSprite->m_W = m_pWipeSprite->GetImage()->GetWidth();
	m_pWipeSprite->m_H = m_pWipeSprite->GetImage()->GetHeight();
	m_pWipeSprite->m_AnchorX = 0.5;
	m_pWipeSprite->m_AnchorY = 0.5;
    m_pWipeSprite->m_Color = CColor( 0, 0, 255, 255 );
    AddChild( m_pWipeSprite );

	m_pWipeText = new CLabel();
	m_pWipeText->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pWipeText->m_Y = (float)IwGxGetScreenHeight() * 0.7f;
	m_pWipeText->SetFont(g_pResources->getFont());
	m_pWipeText->SetText("Wipe boards");
	m_pWipeText->m_AnchorX = 0.5;
	m_pWipeText->m_AnchorY = 0.5;
	m_pWipeText->m_Color = CColor(255,255,255,255);
	AddChild(m_pWipeText);
}

void TitleScene::Update(float deltaTime, float alphaMul)
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
        if( m_pStartSprite->HitTest( g_pInput->m_X, g_pInput->m_Y ) )
        {
            m_SceneManager.SwitchTo( GameSceneManager::keGameState );
            return;
        }
        else if( m_pTutorialSprite->HitTest( g_pInput->m_X, g_pInput->m_Y ) )
        {
            m_SceneManager.SwitchTo( GameSceneManager::keTutorialState );
            return;
        }
        else if( m_pBoardSprite->HitTest( g_pInput->m_X, g_pInput->m_Y ) )
        {
            m_SceneManager.SwitchTo( GameSceneManager::keBoardState );
            return;
        }
        if( m_pWipeSprite->HitTest( g_pInput->m_X, g_pInput->m_Y ) )
        {
            delete g_pGameData;
            g_pGameData = new GameData();
            return;
        }
    }
}

void TitleScene::Render()
{
	Scene::Render();
}
