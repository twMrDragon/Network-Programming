import pandas as pd
import requests
from io import StringIO

# 從網路取得新北市ubike資料
jsonUrl = 'https://data.ntpc.gov.tw/api/datasets/71CD1490-A2DF-4198-BEF1-318479775E8A/json?size=1000'
response = requests.get(jsonUrl)
bikeDataFrame = pd.read_json(StringIO(response.text))

# 空位數大於 10 的站點資料
bikeBempMoreThan10 = bikeDataFrame[bikeDataFrame['bemp']>=10]
for index,row in bikeBempMoreThan10.iterrows():
    print(row['sarea'],row['sna'],row['ar'],row['bemp'])
        
# 每區空位數大於 10 的站點數量
bikeGroupByChineseArea = bikeBempMoreThan10.groupby(by='sarea')
for index,row in bikeGroupByChineseArea:
    print(index,row.shape[0])

# 每區空位數大於 10 的站點空位加總
for index,row in bikeGroupByChineseArea[['bemp']].sum().iterrows():
    print(index,row['bemp'])