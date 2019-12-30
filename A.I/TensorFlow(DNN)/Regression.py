# Steps:
# 1. Load data
# 2. Format data
# 3. Build model (layers)
# 4. compile
# 5. Train

from __future__ import absolute_import, division, print_function

import pathlib

import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns

import tensorflow as tf
from tensorflow import keras
from tensorflow.keras import layers

print(tf.__version__)

# 1. Load data
dataset_path = keras.utils.get_file("auto-mpg.data", "https://archive.ics.uci.edu/ml/machine-learning-databases/auto-mpg/auto-mpg.data")
column_names = ['MPG','Cylinders','Displacement','Horsepower','Weight', 'Acceleration', 'Model Year', 'Origin'] 
raw_dataset = pd.read_csv(dataset_path, names=column_names, na_values = "?", comment='\t', sep=" ", skipinitialspace=True)
dataset = raw_dataset.copy() #dont modify original file
#print(dataset.tail())

# 2. Format data
dataset = dataset.dropna() #drops all rows with Missing Data(NaN)
origin = dataset.pop('Origin') #convert Origin field to One-Hot
dataset['USA'] = (origin == 1)*1.0
dataset['Europe'] = (origin == 2)*1.0
dataset['Japan'] = (origin == 3)*1.0
#print(dataset.tail())

#split data to train and test sets
train_dataset = dataset.sample(frac=0.8,random_state=0) # 80% of data selected "randomly" with seed = 0 
test_dataset = dataset.drop(train_dataset.index)

#Statistics of data for normalization
train_stats = train_dataset.describe()
train_stats.pop("MPG")
train_stats = train_stats.transpose() #swap rows-cols
#print(train_stats)

#remove MPG because we want to predict its value
train_labels = train_dataset.pop('MPG')
test_labels = test_dataset.pop('MPG')

# Normalize by Z-Score
def norm(x):
  return (x - train_stats['mean']) / train_stats['std'] # only train is used because we need to project the test dataset into the same distribution that the model has been trained on.
normed_train_data = norm(train_dataset)
normed_test_data = norm(test_dataset)


# 3. Build model (layers)
def build_model():
  model = keras.Sequential([
    layers.Dense(64, activation=tf.nn.relu, input_shape=[len(train_dataset.keys())]),
    layers.Dense(64, activation=tf.nn.relu),
    layers.Dense(1)
  ])

  optimizer = tf.keras.optimizers.RMSprop(0.001)

  model.compile(loss='mean_squared_error',
                optimizer=optimizer,
                metrics=['mean_absolute_error', 'mean_squared_error'])
  return model
model = build_model()

#test model to see if formated correctly
#example_batch = normed_train_data[:10]
#example_result = model.predict(example_batch)
#print(example_result)

# Display training progress by printing a single dot for each completed epoch
class PrintDot(keras.callbacks.Callback):
  def on_epoch_end(self, epoch, logs):
    if epoch % 100 == 0: print('')
    print('.', end='')

#Train
EPOCHS = 1000

early_stop = keras.callbacks.EarlyStopping(monitor='val_loss', patience=10)

history = model.fit(normed_train_data, train_labels, epochs=EPOCHS, validation_split = 0.2, verbose=0, callbacks=[early_stop, PrintDot()])

print('')

#graph the training history shows cross validation to see if over fiting
def plot_history(history):
  hist = pd.DataFrame(history.history) #convert to pandas object
  hist['epoch'] = history.epoch
  
  plt.figure()
  plt.xlabel('Epoch')
  plt.ylabel('Mean Abs Error [MPG]')
  plt.plot(hist['epoch'], hist['mean_absolute_error'],
           label='Train Error') #training error
  plt.plot(hist['epoch'], hist['val_mean_absolute_error'],
           label = 'Val Error') #cross validation error
  plt.ylim([0,5])
  plt.legend()
  
  plt.figure()
  plt.xlabel('Epoch')
  plt.ylabel('Mean Square Error [$MPG^2$]')
  plt.plot(hist['epoch'], hist['mean_squared_error'],
           label='Train Error')
  plt.plot(hist['epoch'], hist['val_mean_squared_error'],
           label = 'Val Error')
  plt.ylim([0,20])
  plt.legend()
  plt.show()


plot_history(history)

#compare against test set to see accuracy
loss, mae, mse = model.evaluate(normed_test_data, test_labels, verbose=0)
print("Test set Mean Abs Error: {:5.2f} MPG".format(mae))


# Graph Predictions against test set
test_predictions = model.predict(normed_test_data).flatten()

plt.figure()
plt.scatter(test_labels, test_predictions)
plt.xlabel('True Values [MPG]')
plt.ylabel('Predictions [MPG]')
plt.axis('equal')
plt.axis('square')
plt.xlim([0,plt.xlim()[1]])
plt.ylim([0,plt.ylim()[1]])
_ = plt.plot([-100, 100], [-100, 100])

plt.figure()
error = test_predictions - test_labels
plt.hist(error, bins = 25)
plt.xlabel("Prediction Error [MPG]")
_ = plt.ylabel("Count")

plt.show()