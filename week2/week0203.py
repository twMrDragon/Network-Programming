import urllib.request
import ssl
import zipfile
import os
import csv

# ssl 設定
ssl._create_default_https_context = ssl._create_unverified_context

url = "https://data.ntpc.gov.tw/api/datasets/71CD1490-A2DF-4198-BEF1-318479775E8A/csv/zip"
zipName = "ubike.zip"
# api request 請求下載檔案
urllib.request.urlretrieve(url,zipName)

f = zipfile.ZipFile(zipName)
# 解壓縮目錄
file_dir = "./"
for filename in f.namelist():
    # 解壓縮
    f.extract(filename,file_dir)
f.close()

# 讀取csv檔案
f = open(filename,"r",encoding="utf8")
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
os.remove(filename)