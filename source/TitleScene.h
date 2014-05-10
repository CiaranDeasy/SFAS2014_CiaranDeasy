/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__TITLESCENE_H__)
#define __TITLESCENE_H__

#include "scene.h"

namespace SFAS2014
{

class GameSceneManager;

/**
 * @class TitleScene
 *
 * @brief Displays the title screen 
 *
 */
class TitleScene : public Scene
{

public:
    TitleScene( GameSceneManager& sceneManager );
    ~TitleScene();

    /**
     * @fn    virtual void TitleScene::Init();
     *
     * @brief Initialise the scene.
     */
    void    Init();

    /**
     * @fn    virtual void TitleScene::Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
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
     * @fn    virtual void TitleScene::Render();
     *
     * @brief Render the scene.
     */
    void Render();

private: 

    // Reference to the parent scene manager, for switching scenes.
    GameSceneManager& m_SceneManager;

	CSprite* m_pBackground;
    CSprite* m_pStartSprite;
    CLabel* m_pStartText;
    CSprite* m_pTutorialSprite;
    CLabel* m_pTutorialText;
    CSprite* m_pBoardSprite;
    CLabel* m_pBoardText;
    CSprite* m_pWipeSprite;
    CLabel* m_pWipeText;
};
}

#endif  // __TITLESCENE_H__


