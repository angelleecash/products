//
//  _096AppDelegate.cpp
//  4096
//
//  Created by chenliang on 14-4-2.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"

#include "HelloWorldScene.h"

USING_NS_CC;


AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    
    CCEGLView* view = CCEGLView::sharedOpenGLView();
    //view->setDesignResolutionSize(600, 800, kResolutionFixedWidth);
    pDirector->setOpenGLView(view);
    
    

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    view->setDesignResolutionSize(768, 1024, kResolutionFixedWidth);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
//    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
//    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
//    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
//    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
