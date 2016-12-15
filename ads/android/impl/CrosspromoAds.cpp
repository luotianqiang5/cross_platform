

//
//  CrosspromoAds.cpp
//
//  Created by hujie2 on 15/7/9.
//
//

#include "CrosspromoAds.h"
#include "AdsManagerJni.h"
#include "ADS_TYPE.h"

CrosspromoAds* CrosspromoAds::m_pInstance = nullptr;



CrosspromoAds::~CrosspromoAds()
{
    
}

CrosspromoAds* CrosspromoAds::getInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new CrosspromoAds();
    }
    return m_pInstance;
}

bool CrosspromoAds::show()
{
    return AdsManagerJni::getInstance()->showAds(kTypeCrosspromoAds);
}

void CrosspromoAds::preload()
{
    AdsManagerJni::getInstance()->preLoadAds(kTypeCrosspromoAds);
}

void CrosspromoAds::setAutoShow(bool bIsAuto)
{
    AdsManagerJni::getInstance()->setAutoShow(kTypeCrosspromoAds,bIsAuto);
}

bool CrosspromoAds::isAutoShow()
{
    return AdsManagerJni::getInstance()->isAutoShow(kTypeCrosspromoAds);
}

bool CrosspromoAds::isPreloaded()
{
    return AdsManagerJni::getInstance()->isPreloaded(kTypeCrosspromoAds);
}

void CrosspromoAds::setDebugMode(bool bIsDebug)
{
	
}
