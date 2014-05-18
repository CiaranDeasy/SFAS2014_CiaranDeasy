/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__RESULTSSCENE_H__)
#define __RESULTSSCENE_H__

#include "scene.h"

namespace SFAS2014
{

class GameSceneManager;

/**
 * @class ResultsScene
 *
 * @brief Displays the results of the game
 *
 */
class ResultsScene : public Scene
{

public:
    ResultsScene( GameSceneManager& sceneManager );
    ~ResultsScene();

    /**
     * @fn    virtual void ResultsScene::Init();
     *
     * @brief Initialise the scene.
     */
    void    Init();

    /**
     * @fn    virtual void ResultsScene::Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
     *
     * @brief Update the scene.
     *
     * @brief Updates this scene
     *
     * @param deltaTime   Number of seconds that has passed since Update() was last called.
     * @param alphaMul    The alpha value being passed down to this node. Default value is 1.
     */
    void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    /**
     * @fn    virtual void ResultsScene::Render();
     *
     * @brief Render the scene.
     */
    void Render();

    /**
     * @fn    void ResultsScene::SetScore( unsigned int score );
     *
     * @brief Sets the score to be displayed.
     */
    void SetScore( unsigned int score );

private: 

    // Reference to the parent scene manager, for switching scenes.
    GameSceneManager& m_SceneManager;
    
	CSprite* m_Background;
    CLabel* m_GameOver;
    CLabel* m_TapContinue;

    // The last score achieved.
    unsigned int m_Score;
    const char* m_NameEntered;
};
}

#endif  // __RESULTSSCENE_H__


