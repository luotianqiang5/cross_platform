//
//  ADS_TYPE.h
//  sandwich
//
//  Created by luotianqiang1 on 16/9/29.
//
//

#ifndef ADS_TYPE_h
#define ADS_TYPE_h
typedef enum {
    kTypeNativeAds = 1<<5,
    kTypeRectAds = 1<<4,
    kTypeBannerAds = 1<<3,
    kTypeInterstitialAds = 1<<2,
    kTypeCrosspromoAds = 1<<1,
    kTypeRewardedAds = 1<<0
} ADS_TYPE;

#endif /* ADS_TYPE_h */
