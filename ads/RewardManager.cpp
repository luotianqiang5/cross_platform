//
//  RewardManager.cpp
//  BHUG1062
//
//

#include "RewardManager.h"
#include "cocos2d.h"
#include "FrameWorkHelper.h"
#include "STSystemFunction.h"
#include <sys/time.h>
#include "MyDialog.h"

using namespace cocos2d;

#define kRewardLastLockAllTimeKey "RewardLastLockAllTimeKey"

static RewardManager* _s_RewardManager = nullptr;
bool RewardManager::s_showFullAds = true;


RewardManager* RewardManager::getInstance()
{
    if (!_s_RewardManager) {
        _s_RewardManager = new RewardManager();
    }
    return _s_RewardManager;
}

RewardManager::RewardManager()
{
    showDialog = nullptr;
    auto strLastLockAllTime = UserDefault::getInstance()->getStringForKey(kRewardLastLockAllTimeKey, "");
    if(strLastLockAllTime.length() == 0)
    {
        _lastLockAllSecondsAt0ClockOfThatDay = getTodaySecondAt0Clock();
        UserDefault::getInstance()->setStringForKey(kRewardLastLockAllTimeKey, to_string(_lastLockAllSecondsAt0ClockOfThatDay));
        return;
    }
    _lastLockAllSecondsAt0ClockOfThatDay = atol(strLastLockAllTime.c_str());
    Director::getInstance()->getScheduler()->schedule(schedule_selector(RewardManager::reLockTimeCheckSchedule), this, 10.0f, kRepeatForever, 10.0f, false);
}

void RewardManager::loadConfig(string csvPath)
{
    auto* parse = CSVParse::create(csvPath.c_str());
    if (!parse)
    {
        CCLOG("warning:load config failed:%s", csvPath.c_str());
        return;
    }
    auto rows = parse->getRows();
    for (int i = 1; i < rows; i++) {
        string iapId = parse->getDatas(i, REWARD_IAPID);
        string moduleName = parse->getDatas(i, REWARD_ModuleName);
        string keyInModule = parse->getDatas(i, REWARD_KeyInModule);
        string sIndex = parse->getDatas(i, REWARD_Indexs);
        
        if( iapId != "")
        {
            RewardInfoItem item = {iapId, moduleName, keyInModule, -1};
            strArray arrComma;
            FrameWorkHelper::splitWithForm(sIndex, &arrComma);
            if(arrComma.size() == 0)
            {
                mapRewardItems[item.getKey()] = item;
                return;
            }
            for(auto str: arrComma)
            {
                strArray arrLine;
                FrameWorkHelper::split(str, "-", &arrLine);
                if(arrLine.size() <= 1)
                {
                    item.index = atoi(str.c_str());
                    mapRewardItems[item.getKey()] = item;
                }
                else
                {
                    int start = atoi(arrLine[0].c_str()), end = atoi(arrLine[1].c_str());
                    for(int i = start; i <= end; ++i)
                    {
                        item.index = i;
                        mapRewardItems[item.getKey()] = item;
                    }
                }
            }
        }
    }
}

string RewardManager::getItemKey(string moduleName, string keyInModule, const int inx)
{
    return moduleName + keyInModule + to_string(inx);
}

RewardInfoItem RewardManager::getRewardInfoItem(string moduleName, string keyInModule, const int inx)
{
    auto key = getItemKey(moduleName, keyInModule, inx);
    if(mapRewardItems.find(key) != mapRewardItems.end())
        return mapRewardItems[key];
    return RewardInfoItem();
}

void RewardManager::showRewardAds(const RewardInfoItem &item)
{
    if(!isLocked(item))
        return;
    auto endFunc = [=](MyDialog * dialog,int _touchInd){
        if(_touchInd==0){
            STSystemFunction cyf;
            if (!cyf.checkNetworkAvailable()) {
                cyf.popAlertDialog("there is problem with internet connection and try later");
                if(showRewardFalseCall)
                {
                    showRewardFalseCall();
                }
                return;
            }
            bool result = AdsManager::getInstance()->showAds(ADS_TYPE::kTypeRewardedAds);
            log("======kTypeRewardedAds %d====",result);
            if(!result)
            {
                AdsManager::getInstance()->preloadAds(ADS_TYPE::kTypeRewardedAds);
                //        if(CC_PLATFORM_IOS == CC_TARGET_PLATFORM)
                //        {
                //            showRewardFailedHandleIos();
                //            return;
                //        }
                //        else
                {
                    bool result= showRewardFailedHandleAndroid();
                    log("======kTypeRewardedAdsFailed %d====",result);
                    if(!result)
                        return;
                    _waitingUnLockItemInfo = item;
                    unLocked(_waitingUnLockItemInfo);
                    // this->onAdsRewarded("", 0, false);
                }
            }
            
            s_showFullAds = false;
            
            log("=========onAdsCollapsed %d 1111=========",s_showFullAds);
            
            if(showRewardLoadingCall)
            {
                showRewardLoadingCall();
            }
            _waitingUnLockItemInfo = item;
            registerAdsEvents();
        }
    };
//#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//    auto dialog = MyDialog::create("Wonuld you like to watch a video to unlock this item for 24 hours?", MyDialog::oneBtnPath);
//    dialog->dialogBtnClick = endFunc;
//    Director::getInstance()->getRunningScene()->addChild(dialog);
//#else
    endFunc(nullptr,0);
//#endif
  
  
}

