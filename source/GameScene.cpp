/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GameScene.h"
#include "resources.h"
#include "IwGx.h"
#include "GridItem.h"
#include "input.h"
#include "Grid.h"
#include "GameSceneManager.h"
#include "TargetNumberGenerator.h"
#include "audio.h"
#include "GameData.h"

using namespace SFAS2014;

//
//
// GameScene class
//
//
const float GameScene::sTimeLimitInMinutes = 0.5f;
const float GameScene::sLineMultiplier = 2.0f;
const float GameScene::sShapeMultiplier = 2.0f;
const float GameScene::sSuperModeMultiplier = 3.0f;

GameScene::GameScene( GameSceneManager& sceneManager ) : 
        m_Time( 0.0f ), m_Score(0), m_SceneManager( sceneManager )
{

}

GameScene::~GameScene()
{
    delete m_pGrid;
    delete m_pScoreText;
    delete m_pTimeText;
    delete m_pCurrentNumberText;
    delete m_pFirstTargetNumberText;
    delete m_pSecondTargetNumberText;
    delete m_pThirdTargetNumberText;
    delete m_pTNG;
    delete m_pPauseSprite;
    delete m_pSuperModeSprite;
}

void GameScene::Init()
{
	Scene::Init();

    // Scene is inactive until switched to.
    m_IsActive = false;

	IwRandSeed( time( 0 ) );

    // Initialise the GridItem values.
    GridItem::TotalValues = 4;
    GridItem::Values = new unsigned int[GridItem::TotalValues];
    GridItem::Values[0] = 2;
    GridItem::Values[1] = 3;
    GridItem::Values[2] = 5;
    GridItem::Values[3] = 7;

    // Initialise the game state.
    m_pGrid = new Grid( sGridWidth, sGridHeight, *this );
    m_pTNG = new TargetNumberGenerator( m_pGrid );
    m_pGrid->SetTargetNumberGenerator( m_pTNG );
    m_CurrentNumber = 1;
    m_Time = sTimeLimitInMinutes * 60;
    m_SuperModeRemaining = 0;

	// Create the score text
	m_pScoreText = new CLabel();
	m_pScoreText->SetText("00000000");
	m_pScoreText->m_AnchorX = 1.0;
	m_pScoreText->m_AnchorY = 0.0;
	m_pScoreText->m_X = (float)IwGxGetScreenWidth() - 5;
	m_pScoreText->m_Y = 5;
	m_pScoreText->SetFont(g_pResources->getFont());
	m_pScoreText->m_Color = CColor(255,255,255,255);
    m_pScoreText->m_AlignVer = IW_2D_FONT_ALIGN_RIGHT;
	AddChild(m_pScoreText);

	// Create the time text
	m_pTimeText = new CLabel();
	m_pTimeText->SetText("00:00");
	m_pTimeText->m_AnchorX = 0.0;
	m_pTimeText->m_AnchorY = 0.0;
	m_pTimeText->m_X = 5;
	m_pTimeText->m_Y = 5;
	m_pTimeText->SetFont(g_pResources->getFont());
	m_pTimeText->m_Color = CColor(255,255,255,255);
	AddChild(m_pTimeText);

	// Create the current number text
	m_pCurrentNumberText = new CLabel();
	m_pCurrentNumberText->SetText("0");
	m_pCurrentNumberText->m_AnchorX = 0.5;
	m_pCurrentNumberText->m_AnchorY = 0.0;
	m_pCurrentNumberText->m_X = (float)IwGxGetScreenWidth() / 2;
	m_pCurrentNumberText->m_Y = 5;
	m_pCurrentNumberText->SetFont(g_pResources->getFont());
	m_pCurrentNumberText->m_Color = CColor(255,255,255,255);
	AddChild(m_pCurrentNumberText);

    // Create the pause button
    m_pPauseSprite = new CSprite();
	m_pPauseSprite->m_X = 45.0f;
	m_pPauseSprite->m_Y = 5.0f;
	m_pPauseSprite->SetImage(g_pResources->getPause());
	m_pPauseSprite->m_ScaleX = 0.4f;
	m_pPauseSprite->m_ScaleY = 0.4f;
	m_pPauseSprite->m_AnchorX = 0.0;
	m_pPauseSprite->m_AnchorY = 0.0;
    AddChild( m_pPauseSprite );

    // Create the super mode sprite
    m_pSuperModeSprite = new CSprite();
	m_pSuperModeSprite->m_X = (float)IwGxGetScreenWidth() * 0.3f;
	m_pSuperModeSprite->m_Y = 5.0f;
	m_pSuperModeSprite->SetImage(g_pResources->getSuper());
	m_pSuperModeSprite->m_ScaleX = 0.4f;
	m_pSuperModeSprite->m_ScaleY = 0.4f;
	m_pSuperModeSprite->m_AnchorX = 0.0;
	m_pSuperModeSprite->m_AnchorY = 0.0;

	// Create the target number texts
	m_pFirstTargetNumberText = new CLabel();
	m_pFirstTargetNumberText->SetText("0");
	m_pFirstTargetNumberText->m_AnchorX = 0.5;
	m_pFirstTargetNumberText->m_AnchorY = 0.5;
	m_pFirstTargetNumberText->m_X = (float)IwGxGetScreenWidth() * 0.833f;
	m_pFirstTargetNumberText->m_Y = (float)IwGxGetScreenHeight() * 0.925f;
    m_pFirstTargetNumberText->m_ScaleX *= 2.2f;
    m_pFirstTargetNumberText->m_ScaleY *= 2.2f;
	m_pFirstTargetNumberText->SetFont(g_pResources->getFont());
	m_pFirstTargetNumberText->m_Color = CColor(255,255,255,255);
	AddChild(m_pFirstTargetNumberText);

	m_pSecondTargetNumberText = new CLabel();
	m_pSecondTargetNumberText->SetText("0");
	m_pSecondTargetNumberText->m_AnchorX = 0.5;
	m_pSecondTargetNumberText->m_AnchorY = 0.5;
	m_pSecondTargetNumberText->m_X = (float)IwGxGetScreenWidth() * 0.5f;
	m_pSecondTargetNumberText->m_Y = (float)IwGxGetScreenHeight() * 0.925f;
    m_pSecondTargetNumberText->m_ScaleX *= 1.5f;
    m_pSecondTargetNumberText->m_ScaleY *= 1.5f;
	m_pSecondTargetNumberText->SetFont(g_pResources->getFont());
	m_pSecondTargetNumberText->m_Color = CColor(255,255,255,255);
	AddChild(m_pSecondTargetNumberText);
    
	m_pThirdTargetNumberText = new CLabel();
	m_pThirdTargetNumberText->SetText("0");
	m_pThirdTargetNumberText->m_AnchorX = 0.5;
	m_pThirdTargetNumberText->m_AnchorY = 0.5;
	m_pThirdTargetNumberText->m_X = (float)IwGxGetScreenWidth() * 0.167f;
	m_pThirdTargetNumberText->m_Y = (float)IwGxGetScreenHeight() * 0.925f;
    m_pSecondTargetNumberText->m_ScaleX *= 1.0f;
    m_pSecondTargetNumberText->m_ScaleY *= 1.0f;
	m_pThirdTargetNumberText->SetFont(g_pResources->getFont());
	m_pThirdTargetNumberText->m_Color = CColor(255,255,255,255);
	AddChild(m_pThirdTargetNumberText);

    m_Updated = false;
}

