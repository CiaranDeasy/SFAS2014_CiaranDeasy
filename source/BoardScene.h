/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__BOARDSCENE_H__)
#define __BOARDSCENE_H__

#include "scene.h"

namespace SFAS2014
{

class GameSceneManager;

/**
 * @class BoardScene
 *
 * @brief Displays the leaderboards
 *
 */
class BoardScene : public Scene
{

public:
    BoardScene( GameSceneManager& sceneManager );
    ~BoardScene();

    /**
     * @fn    virtual void BoardScene::Init();
     *
     * @brief Initialise the scene.
     */
    void    Init();

    /**
     * @fn    virtual void BoardScene::Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
     *
     * @brief Updates the scene.
     *
     * @param deltaTime   Number of seconds that has passed since Update() was last called.
     * @param alphaMul    The alpha value being passed down to this node. Default value is 1.
     */
    void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    /**
     * @fn    virtual void BoardScene::Render();
     *
     * @brief Render the scene.
     */
    void Render();

private: 

    // Reference to the parent scene manager, for switching scenes.
    GameSceneManager& m_SceneManager;

    CLabel* m_pTitle;
    CLabel* m_pScoreValues[10];
    CLabel* m_pScoreNames[10];

};
}

#endif  // __BOARDSCENE_H__


