# 第四周作業

## week0401 `numpy` `pandas`
用隨機方式產生分數cs (計概), pd(程式設計), 資料集
1. 四個學生，id, name, cs, pd,rank(缺失值)
2. 建構出 dataframe
3. 補上 rank (根據 cs + pd 總分以程式計算補值)
4. 列出cs 大於等於 60 的 資料
5. 列出 cs 大於等於50 的name和 pd資料
upload code

## week0402 `pandas`
使用 Pandas，載入 president_heights.csv
https://drive.google.com/file/d/1fSYtcNDiG3wadQ5LovmZbdUA6GzLdDhx/view?usp=sharing

輸出總統身高的敘述統計資料\
輸出總統身高，最高前 5 筆資料\
輸出總統身高 > 180，最低的 5 筆資料

貼上 code

範例輸出如下

## week0403 `pandas`

小組作業
每一組討論出一個版本，每一位同學都要上傳 code，code 最前面要加入註解 包含小所有名字和學號

計算
1. 決策樹的所有屬性第一層樹的【資訊獲利指標G】(最大屬性例如 X)
2. 決策樹的所有屬性(排除X)第二層樹的第一個屬的第一個值(e.g. sunny)性指標

決策樹參考講義(使用網球資料集)
https://drive.google.com/file/d/1fzVfSohP8Nl_jnzAbXv4NoaPVE4Y63i_/view?usp=sharing

## week 0404 `BeautifulSoup`

輸入一組統一編號
輸出是否中二百元，或者差一個號碼中兩百元

1111574\
中二百元

1111573\
差一個號碼中兩百元

upload code

## week0405 `json` `pandas` `sqlalchemy`

環保署AQI 公開資料集

輸入城市名稱、PM2.5 值以上\
輸出查詢資料 County, SiteName, AQI, PM2.5 avg, Status

臺北市
8

SQL 變成字串\
欄位名稱，用雙引號括起來
```sql
SELECT 欄位名稱1,欄位名稱2 #顯示欄位資料
FROM table_name #哪一個資料庫表格
WHERE condition1 AND condition2 #過濾條件
ORDER BY 欄位名稱 #排序欄位
```
upload code 