void RewardManager::showRewardAds(string moduleName, string keyInModule, const int inx)
{
    auto key = getItemKey(moduleName, keyInModule, inx);
    showRewardAds(key);
}

void RewardManager::showRewardAds(const string key)
{
    if(mapRewardItems.find(key) == mapRewardItems.end())
        return;
    showRewardAds(mapRewardItems[key]);
}

void RewardManager::showRewardFailedHandleIos()
{
    
    if(showDialog)
    {
        showDialog();
    }
}

bool RewardManager::showRewardFailedHandleAndroid()
{
    bool result = AdsManager::getInstance()->showAds(ADS_TYPE::kTypeInterstitialAds);
    STSystemFunction cfy;
    if(!result)
    {
        cfy.popAlertDialog("there is problem with internet connection and try later");
        if(showRewardFalseCall)
        {
            showRewardFalseCall();
        }
    }
    return result;
}

void RewardManager::removeLoadingSchedule(float dt)
{
    if(removeRewardLoadingCall)
    {
        removeRewardLoadingCall();
    }
}

void RewardManager::onAdsCollapsed(ADS_TYPE adType)
{
    Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(RewardManager::removeLoadingSchedule, this), this, 0.1, 0, 0, false, "removeLoadingSchedule");
}

void RewardManager::onAdsRewarded(std::string, int, bool skip)
{
    unRegisterAdsEvents();
    
    if(skip)
    {if(removeRewardLoadingCall)
    {
        removeRewardLoadingCall();
    }
        return;
    }else {
        unLocked(_waitingUnLockItemInfo);
        if(removeRewardLoadingCall)
        {
            removeRewardLoadingCall();
        }
    }
}

void RewardManager::onAdsLoadFailed(std::string error, ADS_TYPE adType)
{
    if (adType == ADS_TYPE::kTypeInterstitialAds)
    {
        this->onAdsRewarded("", 0, true);
    }
}

bool RewardManager::isLocked(string key)
{
    if(mapRewardItems.find(key) == mapRewardItems.end())
        return false;
    return UserDefault::getInstance()->getBoolForKey(key.c_str(), true);
}


bool RewardManager::isLocked(const RewardInfoItem &item)
{
    return isLocked(item.getKey());
}


void RewardManager::unLocked(const RewardInfoItem &item)
{
    return unLocked(item.getKey());
}

void RewardManager::unLocked(string key)
{
    if(mapRewardItems.find(key) == mapRewardItems.end())
        return;
    UserDefault::getInstance()->setBoolForKey(key.c_str(), false);
    UserDefault::getInstance()->flush();
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(kRewardItemStatusChangedNotify);
}

void RewardManager::lockAll()
{
    for(auto itor: mapRewardItems)
    {
        UserDefault::getInstance()->setBoolForKey(itor.second.getKey().c_str(), true);
    }
    _lastLockAllSecondsAt0ClockOfThatDay = getTodaySecondAt0Clock();
    UserDefault::getInstance()->setStringForKey(kRewardLastLockAllTimeKey, to_string(_lastLockAllSecondsAt0ClockOfThatDay));
    UserDefault::getInstance()->flush();
}

bool RewardManager::isItTimeToLockAll()
{
    time_t now = time(nullptr);
    tm* localTm = localtime(&now);;
    time_t nowLocal;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    nowLocal = timegm(localTm);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    nowLocal = mktime(localTm);
#endif
    
    long diffSecond = nowLocal - _lastLockAllSecondsAt0ClockOfThatDay;
    //    __CCLOGWITHFUNCTION("diffSecond:%ld", diffSecond);
    return diffSecond >= secondsOfOneDay;
}

long RewardManager::getTodaySecondAt0Clock()
{
    time_t now = time(nullptr);
    tm* localTm = localtime(&now);;
    time_t nowLocal;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    nowLocal = timegm(localTm);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    nowLocal = mktime(localTm);
#endif
    __CCLOGWITHFUNCTION("%ld, %ld, %ld", nowLocal, nowLocal - nowLocal % secondsOfOneDay, nowLocal % secondsOfOneDay);
    return nowLocal - nowLocal % secondsOfOneDay;
}

void RewardManager::reLockTimeCheckSchedule(float dt)
{
    if(isItTimeToLockAll())
    {
        __CCLOGWITHFUNCTION("time to re lock all");
        lockAll();
    }
}

void RewardManager::registerAdsEvents()
{
    AdsManager::getInstance()->delegate = this;
}

void RewardManager::unRegisterAdsEvents()
{
    if(AdsManager::getInstance()->delegate == this)
        AdsManager::getInstance()->delegate = nullptr;
}

