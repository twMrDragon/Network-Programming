import urllib.request
import zipfile
import os
import pandas as pd

# 調整是否下載zip
IS_DWONLOAD_ZIP = False

# 獲取當前資料夾
scriptDir = os.path.dirname(__file__)

# zip很大，你忍一下
# 這裡我就不重新下載了
zipName = os.path.join(scriptDir, "bus.zip")
if IS_DWONLOAD_ZIP:
    url = 'https://data.ntpc.gov.tw/api/datasets/34b402a8-53d9-483d-9406-24a682c2d6dc/csv/zip'
    # api request 請求下載檔案
    urllib.request.urlretrieve(url, zipName)

# 解壓縮
f = zipfile.ZipFile(zipName)
for filename in f.namelist():
    # 解壓縮至當前檔案
    f.extract(filename, scriptDir)
f.close()

# csv路徑
csvFilename = os.path.join(scriptDir, filename)
df = pd.read_csv(csvFilename)

# 4-1
df = df.groupby(by=df['routeId'])[['routeId']].count()
df = df.rename(columns={'routeId': 'num'})
df = df.sort_values(by=['num', 'routeId'], ascending=[False, False])
print('routeId num')
for index, row in df.head(5).iterrows():
    print(index, row['num'])

# 4-2
n = int(input())
df = df[df['num'] >= n].sort_values(
    by=['num', 'routeId'], ascending=[True, False])
print('routeId num')
for index, row in df.head(5).iterrows():
    print(index, row['num'])

# 清理檔案
if IS_DWONLOAD_ZIP:
    os.remove(zipName)
os.remove(csvFilename)
