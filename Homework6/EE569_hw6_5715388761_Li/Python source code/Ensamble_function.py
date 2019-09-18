# Jiazhi Li
# 5715388761
# jiazhil@usc.edu
# 2019.4.28

from tensorflow.python.platform import flags
import saab_compact as saab
import data
import numpy as np
import sklearn
import keras
from sklearn.cluster import KMeans
from numpy import linalg as LA
from sklearn.metrics.pairwise import euclidean_distances
import cv2

def partition_image(images, image_labels, use_num_images):
    return images[0:use_num_images], image_labels[0:use_num_images]

def getKernel(images, image_labels, kernel_sizes, num_kernels, energy_percent, use_num_images):
    class_list = saab.parse_list_string('0-9')
    images = np.moveaxis(images, 3, 1)
    pca_params = saab.multi_Saab_transform(images, image_labels,
                                           kernel_sizes=kernel_sizes,
                                           num_kernels=num_kernels,
                                           energy_percent=energy_percent,
                                           use_num_images=use_num_images,
                                           use_classes=class_list)
    return pca_params

def getFeature(images, pca_params):
    images= np.moveaxis(images, 3, 1)
    feature = saab.initialize(images, pca_params)
    return feature

def getWeight(images, images_label, feature):
    feature = feature.reshape(images.shape[0], 16, 5, 5)
    feature = np.moveaxis(feature, 1, 3)
    feature = feature.reshape(-1, 5 * 5 * 16)

    # feature normalization
    # std_var = (np.std(feature, axis=0)).reshape(1, -1)
    # feature = feature / std_var

    num_clusters = [120, 84, 10]
    use_classes = 10
    weights = {}
    bias = {}
    for k in range(len(num_clusters)):
        if k != len(num_clusters) - 1:
            # Kmeans
            kmeans = KMeans(n_clusters=num_clusters[k]).fit(feature)
            pred_labels = kmeans.labels_
            num_clas = np.zeros((num_clusters[k], use_classes), dtype=np.float32)
            for i in range(num_clusters[k]):
                for t in range(use_classes):
                    for j in range(feature.shape[0]):
                        if pred_labels[j] == i and images_label[j] == t:
                            num_clas[i, t] += 1
            acc_train = np.sum(np.amax(num_clas, axis=1)) / feature.shape[0]
            print(k, ' layer Kmean (just ref) training acc is {}'.format(acc_train))

            # Compute centroids
            clus_labels = np.argmax(num_clas, axis=1)
            centroid = np.zeros((num_clusters[k], feature.shape[1]), dtype=np.float32)
            for i in range(num_clusters[k]):
                t = 0
                for j in range(feature.shape[0]):
                    if pred_labels[j] == i and clus_labels[i] == images_label[j]:
                        if t == 0:
                            feature_test = feature[j].reshape(1, -1)
                        else:
                            feature_test = np.concatenate((feature_test, feature[j].reshape(1, -1)), axis=0)
                        t += 1
                centroid[i] = np.mean(feature_test, axis=0, keepdims=True)

            # Compute one hot vector
            t = 0
            labels = np.zeros((feature.shape[0], num_clusters[k]), dtype=np.float32)
            for i in range(feature.shape[0]):
                if clus_labels[pred_labels[i]] == images_label[i]:
                    labels[i, pred_labels[i]] = 1
                else:
                    distance_assigned = euclidean_distances(feature[i].reshape(1, -1),
                                                            centroid[pred_labels[i]].reshape(1, -1))
                    cluster_special = [j for j in range(num_clusters[k]) if clus_labels[j] == images_label[i]]
                    distance = np.zeros(len(cluster_special))
                    for j in range(len(cluster_special)):
                        distance[j] = euclidean_distances(feature[i].reshape(1, -1),
                                                          centroid[cluster_special[j]].reshape(1, -1))
                    labels[i, cluster_special[np.argmin(distance)]] = 1

            # least square regression
            A = np.ones((feature.shape[0], 1), dtype=np.float32)
            feature = np.concatenate((A, feature), axis=1)
            weight = np.matmul(LA.pinv(feature), labels)
            feature = np.matmul(feature, weight)
            print('weight {}  dtype: {} '.format(i, weight.dtype))
            print('weights save....')
            weights['%d LLSR weight' % k] = weight[1:weight.shape[0]]
            print('weights saved!')
            bias['%d LLSR bias' % k] = weight[0].reshape(1, -1)
            print(k, ' layer LSR weight shape:', weight.shape)
            print(k, ' layer LSR output shape:', feature.shape)

            pred_labels = np.argmax(feature, axis=1)
            num_clas = np.zeros((num_clusters[k], use_classes), dtype=np.float32)
            for i in range(num_clusters[k]):
                for t in range(use_classes):
                    for j in range(feature.shape[0]):
                        if pred_labels[j] == i and images_label[j] == t:
                            num_clas[i, t] += 1
            acc_train = np.sum(np.amax(num_clas, axis=1)) / feature.shape[0]
            print(k, ' layer LSR training acc is {}'.format(acc_train))

            # Relu
            for i in range(feature.shape[0]):
                for j in range(feature.shape[1]):
                    if feature[i, j] < 0:
                        feature[i, j] = 0

                        # # Double relu
                        # for i in range(feature.shape[0]):
                        # 	for j in range(feature.shape[1]):
                        # 		if feature[i,j]<0:
                        # 			feature[i,j]=0
                        # 		elif feature[i,j]>1:
                        # 			feature[i,j]=1
        else:
            # least square regression
            labels = keras.utils.to_categorical(images_label, 10)
            A = np.ones((feature.shape[0], 1), dtype=np.float32)
            feature = np.concatenate((A, feature), axis=1)
            weight = np.matmul(LA.pinv(feature), labels).astype(np.float32)
            print('weight {}  dtype: {} '.format(i, weight.dtype))
            feature = np.matmul(feature, weight)
            weights['%d LLSR weight' % k] = weight[1:weight.shape[0]]
            bias['%d LLSR bias' % k] = weight[0].reshape(1, -1)
            print(k, ' layer LSR weight shape:', weight.shape)
            print(k, ' layer LSR output shape:', feature.shape)

            pred_labels = np.argmax(feature, axis=1)
            acc_train = sklearn.metrics.accuracy_score(images_label, pred_labels)
            print('training acc is {}'.format(acc_train))
    return weights, bias, feature, acc_train

