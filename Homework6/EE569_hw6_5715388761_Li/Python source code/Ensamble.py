# Jiazhi Li
# 5715388761
# jiazhil@usc.edu
# 2019.4.28

import data
from time import time
from tensorflow.python.platform import flags
import Ensamble_function as A
import numpy as np
from sklearn.decomposition import PCA
from sklearn import svm
import sklearn
import pickle

def main():
    #test loading
    fr = open('acc_tests.pkl', 'rb')
    acc_tests = pickle.load(fr)
    fr.close()

    train_images, train_labels, test_images, test_labels, class_list = data.import_data('0-9')
    trials = 10;
    test_decisions = {}
    train_decisions = {}
    acc_tests = {}
    acc_trains = {}
    for i in range(trials):
        train_images, train_labels = A.partition_image(train_images, train_labels, use_num_images=5000)
        if (i != 9):
            train_images = A.laws_filter(train_images, i)
            test_images = A.laws_filter(test_images,i)
        pca_params = A.getKernel(train_images, train_labels,
                                 kernel_sizes=(5, 5),
                                 num_kernels=(5, 15),
                                 energy_percent=None,
                                 use_num_images=-1)
        feature = A.getFeature(train_images, pca_params)
        weights, bias, train_decision, acc_train= A.getWeight(train_images, train_labels, feature)
        test_decision, acc_test= A.test(test_images, test_labels, pca_params, weights, bias)

        train_decisions['%d decision' % i] = train_decision
        test_decisions['%d decision' % i] = test_decision
        acc_tests['%d test' % i] = acc_test
        acc_trains['%d train' % i] = acc_train


    # save data
    fw = open('acc_tests.pkl', 'wb')
    pickle.dump(acc_tests, fw)
    fw.close()
    # save data
    fw = open('acc_trains.pkl', 'wb')
    pickle.dump(acc_trains, fw)
    fw.close()

    train_decision_concatenate = train_decisions['%d decision' % 0]
    test_decisions_concatenate = test_decisions['%d decision' % 0]
    for i in range(trials-1):
        train_decision = train_decisions['%d decision' % (i+1)]
        train_decision_concatenate = np.concatenate((train_decision_concatenate, train_decision), axis=1)
        test_decision = test_decisions['%d decision' % (i + 1)]
        test_decisions_concatenate = np.concatenate((test_decisions_concatenate, test_decision), axis=1)

    #PCA
    n_components = 60
    pca = PCA(svd_solver='randomized', n_components=n_components, whiten=True).fit(np.transpose(train_decision_concatenate))
    train_decision_PCA = pca.components_[:n_components, :]
    x_train = np.transpose(train_decision_PCA)

    pca = PCA(svd_solver='randomized', n_components=n_components, whiten=True).fit(np.transpose(test_decisions_concatenate))
    test_decision_PCA = pca.components_[:n_components, :]
    x_test = np.transpose(test_decision_PCA)

    # SVM classifier
    clf = svm.SVC(C=0.8, kernel='rbf', gamma=20, decision_function_shape='ovr')
    clf.fit(x_train, train_labels.ravel())

    pred_labels = clf.predict(x_train)
    acc_train = sklearn.metrics.accuracy_score(train_labels, pred_labels)
    print('training acc is {}'.format(acc_train))

    pred_labels = clf.predict(x_test)
    acc_test = sklearn.metrics.accuracy_score(test_labels, pred_labels)
    print('testing acc is {}'.format(acc_test))






if __name__ == '__main__':
    main()