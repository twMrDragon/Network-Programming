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
    # 股利網址
    dividendUrl = f'https://tw.stock.yahoo.com/quote/{code}/dividend'
    html = requests.get(dividendUrl)
    dividendSoup = BeautifulSoup(html.text,'html.parser')
    dividendTabel = dividendSoup.findAll('div',{'class':'Bgc(#fff) table-row D(f) Ai(c) Bgc(#e7f3ff):h Fz(16px) Px(12px) Bxz(bb) Bdbs(s) Bdbw(1px) Bdbc($bd-primary-divider) H(40px)'})
    dividend2023Total = 0.0
    # 計算2023年股利加總
    for dividendRow in dividendTabel:
        year = dividendRow.find('div',{'class':'D(f) W(84px) Ta(start)'},).text
        dividend = dividendRow.find('div',{'class':'Fxg(1) Fxs(1) Fxb(0%) Ta(end) Mend($m-table-cell-space) Mend(0):lc Miw(62px)'}).find('span').text
        if '2023' in year:
            dividend2023Total+=float(dividend)
    stockData = {'name':name,'code':code,'dividend2023':dividend2023Total}
    stockList.append(stockData)

# 排序
stockList.sort(key=lambda x:x['dividend2023'],reverse=True)
for i in range(3):
    print(*stockList[i].values())