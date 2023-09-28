import requests
from bs4 import BeautifulSoup
import pandas as pd
from io import StringIO
import os

# 獲取當前資料夾
scriptDir = os.path.dirname(__file__)
excelFile = os.path.join(scriptDir,"7_11.xlsx")

# # 刪除先前檔案
# if os.path.exists(excelFile):
#     os.remove(excelFile)

# 獲取所有城市選項
def getCitySelection():
    html = requests.get("https://www.ibon.com.tw/retail_inquiry.aspx")
    bsObj = BeautifulSoup(html.content,"lxml")
    result = []
    for countryItem in bsObj.find("select",{"name":"FirstClass"}).findAll("option"):
        result.append(countryItem.text)
    return result

# 街/路的記錄
roadAddressRecord = {}

# 遍歷所有城市
allCitySelection = getCitySelection()
for index,city in enumerate(allCitySelection):
    data = {'strTargetField':'COUNTY','strKeyWords':city}
    # 抓取城市所有店面
    res = requests.post("https://www.ibon.com.tw/retail_inquiry_ajax.aspx",data=data)
    city711Store = pd.read_html(StringIO(res.text), header=0)[0]
    count = city711Store.shape[0]
    # 針對本次城市所有門市統計同一個路的門市
    for i in range(count):
        # 第三欄資料為地址 iloc[i,2]
        fullAddress = city711Store.iloc[i,2]
        start = fullAddress.find(city)
        end = fullAddress.find("路")+1
        if end == -1:
            end = fullAddress.find("街")+1
        if end<3:continue
        roadAddress = fullAddress[start:end]
        if roadAddress not in roadAddressRecord:
            roadAddressRecord[roadAddress]=1
        else:
            roadAddressRecord[roadAddress]+=1
    # if index == 0:
    #     city711Store = pd.read_html(StringIO(res.text), header=0)[0]
    #     city711Store['city']=city
    # elif index>0:
    #     oneCityStore = pd.read_html(StringIO(res.text), header=0)[0]
    #     oneCityStore['city']=city
    #     # city711Store = pd.concat([city711Store,oneCityStore])
    print("%2d) %-*s %4d"%(index+1,5,city,pd.read_html(StringIO(res.text), header=0)[0].shape[0]))
# print(roadAddressRecord)roadAddressRecord = sorted(roadAddressRecord.items(),key=lambda x:x[1],reverse=True)
for i in range(3):
    roadAddress,count = roadAddressRecord[i]
    print("%s:%d"%(roadAddress,count))
# print(city711Store)
# city711Store.to_excel(excelFile)