import pandas as pd
import numpy as np

# 資料數量
dataCount = 4
# 建立字典
data = {
    "id":["id"+str(i) for i in range(dataCount)],
    "name":["name"+str(i) for i in range(dataCount)],
    "cs":np.random.randint(low=0,high=100,size=dataCount),
    "pd":np.random.randint(low=0,high=100,size=dataCount),
}
# 建立dataFrame
student = pd.DataFrame(
    data=data,
    columns= ["id","name","cs","pd","rank"]
)

# 計算rank
# 先在rank放入cs+pd的值
student['rank']=student['cs']+student['pd']
student['rank']=student['rank'].rank(ascending=False)

# 列印答案
print(student)
print(student[student['cs']>60])
print(student[student['cs']>50][['id','name']])