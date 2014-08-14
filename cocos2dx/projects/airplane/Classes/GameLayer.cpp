#include "GameLayer.h"
#include "UFOSprite.h"

using namespace CocosDenshion;

GameLayer *GameLayer::s_gameLayer = nullptr;

GameLayer *GameLayer::getInstance() {
    if (!s_gameLayer) {
        s_gameLayer = new GameLayer();
        if (s_gameLayer)
            s_gameLayer->init();
    }
    return s_gameLayer;
}

void GameLayer::onEnter() {
    CCLog("GameLayer::onEnter()\n");
    restart();
    Layer::onEnter();
}

void GameLayer::restart() {
    stopAllActions();
    unscheduleAllSelectors();
    removeAllChildren();

    if (mPlaneSprite) {
        mPlaneSprite->retain();
        mPlaneSprite->release();
    }

    mPlaneSprite = PlaneSprite::create();
    addChild(mPlaneSprite, 0, "plane");

    schedule(schedule_selector(GameLayer::repeat), 0.6, kRepeatForever, 1);
    schedule(schedule_selector(GameLayer::showUFO), 40, kRepeatForever, 15);
    scheduleUpdate();

    mBomb = 0;

    mBombSprite = Sprite::createWithSpriteFrameName("bomb.png");
    mBombSprite->setAnchorPoint(Point(0, 0));
    mBombSprite->setPosition(5, 5);
    addChild(mBombSprite);

    char buf[8];
    snprintf(buf, sizeof(buf), "X%d", mBomb);
    mBombLabel = Label::createWithBMFont("fonts/score.fnt", buf);
    mBombLabel->setAnchorPoint(Vec2(0, 0));
    Size s = mBombSprite->getContentSize();
    mBombLabel->setPosition(s.width+5, 15);
    addChild(mBombLabel);

    updateBomb();

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch *touch, Event *event) -> bool{
        Point touchPos = touch->getLocation();
        Rect bombRect = mBombSprite->getBoundingBox();
        if (bombRect.containsPoint(touchPos)) {
            if (mBomb > 0) {
                mBomb--;
                bombAllEnemys();
                updateBomb();
                SimpleAudioEngine::getInstance()->playEffect("sound/use_bomb.mp3", false);
            }
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()
        ->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameLayer::updateBomb() {
    char buf[8];
    snprintf(buf, sizeof(buf), "X%d", mBomb);
    mBombLabel->setString(buf);

    if (mBomb > 0) {
        mBombSprite->setVisible(true);
        mBombLabel->setVisible(true);
    } else {
        mBombSprite->setVisible(false);
        mBombLabel->setVisible(false);
    }
}

void GameLayer::repeat(float dt) {
    EnemySprite *enemy;
    int score = ScoreLayer::getInstance()->getCurrentScore();

    enemy = EnemySprite::create(1.0 + score/500000.0 * 0.5);

    addChild(enemy, 0, "enemy");
}

void GameLayer::showUFO(float dt) {
    CCLog("GameLayer::showUFO()\n");
    UFOSprite *ufo = UFOSprite::create(CCRANDOM_0_1() > 0.5 ? 1 : 2);
    addChild(ufo, 0, "ufo");
}

void GameLayer::bombAllEnemys() {
    std::vector<Node*> enemyChilds = utils::findChildren(*this, "enemy");
    for (auto& enemyChild : enemyChilds) {
        if (((EnemySprite *)enemyChild)->isAlive()) {
            ((EnemySprite *)enemyChild)->blowUp();
        }
    }
}

void GameLayer::update(float fDelta) {
    Rect planeBox;
    Rect enemyBox;
    Rect bulletBox;
    Rect UFOBox;

    std::vector<Node*> enemyChilds = utils::findChildren(*this, "enemy");
    std::vector<Node*> bulletChilds = utils::findChildren(*this, "bullet");
    std::vector<Node*> UFOChilds = utils::findChildren(*this, "ufo");

    if (mPlaneSprite) {
        planeBox = mPlaneSprite->getBoundingBox();
        planeBox.origin += Vec2(planeBox.size.width/3, planeBox.size.height/3);
        planeBox.size = planeBox.size * (1.0/3);

        for (auto& UFOChild : UFOChilds) {
            UFOBox = UFOChild->getBoundingBox();

            if (planeBox.intersectsRect(UFOBox)) {
                if (((UFOSprite *)UFOChild)->getType() == 1) {
                    mPlaneSprite->superPower();
                } else {
                    mBomb++;
                    updateBomb();
                    SimpleAudioEngine::getInstance()->playEffect("sound/get_bomb.mp3", false);
                }
                removeChild(UFOChild);
            }
        }

        for (auto& enemyChild : enemyChilds) {

            if (!((EnemySprite *)enemyChild)->isAlive())
                continue;

            enemyBox = enemyChild->getBoundingBox();

            for (auto& bulletChild : bulletChilds) {
                bulletBox = bulletChild->getBoundingBox();

                if (enemyBox.intersectsRect(bulletBox)) {
                    ((BulletSprite *)bulletChild)->blowUp();
                    ((EnemySprite *)enemyChild)->hit();
                    break;
                }
            }

            if (!((EnemySprite *)enemyChild)->isAlive()) {
                ((EnemySprite *)enemyChild)->blowUp();
                continue;
            }

            if (planeBox.intersectsRect(enemyBox)) {
                mPlaneSprite->blowUp();
                mPlaneSprite = NULL;
                ((EnemySprite *)enemyChild)->blowUp();

                gameover();

                break;
            }
        }
    }
}

void GameLayer::gameover() {
    DelayTime *delay = DelayTime::create(1);
    CallFunc *callback = CallFunc::create([]() {
        TransitionMoveInT *tran = TransitionMoveInT::create(1, GameOverScene::create());
        Director::getInstance()->replaceScene(tran);
    });
    Sequence *seq = Sequence::create(delay, callback, nullptr);
    runAction(seq);
}
