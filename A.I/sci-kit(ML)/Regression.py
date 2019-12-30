import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn import metrics
from numpy import sqrt


data = pd.read_csv('http://www-bcf.usc.edu/~gareth/ISL/Advertising.csv', index_col=0)#data is no longer avalible (dead link)
data.rename(str.capitalize, axis='columns' , inplace=True)

#Explore Data
'''
print (data.head())
print(data.shape)
sns.pairplot(data,x_vars=["Tv","Radio","Newspaper"],y_vars="Sales", height=7, aspect=0.7, kind='reg')
plt.show()
'''
# Format Data
Y = data.pop("Sales")
X_train, X_test, Y_train, Y_test = train_test_split(data, Y, test_size=0.4, random_state=7)

print (data.head())

#Model
linreg = LinearRegression()
linreg.fit(X_train, Y_train)

#Interpreting model coefficients
feature_cols = ['TV', 'Radio', 'Newspaper']
cofs = list(zip(feature_cols, linreg.coef_))
print("y = " + str(linreg.intercept_) + " + " + str(cofs[0][1]) + " x " + str(cofs[0][0])
+ " + " + str(cofs[1][1]) + " x " + str(cofs[1][0])
+ " + " + str(cofs[2][1]) + " x " + str(cofs[2][0]))

#Metrics
y_pred = linreg.predict(X_test)

# RMSE(square root of mean squared error)
print("RMSE: " + str(sqrt(metrics.mean_squared_error(Y_test, y_pred))))