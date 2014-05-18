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
    for( unsigned int i = 0; i < 10; i++ )
    {
        if( score > m_ScoreValues[i] )
        {
            // Move lower scores down.
            for( unsigned int j = 9; j > i; j-- )
            {
                m_ScoreValues[j] = m_ScoreValues[j-1];
                SetName( j, &m_ScoreNames[(j-1)*16] );
            }
            // Insert the new score.
            m_ScoreValues[i] = score;
            SetName( i, name );
            return;
        }
    }
}

void GameData::SetName( unsigned int index, const char* newName )
{
    for( unsigned int i = 0; i < 15; i++ )
    {
        m_ScoreNames[index*16 + i] = newName[i];
        if( '\0' == newName[i] )
        {
            return;
        }
    }
    // End with null-termination.
    m_ScoreNames[index*16 + 15] = '\0';
}