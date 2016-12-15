//
//  SSCNativeAds.cpp
//
//  Created by hujie2 on 15/7/9.
//
//

#include "SSCNativeAds.h"
#include "AdsManagerJni.h"
#include "ADS_TYPE.h"
#include <iostream>

SSCNativeAds* SSCNativeAds::m_pInstance = nullptr;



SSCNativeAds::~SSCNativeAds()
{

}

SSCNativeAds* SSCNativeAds::getInstance()
{
    if (!m_pInstance)
    {
        m_pInstance = new SSCNativeAds();
    }
    return m_pInstance;
}

void SSCNativeAds::show()
{
    AdsManagerJni::getInstance()->showAds(kTypeNativeAds);
}

void SSCNativeAds::preload()
{
    
//    cout<<"ssssssssssssssssss";
    std::cout<<"SSCNativeAds"<<std::endl;
    AdsManagerJni::getInstance()->preLoadAds(kTypeNativeAds);
}

void SSCNativeAds::setAutoShow(bool bIsAuto)
{
    AdsManagerJni::getInstance()->setAutoShow(kTypeNativeAds, bIsAuto);
}

bool SSCNativeAds::isAutoShow()
{
    return AdsManagerJni::getInstance()->isAutoShow(kTypeNativeAds);
}

void SSCNativeAds::remove()
{
	AdsManagerJni::getInstance()->remove(kTypeNativeAds);
}

void SSCNativeAds::setVisible(bool isVisibility)
{
	AdsManagerJni::getInstance()->setVisible(kTypeNativeAds,isVisibility);
}

void SSCNativeAds::setDebugMode(bool bIsDebug)
{
	
}

void SSCNativeAds::setLayout(NativeAdsLayoutType kType)
{
	
}
