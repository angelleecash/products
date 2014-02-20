#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MyNode.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    
    glEnable(GL_DEPTH_TEST);
    
    pDirector->setOpenGLView(pEGLView);
    
    
	pEGLView->setDesignResolutionSize(1024, 768, kResolutionNoBorder);
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 30.0);

    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene();

    /*
    CCSprite* imageSprite = CCSprite::create("herthstone.jpg");
    imageSprite->cocos2d::CCNode::setPosition(pEGLView->getDesignResolutionSize().width/2, pEGLView->getDesignResolutionSize().height/2);
    pScene->addChild(imageSprite);
    imageSprite->setAnchorPoint(CCPoint(0.5,0.5));
     */
    //imageSprite->setAnchorPoint(CCPoint(0.,0.));
    
    //MyNode* myNode = new MyNode(pEGLView->getDesignResolutionSize().width/2, 0, pEGLView->getViewPortRect().size.width, pEGLView->getViewPortRect().size.height);
    CCPoint size(240, 320);
    /*
    MyNode* myNode = new MyNode(pEGLView->getViewPortRect().size.width/2,
                                pEGLView->getViewPortRect().size.height/2,
                                size.x,
                                size.y);
    */
    MyNode* myNode = new MyNode(pEGLView->getDesignResolutionSize().width/2,
                                pEGLView->getDesignResolutionSize().height/2 - 200,
                                size.x,
                                size.y);
    
    //MyNode* myNode = new MyNode(0, 0, pEGLView->getDesignResolutionSize().width, pEGLView->getDesignResolutionSize().height);
    //MyNode* myNode = new MyNode(0, 0 , pEGLView->getVisibleSize().width, pEGLView->getVisibleSize().height);
    //myNode->setPosition(CCPoint(0, 0));
    myNode->setAnchorPoint(CCPoint(0.5, 0.0));
    
    pScene->addChild(myNode);
    
    //myNode->setAnchorPoint(CCPoint(.5f, .5f));
    //myNode->setPosition(pEGLView->getDesignResolutionSize().width/2, 0);
    
    
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
