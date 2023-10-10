# 組員：鄭重雨、林品緯、張睿恩
import pandas as pd
from math import log2


# 計算熵
def calEntropy(entropy: list):
    total = sum(entropy)
    result = 0
    for num in entropy:
        p = num/total
        result += (-p*log2(p))
    return result


# 計算資訊獲利
def calGain(df: pd.DataFrame):
    # 總數量
    totalCount = df.shape[0]
    # 元素去重複
    attributeLabels = df.iloc[:, 0].unique()
    # 全部資料獲利
    result = calEntropy(df.iloc[:, 1].value_counts().tolist())
    # 個別元素獲利
    for label in attributeLabels:
        currentLabelDf = df[df.iloc[:, 0] == label]
        currentResult = currentLabelDf.iloc[:, 1]
        result -= (currentLabelDf.shape[0]/totalCount) * \
            calEntropy(currentResult.value_counts().tolist())
    return result


# 資料準備
data = {
    'Outlook': ['Sunny', 'Sunny', 'Overcast', 'Rain', 'Rain', 'Rain', 'Overcast', 'Sunny', 'Sunny', 'Rain'],
    'Temp': ['Hot', 'Hot', 'Hot', 'Mild', 'Cool', 'Cool', 'Cool', 'Mild', 'Cool', 'Mild'],
    'Humidity': ['High', 'High', 'High', 'High', 'Normal', 'Normal', 'Normal', 'High', 'Normal', 'Normal'],
    'Wind': ['Weak', 'Strong', 'Weak', 'Weak', 'Weak', 'Strong', 'Weak', 'Weak', 'Weak', 'Strong'],
    'Play Tennis': ['No', 'No', 'Yes', 'Yes', 'Yes', 'No', 'Yes', 'No', 'Yes', 'Yes']
}

# 塞資料
df = pd.DataFrame(data)

# 模擬資料
dataInput = {
    'Outlook': 'Sunny',
    'Temp': 'Hot',
    'Humidity': 'High',
    'Wind': 'Weak'
}

# 計算每層的結果
for i in range(1, df.shape[1]):
    currentBestGain = float('-inf')
    currentNode = ''
    for label in df.columns[:-1]:
        currentGain = calGain(df[[label, 'Play Tennis']])
        if currentGain > currentBestGain:
            currentBestGain = currentGain
            currentNode = label
    print(f"Level {i}: {currentNode}")
    df = df[df[currentNode] == dataInput[currentNode]]
    df = df.drop(currentNode, axis=1)
    print(df)
    print()

# 印出結果百分比
print(df.value_counts(normalize=True)*100)
