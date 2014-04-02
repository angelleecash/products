//
//  main.cpp
//  boxes
//
//  Created by chenliang on 14-3-3.
//  Copyright (c) 2014年 chenliang.info. All rights reserved.
//

#include "main.h"

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main(int argc, char** argv)
{
    IrrlichtDevice* device = createDevice(video::EDT_OPENGL, dimension2d<u32>(800, 600), 16, false, false, false, 0);
    
    if (!device) {
        return 1;
    }
    
    
    device->setWindowCaption(L"boxes");
    
    IVideoDriver* driver = device->getVideoDriver();
    ISceneManager* smgr = device->getSceneManager();
    
    IMeshSceneNode* cube = smgr->addCubeSceneNode();
    
    smgr->addCameraSceneNode(0);
    
    while (device->run()) {
        driver->beginScene();
        
        smgr->drawAll();
        
        driver->endScene();
    }
    
    return 0;
}
