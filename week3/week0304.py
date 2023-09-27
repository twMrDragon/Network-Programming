import requests
from bs4 import BeautifulSoup
import pandas as pd
from io import StringIO
import os

# 獲取當前資料夾
scriptDir = os.path.dirname(__file__)
excelFile = os.path.join(scriptDir,"7_11.xlsx")

# 刪除先前檔案
if os.path.exists(excelFile):
    os.remove(excelFile)

# 獲取所有城市選項
def getCitySelection():
    html = requests.get("https://www.ibon.com.tw/retail_inquiry.aspx")
    bsObj = BeautifulSoup(html.content,"lxml")
    result = []
    for countryItem in bsObj.find("select",{"name":"FirstClass"}).findAll("option"):
        result.append(countryItem.text)
    return result

allCitySelection = getCitySelection()
# 遍歷所有城市
for index,city in enumerate(allCitySelection):
    data = {'strTargetField':'COUNTY','strKeyWords':city}
    # 抓取城市所有店面
    res = requests.post("https://www.ibon.com.tw/retail_inquiry_ajax.aspx",data=data)
    if index == 0:
        city711Store = pd.read_html(StringIO(res.text), header=0)[0]
        city711Store['city']=city
    elif index>0:
        oneCityStore = pd.read_html(StringIO(res.text), header=0)[0]
        oneCityStore['city']=city
        city711Store = pd.concat([city711Store,oneCityStore])
# city711Store.to_excel(excelFile)