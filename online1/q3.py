import requests
import pandas as pd
from bs4 import BeautifulSoup

# 抓資料
url='https://scweb.cwa.gov.tw/'
html = requests.get(url)
soup = BeautifulSoup(html.text,'html.parser')
tbody = soup.find('table',{'class':'table earthquakeInfoTable'}).find('tbody')
earthQuakes = []
for tr in tbody.findAll('tr'):
    tds = tr.findAll('td')
    earthQuakes.append(
        {
            'time':tds[2].text,
            'scale':tds[3].text,
            'deep':tds[4].text,
            'location':tds[5].text.replace('\r','').replace('\n','').replace(' ','')
        }
    )

# 排序
earthQuakes.sort(key=lambda x:[float(x['scale']),float(x['deep'])])

# 輸出
print('地震時間 深度 規模 地震位置')
for item in earthQuakes[:3]:
    print(item['time'],item['deep'],item['scale'],item['location'])