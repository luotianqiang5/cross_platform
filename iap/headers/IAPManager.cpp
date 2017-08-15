#include "IAPManager.h"
#include "FrameWorkHelper.h"

const char* IAP_ID          =       "IapId";
const char* IAP_IMG_NAME    =       "ImgName";
const char* IAP_RANGE       =       "Range";


const char* UNLOCK_ALL      =       "unlockall";
const char* NO_ADS          =       "noads";

static IAPManager* g_sInstance = nullptr;

IAPManager::IAPManager():_fnAfterPurchase(nullptr),_fnAfterRestore(nullptr)
{
}

IAPManager* IAPManager::getInstance()
{
    if (!g_sInstance)
    {
        g_sInstance = new IAPManager();
    }
    return g_sInstance;
}

void IAPManager::initIAP(const string& csvFile)
{
    if (_products.size() != 0)
    {
        log("old iap information will be cleared.");
        _products.clear();
    }
    
    CSVParse* parse = CSVParse::create(csvFile.c_str());
    if (parse)
    {
        this->csvParse(parse);
    }
    else
    {
        log("csv file has some problems.");
        return;
    }
    
    this->initPurchase();
}

void IAPManager::initPurchase()
{
    _appBilling.setIABDelegate(this);
}

void IAPManager::updatePurchase(const string& id)
{
    Product* product = findProduct(id);
    for (auto it = product->getPkgIndexs().begin(); it != product->getPkgIndexs().end(); ++it)
    {
        if ((*it)<=0 || (*it) > _products.size())
        {
            log("invalid pkg index.");
            continue;
        }
        updatePurchase(_products.at((*it) + 1)->getProductId());
    }
    kUserDefault->setBoolForKey(id.c_str(),true);
    kUserDefault->flush();
}

void IAPManager::updateByOldIAPID(const vector<string>& ids)
{
    long i;
    for (i = 0; i < ids.size(); i++)
    {
        log("Old IAP key:%s",ids.at(i).c_str());
        bool isPurchased = kUserDefault->getBoolForKey(ids.at(i).c_str());
        if (isPurchased)
        {
            updatePurchase(_products.at(i)->getProductId());
        }
    }
    checkAllNormalPackage();
    checkUnlockAllPackage();
}

bool IAPManager::isUnlockAll()
{
    return this->isFree(UNLOCK_ALL);
}

bool IAPManager::isShowAds()
{
    
    if (_products.size() == 0)
    {
        return true;
    }
    
    bool isUnlockAll = this->isUnlockAll();
    if (isUnlockAll)
    {
        return false;
    }
    if (this->findProductByName(NO_ADS))
    {
        return !this->isFree(NO_ADS);
    }
    return true;
}

void IAPManager::purchase(int index)
{
    if (index <= 0 || index > _products.size())
    {
        log("invalid package index.");
        return;
    }
    _appBilling.purchase(_products.at(index - 1)->getProductId().c_str());
}

void IAPManager::restore()
{
    _appBilling.restore();
}

bool IAPManager::isFree(const string& name,long index)
{
    bool flag = false; //是否找到有加锁的iap信息
    bool _isFree = false;
    for (auto iter = _products.begin(); iter != _products.end(); iter++)
    {
        Product* product = *iter;
        if (product->isInPaidRange(name, index))
        {
            flag = true;
            bool isPurchase = kUserDefault->getBoolForKey(product->getProductId().c_str(),false);
            _isFree = _isFree || isPurchase;//只要该商品所从属的其中一个个包买过，该商品就是免费的。
        }
    }
    return flag ? _isFree : true;

}

bool IAPManager::isFree(const string& name)
{
    bool flag = false; //是否找到有加锁的iap信息
    bool _isFree = false;
    for (auto iter = _products.begin(); iter != _products.end(); iter++)
    {
        Product* product = *iter;
        if (product->isInPaidRange(name, 1))
        {
            flag = true;
            bool isPurchase = kUserDefault->getBoolForKey(product->getProductId().c_str(),false);
            _isFree = _isFree || isPurchase;//只要该商品所从属的其中一个个包买过，该商品就是免费的。
        }
    }
    return flag ? _isFree : true;
    
}

bool IAPManager::isPackagePurchased(int index)
{
    if (index <= 0 || index > _products.size())
    {
        return true;
    }
    return this->isPackagePurchased(_products.at(index - 1)->getProductId());
}

bool IAPManager::isPackagePurchased(const string& iapId)
{
    return kUserDefault->getBoolForKey(iapId.c_str(),false);
}

void IAPManager::csvParse(CSVParse* prase)
{
    int rows = prase->getRows();
    for (int i = 1; i < rows; i++)
    {
        string iapId = prase->getDatas(i,IAP_ID);
        string imgName= prase->getDatas(i,IAP_IMG_NAME);
        string range = prase->getDatas(i,IAP_RANGE);
        
        if( iapId != "")
        {
            Product* product = this->findProduct(iapId);
            if (!product)
            {
                product = Product::create(iapId);
                _products.pushBack(product);
            }
            strArray arrComma;
            FrameWorkHelper::splitWithForm(range, &arrComma);
            vector<int> ranges;
            for(auto str: arrComma)
            {
                ranges.push_back( atoi(str.c_str()));
            }
            product->insertImg(imgName,ranges);
        }
    }
}

Product* IAPManager::findProduct(const string& productId)
{
    for (auto iter = _products.begin(); iter != _products.end(); iter++)
    {
        if ((*iter)->getProductId() == productId)
        {
            return *iter;
        }
    }
    return NULL;
}

