

//
//  InterstitialAds.cpp
//
//  Created by hujie2 on 15/7/9.
//
//

#include "InterstitialAds.h"
#include "AdsManagerJni.h"
#include "ADS_TYPE.h"

InterstitialAds* InterstitialAds::m_pInstance = nullptr;



InterstitialAds::~InterstitialAds()
{
    
}

InterstitialAds* InterstitialAds::getInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new InterstitialAds();
    }
    return m_pInstance;
}

bool InterstitialAds::show()
{
    return AdsManagerJni::getInstance()->showAds(kTypeInterstitialAds);
}

void InterstitialAds::preload()
{
    AdsManagerJni::getInstance()->preLoadAds(kTypeInterstitialAds);
}

void InterstitialAds::setAutoShow(bool bIsAuto)
{
    AdsManagerJni::getInstance()->setAutoShow(kTypeInterstitialAds,bIsAuto);
}

bool InterstitialAds::isAutoShow()
{
    return AdsManagerJni::getInstance()->isAutoShow(kTypeInterstitialAds);
}

bool InterstitialAds::isPreloaded()
{
    return AdsManagerJni::getInstance()->isPreloaded(kTypeInterstitialAds);
}

void InterstitialAds::setDebugMode(bool bIsDebug)
{
	
}
