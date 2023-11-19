import requests
import os
import xml.etree.ElementTree as et
import pandas as pd

# 獲取當前資料夾
scriptDir = os.path.dirname(__file__)

# 下載xml
url =  'https://data.ntpc.gov.tw/api/datasets/3c6411d8-57be-462c-add4-046d86bf5de4/xml/preview'
xmlFilename = os.path.join(scriptDir,"data1.xml")
xmlFilename2 = os.path.join(scriptDir,"data2.xml")
xmlContent = requests.get(url)
with open(xmlFilename,'w',encoding='utf8') as xmlFile:
    xmlFile.write(xmlContent.text)

tree = et.parse(xmlFilename)
root = tree.getroot()

# step 1
for child in root:
    if child.find('seqno').text=='23':
        child.find('seqno').text='25'
        break

# step 2
nodeRow = et.Element("row")
nodeName = ['type','seqno','agency_codes','routename','start_and_end','weekday_operation_hours','holiday_operation_hours']
nodeText = ['一般路線','24','382290000H','999','光華路口-北科校園','去程：0600-2100；返程：0600-2100','去程：0600-1630；返程：0640-1710']
for i,v in enumerate(nodeName):
    nodeTemp  = et.Element(v)
    nodeTemp.text = nodeText[i]
    nodeRow.append(nodeTemp)
root.append(nodeRow)

# step 3
# 寫入xml檔案
tree.write(xmlFilename2,xml_declaration=True,encoding="utf-8")

# step 4
df = pd.read_xml(xmlFilename2)
df = df[(df['type']=='一般路線')&(df['weekday_operation_hours']=='去程：0600-2100；返程：0600-2100')]
df = df.sort_values(by=['seqno'])
print('seqno routename start_and_end')
for index,row in df.iterrows():
    print(row['seqno'],row['routename'],row['start_and_end'])