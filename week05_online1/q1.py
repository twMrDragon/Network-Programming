import requests
from bs4 import BeautifulSoup

# 獲取html
html = requests.get("https://www.apple.com/tw/iphone-15-pro/specs/")
soup = BeautifulSoup(html.content,"html.parser")

# storage
print("容量:",end="")
for storage in soup.find('ul',{'class':'techspecs-list'}).findAll('li'):
    print(storage.text,end=',')
print()

# color
print('顏色:',end='')
print(soup.find('p').text)

# weight
print('重量:',end='')
weightDiv = soup.find('div',{'class':'weight-wrapper pro'}).find('p').text
print(weightDiv[:weightDiv.find('公克')+2])

# size
print('尺吋:',end='')
sizeLi = soup.find('div',{'class':'techspecs-section section-display'}).findAll('li')[1].text
print(sizeLi[:sizeLi.find('吋')+1])