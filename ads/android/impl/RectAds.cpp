//
//  RectAds.cpp
//  Ads_Framework
//
//  Created by hujie2 on 15/7/10.
//
//

#include "RectAds.h"

//
//  RectAds.cpp
//
//  Created by hujie2 on 15/7/9.
//
//

#include "RectAds.h"
#include "AdsManagerJni.h"
#include "ADS_TYPE.h"

RectAds* RectAds::m_pInstance = nullptr;



RectAds::~RectAds()
{
    
}

RectAds* RectAds::getInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new RectAds();
    }
    return m_pInstance;
}

void RectAds::show()
{
    AdsManagerJni::getInstance()->showAds(kTypeRectAds);
}

void RectAds::preload()
{
    AdsManagerJni::getInstance()->preLoadAds(kTypeRectAds);
}

void RectAds::setAutoShow(bool bIsAuto)
{
    AdsManagerJni::getInstance()->setAutoShow(kTypeRectAds,bIsAuto);
}

bool RectAds::isAutoShow()
{
    return AdsManagerJni::getInstance()->isAutoShow(kTypeRectAds);
}

void RectAds::remove()
{
    AdsManagerJni::getInstance()->remove(kTypeRectAds);
}

void RectAds::setVisible(bool isVisibility)
{
    AdsManagerJni::getInstance()->setVisible(kTypeRectAds,isVisibility);
}

void RectAds::setDebugMode(bool bIsDebug)
{
	
}
