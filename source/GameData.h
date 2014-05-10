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

    void AddScore( unsigned int score );

private: 
    
    int m_Version;
    unsigned int m_ScoreValues[10];
};
}

extern SFAS2014::GameData* g_pGameData;

#endif  // __GAMEDATA_H__
