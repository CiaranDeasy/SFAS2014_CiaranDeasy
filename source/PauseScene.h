/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__PAUSESCENE_H__)
#define __PAUSESCENE_H__

#include "scene.h"

namespace SFAS2014
{

class GameSceneManager;

/**
 * @class PauseScene
 *
 * @brief Displays the game's paused state.
 *
 */
class PauseScene : public Scene
{

public:
    PauseScene( GameSceneManager& sceneManager );
    ~PauseScene();

    /**
     * @fn    virtual void PauseScene::Init();
     *
     * @brief Initialise the scene.
     */
    void    Init();

    /**
     * @fn    virtual void PauseScene::Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
     *
     * @brief Updates the scene.
     *
     * @param deltaTime   Number of seconds that has passed since Update() was last called.
     * @param alphaMul    The alpha value being passed down to this node. Default value is 1.
     */
	void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    /**
     * @fn    virtual void PauseScene::Render();
     *
     * @brief Render the scene.
     */
    void Render();

private: 

    // Reference to the parent scene manager, for switching scenes.
    GameSceneManager& m_SceneManager;

    CSprite* m_pResumeSprite;
    CLabel* m_pResumeText;
};
}

#endif  // __PAUSESCENE_H__