void GameScene::Reset()
{
	m_Time = sTimeLimitInMinutes * 60.0f;
	m_Score = 0;
    m_pGrid->Reset();
    m_pTNG->Reset( m_pGrid );
    m_CurrentNumber = 1;
    m_SuperModeRemaining = 0;
    m_Updated = false;
}

void GameScene::Update(float deltaTime, float alphaMul)
{
    // Don't update if the scene isn't active.
    if( !m_IsActive )
    {
        return;
    }

    m_Updated = true;

	Scene::Update( deltaTime, alphaMul);
    m_pGrid->Update( deltaTime );

    // Play music if it's not playing already.
    if( !Audio::IsPlaying() )
    {
        Audio::PlayMusic( "audio/in_game.mp3" );
    }

	// Update time remaining.
	m_Time -= deltaTime;
    // Leave the state if time is up.
	if( m_Time <= 0.0f )
	{
        Audio::StopMusic();
        g_pGameData->AddScore( m_Score );
        GameData::SaveGameData(g_pGameData);
        m_SceneManager.SwitchTo( GameSceneManager::keResultsState );
        return;
	}
	else
	{
        if( g_pInput->m_Pressed )
        {
            // If a shape is being touched, highlight it.
            GridItem* touchedItem = 
                    m_pGrid->GetTouchedItem( g_pInput->m_X, g_pInput->m_Y );
            if( touchedItem != NULL )
		    {
				bool highlighted = touchedItem->Toggle();
                if( highlighted ) 
                {
                    m_CurrentNumber *= touchedItem->GetValue();
                }
                else
                {
                    m_CurrentNumber /= touchedItem->GetValue();
                }
			}
            // Or if the pause button is pressed, pause the game.
            else if( m_pPauseSprite->HitTest( g_pInput->m_X, g_pInput->m_Y ) )
            {
                m_SceneManager.SwitchTo( GameSceneManager::kePauseState );
            }
		}
        // If the player has met the target, clear the highlighted items and 
        // pick a new target.
        if( m_pTNG->GetFirstTarget() == m_CurrentNumber )
        {
            float scoreMultiplier = 1.0f;
            float timeMultiplier = 1.0f;
            bool lineBonus = m_pGrid->LineBonus();
            bool sameShapeBonus = m_pGrid->SameShapeBonus();
            if( lineBonus )
            {
                scoreMultiplier *= sLineMultiplier;
            }
            if( sameShapeBonus )
            {
                scoreMultiplier *= sShapeMultiplier;
            }
            if( lineBonus && sameShapeBonus )
            {
                if( m_SuperModeRemaining == 0 )
                {
                    AddChild( m_pSuperModeSprite );
                }
                scoreMultiplier *= sSuperModeMultiplier;
                timeMultiplier *= 1.5f;
                m_SuperModeRemaining = sSuperModeTicks;
            }
            else if( m_SuperModeRemaining > 0 )
            {
                scoreMultiplier *= sSuperModeMultiplier;
                timeMultiplier *= 1.5f;
                m_SuperModeRemaining--;
                if( m_SuperModeRemaining == 0 )
                {
                    RemoveChild( m_pSuperModeSprite );
                }
            }
            m_Score += sBaseScore * scoreMultiplier;
            m_pGrid->ClearHighlightedItems();
            // Play a sound effect.
            g_pAudio->PlaySound("audio/gem_destroyed.wav");

            m_Time += sBaseTime * timeMultiplier;
            m_pTNG->ConsumeTargetAndGridItems();
            m_CurrentNumber = 1;
        }
	}
    
    UpdateHUD();
}

