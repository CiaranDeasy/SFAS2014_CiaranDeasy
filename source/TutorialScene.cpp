/*
 * (C) 2014 Search for a Star
 * 
 */

#include "TutorialScene.h"
#include "IwGx.h"
#include "resources.h"
#include "input.h"
#include "GameSceneManager.h"

using namespace SFAS2014;

//
//
// TutorialScene class
//
//
TutorialScene::TutorialScene( GameSceneManager& sceneManager )
        : m_SceneManager( sceneManager )
{
    
}

TutorialScene::~TutorialScene()
{
    for( unsigned int i = 0; i < keNumberOfPages; i++ )
    {
        delete m_pPages;
    }
    delete m_pButtonSprite;
    delete m_pButtonLabel;
}

void TutorialScene::Init()
{
	Scene::Init();

    m_IsActive = false;

    // Create pages.
    for( unsigned int i = 0; i < keNumberOfPages; i++ )
    {
	    m_pPages[i] = new CSprite();
	    m_pPages[i]->m_X = 0.0f;
	    m_pPages[i]->m_Y = 0.0f;
	    m_pPages[i]->SetImage( g_pResources->getTutorialPage( i ) );
	    m_pPages[i]->m_W = m_pPages[i]->GetImage()->GetWidth();
	    m_pPages[i]->m_H = m_pPages[i]->GetImage()->GetHeight();
	    m_pPages[i]->m_AnchorX = 0.0f;
	    m_pPages[i]->m_AnchorY = 0.0f;
    }

    m_ActivePage = kePage0;
    AddChild(m_pPages[kePage0]);

    // Create Button
    m_pButtonSprite = new CSprite();
	m_pButtonSprite->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pButtonSprite->m_Y = (float)IwGxGetScreenHeight() * 0.8f;
	m_pButtonSprite->SetImage(g_pResources->getButton());
	m_pButtonSprite->m_W = m_pButtonSprite->GetImage()->GetWidth();
	m_pButtonSprite->m_H = m_pButtonSprite->GetImage()->GetHeight();
	m_pButtonSprite->m_AnchorX = 0.5;
	m_pButtonSprite->m_AnchorY = 0.5;
    m_pButtonSprite->m_Color = CColor( 255, 0, 0, 255 );
    AddChild( m_pButtonSprite );

	m_pButtonLabel = new CLabel();
	m_pButtonLabel->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pButtonLabel->m_Y = (float)IwGxGetScreenHeight() * 0.8f;
	m_pButtonLabel->SetFont(g_pResources->getFont());
	m_pButtonLabel->SetText("Next");
	m_pButtonLabel->m_AnchorX = 0.5;
	m_pButtonLabel->m_AnchorY = 0.5;
	m_pButtonLabel->m_Color = CColor(255,255,255,255);
	AddChild(m_pButtonLabel);
}

void TutorialScene::Update(float deltaTime, float alphaMul)
{
    // Don't update if the scene isn't active.
    if( !m_IsActive )
    {
        return;
    }

	Scene::Update(deltaTime, alphaMul);

    if( g_pInput->m_Pressed && 
            m_pButtonSprite->HitTest( g_pInput->m_X, g_pInput->m_Y ) )
    {
        // If we're on the last page, return to the title scene.
        if( m_ActivePage == kePage5 )
        {
            GoToPage( kePage0 );
            m_SceneManager.SwitchTo( GameSceneManager::keTitleState );
            return;
        }
        // Otherwise turn the page.
        else
        {
            GoToPage( (Page) ( m_ActivePage + 1 ) );
        }
    }
}

void TutorialScene::Render()
{
	Scene::Render();
}

void TutorialScene::GoToPage( Page page )
{
    // Change the display.
    RemoveChild( m_pPages[m_ActivePage] );
    AddChild( m_pPages[page] );
    // Re-add the button to show it on top.
    RemoveChild( m_pButtonSprite );
    AddChild( m_pButtonSprite );
    RemoveChild( m_pButtonLabel );
    AddChild( m_pButtonLabel );

    // Position the button.
    switch( page )
    {
    case kePage0:
	    m_pButtonSprite->m_Y = (float)IwGxGetScreenHeight() * 0.8f;
	    m_pButtonLabel->m_Y = (float)IwGxGetScreenHeight() * 0.8f;
        break;
    case kePage1:
	    m_pButtonSprite->m_Y = (float)IwGxGetScreenHeight() * 0.7f;
	    m_pButtonLabel->m_Y = (float)IwGxGetScreenHeight() * 0.7f;
        break;
    case kePage2:
	    m_pButtonSprite->m_Y = (float)IwGxGetScreenHeight() * 0.525f;
	    m_pButtonLabel->m_Y = (float)IwGxGetScreenHeight() * 0.525f;
        break;
    case kePage3:
	    m_pButtonSprite->m_Y = (float)IwGxGetScreenHeight() * 0.4f;
	    m_pButtonLabel->m_Y = (float)IwGxGetScreenHeight() * 0.4f;
        break;
    case kePage4:
	    m_pButtonSprite->m_Y = (float)IwGxGetScreenHeight() * 0.4f;
	    m_pButtonLabel->m_Y = (float)IwGxGetScreenHeight() * 0.4f;
        break;
    case kePage5:
	    m_pButtonSprite->m_Y = (float)IwGxGetScreenHeight() * 0.55f;
	    m_pButtonLabel->m_Y = (float)IwGxGetScreenHeight() * 0.55f;
        break;
    }

    m_ActivePage = page;
}
