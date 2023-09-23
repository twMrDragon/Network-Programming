# 第二週作業

## week0203
[新北市公共自行車即時資訊](https://data.ntpc.gov.tw/datasets/71CD1490-A2DF-4198-BEF1-318479775E8A)\
針對新北市公共自行車即時資訊，撰寫程式，下載ZIP檔案，
印出空位數量超過 4 (>=4) 的場站資料，包含
sno：站點代號、sna：場站名稱、tot：場站總停車格、sbi：場站目前車輛數量、ar：地址(中文)、bemp：空位數量
將程式碼和結果截圖上傳

## week 0204
[全國環境輻射偵測即時資訊](https://www.aec.gov.tw/dataopen/index.php?id=2)\
針對全國環境輻射偵測即時資訊，寫Python程式

輸入:\
一個經緯度(整數)、經度與緯度偏離值

輸出:\
這個經緯度周圍偏離值的監測點和監測值
以監測值大小排序(小->大)

例如輸入\
經緯度(整數): 121 25\
經度偏離值 2\
緯度偏離值 2

輸出\
(121-2, 121+2) ~ (25-2, 25+2) 包含區域的監測站的資料

貼上你的code
## week 0205
[新北市公共自行車即時資訊](https://data.ntpc.gov.tw/datasets/71CD1490-A2DF-4198-BEF1-318479775E8A)\
針對新北市公共自行車即時資訊，寫一隻程式，讀取 json格式檔案，印出【場站目前車輛數量】超過 5 (>=5) 的場站資料，以目前數量大小排(小->大)顯示包含sno：站點代號、sna：場站名稱、tot：場站總停車格、sbi：場站目前車輛數量、ar：地址(中文)、bemp：空位數量

貼上你的 code
## week 0206
```xml
<?xml version="1.0"?>
<menu>
	<breakfast hours="7-11">
		<item price="$60">breakfast burritos</item>
		<item price="$40">pancakes</item>
	</breakfast>
	<lunch hours="11-14">
		<item price="$50">hamburger</item>
	</lunch>
	<dinner hours="15-19">
		<item price="80">spaghetti</item>
	</dinner>
</menu>
```
1. 將上面XML菜單存檔 menu.xml
2. 寫程式，讀取 menu.xml，增加
* 宵夜(Night snack) hours: 21-23
    * beer: $15
    * skewers: $20
    * barbecue: $25

轉成 json 格式存檔成 menu.json
## week 0208
```xml
<?xml version="1.0"?>
<data>
	<country name="愛爾蘭">
		<rank>4</rank>
		<year>2017</year>
		<gdppc>70638</gdppc>
		<neighbor name="英國" direction="北"/>
	</country>
	<country name="新加坡">
		<rank>8</rank>
		<year>2017</year>
		<gdppc>57713</gdppc>
		<neighbor name="馬來西亞" direction="北"/>
	</country>
	<country name="巴拿馬">
		<rank>68</rank>
		<year>2011</year>
		<gdppc>13600</gdppc>
		<neighbor name="哥斯大黎加" direction="西"/>
		<neighbor name="哥倫比亞" direction="東"/>
	</country>
</data>
```
將上面資料存成 cont.xml 檔案\
寫程式讀取 cont.xml
1. 加入新加坡 南邊鄰國 亞特蘭提斯，修改愛爾蘭 gdppc 值 88888，寫入 cont2.xml
2. 讀出 cont2.xml 將所有相鄰國家列出\
愛爾蘭:英國\
英國:愛爾蘭
...