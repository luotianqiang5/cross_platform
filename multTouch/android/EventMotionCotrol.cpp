//
//  EventMotionCotrll.cpp
//  Milkshake
//
//  Created by luotianqiang1 on 4/15/15.
//
//

#include "EventMotionCotrol.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#define CLASS_NAME "com/common/lqview/LQ_glView"
using namespace cocos2d;

void EventMotionCotrol::setMultTouch(bool flag){
    JniMethodInfo t;
    if(JniHelper::getStaticMethodInfo(t, CLASS_NAME, "setMultTouch", "(Z)V"))
    	t.env->CallStaticVoidMethod(t.classID, t.methodID,flag);
    else
    	log("not fount======");
}
