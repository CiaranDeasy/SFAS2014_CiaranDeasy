/*
 * (C) 2014 Search for a Star
 * 
 */

#include "GameData.h"
#include <malloc.h>
#include "s3eSecureStorage.h"

using namespace SFAS2014;

GameData* g_pGameData = NULL;

//
//
// GameData class
//
//
GameData::GameData()
{
    m_Version = 1;
    for( int i = 0; i < 10; i++ )
    {
        m_ScoreValues[i] = 0;
    }
}

GameData::~GameData()
{
    
}

unsigned int GameData::GetScore( unsigned int index )
{
    return m_ScoreValues[index];
}

GameData* GameData::LoadGameData()
{
    void* data = malloc( sizeof( GameData ) );

    if( S3E_RESULT_SUCCESS == s3eSecureStorageGet( data, sizeof( GameData ) ) )
    {
        return (GameData*) data;
    }
    else
    {
        free( data );
        return new GameData();
    }
}

void GameData::SaveGameData( GameData* data )
{
    s3eSecureStoragePut( data, sizeof( GameData ) );
}

void GameData::AddScore( unsigned int score )
{
    for( unsigned int i = 0; i < 10; i++ )
    {
        if( score > m_ScoreValues[i] )
        {
            for( unsigned int j = 9; j > i; j-- )
            {
                m_ScoreValues[j] = m_ScoreValues[j-1];
            }
            m_ScoreValues[i] = score;
            break;
        }
    }
}