def test(images, images_labels, pca_params, weights, bias):
    # testing (Convolution layer)
    print('--------Testing--------')
    images = np.moveaxis(images, 3, 1)
    feature = saab.initialize(images, pca_params)

    feature = feature.reshape(feature.shape[0], -1)
    print("S4 shape:", feature.shape)
    print('--------Finish Feature Extraction subnet--------')
    print('feature.dtype: {}'.format(feature.dtype))

    feature = feature.reshape(images.shape[0], 16, 5, 5)
    feature = np.moveaxis(feature, 1, 3)
    feature = feature.reshape(-1, 5 * 5 * 16)

    num_clusters = [120, 84, 10]

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
    acc_test = sklearn.metrics.accuracy_score(images_labels, pred_labels)
    print('testing acc is {}'.format(acc_test))
    return feature, acc_test

def laws_filter(images,index):
    L = np.array([1,2,1])
    E = np.array([-1,0,1])
    S = np.array([-1,2,-1])
    L = L.reshape(1,3)
    E = E.reshape(1,3)
    S = S.reshape(1,3)

    LL = np.matmul(np.transpose(L),L)
    LE = np.matmul(np.transpose(L),E)
    LS = np.matmul(np.transpose(L),S)
    EL = np.matmul(np.transpose(E),L)
    EE = np.matmul(np.transpose(E),E)
    ES = np.matmul(np.transpose(E),S)
    SL = np.matmul(np.transpose(S),L)
    SE = np.matmul(np.transpose(S),E)
    SS = np.matmul(np.transpose(S),S)

    Laws_filter = np.dstack((LL,LE))
    Laws_filter = np.dstack((Laws_filter, LS))
    Laws_filter = np.dstack((Laws_filter, EL))
    Laws_filter = np.dstack((Laws_filter, EE))
    Laws_filter = np.dstack((Laws_filter, ES))
    Laws_filter = np.dstack((Laws_filter, SL))
    Laws_filter = np.dstack((Laws_filter, SE))
    Laws_filter = np.dstack((Laws_filter, SS))
    Laws_filter = np.moveaxis(Laws_filter,2,0)

    filter = Laws_filter[index]

    for i in range(images.shape[0]):
        img = images[i].reshape(images.shape[1],images.shape[2])
        img_conv = cv2.filter2D(img, -1, filter)
        images[i] = img_conv.reshape(images.shape[1],images.shape[2],1)

    return images

