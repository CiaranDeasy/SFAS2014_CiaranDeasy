/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__GAMESCENE_H__)
#define __GAMESCENE_H__

#include "scene.h"

namespace SFAS2014
{
	
class GridItem;
class Grid;
class GameSceneManager;
class TargetNumberGenerator;

/**
 * @class GameScene
 *
 * @brief Displays and updates the game
 *
 */
class GameScene : public Scene
{

public:
    GameScene( GameSceneManager& sceneManager );
    ~GameScene();

    /**
     * @fn    void GameScene::Init();
     *
     * @brief Initialise the scene.
     */
    void    Init();

    /**
     * @fn    void GameScene::Reset();
     *
     * @brief Resets the scene.
     */
    void    Reset();

    /**
     * @fn    virtual void GameScene::Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
     *
     * @brief Updates the scene.
     *
     * @param deltaTime   Number of seconds that has passed since Update() was last called.
     * @param alphaMul    The alpha value being passed down to this node. Default value is 1.
     */
    void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    /**
     * @fn    virtual void GameScene::Render();
     *
     * @brief Render the scene.
     */
    void Render();

    /**
     * @fn    bool GameScene::WasUpdated();
     *
     * @brief Returns true if Update() was called since the GameScene was last reset.
     */
    bool WasUpdated();

private: 
    
    static const int sGridWidth = 4;
    static const int sGridHeight = 6;
    static const int sBaseScore = 10;
    static const int sBaseTime = 5;

    static const float sTimeLimitInMinutes;
    // Bonus score multipliers.
    static const float sLineMultiplier;
    static const float sShapeMultiplier;
    static const float sSuperModeMultiplier;

    // The number of times the award for super bonus is given.
    static const int sSuperModeTicks = 5;

    // Reference to the parent scene manager, for switching scenes.
    GameSceneManager& m_SceneManager;
    
    Grid* m_pGrid;

	CLabel* m_pScoreText;
	CLabel* m_pTimeText;
    CLabel* m_pCurrentNumberText;
	CLabel* m_pFirstTargetNumberText;
	CLabel* m_pSecondTargetNumberText;
	CLabel* m_pThirdTargetNumberText;
    CSprite* m_pPauseSprite;
    CSprite* m_pSuperModeSprite;

	float m_Time;
	int m_Score;
    int m_SuperModeRemaining;

    // Indicates whether the game scene has been active since the last reset.
    bool m_Updated;

    unsigned int m_CurrentNumber;
    TargetNumberGenerator* m_pTNG;

    // Updates the content of the strings in the HUD.
    void UpdateHUD();
};
}

#endif  // __GAMESCENE_H__