void GameScene::Render()
{
	Scene::Render();
}

bool GameScene::WasUpdated()
{
    return m_Updated;
}

void GameScene::UpdateHUD()
{
    Iw2DSetFont(m_pScoreText->m_Font);

	char scoreBuffer[9];
	sprintf(scoreBuffer, "%.8d", m_Score );
	m_pScoreText->SetText(scoreBuffer);
    // Add a few extra pixels to the width, because the function underestimates.
    m_pScoreText->m_W = (float)Iw2DGetStringWidth(scoreBuffer) + 5;

	int minutes, seconds;
	minutes = ( m_Time / 60 );
	seconds = ( m_Time - ( minutes * 60.0f ) );
	char timeBuffer[6];
	sprintf(timeBuffer, "%.2d:%.2d", minutes, seconds );
	m_pTimeText->SetText(timeBuffer);
    // Add a few extra pixels to the width, because the function underestimates.
    m_pTimeText->m_W = (float)Iw2DGetStringWidth(timeBuffer) + 5;

	char numberBuffer[5];
	sprintf(numberBuffer, "%d", m_CurrentNumber );
	m_pCurrentNumberText->SetText(numberBuffer);
    m_pCurrentNumberText->m_W = (float)Iw2DGetStringWidth(numberBuffer) + 5;
	sprintf(numberBuffer, "%d", m_pTNG->GetFirstTarget() );
	m_pFirstTargetNumberText->SetText(numberBuffer);
    m_pFirstTargetNumberText->m_W = (float)Iw2DGetStringWidth(numberBuffer) + 5;
	sprintf(numberBuffer, "%d", m_pTNG->GetSecondTarget() );
	m_pSecondTargetNumberText->SetText(numberBuffer);
    m_pSecondTargetNumberText->m_W = (float)Iw2DGetStringWidth(numberBuffer) + 5;
	sprintf(numberBuffer, "%d", m_pTNG->GetThirdTarget() );
	m_pThirdTargetNumberText->SetText(numberBuffer);
    m_pThirdTargetNumberText->m_W = (float)Iw2DGetStringWidth(numberBuffer) + 5;
}
