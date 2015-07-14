#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    cocos2d::Sprite *ball;
    
    void touchEvent( Ref *sender, ui::Widget::TouchEventType type);
    
private:
    cocos2d::PhysicsWorld *gameWorld;
    void SetPhysicsWorld(cocos2d::PhysicsWorld *world) {gameWorld = world;}
};

#endif // __HELLOWORLD_SCENE_H__
