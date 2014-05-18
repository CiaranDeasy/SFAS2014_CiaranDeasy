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
    m_Version = 2;
    for( int i = 0; i < 10; i++ )
    {
        m_ScoreValues[i] = 0;
        for( int j = 0; j < 16; j++ )
        {
            m_ScoreNames[i*16 + j] = '\0';
        }
    }
}

GameData::~GameData()
{
    
}

unsigned int GameData::GetScore( unsigned int index )
{
    return m_ScoreValues[index];
}

const char* const GameData::GetName( unsigned int index ) const
{
    return &(m_ScoreNames[index*16]);
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

void GameData::AddScore( unsigned int score, const char* name )
{
    int scoreIndex = -1;
    for( unsigned int i = 0; i < 10; i++ )
    {
        if( score > m_ScoreValues[i] )
        {
            for( unsigned int j = 9; j > i; j-- )
            {
                m_ScoreValues[j] = m_ScoreValues[j-1];
            }
            m_ScoreValues[i] = score;
            scoreIndex = i;
            break;
        }
    }
    for( unsigned int i = 0; i < 16; i++ )
    {
        m_ScoreNames[scoreIndex + i] = name[i];
        if( '\0' == name[i] )
        {
            break;
        }
    }
}
