//
// Created by luotianqiang1 on 16/9/6.
//

#include "AdsManagerJni.h"
#include "BannerAds.h"
#include "CrosspromoAds.h"
#include "InterstitialAds.h"
#include "RewardedAds.h"
#include "ADS_TYPE.h"
AdsManagerJni* AdsManagerJni::instance = nullptr;

void AdsManagerJni::onRewarded(int adsType,const char* var, int amount, bool isSkip){
#if __cplusplus > 201100L
    if(RewardedAds::getInstance()->onRewarded){
        RewardedAds::getInstance()->onRewarded(var,amount,isSkip);
    }
#endif
    if(RewardedAds::getInstance()->delegate){
        RewardedAds::getInstance()->delegate->onRewarded(var,amount,isSkip);
    }
}
void AdsManagerJni::onLoadedSuccess(int adsType){
    switch (adsType) {
        case kTypeRewardedAds:
#if __cplusplus > 201100L
            if(RewardedAds::getInstance()->onRewardedLoaded){
                RewardedAds::getInstance()->onRewardedLoaded();
            }
#endif
            if(RewardedAds::getInstance()->delegate){
                RewardedAds::getInstance()->delegate->onRewardedLoaded();
            }
            break;
        case kTypeBannerAds:
#if __cplusplus > 201100L
            if(BannerAds::getInstance()->onBannerLoaded){
                BannerAds::getInstance()->onBannerLoaded();
            }
#endif
            if(BannerAds::getInstance()->delegate){
                BannerAds::getInstance()->delegate->onBannerLoaded();
            }
            break;
        case kTypeCrosspromoAds:
#if __cplusplus > 201100L
            if(CrosspromoAds::getInstance()->onCrosspromoLoaded){
                CrosspromoAds::getInstance()->onCrosspromoLoaded();
            }
#endif
            if(CrosspromoAds::getInstance()->delegate){
                CrosspromoAds::getInstance()->delegate->onCrosspromoLoaded();
            }
            break;
        case kTypeInterstitialAds:
#if __cplusplus > 201100L
            if(InterstitialAds::getInstance()->onInterstitialLoaded){
                InterstitialAds::getInstance()->onInterstitialLoaded();
            }
#endif
            if(InterstitialAds::getInstance()->delegate){
                InterstitialAds::getInstance()->delegate->onInterstitialLoaded();
            }
            break;
        default:
            break;
    }
}
void AdsManagerJni::onLoadedFail(int adsType){
    switch (adsType) {
        case kTypeRewardedAds:
#if __cplusplus > 201100L
            if(RewardedAds::getInstance()->onRewardedFailed){
                RewardedAds::getInstance()->onRewardedFailed("");
            }
#endif
            if(RewardedAds::getInstance()->delegate){
                RewardedAds::getInstance()->delegate->onRewardedFailed("");
            }
            break;
        case kTypeBannerAds:
#if __cplusplus > 201100L
            if(BannerAds::getInstance()->onBannerLoadFailed){
                BannerAds::getInstance()->onBannerLoadFailed("");
            }
#endif
            if(BannerAds::getInstance()->delegate){
                BannerAds::getInstance()->delegate->onBannerLoadFailed("");
            }
            break;
        case kTypeCrosspromoAds:
#if __cplusplus > 201100L
            if(CrosspromoAds::getInstance()->onCrosspromoFailed){
                CrosspromoAds::getInstance()->onCrosspromoFailed("");
            }
#endif
            if(CrosspromoAds::getInstance()->delegate){
                CrosspromoAds::getInstance()->delegate->onCrosspromoFailed("");
            }
            break;
        case kTypeInterstitialAds:
#if __cplusplus > 201100L
            if(InterstitialAds::getInstance()->onInterstitialFailed){
                InterstitialAds::getInstance()->onInterstitialFailed("");
            }
#endif
            if(InterstitialAds::getInstance()->delegate){
                InterstitialAds::getInstance()->delegate->onInterstitialFailed("");
            }
            break;
        default:
            break;
    }
}
void AdsManagerJni::onAdsOpened(int adsType){
    switch (adsType) {
        case kTypeRewardedAds:
#if __cplusplus > 201100L
            if(RewardedAds::getInstance()->onRewardedExpanded){
                RewardedAds::getInstance()->onRewardedExpanded();
            }
#endif
            if(RewardedAds::getInstance()->delegate){
                RewardedAds::getInstance()->delegate->onRewardedExpanded();
            }
            break;
        case kTypeBannerAds:
#if __cplusplus > 201100L
            if(BannerAds::getInstance()->onBannerExpanded){
                BannerAds::getInstance()->onBannerExpanded();
            }
#endif
            if(BannerAds::getInstance()->delegate){
                BannerAds::getInstance()->delegate->onBannerExpanded();
            }
            break;
        case kTypeCrosspromoAds:
#if __cplusplus > 201100L
            if(CrosspromoAds::getInstance()->onCrosspromoExpanded){
                CrosspromoAds::getInstance()->onCrosspromoExpanded();
            }
#endif
            if(CrosspromoAds::getInstance()->delegate){
                CrosspromoAds::getInstance()->delegate->onCrosspromoExpanded();
            }
            break;
        case kTypeInterstitialAds:
#if __cplusplus > 201100L
            if(InterstitialAds::getInstance()->onInterstitialExpanded){
                InterstitialAds::getInstance()->onInterstitialExpanded();
            }
#endif
            if(InterstitialAds::getInstance()->delegate){
                InterstitialAds::getInstance()->delegate->onInterstitialExpanded();
            }
            break;
        default:
            break;
    }
}
void AdsManagerJni::onAdsClosed(int adsType){
    switch (adsType) {
        case kTypeRewardedAds:
#if __cplusplus > 201100L
            if(RewardedAds::getInstance()->onRewardedCollapsed){
                RewardedAds::getInstance()->onRewardedCollapsed();
            }
#endif
            if(RewardedAds::getInstance()->delegate){
                RewardedAds::getInstance()->delegate->onRewardedCollapsed();
            }
            break;
        case kTypeBannerAds:
#if __cplusplus > 201100L
            if(BannerAds::getInstance()->onBannerCollapsed){
                BannerAds::getInstance()->onBannerCollapsed();
            }
#endif
            if(BannerAds::getInstance()->delegate){
                BannerAds::getInstance()->delegate->onBannerCollapsed();
            }
            break;
        case kTypeCrosspromoAds:
#if __cplusplus > 201100L
            if(CrosspromoAds::getInstance()->onCrosspromoCollapsed){
                CrosspromoAds::getInstance()->onCrosspromoCollapsed();
            }
#endif
            if(CrosspromoAds::getInstance()->delegate){
                CrosspromoAds::getInstance()->delegate->onCrosspromoCollapsed();
            }
            break;
        case kTypeInterstitialAds:
#if __cplusplus > 201100L
            if(InterstitialAds::getInstance()->onInterstitialCollapsed){
                InterstitialAds::getInstance()->onInterstitialCollapsed();
            }
#endif
            if(InterstitialAds::getInstance()->delegate){
                InterstitialAds::getInstance()->delegate->onInterstitialCollapsed();
            }
            break;
        default:
            break;
    }
}
void AdsManagerJni::onAdsClicked(int adsType){
    switch (adsType) {
        case kTypeRewardedAds:
#if __cplusplus > 201100L
            if(RewardedAds::getInstance()->onRewardedClicked){
                RewardedAds::getInstance()->onRewardedClicked();
            }
#endif
            if(RewardedAds::getInstance()->delegate){
                RewardedAds::getInstance()->delegate->onRewardedClicked();
            }
            break;
        case kTypeBannerAds:
#if __cplusplus > 201100L
            if(BannerAds::getInstance()->onBannerClicked){
                BannerAds::getInstance()->onBannerClicked();
            }
#endif
            if(BannerAds::getInstance()->delegate){
                BannerAds::getInstance()->delegate->onBannerClicked();
            }
            break;
        case kTypeCrosspromoAds:
#if __cplusplus > 201100L
            if(CrosspromoAds::getInstance()->onCrosspromoClicked){
                CrosspromoAds::getInstance()->onCrosspromoClicked();
            }
#endif
            if(CrosspromoAds::getInstance()->delegate){
                CrosspromoAds::getInstance()->delegate->onCrosspromoClicked();
            }
            break;
        case kTypeInterstitialAds:
#if __cplusplus > 201100L
            if(InterstitialAds::getInstance()->onInterstitialClicked){
                InterstitialAds::getInstance()->onInterstitialClicked();
            }
#endif
            if(InterstitialAds::getInstance()->delegate){
                InterstitialAds::getInstance()->delegate->onInterstitialClicked();
            }
            break;
        default:
            break;
    }
}

