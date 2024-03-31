import pandas as pd

df = pd.read_csv("databases\female-to-male-ratio-of-time-devoted-to-unpaid-care-work.csv")


print(df.isnull().sum())

df.dropna(inplace=True)

