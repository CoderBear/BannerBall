#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene->getPhysicsWorld()->setGravity(Vec2(0,0));
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // Screen Boundry
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT,3);
    
    auto edgeNode = Node::create();
    edgeNode->setPosition((visibleSize.width/2) + origin.x, (visibleSize.height/2)+origin.y);
    edgeNode->setPhysicsBody(edgeBody);
    
    this->addChild(edgeNode);
    
    // Our bouncing ball
    ball = Sprite::create("redball.png");
    ball->setPosition((visibleSize.width/2) + origin.x, (visibleSize.height/2)+origin.y);
    
    auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width/2, PhysicsMaterial(0,1,0));
    ballBody->setAngularVelocity(200);
    ballBody->setVelocity(Vec2(100, 247));
//    ballBody->setVelocityLimit(300);
    
    ballBody->setCategoryBitmask(1);
    ballBody->setContactTestBitmask(true);
    ball->setPhysicsBody(ballBody);
    
    this->addChild(ball);
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan=CC_CALLBACK_2(HelloWorld::onTouchBegan,this);
    touchListener->onTouchMoved=CC_CALLBACK_2(HelloWorld::onTouchMoved,this);
    touchListener->onTouchEnded=CC_CALLBACK_2(HelloWorld::onTouchEnded,this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("onTouchBegan x = %f, y = %f",touch->getLocation().x,touch->getLocation().y);
    
    return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("onTouchedMoved x = %f, y = %f",touch->getLocation().x,touch->getLocation().y);
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    CCLOG("onTouchedEnded x = %f, y = %f",touch->getLocation().x,touch->getLocation().y);
}