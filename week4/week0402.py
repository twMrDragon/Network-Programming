import pandas as pd
import os

# 獲取當前資料夾
currentDir = os.path.dirname(__file__)
readCsv = os.path.join(currentDir,"president_heights.csv")

presidentHeightDataFrame = pd.read_csv(readCsv)
# 輸出總統身高的敘述統計資料
print(presidentHeightDataFrame.describe())
# 輸出總統身高，最高前 5 筆資料
print(presidentHeightDataFrame.sort_values(by=['height(cm)'],ascending=[False]).head(5))
# 輸出總統身高 > 180，最低的 5 筆資料
print(presidentHeightDataFrame[presidentHeightDataFrame['height(cm)']>180].sort_values(by=['height(cm)']).head(5))