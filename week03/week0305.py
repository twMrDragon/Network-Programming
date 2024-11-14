import pandas as pd

xmlFile = 'https://storage.googleapis.com/learn_pd_like_tidyverse/gapminder.xlsx'
gapminder = pd.read_excel(xmlFile)
# 2002 年全球人口各國平均數
popAverage = gapminder[gapminder['year']==2002]['pop'].mean()
print(popAverage)
# 2002 年全球各洲平均壽命、平均財富
lifeExpGDPAverage = gapminder[gapminder['year']==2002].groupby(by='continent')[['lifeExp','gdpPercap']].mean()
print(lifeExpGDPAverage)