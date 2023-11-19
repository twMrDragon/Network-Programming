import requests
from bs4 import BeautifulSoup

# yahoo ETF股
url = 'https://tw.stock.yahoo.com/tw-etf/volume'
html = requests.get(url)
html.raise_for_status()
soup = BeautifulSoup(html.text,"html.parser")

# 前10股票資訊
stockList = []

# 網頁中的列表排序前10個
for row in soup.find('ul',{'class':'M(0) P(0) List(n)'}).findAll('li',limit=10):
    name = row.findAll('div')[6].text
    # 編號前10代號
    code = row.find('span',{'class':'Fz(14px) C(#979ba7) Ell'}).text
    # 績效表現
    performanceUrl = f'https://tw.stock.yahoo.com/quote/{code}/performance'
    html = requests.get(performanceUrl)
    performanceSoup = BeautifulSoup(html.text,'html.parser')
    performanceGrid = performanceSoup.find('div',{'class':'grid-item item-span-6 break-mobile default-row-gap'})
    # print(performanceGrid)
    # print(performanceGrid.find('span').text)
    sign = 1 if performanceGrid.find('span').find('span').attrs['style']=='border-color:transparent transparent #ff333a transparent;border-width:0 5px 7px 5px' else -1
    stockList.append({"Code":code,'Performance':sign*float(performanceGrid.find('span').text.replace('%',''))})

# 排序
stockList.sort(key=lambda x:x['Performance'],reverse=True)
for i in range(3):
    print(stockList[i]['Code']," ",stockList[i]['Performance'],"%",sep='')