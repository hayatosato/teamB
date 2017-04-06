//
//  MultiResolution.h
//  OreTobe
//
//  Created by Furukawa on 2014/12/23.
//
//

#ifndef CrossProject007_MultiResolution_h
#define CrossProject007_MultiResolution_h

#include "cocos2d.h"

static cocos2d::Size designResolutionSize = cocos2d::Size(1080, 1920);//iphone6+
//static cocos2d::Size designResolutionSize = cocos2d::Size(1334, 750);//iphone6
//static cocos2d::Size designResolutionSize = cocos2d::Size(1536, 2048);


static cocos2d::Vec2 visibleCenter = cocos2d::Vec2(designResolutionSize.width/2,
                                                   designResolutionSize.height/2);

#endif
