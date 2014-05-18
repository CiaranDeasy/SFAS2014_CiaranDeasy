/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GameSceneManager.h"

#include "TitleScene.h"
#include "GameScene.h"
#include "ResultsScene.h"
#include "PauseScene.h"
#include "BoardScene.h"
#include "TutorialScene.h"
#include "input.h"

using namespace SFAS2014;

//
//
// GameSceneManager class
//
//
GameSceneManager::GameSceneManager()
{
	// Create the game scenes 
	m_pScenes[keTitleState] = new TitleScene( *this );
	m_pScenes[keGameState] = new GameScene( *this );
	m_pScenes[keResultsState] = new ResultsScene( *this );
	m_pScenes[kePauseState] = new PauseScene( *this );
	m_pScenes[keBoardState] = new BoardScene( *this );
	m_pScenes[keTutorialState] = new TutorialScene( *this );

	// Set the scene names
	m_pScenes[keTitleState]->SetName( "TitleState" );
	m_pScenes[keGameState]->SetName( "GameState" );
	m_pScenes[keResultsState]->SetName( "ResultsState" );
	m_pScenes[kePauseState]->SetName( "PauseState" );
	m_pScenes[keBoardState]->SetName( "BoardState" );
	m_pScenes[keTutorialState]->SetName( "TutorialState" );

	// Add and init all the scenes
	for( int count = 0; count < keNumberOfStates; count++ )
	{
		m_pScenes[count]->Init();
		Add( m_pScenes[count] );
	}

	SwitchTo( GameSceneManager::keTitleState );
}

GameSceneManager::~GameSceneManager()
{
	// Scenes are deleted by the scene manager destructor
}

void GameSceneManager::Update(float deltaTime)
{
	SceneManager::Update( deltaTime );	
	bool pressed = g_pInput->m_Pressed;
}

void GameSceneManager::SwitchTo(GameSceneManager::State state)
{
    // If switching to the title state, reset the game state.
    if( keTitleState == state && 
            ( (GameScene*) m_pScenes[keGameState] )->WasUpdated() )
    {
        m_pScenes[keGameState]->Reset();
    }

	SceneManager::SwitchTo( m_pScenes[state] );
    g_pInput->Reset();
}

void GameSceneManager::SwitchToResultsState( unsigned int score )
{
    dynamic_cast<ResultsScene *>(m_pScenes[keResultsState])->SetScore( score );
	SceneManager::SwitchTo( m_pScenes[keResultsState] );
    g_pInput->Reset();
}


