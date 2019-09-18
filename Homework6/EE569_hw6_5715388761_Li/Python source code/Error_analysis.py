# Jiazhi Li
# 5715388761
# jiazhil@usc.edu
# 2019.4.28

# import the modules we need
from keras import backend as K
from keras.models import Sequential
from keras.layers.convolutional import Conv2D
from keras.layers.convolutional import MaxPooling2D
from keras.layers.core import Activation
from keras.layers.core import Flatten
from keras.layers.core import Dense
from keras.layers import Dropout
from keras.datasets import mnist
from keras.utils import np_utils
from keras import optimizers
from keras.optimizers import SGD, RMSprop, Adam
import numpy as np
import matplotlib.pyplot as plt
import cv2
import data
import pickle
import numpy as np
import saab_compact as saab
import sklearn


# BP-CNNs
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
            # Dropout(0.8),
            Dense(84),
            Activation("relu"),
            #  Dropout(0.5),
            Dense(10),
            Activation("softmax"),
        ]

        model = Sequential(feature_layers + classification_layers)
        return model

def main():
    error_test_BP = BP_error()
    error_test_FF = FF_error()

    union = []

    for i in range(len(error_test_FF)):
        for j in range(len(error_test_BP)):
            if error_test_FF[i] == error_test_BP[j]:
                union.append(error_test_FF[i])
                break

    print('The number of error images of BP-CNNs is {}'.format(len(error_test_BP)))
    print('The number of error images of FF-CNNs is {}'.format(len(error_test_FF)))
    print('The number of same error images of is {}'.format(len(union)))

    print('Same error percentages of FF-CNNs is {}'.format(len(union)/len(error_test_FF)))
    print('Same error percentages of BP-CNNs is {}'.format(len(union) / len(error_test_BP)))

    (X_train, Y_train), (X_test, Y_test) = mnist.load_data()

    image_show = X_test[union[0]]
    for j in range(len(union)):
        for i in range(X_test.shape[0]):
            if i == union[j]:
                image_show = np.dstack((image_show, X_test[i]))
                break

    image_show = np.moveaxis(image_show, 2, 0)






    # Show image by opencv
    images = []
    img = []

    for i in range(image_show.shape[0]):
        im = image_show[i]
        im = im.reshape(28, 28)
        if (img == []):
            img = im
        else:
            # combination by rows
            img = np.hstack((img, im))

        # Present 60 images in a row
        if (img.shape[1] / 28 == 20):
            if (images == []):
                images = img.copy()
                img = []
            else:
                # Combination by columns
                images = np.vstack((images, img))
                img = []

        if (i == 1200):
            break;

    cv2.imshow('Union mislabeled images',images)
    cv2.waitKey()
    cv2.destroyAllWindows()








#return the index of error label image as a list
def error_compare(pred_labels, real_labels):
    res = []
    for i in range(pred_labels.shape[0]):
        if pred_labels[i] != real_labels[i]:
           res.append(i)
    return res

def BP_error():
    # Parameters for presentation
    VERBOSE = 1  # 0 represent showing nothing; 1 represent more detail; 2 represent only result
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

    print(X_train.shape)
    print(Y_train.shape)
    print(X_test.shape)
    print(Y_test.shape)

    # normalize the data
    X_train = X_train.astype("float32")  # change the type of ndarray
    X_test = X_test.astype("float32")
    X_train /= 255
    X_test /= 255
    X_train = X_train.reshape(X_train.shape[0], 1, IMG_ROWS, IMG_COLS)
    X_test = X_test.reshape(X_test.shape[0], 1, IMG_ROWS, IMG_COLS)
    print(X_train.shape[0], "train samples")
    print(Y_test.shape[0], "test samples")

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

    # # Evaluate the result by training data
    # score = model.evaluate(X_train, Y_train, verbose=VERBOSE)
    # print("Training score:", score[0])
    # print("Training accuracy:", score[1])
    #
    # # Evaluate the result by testing data
    # score = model.evaluate(X_test, Y_test, verbose=VERBOSE)
    # print("Test score:", score[0])
    # print("Test accuracy:", score[1])

    test_Pred_BP = model.predict(X_test, verbose=VERBOSE)
    test_Pred_BP = np.argmax(test_Pred_BP, axis=1)

    test_labels = np.argmax(Y_test,axis = 1)

    error_test_BP = error_compare(test_Pred_BP, test_labels)
    return error_test_BP

def FF_error():
    # FF-CNNs
    fr = open('pca_params_compact.pkl', 'rb')
    pca_params = pickle.load(fr)
    fr.close()

    # load data
    fw = open('llsr_weights_compact_v2.pkl', 'rb')
    weights = pickle.load(fw)
    fw.close()
    fw = open('llsr_bias_compact_v2.pkl', 'rb')
    bias = pickle.load(fw)
    fw.close()

    # read data     ·
    train_images, train_labels, test_images, test_labels, class_list = data.import_data("0-9")
    print('Training image size: dtype: ', train_images.shape, train_images.dtype)
    print('Testing_image size:', test_images.shape)

    # testing (Convolution layer)
    print('--------Testing--------')
    test_images = np.moveaxis(test_images, 3, 1)
    feature = saab.initialize(test_images, pca_params)
    # 10000x400 (16*5*5)
    feature = feature.reshape(feature.shape[0], -1)
    print("S4 shape:", feature.shape)
    print('--------Finish Feature Extraction subnet--------')
    print('feature.dtype: {}'.format(feature.dtype))

    feature = feature.reshape(10000, 16, 5, 5)
    feature = np.moveaxis(feature, 1, 3)
    feature = feature.reshape(-1, 5 * 5 * 16)

    num_clusters = [120, 84, 10]
    use_classes = 10

    for k in range(len(num_clusters)):
        w = weights['%d LLSR weight' % k]
        b = bias['%d LLSR bias' % k]
        A = np.ones((feature.shape[0], 1), dtype=np.float32)
        feature = np.concatenate((A, feature), axis=1)
        weight = np.concatenate((b, w), axis=0)
        feature = np.matmul(feature, weight)

        # Relu
        for i in range(feature.shape[0]):
            for j in range(feature.shape[1]):
                if feature[i, j] < 0:
                    feature[i, j] = 0

        pred_labels = np.argmax(feature, axis=1)

    acc_test = sklearn.metrics.accuracy_score(test_labels, pred_labels)
    print('testing acc is {}'.format(acc_test))
    error_test_FF = error_compare(pred_labels, test_labels)

    return error_test_FF

if __name__ == '__main__':
    main()