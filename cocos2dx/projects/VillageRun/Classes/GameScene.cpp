#include "GameScene.h"

bool GameScene::init() {
	bool bRet = false;

	do {
		CC_BREAK_IF(!Scene::initWithPhysics());

		//getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		getPhysicsWorld()->setGravity(Vec2(0, -98.0f));
        getPhysicsWorld()->setSpeed(6.0f);

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/heroSheet.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/spriteSheet.plist");

		Size wsize = Director::getInstance()->getWinSize();
		Node *node = Node::create();
		node->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		node->setPosition(wsize.width/2, wsize.height/2);
		PhysicsBody *body = PhysicsBody::createEdgeBox(wsize, PHYSICSSHAPE_MATERIAL_DEFAULT, 3);
		node->setPhysicsBody(body);
		//addChild(node);

		mGameLayer = GameLayer::create();
		addChild(mGameLayer, 0, "gamelayer");

		bRet = true;
	} while(0);

	return bRet;
}
