#include "HelloWorldScene.h"
#include "SonarFrameworks.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

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
    
    // Our Ball Button
    Button *ballButton = Button::create("redball.png","redball.png");
    ballButton->setPosition(Vec2((visibleSize.width/2) + origin.x, (visibleSize.height/2)+origin.y));
    
    auto ballBody = PhysicsBody::createCircle(ballButton->getContentSize().width/2, PhysicsMaterial(0,1,0));
    ballBody->setVelocity(Vec2(256, 256));
//    ballBody->setVelocityLimit(300);
    ballBody->setCategoryBitmask(1);
    ballBody->setContactTestBitmask(true);
    
    ballButton->setPhysicsBody(ballBody);
    this->addChild(ballButton);
    ballButton->addTouchEventListener(CC_CALLBACK_2(HelloWorld::touchEvent, this));
    
    SonarCocosHelper::IOS::Setup();
    SonarCocosHelper::Mopub::showBannerAd();
    
    return true;
}

void HelloWorld::touchEvent( Ref *sender, ui::Widget::TouchEventType type){
    switch (type) {
        case Widget::TouchEventType::BEGAN:
            log("Touch began");
            SonarCocosHelper::Mopub::refreshAd();
            break;
        case Widget::TouchEventType::MOVED:
            log("Touch moved");
            break;
        case Widget::TouchEventType::ENDED:
            log("Touch ended");
            break;
        case Widget::TouchEventType::CANCELED:
            log("Touch cancelled");
            break;

        default:
            break;
    }
}