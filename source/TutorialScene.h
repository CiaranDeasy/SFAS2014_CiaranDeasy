/*
 * (C) 2014 Search for a Star
 * 
 */

#if !defined(__TUTORIALSCENE_H__)
#define __TUTORIALSCENE_H__

#include "scene.h"

namespace SFAS2014
{

class GameSceneManager;

/**
 * @class TutorialScene
 *
 * @brief Displays instructions for playing the game.
 *
 */
class TutorialScene : public Scene
{

public:
    TutorialScene( GameSceneManager& sceneManager );
    ~TutorialScene();

    /**
     * @fn    virtual void TutorialScene::Init();
     *
     * @brief Initialise the scene.
     */
    void    Init();

    /**
     * @fn    virtual void TutorialScene::Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
     *
     * @brief Updates the scene.
     *
     * @param deltaTime   Number of seconds that has passed since Update() was last called.
     * @param alphaMul    The alpha value being passed down to this node. Default value is 1.
     */
    void Update(float deltaTime = 0.0f, float alphaMul = 1.0f);

    /**
     * @fn    virtual void TutorialScene::Render();
     *
     * @brief Render the scene.
     */
    void Render();

private: 

    enum Page
    {
        kePage0 = 0,
        kePage1,
        kePage2,
        kePage3,
        kePage4,
        kePage5,

        keNumberOfPages,
    };

    // Reference to the parent scene manager, for switching scenes.
    GameSceneManager& m_SceneManager;
    
    CSprite* m_pButtonSprite;
    CLabel* m_pButtonLabel;

    CSprite* m_pPages[keNumberOfPages];
    Page m_ActivePage;

    // Advances to the desired page of the tutorial.
    void GoToPage( Page page );

};
}

#endif  // __TUTORIALSCENE_H__


