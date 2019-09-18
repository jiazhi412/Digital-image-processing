# Jiazhi Li
# 5715388761
# jiazhil@usc.edu
# 2019.4.28

import data
import pickle
import numpy as np
import saab_compact as saab
import sklearn
import cv2
import keras
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
from numpy import linalg as LA
import matplotlib.pyplot as plt
from sklearn.metrics.pairwise import euclidean_distances

import os

os.environ["CUDA_VISIBLE_DEVICES"] = "1"

from keras import backend as K

K.tensorflow_backend._get_available_gpus()
import random
random.seed(9001)



def main():

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



    # training (Convolution layer)
    print('--------Training--------')
    train_images = np.moveaxis(train_images, 3, 1)
    feature = saab.initialize(train_images, pca_params)
    # 10000x400 (16*5*5)
    feature = feature.reshape(feature.shape[0], -1)
    print("S4 shape:", feature.shape)
    print('--------Finish Feature Extraction subnet--------')
    print('feature.dtype: {}'.format(feature.dtype))

    feature = feature.reshape(60000, 16, 5, 5)
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

    acc_train = sklearn.metrics.accuracy_score(train_labels, pred_labels)
    print('training acc is {}'.format(acc_train))





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

    print('training acc is {}'.format(0.9982))
    acc_test = sklearn.metrics.accuracy_score(test_labels, pred_labels)
    print('testing acc is {}'.format(acc_test))


if __name__ == '__main__':
    main()