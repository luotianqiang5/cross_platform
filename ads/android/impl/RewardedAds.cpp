

//
//  RewardedAds.cpp
//
//  Created by hujie2 on 15/7/9.
//
//

#include "RewardedAds.h"
#include "AdsManagerJni.h"
#include "ADS_TYPE.h"
RewardedAds* RewardedAds::m_pInstance = nullptr;



RewardedAds::~RewardedAds()
{
    
}

RewardedAds* RewardedAds::getInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new RewardedAds();
    }
    return m_pInstance;
}

bool RewardedAds::show()
{
    return AdsManagerJni::getInstance()->showAds(kTypeRewardedAds);
}

void RewardedAds::preload()
{
    AdsManagerJni::getInstance()->preLoadAds(kTypeRewardedAds);
}

void RewardedAds::setAutoShow(bool bIsAuto)
{
    AdsManagerJni::getInstance()->setAutoShow(kTypeRewardedAds,bIsAuto);
}

bool RewardedAds::isAutoShow()
{
    return AdsManagerJni::getInstance()->isAutoShow(kTypeRewardedAds);
}

bool RewardedAds::isPreloaded()
{
    return AdsManagerJni::getInstance()->isPreloaded(kTypeRewardedAds);
}

void RewardedAds::setDebugMode(bool bIsDebug)
{
	
}
