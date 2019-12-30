# Steps:
# 1. Load data
# 2. Explore data
# 3. Preprocess data
# 4. Build model (layers)
# 5. compile
# 6. Train

# TensorFlow and tf.keras
import tensorflow as tf
from tensorflow import keras

# Helper libraries
import numpy as np
import matplotlib.pyplot as plt

print(tf.__version__)

#load fashion dataset from internet.
fashion_mnist = keras.datasets.fashion_mnist
(train_images, train_labels), (test_images, test_labels) = fashion_mnist.load_data()

#labels are maped to 0-9, eg 8 corresponds to Bag
class_names = ['T-shirt/top', 'Trouser', 'Pullover', 'Dress', 'Coat', 'Sandal', 'Shirt', 'Sneaker', 'Bag', 'Ankle boot']

#Explore data
print(train_images.shape,   #how traning data is formated
len(train_labels),          #number of items/labels
train_labels,               #values of the labels, 0-9 corresponding to clothing article.
test_images.shape,          #how test data is formated
len(test_labels))           #number of items/labels in test set



#Pre-processing , Normalize images
train_images = train_images / 255.0
test_images = test_images / 255.0


'''
#plot a few images
plt.figure(figsize=(10,10))
for i in range(25):
    plt.subplot(np.sqrt(25),np.sqrt(25),i+1)
    plt.xticks([])
    plt.yticks([])
    plt.grid(False)
    plt.xlabel(class_names[train_labels[i]])
    plt.imshow(train_images[i], cmap=plt.cm.binary)
plt.show()
'''

model = keras.Sequential([
    keras.layers.Flatten(input_shape=(28, 28)), # 2d -> 1d array
    keras.layers.Dense(128, activation=tf.nn.relu), # 1 Layer
    keras.layers.Dense(10, activation=tf.nn.softmax) # Output
])

# Loss function —Function for calculating error from preddicted.
# Optimizer —This is how the model is updated based on the data it sees and its loss function.
# Metrics —Used to monitor the training and testing steps. The following example uses accuracy, the fraction of the images that are correctly classified.
model.compile(optimizer='adam', 
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

#Train
model.fit(train_images, train_labels, epochs=5)

#Evaluate on test set
test_loss, test_acc = model.evaluate(test_images, test_labels)
print('Test accuracy:', test_acc)

#Use Model
predictions = model.predict(test_images) #make predication on data
predictedItem = np.argmax(predictions[0])
print(class_names[predictedItem])


plt.figure()
plt.imshow(train_images[0], cmap=plt.cm.binary)
plt.xlabel(class_names[predictedItem])
plt.show()

