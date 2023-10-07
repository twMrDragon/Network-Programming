import urllib.request
import ssl
from bs4 import BeautifulSoup

# ssl 設定
ssl._create_default_https_context = ssl._create_unverified_context

# 財政部官網
requestUrl = 'https://invoice.etax.nat.gov.tw/index.html'
htmlContent = urllib.request.urlopen(requestUrl).read()
soup = BeautifulSoup(htmlContent, "html.parser")

# 找出獎項及中獎號碼
prices = {}
tbody = soup.find("tbody")
for tr in tbody.findAll("tr")[:3]:
    subTitle = tr.find('td', {'headers': 'th01'}).text
    # 特別獎、特獎只有1組號碼
    if subTitle in ['特別獎', '特獎']:
        price = tr.find(
            'span', {'class': 'font-weight-bold etw-color-red'}).text
    # 頭獎有3組號碼
    elif subTitle == '頭獎':
        price = []
        for item in tr.findAll('p', {'class': 'etw-tbiggest mb-md-4'}):
            first5 = item.find('span', {'class': 'font-weight-bold'}).text
            last3 = item.find(
                'span', {'class': 'font-weight-bold etw-color-red'}).text
            price.append(first5+last3)
    prices[subTitle] = price

# 兌獎
maxScore = 0
ticketNumber = input("輸入一組統一發票編號:")
for eachNumber in prices['頭獎']:
    score = 0
    officeLast3 = eachNumber[-3:]
    inputLast3 = ticketNumber[-3:]
    if officeLast3[0] == inputLast3[0]:
        score += 1
    if officeLast3[1] == inputLast3[1]:
        score += 1
    if officeLast3[2] == inputLast3[2]:
        score += 1
    maxScore = max(maxScore,score)
if maxScore ==3:
    print('中二百元')
elif maxScore==2:
    print('差一個號碼中兩百元')