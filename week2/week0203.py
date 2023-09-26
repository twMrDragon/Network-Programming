import urllib.request
import ssl
import zipfile
import os
import csv

# ssl 設定
ssl._create_default_https_context = ssl._create_unverified_context
# 獲取當前資料夾
scriptDir = os.path.dirname(__file__)

url = "https://data.ntpc.gov.tw/api/datasets/71CD1490-A2DF-4198-BEF1-318479775E8A/csv/zip"
zipName = os.path.join(scriptDir,"ubike.zip")
# api request 請求下載檔案
urllib.request.urlretrieve(url,zipName)

f = zipfile.ZipFile(zipName)
for filename in f.namelist():
    # 解壓縮至當前檔案
    f.extract(filename,scriptDir)
f.close()

# csv路徑
csvFilename = os.path.join(scriptDir,filename)

# 讀取csv檔案
f = open(csvFilename,"r",encoding="utf8")
plots = csv.reader(f,delimiter=',')
# 跳過標題列
next(plots)
for row in plots:
    bemp = int(row[12])
    # 根據條件篩選 bemp(空位)>=4
    if bemp>=4:
        print('%5s' %row[0], '%15s' %row[1],'%5s' %row[2], '%5s' %row[3],'%5s' %row[8], '%5s' %row[12])
f.close()

# 清理檔案
os.remove(zipName)
os.remove(csvFilename)