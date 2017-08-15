//
//  IAPManager.h
//  CodeBase
//
//  Created by zhangguangzong1 on 9/1/14.
//
//

#ifndef CODEBASE_COMPONENT_IAP_IAPMANAGER_H_
#define CODEBASE_COMPONENT_IAP_IAPMANAGER_H_
#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "CSVParse.h"
#include "STAppBilling.h" 

using namespace std;
USING_NS_CC;

#define kUserDefault        UserDefault::getInstance()
#define kIAPManager         IAPManager::getInstance()

class Product;

typedef vector<vector<int>> PaidRange;
typedef unordered_map<string, PaidRange> ImgMap;
typedef vector<int> PkgIndex;

class IAPManager : public STAppBillingDelegate{
    
public:
    static IAPManager* getInstance();
    
    /*initialization IAP information*/
    void initIAP(const string& csvFile);
    
    void initPurchase();
    /**
     *  after purchase successfully you should call this function
     *
     *  @param iapid
     */
    void updatePurchase(const string& iapid);
    /**
     *  if the img is free
     *
     *  @param name img name
     *
     *  @param index the index of img
     *
     *  @return true->free false->paid
     */
    bool isFree(const string& name,long index);
    /*只有一个商品的情况，即index = 1*/
    bool isFree(const string& name);
    /**
     *  if buy all the packages
     *
     *  @return true->unlockall
     */
    bool isUnlockAll();
    /**
     *  if show ads
     *
     *  @return true->show
     */
    bool isShowAds();
    /**
     *  if this package is purchased
     *
     *  @param index package index
     *
     *  @return true->has purchased
     */
    bool isPackagePurchased(int index);
    /**
     *  if this package is purchased
     *
     *  @param iapId iap id for this package
     *
     *  @return true->has purchased
     */
    bool isPackagePurchased(const string& iapId);
    /**
     *  purchase package by index
     *
     *  @param index package index.
     */
    void purchase(int index);
    
    void restore();
    
    /*
     * 通过传入一组以前存储的key,更新当前IAP。
     * 需要注意的是以前的key值顺序应当和当前的IAP ID顺序对应一致
     */
    void updateByOldIAPID(const vector<string>& ids);

    /*purchase callback*/
    virtual void purchaseSuccessful(const char* pid);

    virtual void purchaseFailed(const char *pid, int errorCode);
    
    virtual void restoreSuccessful(const char* pid);
    
    virtual void restoreSuccessfulNotify(bool isPurchase);
    
    virtual void restoreFailed(const char* pid, int errorCode);
    
    void setAfterPurchaseCallback(std::function<void(bool/*success*/)> fnPurchase)
    {
        _fnAfterPurchase = fnPurchase;
    }
    void setAfterRestoreCallback(std::function<void(bool/*success*/,bool/*isPurchase*/)> fnRestore)
    {
        _fnAfterRestore = fnRestore;
    }
    
    /*debug print*/
    void printProductInfos();
protected:
    IAPManager();
private:
    void csvParse(CSVParse*);
    Product* findProduct(const string& iapId);
    Product* findProductByName(const string& name);
    bool checkAllNormalPackage();
    bool checkUnlockAllPackage();
    bool isUnlockAllPackage(const string& pid);

    /*iap products*/
    Vector<Product*>    _products;
    
    STAppBilling    _appBilling;
    
    /*purchase call*/
    std::function<void(bool/*success*/)>   _fnAfterPurchase;
    std::function<void(bool/*success*/,bool/*isPurchase*/)>   _fnAfterRestore;
    
    CC_DISALLOW_COPY_AND_ASSIGN(IAPManager);
};

/**
 *  IAP product
 */
class Product : public Ref
{
public:
    static Product* create(const string& iapId);
    /**
     *  insert img iap info
     *
     *  @param imgName img name
     *  @param range   paid range
     */
    void insertImg(const string& imgName,const vector<int>& range);
    
    bool isInPaidRange(const string& name,long index);
    
    bool hasImg(const string& imgName);
    
    bool checkPkgIndex(const string& imgName);
    
    /*debug print*/
    void printProductInfos();
    
    const ImgMap& getImgMap() const
    {
        return _imgs;
    }
    
    const PkgIndex& getPkgIndexs() const
    {
        return _pkgIndexs;
    }
    
    string getProductId() const
    {
        return _productId;
    }
protected:
    Product(const string& iapId):_productId(iapId)
    {}
    virtual ~Product(){}
    
    /*iap id*/
    string      _productId;
    /*key:img name,value:a vector */
    ImgMap      _imgs;
    /*unlock other pkgs*/
    PkgIndex    _pkgIndexs;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(Product);
};

#endif /* defined(CODEBASE_COMPONENT_IAP_IAPMANAGER_H_) */