Product* IAPManager::findProductByName(const string& name)
{
    for (auto iter = _products.begin(); iter != _products.end(); iter++)
    {
        if ((*iter)->hasImg(name))
        {
            return *iter;
        }
    }
    return NULL;
}

bool IAPManager::checkAllNormalPackage()
{
    bool buyAll = true;
    for (auto iter = _products.begin(); iter != _products.end(); iter++)
    {
        if (!this->isPackagePurchased((*iter)->getProductId()))
        {
            if (!this->isUnlockAllPackage((*iter)->getProductId()))
            {
                buyAll = false;
                return false;
            }
        }
    }
    if (buyAll)
    {
        Product* product = this->findProductByName(UNLOCK_ALL);
        if (product)
        {
            this->updatePurchase(product->getProductId());
        }
    }
    return true;
}

bool IAPManager::checkUnlockAllPackage()
{
    Product* product = this->findProductByName(UNLOCK_ALL);
    if (product)
    {
        if (this->isPackagePurchased(product->getProductId()))
        {
            for (auto iter = _products.begin(); iter != _products.end(); iter++)
            {
                 this->updatePurchase((*iter)->getProductId());
            }
        }
    }
    return true;
}

bool IAPManager::isUnlockAllPackage(const string& pid)
{
    Product* product = this->findProductByName(UNLOCK_ALL);
    if (product)
    {
        return product->getProductId() == pid;
    }
    return false;
}

void IAPManager::purchaseSuccessful(const char* pid)
{
    this->updatePurchase(string(pid));
    if (this->isUnlockAllPackage(pid))
    {
        this->checkUnlockAllPackage();
    }
    else
    {
        this->checkAllNormalPackage();
    }
    
    if (_fnAfterPurchase)
    {
        _fnAfterPurchase(true);
    }
}

void IAPManager::purchaseFailed(const char *pid, int errorCode)
{
    if (_fnAfterPurchase)
    {
        _fnAfterPurchase(false);
    }
}

void IAPManager::restoreSuccessful(const char* pid)
{
    this->updatePurchase(string(pid));
    if (this->isUnlockAllPackage(pid))
    {
        this->checkUnlockAllPackage();
    }
    else
    {
        this->checkAllNormalPackage();
    }
}

void IAPManager::restoreSuccessfulNotify(bool isPurchase)
{
    if (_fnAfterRestore)
    {
        _fnAfterRestore(true,isPurchase);
    }
}

void IAPManager::restoreFailed(const char* pid, int errorCode)
{
    if (_fnAfterRestore)
    {
        _fnAfterRestore(false,false);
    }
}

void IAPManager::printProductInfos()
{
    int count = (int)_products.size();
    for (int i = 0; i < count; i++)
    {
        Product* product = _products.at(i);
        product->printProductInfos();
    }
}

/*************************@implementation product****************************/
Product* Product::create(const string& iapId)
{
    Product* product = new Product(iapId);
    if (product)
    {
        product->autorelease();
        return product;
    }
    CC_SAFE_DELETE(product);
    return NULL;
}

bool Product::isInPaidRange(const string& name,long index)
{
    ImgMap::iterator it = _imgs.find(name);
    if (it != _imgs.end())
    {
        PaidRange vRange = it->second;
        for (int i = 0; i < vRange.size();i++ )
        {
            auto range = vRange[i];
            if (std::find(range.begin(), range.end(), index) != range.end())
            {
                return true;
            }
        }
    }else
    {
        return false;
    }
    return false;
}

bool Product::checkPkgIndex(const string& imgName)
{
    strArray strInex;
    FrameWorkHelper::splitWithForm(imgName, &strInex);
    if(strInex.size())
    {
        for (auto it = strInex.begin(); it != strInex.end(); ++it)
        {
            int index = atoi((*it).c_str());
            _pkgIndexs.push_back(index);
        }
        return true;
    }
    
    return false;
}

void Product::insertImg(const string& imgName,const vector<int>& range)
{
    if (checkPkgIndex(imgName))
        return;
    
    ImgMap::iterator it = _imgs.find(imgName);
    if (it != _imgs.end())
    {
        (it->second).push_back(range);
    }else
    {
        PaidRange vRange;
        vRange.push_back(range);
        _imgs.insert(pair<string,PaidRange>(imgName,vRange));
    }
}

bool Product::hasImg(const string& imgName)
{
    ImgMap::iterator it = _imgs.find(imgName);
    if(it != _imgs.end())
    {
        return true;
    }else
    {
        return false;
    }
}

void Product::printProductInfos()
{
    if (!_pkgIndexs.empty())
    {
        __String* unlockStr = __String::createWithFormat("unlock other pkgs = ");
        for (auto it = _pkgIndexs.begin(); it != _pkgIndexs.end(); ++it)
        {
            unlockStr->appendWithFormat("%d, ",*it);
        }
        log("IAP ID:%s\n%s",_productId.c_str(),unlockStr->getCString());
    }else
    {
        log("IAP ID:%s : not unlock other pkg",_productId.c_str());
    }
    for (auto it = _imgs.begin(); it != _imgs.end(); ++it)
    {
        PaidRange vRange = it->second;
        __String* rangStr = __String::createWithFormat("range = ");
        for (int i = 0; i < vRange.size(); i++)
        {
            auto range = vRange[i];
            rangStr->append("{");
            for(auto index:range){
                 rangStr->appendWithFormat("%d,",index);
            }
            rangStr->append("},");
        }
        log("IAP ID:%s\nImgName = %s\n%s",_productId.c_str(),it->first.c_str(),rangStr->getCString());
    }
}