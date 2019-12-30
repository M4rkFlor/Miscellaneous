# Steps:
# 1. Load data
# 2. Explore data
# 3. Preprocess data
# 4. Build model (layers)
# 5. compile
# 6. Train

# TensorFlow and tf.keras
import tensorflow as tf
import keras
from keras.preprocessing.image import ImageDataGenerator, load_img, img_to_array, array_to_img
from keras.models import load_model

#Keras Layer Functions
from keras.layers import Conv2D, BatchNormalization, Activation, Flatten, Dense, Dropout, MaxPooling2D
from keras.callbacks import EarlyStopping, ModelCheckpoint
# Helper libraries
import numpy as np
import matplotlib
matplotlib.use('agg')
import matplotlib.pyplot as plt
import pandas as pd
from sklearn.model_selection import train_test_split

#load Cactus dataset
data = pd.read_csv('../../DataSets/cactus/train.csv') #naviagte to train csv provided from Kaggel dataset
File_Names = data.id
train_label = np.array(data.has_cactus)
print("type:" + str(type(train_label)) + " shape:" + str(train_label.shape))

#convert images to array and load them
train_image_list = []
progress = 0
for File in File_Names:
    FilePath = "../../DataSets/cactus/train/" + File
    train_image_list.append(img_to_array(load_img(FilePath)))
    progress+=1
    if(progress%4375==0):
        print("read:" + str(progress))

train_images = np.array(train_image_list)
print(train_images[0].shape) #(32, 32, 3)
print(train_images.shape) #(17500, 32, 32, 3)

#Pre-processing , Normalize images
train_images = train_images / 255.0

# sub-sample
train_label = train_label[::1] #stride of 1
train_images = train_images[::1]
print(train_label.shape) #(32, 32, 3)
print(train_images.shape) #(17500, 32, 32, 3)
#split(validation set) could use k fold instead
X_train, X_test, Y_train, Y_test = train_test_split(train_images, train_label, test_size=0.05, random_state=23)

#model
dropout_dense_layer = 0.6
model = keras.Sequential([
    Conv2D(32, (3, 3), input_shape=(32, 32, 3)), #32 output filters|3x3 window   ,  (3,3) can be just 3 from docs
    BatchNormalization(),
    Activation('relu'),
    Conv2D(32, (3, 3)),
    BatchNormalization(),
    Activation('relu'),
    Conv2D(32, (3, 3)),
    BatchNormalization(),
    Activation('relu'),
    MaxPooling2D(pool_size=(2, 2)),

    Conv2D(64, (3, 3)),
    BatchNormalization(),
    Activation('relu'),
    Conv2D(64, (3, 3)),
    BatchNormalization(),
    Activation('relu'),
    Conv2D(64, (3, 3)),
    BatchNormalization(),
    Activation('relu'),
    MaxPooling2D(pool_size=(2, 2)),
    
    Conv2D(128, (3, 3)),
    BatchNormalization(),
    Activation('relu'),
    Flatten(),
    Dense(1024),
    Activation('relu'),
    Dropout(dropout_dense_layer),
    Dense(256),
    Activation('relu'),
    Dropout(dropout_dense_layer),

    Dense(1),
    Activation('sigmoid')
])

model.compile(optimizer='adam', 
              loss='binary_crossentropy',
              )#metrics=['accuracy']
#callback
callbacks = [EarlyStopping(monitor='val_loss', patience=25), 
                ModelCheckpoint(filepath='best_model.h5', monitor='val_loss', save_best_only=True)]

#Re-Format
#X_train, X_test, Y_train, Y_test = np.array(X_train),np.array(X_test),np.array(Y_train),np.array(Y_test)
X_train, Y_train = tf.cast(X_train,tf.float32), tf.cast(Y_train,tf.float32)
Y_Test_Uncasted = Y_test
X_test, Y_test = tf.cast(X_test,tf.int32), tf.cast(Y_test,tf.int32)


#loaded_model = create_model()
try:
        model.load_weights('cactus_model.h5')
        modelLoaded = True
        #del model
except OSError:
        print("Could NOT load Model!")
        modelLoaded = False

if(modelLoaded == False):
        #Train if no model exists   
        model.fit(X_train, Y_train, epochs=30, steps_per_epoch=1)
        model.save_weights('cactus_model.h5')
        print("saved model")
        #test_loss = model.evaluate(X_test, Y_test, steps=1)
        #print('Test Loss:', test_loss)
        
else:
        print("loaded model")
'''
pred = model.predict_on_batch(X_test)
print("pred:actual , " + str(pred[1]) + ":" + str(Y_Test_Uncasted[1]))
acc = 0
for i in range(len(pred)-1):
        print("pred:actual , " + str(int(round(pred[i][0]))) + ":" + str(Y_Test_Uncasted[i]))
        if (Y_Test_Uncasted[i] == int(round(pred[i][0]))):
                acc+=1
print(acc)
print(len(pred))
print("Validation acc is: " + str(float(acc)/float(len(pred))) + "%")
'''






## Save To CV ##

#load Cactus dataset
SubmissionData = pd.read_csv('../../DataSets/cactus/sample_submission.csv')
Submission_File_Names = SubmissionData.id

#load and convert images to array
Submission_image_list = []
progress = 0
for File in Submission_File_Names:
    FilePath = "../../DataSets/cactus/test/" + File
    Submission_image_list.append(img_to_array(load_img(FilePath)))
    progress+=1
    if(progress%int(len(Submission_File_Names)/4)==0):
        print("read:" + str(progress))
Submission_images = np.array(Submission_image_list)

#Pre-processing , Normalize images
Submission_images = Submission_images / 255.0
Submission_images = tf.cast(Submission_images,tf.float32)
#predict and submit csv
pred = model.predict_on_batch(Submission_images)
SubmissionData.has_cactus = np.round(pred, 0).astype(int)
print(SubmissionData.head(25))
SubmissionData.to_csv('Submission.csv',index=False)