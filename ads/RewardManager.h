//
//  RewardManager.h
//  BHUG1062
//
//

#ifndef RewardManager_hpp
#define RewardManager_hpp

#include <stdio.h>
#include "SingleTon.h"
#include "CSVParse.h"
#include "AdsManager.h"
#include <vector>
#include <map>

using namespace std;

#define REWARD_IAPID        "IAPID"
#define REWARD_ModuleName   "ModuleName"
#define REWARD_KeyInModule  "Key"
#define REWARD_Indexs       "Indexs"

#define kRewardItemStatusChangedNotify "kRewardItemStatusChangedNotify"



struct RewardInfoItem
{
public:
    
    RewardInfoItem(){}
    
    RewardInfoItem(string aIapId, string aModuleName, string aKeyInModule, int aIndex):
    iapId(aIapId),
    moduleName(aModuleName),
    keyInModule(aKeyInModule),
    index(aIndex)
    {
    }
    
    string getKey() const
    {
        return moduleName + keyInModule + to_string(index);
    }
    
    bool isNull()
    {
        return index == INT_MAX;
    }
    
    //所归属的iap项(该iap购买后，reward锁也解了)
    string iapId;
    //模块名称+类别名称+index，用作需要解锁物品的key
    //模块名称
    string moduleName;
    //类别名称。。
    string keyInModule;
    int index = INT_MAX;
};

static const long secondsOfOneDay = 24 * 3600;

class RewardManager: public Ref, public AdsManagerDelegate
{
    RewardManager();
public:
    static RewardManager* getInstance();
    
    void loadConfig(string csvPath);
    
    string getItemKey(string moduleName, string keyInModule, const int inx);
    
    RewardInfoItem getRewardInfoItem(string moduleName, string keyInModule, const int inx);
    
    void showRewardAds(const string key);
    void showRewardAds(const RewardInfoItem& item);
    void showRewardAds(string moduleName, string keyInModule, const int inx);
    
    bool isLocked(string key);
    bool isLocked(const RewardInfoItem& item);
    
    void unLocked(string key);
    void unLocked(const RewardInfoItem& item);
    
    void lockAll();
    
    bool isItTimeToLockAll();
    
    std::function<void()> showRewardFalseCall = nullptr;
    std::function<void()> showRewardLoadingCall = nullptr;
    std::function<void()> removeRewardLoadingCall = nullptr;
    std::function<void()> showDialog = nullptr;
    
    static bool s_showFullAds;
private:
    void removeLoadingSchedule(float dt);
    
    virtual void onAdsCollapsed(ADS_TYPE adType) override;
    
    virtual void onAdsRewarded(std::string, int, bool) override;
    
    virtual void onAdsLoadFailed(std::string error, ADS_TYPE adType) override;
    
private:
    //    string getItemKey(string moduleName, string keyInModule, const int inx);
    
    long getTodaySecondAt0Clock();
    
    void reLockTimeCheckSchedule(float dt);
    
    void showRewardFailedHandleIos();
    
    //安卓视频广告失败了，播全屏
    bool showRewardFailedHandleAndroid();
    
    void registerAdsEvents();
    
    void unRegisterAdsEvents();
    
    template<typename T>  string to_string(T value){
        stringstream _temp;
        _temp<<value;
        return _temp.str();
    }
private:
    map<string, RewardInfoItem> mapRewardItems;
    
    //上次重新锁上的时间(秒), 所在天的0点秒数
    long _lastLockAllSecondsAt0ClockOfThatDay = 0;
    
    RewardInfoItem _waitingUnLockItemInfo;
};

#define kRewardManager RewardManager::getInstance()

#endif /* RewardManager_hpp */
