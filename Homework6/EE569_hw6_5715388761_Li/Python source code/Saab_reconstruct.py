# Jiazhi Li
# 5715388761
# jiazhil@usc.edu
# 2019.4.28

from tensorflow.python.platform import flags
import pickle
import data
import saab_compact as saab
import numpy as np
from cv2 import imread,imshow,waitKey,imwrite

flags.DEFINE_string("output_path", None, "The output dir to save params")
flags.DEFINE_string("use_classes", "0-9", "Supported format: 0,1,5-9")
flags.DEFINE_string("kernel_sizes", "4,4", "Kernels size for each stage. Format: '3,3'")
flags.DEFINE_string("num_kernels", "5,15", "Num of kernels for each stage. Format: '4,10'")
flags.DEFINE_float("energy_percent", None, "Energy to be preserved in each stage")
flags.DEFINE_integer("use_num_images", -1, "Num of images used for training") #use a subset of train images
FLAGS = flags.FLAGS


def main():
    # read data
    train_images, train_labels, test_images, test_labels, class_list = data.import_data(FLAGS.use_classes)
    print('Training image size:', train_images.shape)
    print('Testing_image size:', test_images.shape)
    print ('Training images.dtype ', train_images.dtype)

    kernel_sizes = saab.parse_list_string(FLAGS.kernel_sizes)
    if FLAGS.num_kernels:
        num_kernels = saab.parse_list_string(FLAGS.num_kernels)
    else:
        num_kernels = None
    energy_percent = FLAGS.energy_percent
    use_num_images = FLAGS.use_num_images
    print('Parameters:')
    print('use_classes:', class_list)
    print('Kernel_sizes:', kernel_sizes)
    print('Number_kernels:', num_kernels)
    print('Energy_percent:', energy_percent)
    print('Number_use_images:', use_num_images)
    train_images=np.moveaxis(train_images, 3, 1)
    pca_params = saab.multi_Saab_transform_wo_pooling(train_images, train_labels,
                                           kernel_sizes=kernel_sizes,
                                           num_kernels=num_kernels,
                                           energy_percent=energy_percent,
                                           use_num_images=use_num_images,
                                           use_classes=class_list)
    # save data
    fw = open('pca_params_compact_wo_pooling.pkl', 'wb')
    pickle.dump(pca_params, fw)
    fw.close()

    # load data
    fr = open('pca_params_compact_wo_pooling.pkl', 'rb')
    pca_params = pickle.load(fr)
    # print(data1)
    fr.close()

    # read image
    image_label = 1
    path = "G:/569/Homework/HW6/Image/HW6_Images_JPG/"
    image = imread(path + str(image_label) + ".png")
    image = image[:,:,1]
    image_reshape = image.reshape([1,1,32,32])

    # Calculate feature after two stage Saab
    feature = saab.initialize_wo_pooling(image_reshape, pca_params)
    # 1x64 (16*2*2)
    feature = feature.reshape(feature.shape[1], -1)
    feat = {}
    feat['feature'] = feature

    # save data
    fw2 = open('feat_compact_wo_pooling.pkl', 'wb')
    pickle.dump(feat, fw2)
    fw2.close()

    image_reconstruct = saab.Reconstruct(feature,pca_params)
    image_reconstruct = image_reconstruct.reshape(32,32)
    image_norm = saab.norm(image_reconstruct)
    imwrite("G:/569/Homework/HW6/Image/HW6_result/" + str(image_label) + "_" + str(num_kernels[0]) + "_" + str(num_kernels[1]) + ".jpg",image_norm)

    PSNR = saab.PSNR(image_norm,image)

    fw3 = open("G:/569/Homework/HW6/Image/HW6_result/" + str(image_label) + "_" + str(num_kernels[0]) + "_" + str(num_kernels[1]) + ".txt", 'w')
    fw3.write(str(PSNR))
    fw3.close()






if __name__ == '__main__':
    main()


