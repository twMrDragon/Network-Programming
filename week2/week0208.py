import xml.etree.ElementTree as et

# 讀取cont.xml
tree = et.parse("cont.xml")
root = tree.getroot()

# 遍歷
for country in root:
    if country.attrib['name'] == "新加坡":
        # 新增neighbor
        neighbor = et.Element("neighbor")
        neighbor.set("name","亞特蘭提斯")
        neighbor.set("direction","南") 
        country.append(neighbor)
    elif country.attrib['name'] == "愛爾蘭":
        # 修改gdpcc
        country.find("gdppc").text = "88888"

# 寫入xml檔案
tree.write("cont2.xml",xml_declaration=True,encoding="utf-8")

# 讀取cont2.xml
tree = et.parse("cont2.xml")
root = tree.getroot()

# 遍歷
for country in root:
    for neighbor in country.findall("neighbor"):
        # 列印相鄰國家
        print(f"{country.attrib['name']}:{neighbor.attrib['name']}")
        print(f"{neighbor.attrib['name']}:{country.attrib['name']}")