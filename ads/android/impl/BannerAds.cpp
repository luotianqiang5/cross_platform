//
//  BannerAds.cpp
//
//  Created by hujie2 on 15/7/9.
//
//

#include "BannerAds.h"
#include "AdsManagerJni.h"
#include "ADS_TYPE.h"

BannerAds* BannerAds::m_pInstance = nullptr;



BannerAds::~BannerAds()
{
    
}

BannerAds* BannerAds::getInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new BannerAds();
    }
    return m_pInstance;
}

void BannerAds::show()
{
    AdsManagerJni::getInstance()->showAds(kTypeBannerAds);
}

void BannerAds::preload()
{
    AdsManagerJni::getInstance()->preLoadAds(kTypeBannerAds);
}

void BannerAds::setAutoShow(bool bIsAuto)
{
    AdsManagerJni::getInstance()->setAutoShow(kTypeBannerAds,bIsAuto);
}

bool BannerAds::isAutoShow()
{
    return AdsManagerJni::getInstance()->isAutoShow(kTypeBannerAds);
}

void BannerAds::remove()
{
    AdsManagerJni::getInstance()->remove(kTypeBannerAds);
}

void BannerAds::setVisible(bool isVisibility)
{
    AdsManagerJni::getInstance()->setVisible(kTypeBannerAds,isVisibility);
}

void BannerAds::setDebugMode(bool bIsDebug)
{
	
}

void BannerAds::setLayout(LAYOUT_TYPE kType)
{
	
}
