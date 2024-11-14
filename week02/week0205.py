import urllib.request
import ssl
import os
import json

# ssl設定
ssl._create_default_https_context = ssl._create_unverified_context
# 獲取當前資料夾
scriptDir = os.path.dirname(__file__)

# 下載json檔案
url = "https://data.ntpc.gov.tw/api/datasets/71CD1490-A2DF-4198-BEF1-318479775E8A/json/preview"
filename = os.path.join(scriptDir,"ubike.json")
urllib.request.urlretrieve(url,filename)

# 開啟json檔案
with open(filename,encoding="utf8") as jsonFile:
    jsonArray = json.load(jsonFile)
    # 根據sbi(站點目前車輛數量)排序
    jsonArray.sort(key = lambda x:int(x['sbi']))
    for jsonObject in jsonArray:
        # 根據條件 場站目前車輛數量超過 5 (>=5) 篩選
        if(int(jsonObject['sbi'])>=5):
            print(jsonObject['sno'],jsonObject['sna'],jsonObject['tot'],jsonObject['sbi'],jsonObject['ar'],jsonObject['bemp'])

# 清理檔案
os.remove(filename)