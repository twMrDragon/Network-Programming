import requests
from bs4 import BeautifulSoup
import pandas as pd
from io import StringIO

# 獲取所有城市選項
def getCitySelection():
    html = requests.get("https://www.ibon.com.tw/retail_inquiry.aspx")
    # 如果使用lxml 需安裝 pip install lxml
    bsObj = BeautifulSoup(html.content,"html.parser")
    result = []
    for countryItem in bsObj.find("select",{"name":"FirstClass"}).findAll("option"):
        result.append(countryItem.text)
    return result   

# 所有條件成立的店面(最後印出) 
allTargetStore = []

# user input
street = str(input())

# 遍歷所有城市
allCitySelection = getCitySelection()
for index,city in enumerate(allCitySelection):
    data = {'strTargetField':'COUNTY','strKeyWords':city}
    # 抓取該城市所有店面
    currentStore = []
    res = requests.post("https://www.ibon.com.tw/retail_inquiry_ajax.aspx",data=data)
    city711Store = pd.read_html(StringIO(res.text), header=0)[0]
    count = city711Store.shape[0]
    # 包含輸入的路
    for i in range(count):
        # 第三欄資料為地址 iloc[i,2]
        fullAddress = city711Store.iloc[i,2]
        # 如果包含查詢路名
        if street in fullAddress:
            # 找出排序號碼
            currentSort = 0
            hasStart = False
            digit = '1234567890'
            for d in fullAddress:
                if d in digit:
                    hasStart=True
                    currentSort=currentSort*10+int(d)
                elif hasStart:
                    break
            currentStore.append({
                'storeNum':city711Store.iloc[i,0],
                'storeName':city711Store.iloc[i,1],
                'storeFullAddress':city711Store.iloc[i,2],
                'storeSort':currentSort
            })
    
    # 排序
    currentStore.sort(key=lambda x:x['storeSort'])
    allTargetStore.extend(currentStore)

# 列印
for store in allTargetStore:
    print(*list(store.values())[:3])