void AdsManagerJni::preLoadAds(int adType){
    if (!stSFJava)
    {
        LOGE("AdsManagerJni::preLoadAds() failed!");
        return;
    }
    JNIEnv* lEnv = JNIHelper::getJNIEnv();
    lEnv->CallVoidMethod(stSFJava, MethodPreloadAds, adType);
}
bool AdsManagerJni::showAds(int adType){
    if (!stSFJava)
    {
        LOGE("AAdsManagerJni::showAds() failed!");
        return false;
    }
    JNIEnv* lEnv = JNIHelper::getJNIEnv();
    
    jboolean ret = lEnv->CallBooleanMethod(stSFJava, MethodShowAds,adType);
    return (ret == JNI_TRUE ? true : false);
}

void AdsManagerJni::setVisible(int adType, bool visible){
    if (!stSFJava)
    {
        LOGE("AdsManagerJni::setVisible failed!");
        return;
    }
    JNIEnv* lEnv = JNIHelper::getJNIEnv();
    lEnv->CallVoidMethod(stSFJava, MethodSetVisible, adType,visible);

}
bool AdsManagerJni::isFullScreenShowing(){
    if (!stSFJava)
    {
        LOGE("AdsManagerJni::isFullScreenShowing() failed!");
        return false;
    }
    JNIEnv* lEnv = JNIHelper::getJNIEnv();
    
    jboolean ret = lEnv->CallBooleanMethod(stSFJava, MethodIsFullScreenShowing);
    return (ret == JNI_TRUE ? true : false);
    return false;
}

