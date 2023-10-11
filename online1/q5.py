import requests
import pandas as pd
from io import StringIO

jsonUrl = 'https://data.ntpc.gov.tw/api/datasets/54a507c4-c038-41b5-bf60-bbecb9d052c6/json/preview'
response = requests.get(jsonUrl)
df = pd.read_json(StringIO(response.text))
df = df[(df['CELLSTATUS'] == 'Y') & (df['PAY'] == '計時收費')]
print("ROADNAME", "DAY", "HOUR")
for index, row in df.iloc[:5].iterrows():
    print(row['ROADNAME'], row["DAY"], row['HOUR'])
