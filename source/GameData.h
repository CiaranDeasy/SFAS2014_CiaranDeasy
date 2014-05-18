/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__GAMEDATA_H__)
#define __GAMEDATA_H__

namespace SFAS2014
{

/**
 * @class GameData
 *
 * @brief Object to be read from and written to secure storage.
 *        Contains leaderboard data.
 *
 */
class GameData
{

public:	
    
    static GameData* LoadGameData();
    static void SaveGameData( GameData* data );

    GameData();
    ~GameData();

    unsigned int GetScore( unsigned int index );
    const char* const GetName( unsigned int index ) const;

    void AddScore( unsigned int score, const char* name );

private: 
    
    int m_Version;
    unsigned int m_ScoreValues[10];
    char m_ScoreNames[160];

    // Sets the name at the given index of the scoreboard.
    void SetName( unsigned int index, const char* newName );
};
}

extern SFAS2014::GameData* g_pGameData;

#endif  // __GAMEDATA_H__
