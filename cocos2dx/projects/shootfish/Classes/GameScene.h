#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "GameLayer.h"
#include "ScoreLayer.h"

class GameScene : public cocos2d::Scene
{
public:
    virtual bool init();
    CREATE_FUNC(GameScene);

private:
    BackgroundLayer *mBackgroundLayer;
    GameLayer *mGameLayer;
    ScoreLayer *mScoreLayer;

    void onEnter() override;
    void onExit() override;
};

#endif
