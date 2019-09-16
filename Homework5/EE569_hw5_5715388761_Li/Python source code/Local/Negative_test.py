# Jiazhi Li
# 5715388761
# jiazhil@usc.edu
# 2019.4.4


# import the modules we need
from keras import backend as K
from keras.models import Sequential
from keras.layers.convolutional import Conv2D
from keras.layers.convolutional import MaxPooling2D
from keras.layers.core import Activation
from keras.layers.core import Flatten
from keras.layers.core import Dense
from keras.datasets import mnist
from keras.utils import np_utils
from keras import optimizers
from keras.optimizers import SGD, RMSprop, Adam
import numpy as np
import matplotlib.pyplot as plt
import cv2


# define the Sequential model
class LeNet:

    @staticmethod
    def createLeNet(input_shape, nb_class):
        # padding.same = with zero padding; padding.valid = without zero padding
        feature_layers = [
            Conv2D(filters=6, kernel_size=(5, 5), padding="same", input_shape=input_shape),
            Activation("relu"),
            MaxPooling2D(pool_size=(2, 2), strides=(2, 2)),
            Conv2D(filters=16, kernel_size=(5, 5), border_mode="same"),
            Activation("relu"),
            MaxPooling2D(pool_size=(2, 2), strides=(2, 2)),
            Flatten()
        ]

        classification_layers = [
            Dense(120),
            Activation("relu"),
            Dense(84),
            Activation("relu"),
            Dense(10),
            Activation("softmax")
        ]

        model = Sequential(feature_layers + classification_layers)
        return model


# Parameters for presentation
VERBOSE = 2  # 0 represent showing nothing; 1 represent more detial; 2 represent only result
VALIDATION_SPLIT = 0.2  # split the whole set into two parts, rate for evaluation

# parameters for images
IMG_ROWS, IMG_COLS = 28, 28  # input image size
INPUT_SHAPE = (1, IMG_ROWS, IMG_COLS)  # gray scale image
NB_CLASSES = 10  # 10 classes

# hyperparameters for network
NB_EPOCH = 12  # training iteration epoch
BATCH_SIZE = 128  # the size of image for one-time backpropogation

# hyperparameters for optimizer (Stochastic gradient descent)
LR = 0.01  # learning rate
DECAY = 1e-6  # decay for learning rate after refresh
MOMENTUM = 0.9

sgd = optimizers.SGD(lr=LR, decay=DECAY, momentum=MOMENTUM, nesterov=True)
OPTIMIZER = sgd  # tell the model how to adjust the parameter and how much the parameter was adjusted

# load mnist dataset
(X_train, Y_train), (X_test, Y_test) = mnist.load_data()
K.set_image_dim_ordering("th")  # channel first

# Get negative mnist dataset
X_train_negative = 255 - X_train
X_test_negative = 255 - X_test

# Show image by opencv
images = []
img = []

for i in range(X_train.shape[0]):
    im = X_train[i]
    im = im.reshape(28, 28)
    if (img == []):
        img = im
    else:
        # combination by rows
        img = np.hstack((img, im))

    # Present 60 images in a row
    if (img.shape[1] / 28 == 60):
        if (images == []):
            images = img.copy()
            img = []
        else:
            # Combination by columns
            images = np.vstack((images, img))
            img = []

    if (i == 1200):
        break;

cv2_imshow(images)
cv2.waitKey()
cv2.destroyAllWindows()

# Show negative image by opencv
images = []
img = []

for i in range(X_train_negative.shape[0]):
    im = X_train_negative[i]
    im = im.reshape(28, 28)
    if (img == []):
        img = im
    else:
        # combination by rows
        img = np.hstack((img, im))

    # Present 60 images in a row
    if (img.shape[1] / 28 == 60):
        if (images == []):
            images = img.copy()
            img = []
        else:
            # Combination by columns
            images = np.vstack((images, img))
            img = []

    if (i == 1200):
        break;

cv2_imshow(images)
cv2.waitKey()
cv2.destroyAllWindows()

# normalize the data
X_train = X_train.astype("float32")  # change the type of ndarray
X_test = X_test.astype("float32")
X_train /= 255
X_test /= 255
X_train = X_train.reshape(X_train.shape[0], 1, IMG_ROWS, IMG_COLS)
X_test = X_test.reshape(X_test.shape[0], 1, IMG_ROWS, IMG_COLS)
print(X_train.shape[0], "train samples")
print(Y_test.shape[0], "test samples")

# normalize the neagtive data
X_train_negative = X_train_negative.astype("float32")  # change the type of ndarray
X_test_negative = X_test_negative.astype("float32")
X_train_negative /= 255
X_test_negative /= 255
X_train_negative = X_train_negative.reshape(X_train_negative.shape[0], 1, IMG_ROWS, IMG_COLS)
X_test_negative = X_test_negative.reshape(X_test_negative.shape[0], 1, IMG_ROWS, IMG_COLS)

# convert class vectors to binary class matrices
Y_train = np_utils.to_categorical(Y_train, NB_CLASSES)
Y_test = np_utils.to_categorical(Y_test, NB_CLASSES)

# init the optimizer and model
model = LeNet.createLeNet(input_shape=INPUT_SHAPE, nb_class=NB_CLASSES)
model.compile(loss="categorical_crossentropy", optimizer=OPTIMIZER, metrics=["accuracy"])

history = model.fit(X_train, Y_train,
                    batch_size=BATCH_SIZE,
                    epochs=NB_EPOCH,
                    verbose=VERBOSE,
                    validation_split=VALIDATION_SPLIT)

# Evaluate the result
score = model.evaluate(X_test, Y_test, verbose=VERBOSE)
print("Test score:", score[0])
print("Test accuracy:", score[1])

# Evaluate the model by negative sample
score = model.evaluate(X_test_negative, Y_test, verbose=VERBOSE)
print("Test score by negative images:", score[0])
print("Test accuracy by negative images:", score[1])

# Save model
model.save("model.h5")

# show the data in history
print(history.history.keys())

# summarize history for accuracy
plt.plot(history.history["acc"])
plt.plot(history.history["val_acc"])
plt.title("Model accuracy")
plt.ylabel("accuracy")
plt.xlabel("epoch")
plt.legend(["train", "test"], loc="upper left")
plt.show()

# summarize history for loss
plt.plot(history.history["loss"])
plt.plot(history.history["val_loss"])
plt.title("Model loss")
plt.ylabel("loss")
plt.xlabel("epoch")
plt.legend(["train", "test"], loc="upper left")
plt.show()
