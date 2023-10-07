import requests
import json
import pandas as pd
from sqlalchemy import create_engine

# 環保署PM2.5開放資料
url = 'https://data.moenv.gov.tw/api/v2/aqx_p_432?api_key=e8dd42e6-9b8b-43f8-991e-b3dee723a52d&limit=1000&sort=ImportDate%20desc&format=JSON'
response = requests.get(url)
data = json.loads(response.content.decode('utf8'))

# 轉換成可SQL查詢方式
df = pd.DataFrame(data['records'])
engine = create_engine('sqlite:///:memory:')
df.to_sql('AQI_table', engine, index=False)

# # 使用者輸入
searchCounty = input("輸入城市名:")
searchPM25 = float(input("PM2.5值:"))

# sql查詢
sqlQuery = f"""SELECT "county" as "縣市","sitename" as "區域","aqi" as "空氣品質指標","pm2.5" as "細懸浮微粒","pm2.5_avg" as "細懸浮微粒移動平均值","status" as "狀態" FROM AQI_table
               WHERE county='臺北市' AND CAST("pm2.5" as FLOAT)>{searchPM25}"""
# 列印查詢結果
print(pd.read_sql_query(sqlQuery, engine))
