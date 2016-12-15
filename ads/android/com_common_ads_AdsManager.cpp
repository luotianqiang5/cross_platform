//
// Created by luotianqiang1 on 16/9/6.
//

#include "com_common_ads_AdsManager.h"
#include "AdsManagerJni.h"

JNIEXPORT void JNICALL Java_com_common_ads_AdsManager_init
(JNIEnv *jniEnv, jobject jobject1){
    AdsManagerJni::getInstance()->init(jniEnv,jobject1);
}

/*
 * Class:     com_common_ads_AdsManager
 * Method:    onRewarded
 * Signature: (ILjava/lang/String;IZ)V
 */
JNIEXPORT void JNICALL Java_com_common_ads_AdsManager_onRewarded
        (JNIEnv * jniEnv, jobject jobject1, jint type, jstring var, jint amount, jboolean isSkip){
        const char *str = jniEnv->GetStringUTFChars(var, 0);
        AdsManagerJni::getInstance()->onRewarded(type,str,amount,isSkip);
        jniEnv->ReleaseStringUTFChars(var, str);
}

/*
 * Class:     com_common_ads_AdsManager
 * Method:    onLoadedSuccess
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_common_ads_AdsManager_onLoadedSuccess
        (JNIEnv * jniEnv, jobject jobject1, jint type){
        AdsManagerJni::getInstance()->onLoadedSuccess(type);
}

/*
 * Class:     com_common_ads_AdsManager
 * Method:    onLoadedFail
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_common_ads_AdsManager_onLoadedFail
        (JNIEnv * jniEnv, jobject jobject1, jint type){
        AdsManagerJni::getInstance()->onLoadedFail(type);
}

/*
 * Class:     com_common_ads_AdsManager
 * Method:    onAdsOpened
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_common_ads_AdsManager_onAdsOpened
        (JNIEnv * jniEnv, jobject jobject1, jint type){
        AdsManagerJni::getInstance()->onAdsOpened(type);
}

/*
 * Class:     com_common_ads_AdsManager
 * Method:    onAdsClosed
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_common_ads_AdsManager_onAdsClosed
        (JNIEnv * jniEnv, jobject jobject1, jint type){
        AdsManagerJni::getInstance()->onAdsClosed(type);
}

/*
 * Class:     com_common_ads_AdsManager
 * Method:    onAdsClicked
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_common_ads_AdsManager_onAdsClicked
        (JNIEnv * jniEnv, jobject jobject1, jint type){
        AdsManagerJni::getInstance()->onAdsClicked(type);
}

/*
 * Class:     com_common_ads_AdsManager
 * Method:    onOtherEvent
 * Signature: (ILjava/lang/String;[Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_com_common_ads_AdsManager_onOtherEvent
        (JNIEnv * jniEnv, jobject jobject1, jint type, jstring var, jobjectArray jArray){

}