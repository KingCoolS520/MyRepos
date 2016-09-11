#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "T01TextureCache.h"
#include "T02SpriteFrame.h"
#include "T03Node.h"
#include "T04Lambada.h"
#include "T05BatchNode.h"
#include "T06RenderTexture.h"
#include "T07Action.h"
#include "T08GridAction.h"
#include "T09Animation.h"
#include "T10Spine.h"
#include "T11EventDisp.h"
#include "T12Menu.h"
#include "T13UI.h"
#include "T14TileMap.h"
#include "T15Partise.h"
#include "T16IO.h"
#include "T17Socket.h"
#include "T18Thread.h"
#include "T19Http.h"
#include "T20Box2D.h"
#include "T21Physics.h"
#include "T22RayCast.h"
#include "T23Blend.h"
#include "T24ClippingNode.h"
#include "T25Clipping.h"
#include "T26Clipping.h"
#include "T27Shader.h"
#include "T28Chess.h"
#include "T29Graph.h"
#include "T30Dijkstra.h"
USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    
    if(glview->getFrameSize().width > 1600)
    {
        // 认为用户在用手机
        // 使用手机资源
        // 设置手机资源的路径
        
       // FileUtils::getInstance()->addSearchPath("ccb");
        
        glview->setDesignResolutionSize(480*2, 320*2, ResolutionPolicy::SHOW_ALL);
    }
    else
    {
        // 认为用户在用平板
        // 使用平板资源
        // 设置平板资源的路径
      //  FileUtils::getInstance()->addSearchPath("chess");
        
        glview->setDesignResolutionSize(480*2, 320*2, ResolutionPolicy::SHOW_ALL);
    }
    
    
    
    // turn on display FPS
    director->setDisplayStats(true);
    
 //   director->setClearColor(Color4F::WHITE);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

    // create a scene. it's an autorelease object
 //   auto scene = HelloWorld::createScene();

	Layer* layer = T30Dijkstra::create();
    
    Scene* scene = Scene::createWithPhysics();
    
	scene->addChild(layer);
    
    

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
