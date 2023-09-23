import xml.etree.ElementTree as et
import json

# 稍後加入的資料
nightSnackItems = ["beer","skewers","barbecue"]
nightSnackPrices = ["$15","$20","$25"]

# 讀取xml檔案
tree = et.parse("menu.xml")
root = tree.getroot()
# 建立Night snack element
nightSnack = et.Element("Night snack")
# 設定屬性
nightSnack.set("hours","21-23")
for i in range(len(nightSnackItems)):
    # 建立item element
    item = et.Element("item")
    # 設定屬性
    item.set("price",nightSnackPrices[i])
    # 設定文字
    item.text=nightSnackItems[i]
    # 加入至night snack
    nightSnack.append(item)
# 加入至根節點
root.append(nightSnack)

# 產生menu dict
menuDict = {}
for menuChild in root:
    menuChildDict = menuChild.attrib
    menuItemDict = {}
    for childSelection in menuChild:
        menuItemDict[childSelection.text] = childSelection.attrib["price"]
    menuChildDict["items"]=menuItemDict
    menuDict[menuChild.tag]=menuChildDict
    
# 寫入json file
with open("menu.json",'w') as jsonFile:
    json.dump({"menu":menuDict},jsonFile)