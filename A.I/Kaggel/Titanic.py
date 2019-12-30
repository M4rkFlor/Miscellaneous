from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn import metrics
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestRegressor
import matplotlib.pyplot as plt
from numpy import argmax
import pandas as pd
import seaborn as sns
from warnings import filterwarnings
filterwarnings("ignore")




#Methods
#metrics
def Acc(Y_Prediction, printOut=True):
    acc = metrics.accuracy_score(Y_test, Y_Prediction)
    if printOut:
        print(acc)
    return acc
#load data
data = pd.read_csv('../../DataSets/titanic/train.csv', index_col=0) #Titanic dataset from Kaggel
#Explore data
'''
sns.pairplot(data,x_vars=["Survived","Pclass","Age","SibSp","Parch","Fare"],y_vars="Survived", height=7, aspect=0.7, kind='reg')
sns.distplot(data.Survived, rug=True,hist=True)
g = sns.FacetGrid(data, height=4, aspect=2)
g.map(sns.barplot, "Survived", "Fare")
plt.show()
print(data.describe())
print(data.isna().sum()) # what is NaN
print(data.head())
'''
#Modify data

#fill NaN
data['Age'].fillna(data['Age'].mean(), inplace=True)  
data['Cabin'].fillna(data['Cabin'].mode(dropna=True)[2], inplace=True)
data['Embarked'].fillna(data['Embarked'].mode(dropna=True)[0], inplace=True)
#print(data['Cabin'].mode(dropna=True)[2])
#print(data['Embarked'].mode(dropna=True)[0])
print(data.isna().sum())

data["Cabin"] = data["Cabin"].str[0]
#print(data['Cabin'].value_counts())
target = data.pop("Survived")
data.pop("Ticket")
#These fields could be used but require multipule formating steps, remove them for now
data.pop("Name") # can categorize prefixes


#convert 1-hot: Pclass,Sex,Embarked
    #Pclass: Ticket class
Pclass = data.pop('Pclass')
data['1st-class'] = (Pclass == 1)*1.0
data['2nd-class'] = (Pclass == 2)*1.0
data['3rd-class'] = (Pclass == 3)*1.0
    #Sex
Sex = data.pop('Sex')
data['Male'] = (Sex == "male")*1.0
data['Female'] = (Sex == "female")*1.0
    #Embarked: Port of Embarkation
Embarked = data.pop('Embarked')
data['Cherbourg'] = (Embarked == "C")*1.0
data['Queenstown'] = (Embarked == "Q")*1.0
data['Southampton'] = (Embarked == "S")*1.0
    #Cabin
Cabin = data.pop('Cabin')
data['A'] = (Cabin == "A")*1.0
data['B'] = (Cabin == "B")*1.0
data['C'] = (Cabin == "C")*1.0
data['D'] = (Cabin == "D")*1.0
data['E'] = (Cabin == "E")*1.0
data['F'] = (Cabin == "F")*1.0
data['G'] = (Cabin == "G")*1.0
data['T'] = (Cabin == "T")*1.0
#print (data.head())
print (data.tail())
print (data.shape)
#split could use k fold instead
X_train, X_test, Y_train, Y_test = train_test_split(data, target, test_size=0.4, random_state=23)

#Estimators/models

##############_KNeighborsClassifier_##############
k_range = list(range(1, 26)) # 1...25
scores = []
for k in k_range:
    knn = KNeighborsClassifier(n_neighbors=k)
    knn.fit(X_train, Y_train)
    scores.append(Acc(knn.predict(X_test), printOut=False))
#visual repesentation of K
plt.plot(k_range, scores)
plt.xlabel('Value of K for KNN')
plt.ylabel('Testing Accuracy')
# plot show at end to allow program to run to end
k = argmax(scores)+1 # returns lowest K with highest acc
knn = KNeighborsClassifier(n_neighbors=k)
knn.fit(X_train,Y_train) #final version should use all avalibe data (X,Y) not (X_Train, Y_Train)
print('KNN:'+ str(k) +': ', end='')
Acc(knn.predict(X_test))

##############_LogisticRegression_##############
logreg = LogisticRegression(solver='lbfgs', multi_class='auto')
logreg.fit(X_train,Y_train)
print('LogisticRegression: ', end='')
Acc(logreg.predict(X_test))
plt.show()

##############Random_Forest_Regressor##############
RandomForestRegressor = RandomForestRegressor(n_estimators=20, random_state=0)  
RandomForestRegressor.fit(X_train, Y_train)  
RFR_Pred = RandomForestRegressor.predict(X_test)
RFR_Pred = pd.DataFrame(RFR_Pred)
RFR_Pred.rename(columns={0:'col1'}, inplace=True)
RFR_Pred.loc[RFR_Pred['col1'] < 0.5, 'col1'] = 0
RFR_Pred.loc[RFR_Pred['col1'] >= 0.5, 'col1'] = 1
print(metrics.classification_report(Y_test,RFR_Pred))

##############TestSet .csv submission##############

#FINAL_MODEL

#train on remaing data
#logreg.fit(X_test,Y_test)
RandomForestRegressor.fit(X_test, Y_test) 

TestData = pd.read_csv('../../DataSets/titanic/test.csv', index_col=0)
index = TestData.index
print(TestData.shape)
#*********** TestSet Need 2 do same formating
#Modify data

#fill NAN
TestData['Age'].fillna(TestData['Age'].mean(), inplace=True)  
TestData['Cabin'].fillna("G", inplace=True)
TestData['Embarked'].fillna(TestData['Embarked'].mode(dropna=True)[0], inplace=True)
TestData['Fare'].fillna(TestData['Fare'].mean(), inplace=True)
#print(TestData.isna().sum()) #VERIFY FILLED NaN

TestData.pop("Ticket")
TestData.pop("Name")
TestData['Cabin'] = TestData['Cabin'].str[0]
Pclass = TestData.pop('Pclass')
TestData['1st-class'] = (Pclass == 1)*1.0
TestData['2nd-class'] = (Pclass == 2)*1.0
TestData['3rd-class'] = (Pclass == 3)*1.0
Sex = TestData.pop('Sex')
TestData['Male'] = (Sex == "male")*1.0
TestData['Female'] = (Sex == "female")*1.0
Embarked = TestData.pop('Embarked')
TestData['Cherbourg'] = (Embarked == "C")*1.0
TestData['Queenstown'] = (Embarked == "Q")*1.0
TestData['Southampton'] = (Embarked == "S")*1.0
Cabin = TestData.pop('Cabin')
TestData['A'] = (Cabin == "A")*1.0
TestData['B'] = (Cabin == "B")*1.0
TestData['C'] = (Cabin == "C")*1.0
TestData['D'] = (Cabin == "D")*1.0
TestData['E'] = (Cabin == "E")*1.0
TestData['F'] = (Cabin == "F")*1.0
TestData['G'] = (Cabin == "G")*1.0
TestData['T'] = (Cabin == "T")*1.0
#***********Predict and export as csv
#preddiction = logreg.predict(TestData)


RFR_Pred = RandomForestRegressor.predict(TestData)
RFR_Pred = pd.DataFrame(RFR_Pred)
RFR_Pred.rename(columns={0:'col1'}, inplace=True)
RFR_Pred.loc[RFR_Pred['col1'] < 0.5, 'col1'] = 0
RFR_Pred.loc[RFR_Pred['col1'] >= 0.5, 'col1'] = 1

ans = pd.DataFrame({'PassengerId' : index , 'Survived': RFR_Pred['col1'].astype(int)})
ans.to_csv('submit.csv', index = False) #0.77033% acc -> 0.43 