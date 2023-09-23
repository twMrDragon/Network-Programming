import ssl
import urllib.request
import csv
import os

# ssl設定
ssl._create_default_https_context = ssl._create_unverified_context

# 取得用戶輸入
x, y = map(int, input().split(" "))
dX,dY = int(input()),int(input())

# 下載csv
url = "https://www.aec.gov.tw/dataopen/index.php?id=2"
donwloadFilename = "pmi.csv"
urllib.request.urlretrieve(url, donwloadFilename)

# 讀取csv
with open(donwloadFilename, "r", encoding="ansi") as csvFile:
    plots = csv.reader(csvFile, delimiter=",")
    # 跳過標題
    next(plots)
    data = [row for row in plots]
    data.sort(key=lambda x:float(x[2]))
    for row in data:
        loactionX = float(row[4])
        locationY = float(row[5])
        # 根據用戶輸入篩選
        if loactionX>=x-dX and loactionX<=x+dX and locationY>=y-dY and locationY<=y+dY:
            print(*row)

# 清理檔案
os.remove(donwloadFilename)