void AdsManagerJni::setAutoShow(int adType,bool bIsAuto){
    if (!stSFJava)
    {
        LOGE("AdsManagerJni::setAutoShow failed!");
        return;
    }
    JNIEnv* lEnv = JNIHelper::getJNIEnv();
    lEnv->CallVoidMethod(stSFJava, MethodSetAutoShow, adType,bIsAuto);
}

bool AdsManagerJni::isAutoShow(int adsTye) {
    if (!stSFJava)
    {
        LOGE("AdsManagerJni::isAutoShow() failed!");
        return false;
    }
    JNIEnv* lEnv = JNIHelper::getJNIEnv();
    
    jboolean ret = lEnv->CallBooleanMethod(stSFJava, MethodIsAutoShow);
    return (ret == JNI_TRUE ? true : false);
    return false;
}

void AdsManagerJni::remove(int adsTye){
    if (!stSFJava)
    {
        LOGE("AdsManagerJni::rewmoveAds failed!");
        return;
    }
    JNIEnv* lEnv = JNIHelper::getJNIEnv();
    lEnv->CallVoidMethod(stSFJava, MethodRemove, adsTye);

}

bool AdsManagerJni::isPreloaded(int adsTye){
    if (!stSFJava)
    {
        LOGE("AdsManagerJni::isPreloaded() failed!");
        return false;
    }
    JNIEnv* lEnv = JNIHelper::getJNIEnv();
    
    jboolean ret = lEnv->CallBooleanMethod(stSFJava, MethodIsPreloaded,adsTye);
    return (ret == JNI_TRUE ? true : false);
    return false;
}

bool AdsManagerJni::init(JNIEnv * pEnv, jobject pJava){
    ClassSF = pEnv->GetObjectClass(pJava);
    if (!ClassSF)
    {
        LOGE("get AdsManagerJni class Failed!");
        return false;
    }
    
    MethodPreloadAds = pEnv->GetMethodID(ClassSF, "preLoadAds", "(I)V");
    if (!MethodPreloadAds)
    {
        LOGE("get MethodPreloadAds class Failed!");
        return false;
    }
    MethodShowAds = pEnv->GetMethodID(ClassSF, "showAds", "(I)Z");
    if (!MethodShowAds)
    {
        LOGE("get MethodShowAds class Failed!");
        return false;
    }
    MethodSetVisible= pEnv->GetMethodID(ClassSF, "setVisible", "(IZ)V");
    if (!MethodSetVisible)
    {
        LOGE("get MethodSetVisible class Failed!");
        return false;
    }
    MethodIsFullScreenShowing = pEnv->GetMethodID(ClassSF, "isFullScreenShowing", "()Z");
    if (!MethodIsFullScreenShowing)
    {
        LOGE("get MethodIsFullScreenShowing class Failed!");
        return false;
    }
    MethodSetAutoShow = pEnv->GetMethodID(ClassSF, "setAutoShow", "(IZ)V");
    if (!MethodSetAutoShow)
    {
        LOGE("get MethodSetAutoShow class Failed!");
        return false;
    }
    MethodIsAutoShow = pEnv->GetMethodID(ClassSF, "isAutoShow", "(I)Z");
    if (!MethodIsAutoShow)
    {
        LOGE("get MethodIsAutoShow class Failed!");
        return false;
    }
    MethodRemove= pEnv->GetMethodID(ClassSF, "remove", "(I)V");
    if (!MethodRemove)
    {
        LOGE("get MethodRemove class Failed!");
        return false;
    }
    MethodIsPreloaded = pEnv->GetMethodID(ClassSF, "isPreloaded", "(I)Z");
    if (!MethodIsPreloaded)
    {
        LOGE("get MethodIsPreloaded class Failed!");
        return false;
    }
    stSFJava = JNIHelper::makeGlobalRef(pEnv, pJava);
    if (!stSFJava)
    {
        LOGE("Cache stSFJava Failed!");
        return false;
    }
    return true;
}