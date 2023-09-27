import requests
import csv
import os
from bs4 import BeautifulSoup
from time import localtime,strftime

# 獲取當前資料夾
scriptDir = os.path.dirname(__file__)
resultCsv = os.path.join(scriptDir,"result.csv")

# 獲取html
html = requests.get("https://rate.bot.com.tw/xrt?Lang=zh-TW")
bsObj = BeautifulSoup(html.content,"html.parser")

# 全部貨幣list
allCurrency = []

# 貨幣排序條件
def currencyLambdaSort(currency):
    if currency['本行現金賣出'] =="-" or currency['本行現金買入']=="-":
        return float("-inf")
    else:
        return float(currency['本行現金賣出'])-float(currency['本行現金買入'])

# 先找尋表格，再把表格中的資料找出來(不含欄位名稱)
for single_tr in bsObj.find("table", {"title":"牌告匯率"}).find("tbody").findAll("tr"):
    # 找單筆資料中所有欄位
    cell = single_tr.findAll("td")
    # 找貨幣名稱
    currencyName = cell[0].find("div",{"class":"visible-phone print_hide"}).text
    # 去掉空白及換行
    currencyName = currencyName.replace("\n","").replace("\r","").replace(" ","")
    # 該貨幣全部匯率資料
    currencyRateDict = {"name":currencyName}
    for index in range(1,5):
        rateTd = cell[index]
        rate = rateTd.text.replace("\n","").replace("\r","").replace(" ","")
        currencyRateDict[rateTd['data-table']]=rate
    allCurrency.append(currencyRateDict)

# 根據條件做排序
allCurrency.sort(key=lambda x: currencyLambdaSort(x),reverse=True)

# 列印前三項
for currency in allCurrency[0:3]:
    print(currency['name'],float(currency['本行現金賣出'])-float(currency['本行現金買入']))