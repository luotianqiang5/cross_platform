//
// Created by luotianqiang1 on 16/9/6.
//

#ifndef ADS_AdsManagerJni_H
#define ADS_AdsManagerJni_H
#include "JNIHelper.h"
#include <string>
using namespace std;
class AdsManagerJni {
private:
    AdsManagerJni(): ClassSF(0),
     stSFJava(0),
     MethodPreloadAds(0),
     MethodShowAds(0),
     MethodSetVisible(0),
     MethodIsFullScreenShowing(0),
     MethodSetAutoShow(0),
     MethodIsAutoShow(0),
     MethodRemove(0),
     MethodIsPreloaded(0)
    {
    }
    static AdsManagerJni* instance;
public:
    static AdsManagerJni* getInstance(){
        if(instance == nullptr)
            instance = new AdsManagerJni();
        return instance;
    }

     void onRewarded(int adsType,const char* var, int amount, bool isSkip);
     void onLoadedSuccess(int adsType);
     void onLoadedFail(int adsType);
     void onAdsOpened(int adsType);
     void onAdsClosed(int adsType);
     void onAdsClicked(int adsType);

     void preLoadAds(int adType);
     bool showAds(int adType);
     void setVisible(int adType, bool visible);
     bool isFullScreenShowing();
     void setAutoShow(int adType,bool bIsAuto);
    bool isAutoShow(int adsTye);
     void remove(int adsTye);
    bool isPreloaded(int adsTye);
    
    bool init(JNIEnv * pEnv, jobject pJava);
private:
    // Cached Classes.
    jclass ClassSF;
    // Cached java object
    jobject stSFJava;
    // Cached active Methods.
    jmethodID MethodPreloadAds;
    jmethodID MethodShowAds;
    jmethodID MethodSetVisible;
    jmethodID MethodIsFullScreenShowing;
    jmethodID MethodSetAutoShow;
    jmethodID MethodIsAutoShow;
    jmethodID MethodRemove;
    jmethodID MethodIsPreloaded;
};

#endif //ADS_DEMO_ADSMANAGER_H
