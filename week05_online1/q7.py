import requests
from bs4 import BeautifulSoup

def format(s):
    return s.replace('\n','').replace('\t','')

# 獲取html
html = requests.get("https://www.intel.com.tw/content/www/tw/zh/products/sku/230490/intel-core-i713700-processor-30m-cache-up-to-5-20-ghz/specifications.html")
soup = BeautifulSoup(html.content,"html.parser")

# ID
container = soup.findAll('div',{'class':'tech-section'})[0]
id = container.findAll('div',{'class':'col-xs-6 col-lg-6 tech-data'})[3]
print('處理器編號:',format(id.text))

# core count
container = soup.findAll('div',{'class':'tech-section'})[1]
coreCount = container.findAll('div',{'class':'col-xs-6 col-lg-6 tech-data'})[0]
print('核心數量:',format(coreCount.text))

# burst 
maxBurst = container.findAll('div',{'class':'col-xs-6 col-lg-6 tech-data'})[4]
print('最大超頻:',format(maxBurst.text))

# cache
cache = container.findAll('div',{'class':'col-xs-6 col-lg-6 tech-data'})[10]
print('快取記憶體:',format(cache.text))

# date
container = soup.findAll('div',{'class':'tech-section'})[2]
date = container.findAll('div',{'class':'col-xs-6 col-lg-6 tech-data'})[1]
print('推出日期:',format(date.text))

# memory
container = soup.findAll('div',{'class':'tech-section'})[3]
memory = container.findAll('div',{'class':'col-xs-6 col-lg-6 tech-data'})[0]
print('最大記憶體大小:',format(memory.text))

# graph
container = soup.findAll('div',{'class':'tech-section'})[4]
graph = container.findAll('div',{'class':'col-xs-6 col-lg-6 tech-data'})[0]
print('最大記憶體大小:',format(graph.text))

# graph base hz
container = soup.findAll('div',{'class':'tech-section'})[4]
graphBaseHz = container.findAll('div',{'class':'col-xs-6 col-lg-6 tech-data'})[1]
print('繪圖基頻:',format(graphBaseHz.text))

# 範例輸出
"""
處理器編號: i7-13700
核心數量: 16
最大超頻: 5.20 Ghz
快取記憶體: 30 MB Intel® Smart Cache
推出日期: Q1’23
最大記憶體大小: 192GB
處理器繪圖: Intel® UHD Graphics 770
繪圖基頻: 300 Mhz
"""