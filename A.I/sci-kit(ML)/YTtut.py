from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn import metrics
from sklearn.linear_model import LogisticRegression
import matplotlib.pyplot as plt
from numpy import argmax
#Methods
#metrics
def Acc(Y_Prediction, printOut=True):
    acc = metrics.accuracy_score(Y_test, Y_Prediction)
    if printOut:
        print(acc)
    return acc
#load data
iris = load_iris()
#Explore data
''' 
print (iris.data)
print (iris.data.shape)
print (iris.target.shape)
print (iris.target)
'''
#Modify data
X_train, X_test, Y_train, Y_test = train_test_split(iris.data, iris.target, test_size=0.4, random_state=4)

#Estimators/models

#Find best k value
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
# plot at end to allow program to run to end

k = argmax(scores) # returns lowest K with highest acc
knn = KNeighborsClassifier(n_neighbors=k)
knn.fit(X_train,Y_train) #final version should use all avalibe data (X,Y) not (X_Train, Y_Train)
print('KNN:', end='')
Acc(knn.predict(X_test))

logreg = LogisticRegression(solver='lbfgs', multi_class='auto')
logreg.fit(X_train,Y_train)
print('LogisticRegression:', end='')
Acc(logreg.predict(X_test))

plt.show()