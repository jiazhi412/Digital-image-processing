// Jiazhi Li
// 5715388761
// jiazhil@usc.edu
// 2019.3.15

#include "OpencvAlgorithm.h"

using namespace cv;

vector<string> OpencvAlgorithm::Laws_label() {
	vector<string> Laws_label;
	Laws_label.push_back("LL");
	Laws_label.push_back("LE");
	Laws_label.push_back("LS");
	Laws_label.push_back("LW");
	Laws_label.push_back("LR");

	Laws_label.push_back("EL");
	Laws_label.push_back("EE");
	Laws_label.push_back("ES");
	Laws_label.push_back("EW");
	Laws_label.push_back("ER");

	Laws_label.push_back("SL");
	Laws_label.push_back("SE");
	Laws_label.push_back("SS");
	Laws_label.push_back("SW");
	Laws_label.push_back("SR");

	Laws_label.push_back("WL");
	Laws_label.push_back("WE");
	Laws_label.push_back("WS");
	Laws_label.push_back("WW");
	Laws_label.push_back("WR");

	Laws_label.push_back("RL");
	Laws_label.push_back("RE");
	Laws_label.push_back("RS");
	Laws_label.push_back("RW");
	Laws_label.push_back("RR");
	return Laws_label;
}

void OpencvAlgorithm::SIFT(Mat img_1, Mat img_2, double thres) {
	//Create SIFT class pointer
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	//Detect the keypoints
	vector<KeyPoint> keypoints_1, keypoints_2;
	f2d->detect(img_1, keypoints_1);
	f2d->detect(img_2, keypoints_2);

	Mat imageL2, imageR2;
	drawKeypoints(img_1, keypoints_1, imageL2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	drawKeypoints(img_2, keypoints_2, imageR2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);


	//namedWindow("KeyPoints of imageL", 0);
	//namedWindow("KeyPoints of imageR", 0);

	imshow("KeyPoints of river1", imageL2);
	imshow("KeyPoints of river2", imageR2);

	//Calculate descriptors (feature vectors)
	Mat descriptors_1, descriptors_2;
	f2d->compute(img_1, keypoints_1, descriptors_1);
	f2d->compute(img_2, keypoints_2, descriptors_2);

	//Matching descriptor vector using BFMatcher
	BFMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	//plot all matching points
	Mat img_matches;
	drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_matches);
	imshow("match image", img_matches);

	// Calculate min and max distance of sift descriptors
	double maxsift = 0;
	double minsift = 100;
	for (int i = 0; i < descriptors_1.rows; i++) {
		double dist = matches[i].distance;
		if (dist < minsift) {
			minsift = dist;
		}
		if (dist > maxsift) {
			maxsift = dist;
		}
	}

	// finding good matches
	vector<DMatch> good_matches_sift;
	for (int i = 0; i < descriptors_1.rows; i++) {
		if (matches[i].distance <= thres * minsift) {
			good_matches_sift.push_back(matches[i]);
		}
	}

	// plot all good matching points
	Mat img_good_matches;
	drawMatches(img_1, keypoints_1, img_2, keypoints_2, good_matches_sift, img_good_matches);
	imshow("good match image", img_good_matches);

	waitKey(0);
}

void OpencvAlgorithm::SIFT_largestscale(Mat img_1, Mat img_2) {
	//Create SIFT class pointer
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	//Detect the keypoints
	vector<KeyPoint> keypoints_1, keypoints_2;
	f2d->detect(img_1, keypoints_1);
	f2d->detect(img_2, keypoints_2);	

	// find the key point with the largest scale
	double max = 0;
	for (int i = 0; i < keypoints_1.size(); i++) {
		if (keypoints_1[i].size > max) {
			max = keypoints_1[i].size;		
		}
	}

	vector<KeyPoint> keypoint_largest_scale;
	for (int i= 0; i < keypoints_1.size(); i++) {
		if (keypoints_1[i].size == max) {
			keypoint_largest_scale.push_back(keypoints_1[i]);
		}
	}
		
	Mat image3;
	drawKeypoints(img_1, keypoint_largest_scale, image3, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("KeyPoint with largest scale", image3);

	//Calculate descriptors (feature vectors)
	Mat descriptors_1, descriptors_2;
	f2d->compute(image3, keypoint_largest_scale, descriptors_1);
	f2d->compute(img_2, keypoints_2, descriptors_2);

	//Matching descriptor vector using BFMatcher
	BFMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	//plot all matching points
	Mat img_matches;
	drawMatches(image3, keypoint_largest_scale, img_2, keypoints_2, matches, img_matches);
	imshow("match image ofr keypoint with largest scale", img_matches);

	waitKey(0);
}

void OpencvAlgorithm::SIFT_smallestscale(Mat img_1, Mat img_2) {
	//Create SIFT class pointer
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	//Detect the keypoints
	vector<KeyPoint> keypoints_1, keypoints_2;
	f2d->detect(img_1, keypoints_1);
	f2d->detect(img_2, keypoints_2);

	// find the key point with the largest scale
	double min = 100;
	for (int i = 0; i < keypoints_1.size(); i++) {
		if (keypoints_1[i].size < min) {
			min = keypoints_1[i].size;
		}
	}

	vector<KeyPoint> keypoint_largest_scale;
	for (int i = 0; i < keypoints_1.size(); i++) {
		if (keypoints_1[i].size == min) {
			keypoint_largest_scale.push_back(keypoints_1[i]);
		}
	}

	Mat image3;
	drawKeypoints(img_1, keypoint_largest_scale, image3, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("KeyPoint with smallest scale", image3);

	//Calculate descriptors (feature vectors)
	Mat descriptors_1, descriptors_2;
	f2d->compute(image3, keypoint_largest_scale, descriptors_1);
	f2d->compute(img_2, keypoints_2, descriptors_2);

	//Matching descriptor vector using BFMatcher
	BFMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	//plot all matching points
	Mat img_matches;
	drawMatches(image3, keypoint_largest_scale, img_2, keypoints_2, matches, img_matches);
	imshow("match image ofr keypoint with smallest scale", img_matches);

	waitKey(0);
}

void OpencvAlgorithm::SIFT_firstoctave(Mat img_1, Mat img_2) {
	//Create SIFT class pointer
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	//Detect the keypoints
	vector<KeyPoint> keypoints_1, keypoints_2;
	f2d->detect(img_1, keypoints_1);
	f2d->detect(img_2, keypoints_2);

	int first_octave = 1000000;
	for (int i = 0; i < keypoints_1.size(); i++) {
		if (keypoints_1[i].octave < first_octave) {
			first_octave = keypoints_1[i].octave;
		}
	}
	vector<KeyPoint> keypoint_new;
	for (int i = 0; i < keypoints_1.size(); i++) {
		if (keypoints_1[i].octave == first_octave) {
			keypoint_new.push_back(keypoints_1[i]);
		}
	}
	

	Mat image3;
	drawKeypoints(img_1, keypoint_new, image3, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("KeyPoint with first octave", image3);

	//Calculate descriptors (feature vectors)
	Mat descriptors_1, descriptors_2;
	f2d->compute(image3, keypoint_new, descriptors_1);
	f2d->compute(img_2, keypoints_2, descriptors_2);

	//Matching descriptor vector using BFMatcher
	BFMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	//plot all matching points
	Mat img_matches;
	drawMatches(image3, keypoint_new, img_2, keypoints_2, matches, img_matches);
	imshow("match image ofr keypoint with smallest scale", img_matches);

	waitKey(0);
}

void OpencvAlgorithm::SIFT_largestdistance(Mat img_1, Mat img_2) {
	//Create SIFT class pointer
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	//Detect the keypoints
	vector<KeyPoint> keypoints_1, keypoints_2;
	f2d->detect(img_1, keypoints_1);
	f2d->detect(img_2, keypoints_2);

	Mat imageL2, imageR2;
	drawKeypoints(img_1, keypoints_1, imageL2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	drawKeypoints(img_2, keypoints_2, imageR2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);


	//namedWindow("KeyPoints of imageL", 0);
	//namedWindow("KeyPoints of imageR", 0);

	imshow("KeyPoints of river1", imageL2);
	imshow("KeyPoints of river2", imageR2);

	//Calculate descriptors (feature vectors)
	Mat descriptors_1, descriptors_2;
	f2d->compute(img_1, keypoints_1, descriptors_1);
	f2d->compute(img_2, keypoints_2, descriptors_2);

	//Matching descriptor vector using BFMatcher
	BFMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	//plot all matching points
	Mat img_matches;
	drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_matches);
	imshow("match image", img_matches);

	// Calculate min and max distance of sift descriptors
	double maxsift = 0;
	double minsift = 100;
	for (int i = 0; i < descriptors_1.rows; i++) {
		double dist = matches[i].distance;
		if (dist < minsift) {
			minsift = dist;
		}
		if (dist > maxsift) {
			maxsift = dist;
		}
	}

	// finding good matches
	vector<DMatch> good_matches_sift;
	for (int i = 0; i < descriptors_1.rows; i++) {
		if (matches[i].distance == maxsift) {
			good_matches_sift.push_back(matches[i]);
		}
	}

	// plot all good matching points
	Mat img_good_matches;
	drawMatches(img_1, keypoints_1, img_2, keypoints_2, good_matches_sift, img_good_matches);
	imshow("largest distance match image", img_good_matches);

	waitKey(0);
}

void OpencvAlgorithm::SIFT_lastoctave(Mat img_1, Mat img_2) {
	//Create SIFT class pointer
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	//Detect the keypoints
	vector<KeyPoint> keypoints_1, keypoints_2;
	f2d->detect(img_1, keypoints_1);
	f2d->detect(img_2, keypoints_2);

	int first_octave = 0;
	for (int i = 0; i < keypoints_1.size(); i++) {
		if (keypoints_1[i].octave > first_octave) {
			first_octave = keypoints_1[i].octave;
		}
	}
	vector<KeyPoint> keypoint_new;
	for (int i = 0; i < keypoints_1.size(); i++) {
		if (keypoints_1[i].octave == first_octave) {
			keypoint_new.push_back(keypoints_1[i]);
		}
	}


	Mat image3;
	drawKeypoints(img_1, keypoint_new, image3, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("KeyPoint with first octave", image3);

	//Calculate descriptors (feature vectors)
	Mat descriptors_1, descriptors_2;
	f2d->compute(image3, keypoint_new, descriptors_1);
	f2d->compute(img_2, keypoints_2, descriptors_2);

	//Matching descriptor vector using BFMatcher
	BFMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptors_1, descriptors_2, matches);

	//plot all matching points
	Mat img_matches;
	drawMatches(image3, keypoint_new, img_2, keypoints_2, matches, img_matches);
	imshow("match image for keypoint with smallest scale", img_matches);

	waitKey(0);
}

void OpencvAlgorithm::SIFT_feature(Mat image,string path) {
	//Create SIFT class pointer
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	//Detect the keypoints
	vector<KeyPoint> keypoints_1, keypoints_2;
	f2d->detect(image, keypoints_1);

	Mat imageL2;
	drawKeypoints(image, keypoints_1, imageL2, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	imshow("KeyPoints of image", imageL2);
	imwrite(path, imageL2);
}

Kernel OpencvAlgorithm::Mat2Kernel(cv::Mat mat) {
	const int row = mat.rows;
	const int col = mat.cols;
	Kernel res(row, col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			res.set_data(mat.at<double>(i, j), i, j);
		}
	}
	return res;
}

vector<vector<double>> OpencvAlgorithm::PCA(cv::Mat pcaSet) {

	cout << "origin Matrix:\n" << pcaSet << endl;

	cv::PCA pca(pcaSet, cv::Mat(), CV_PCA_DATA_AS_ROW, 3);

	cout << "mean \n" << pca.mean << endl;// mean

	cout << "eigen value\n" << pca.eigenvalues << endl;// eigenvalue

	cout << "eigen vector\n" << pca.eigenvectors << endl;// eigenvector

	cv::Mat dst = pca.project(pcaSet);// projection in subspace
	cout << "projection in subspace\n" << dst << endl;// eigenvector

	vector<vector<double>> res(dst.rows, vector<double>(1, 0));
	for (int i = 0; i < dst.rows; i++) {
		double* data = dst.ptr<double>(i);
		res[i][0] = *data;
		for (int j = 1; j < dst.cols; j++) {
			data++;
			res[i].push_back(*data);
		}
	}
	return res;
}

vector<vector<double>> OpencvAlgorithm::PCA_no_print(cv::Mat pcaSet) {

	cv::PCA pca(pcaSet, cv::Mat(), CV_PCA_DATA_AS_ROW, 3);//参数依次为：原始数据；原始数据均值，输入空会自己计算；每行/列代表一个样本；保留多少特征值，默认全保留	
	cv::Mat dst = pca.project(pcaSet);//映射新空间
	vector<vector<double>> res(dst.rows, vector<double>(1, 0));
	for (int i = 0; i < dst.rows; i++) {
		double* data = dst.ptr<double>(i);
		res[i][0] = *data;
		for (int j = 1; j < dst.cols; j++) {
			data++;
			res[i].push_back(*data);
		}
	}
	return res;
}

cv::Mat OpencvAlgorithm::Kernel2Mat(Kernel k) {
	const int row_num = k.get_height();
	const int col_num = k.get_width();
	vector<double> array = k.Kernel2vector();

	cv::Mat pcaSet(row_num, col_num, CV_64FC1, cv::Scalar::all(0));
	double* data = nullptr;
	for (int i = 0; i < row_num; i++)
	{
		data = pcaSet.ptr<double>(i);
		for (int j = 0; j < col_num; j++)
		{
			*data++ = array[i*col_num + j];
		}
	}
	//cout << "origin Matrix:\n" << pcaSet << endl;
	return pcaSet;
}

void OpencvAlgorithm::k_mean_cluster(vector<vector<double>> data) {
	// cluster
	vector<Cluster> clusters_out = k_means(data, 4, 300);

	// cluster result
	for (int i = 0; i < clusters_out.size(); i++)
	{
		cout << "Cluster " << i + 1 << " :" << endl;

		// cluster center
		cout << "\t" << "Centroid selected: " << "\n\t\t[ ";
		for (int j = 0; j < clusters_out[i].centroid.size(); j++)
		{
			cout << clusters_out[i].centroid[j] << " ";
		}
		cout << "]" << endl;

		// cluster sample
		cout << "\t" << "Texture number:\n";
		for (int k = 0; k < clusters_out[i].samples.size(); k++)
		{
			int c = clusters_out[i].samples[k];
			cout << "\t\t[ ";
			for (int m = 0; m < data[0].size(); m++)
			{
				cout << data[c][m] << " ";
			}
			cout << "]";
			cout << c + 1 << endl;
		}
	}
}

vector<vector<int>> OpencvAlgorithm::k_mean_cluster_no_print(vector<vector<double>> data, int cluster_number, int iteration_number) {
	// cluster
	vector<Cluster> clusters_out = k_means(data, cluster_number, iteration_number);

	vector<vector<int>> res(cluster_number, vector<int>(1, 0));
	// cluster result
	for (int i = 0; i < clusters_out.size(); i++)
	{
		res[i][0] = clusters_out[i].samples[0];
		for (int k = 1; k < clusters_out[i].samples.size(); k++)
		{
			int c = clusters_out[i].samples[k];
			res[i].push_back(c);
		}
	}
	return res;
}

vector<vector<double>> OpencvAlgorithm::Energy_feature_computation(vector<Imagedata> Image, int window_size) {
	vector<vector<double>> res(25, vector<double>(510 * 510, 0));
	int ind = (window_size - 1) / 2;

	for (int s = 0; s < Image.size(); s++) {
		//Boundaryextension
		Imagedata temp = Image[s];
		Imagedata temp_ex = temp.Boundaryextension_double(ind);
		vector<vector<vector<double>>> rawdata = temp_ex.get_data_double();

		int height = temp.get_height();
		int width = temp.get_width();
		int byteperpixel = temp.get_byteperpixel();


		//Convolution
		Imagedata temp_ex_Conv(height + ind * 2, width + ind * 2, byteperpixel);
		temp_ex_Conv.set_doubledata();

		int index = 0;
		for (int i = ind; i < height + ind; i++) {
			for (int j = ind; j < width + ind; j++) {
				double Energy = 0;
				for (int k = 0; k < window_size; k++) {
					for (int l = 0; l < window_size; l++) {
						Energy += rawdata[0][i - ind + k][j - ind + l] * rawdata[0][i - ind + k][j - ind + l];
					}
				}
				res[s][index] = Energy / window_size / window_size;
				index++;
			}
		}
	}
	return res;
}

vector<vector<double>> OpencvAlgorithm::Energy_feature_normalizationwithLL(vector<vector<double>> Energy_feature) {
	for (int j = 0; j < Energy_feature[0].size(); j++) {
		double LL = Energy_feature[0][j];
		for (int i = 0; i < Energy_feature.size(); i++) {
			Energy_feature[i][j] /= LL;
		}
	}
	return Energy_feature;
}

vector<vector<double>> OpencvAlgorithm::k_mean_cluster_centroid(vector<vector<double>> data, int cluster_number, int iteration_number) {
	vector<vector<double>> res(cluster_number, vector<double>(data[0].size(), 0));

	// cluster
	vector<Cluster> clusters_out = k_means(data, cluster_number, iteration_number);

	// cluster center
	for (int i = 0; i < clusters_out.size(); i++)
	{
		for (int j = 0; j < clusters_out[i].centroid.size(); j++)
		{
			res[i][j] = clusters_out[i].centroid[j];
		}
	}
	return res;
}

vector<int> OpencvAlgorithm::hist_cal(Mat test, vector<vector<double>> centroids) {
	vector<int> score(2, 0);
	vector<double> centroids_1 = centroids[0];
	vector<double> centroids_2 = centroids[1];

	// Initialize Sift and Surf feature extractor:
	Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
	vector <KeyPoint> siftPoints;

	// Detect points of interest
	f2d->detect(test, siftPoints);

	Mat descriptors;
	f2d->compute(test, siftPoints, descriptors);
	for (int i = 0; i < descriptors.rows; i++) {
		vector<double> feature;
		for (int j = 0; j < descriptors.cols; j++) {
			feature.push_back(descriptors.at<double>(i, j));
		}
		double dist1 = cal_distance(feature, centroids_1);
		double dist2 = cal_distance(feature, centroids_2);
		if (dist1 < dist2) {
			score[0]++;
		}
		else {
			score[1]++;
		}
	}

	cout << "The number of feature: " << score[0] + score[1] << endl;
	cout << "First label score: " << score[0] << endl;
	cout << "Second label score: " << score[1] << endl;
	cout << endl;
	return score;
}

Mat OpencvAlgorithm::BOWKMEANSTRAINER() {
	int clusterCount = 2;
	BOWKMeansTrainer trainer(clusterCount, cv::TermCriteria(), 3, cv::KMEANS_PP_CENTERS);

	for (int i = 0; i < 5; i++) {
		Mat img = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\zero_" + to_string(i + 1) + ".jpg");

		//imshow("origin", img);
		// Initialize Sift and Surf feature extractor:
		Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
		vector <KeyPoint> siftPoints;

		// Detect points of interest
		f2d->detect(img, siftPoints);

		Mat descriptors;
		f2d->compute(img, siftPoints, descriptors);

		Mat image;
		drawKeypoints(img, siftPoints, image, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

		imwrite("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\zero_Feature_" + to_string(i + 1) + ".jpg", image);

		//	imshow("KeyPoints of imageR", image);
		trainer.add(descriptors);
	}


	for (int i = 0; i < 4; i++) {
		Mat img = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\one_" + to_string(i + 1) + ".jpg");

		//imshow("origin", img);
		// Initialize Sift and Surf feature extractor:
		Ptr<Feature2D> f2d = xfeatures2d::SIFT::create();
		vector <KeyPoint> siftPoints;

		// Detect points of interest
		f2d->detect(img, siftPoints);

		Mat descriptors;
		f2d->compute(img, siftPoints, descriptors);

		Mat image;
		drawKeypoints(img, siftPoints, image, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

		imwrite("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\one_Feature_" + to_string(i + 1) + ".jpg", image);
		//imshow("KeyPoints of imageR", image);
		trainer.add(descriptors);
	}
	Mat All_descriptors = trainer.cluster();
	return All_descriptors;
}

void OpencvAlgorithm::BOWHIST_STATISTIC(Kernel Centroids) {
	Mat test = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\one_1.jpg");	
	cout << "one_1" << endl;
	hist_cal(test, Centroids.Kernel2vector2D());

	test = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\one_2.jpg");
	cout << "one_2" << endl;
	hist_cal(test, Centroids.Kernel2vector2D());

	test = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\one_3.jpg");
	cout << "one_3" << endl;
	hist_cal(test, Centroids.Kernel2vector2D());

	test = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\one_4.jpg");
	cout << "one_4" << endl;
	hist_cal(test, Centroids.Kernel2vector2D());

	test = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\one_5.jpg");
	cout << "one_5" << endl;
	hist_cal(test, Centroids.Kernel2vector2D());

	test = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\zero_1.jpg");
	cout << "zero_1" << endl;
	hist_cal(test, Centroids.Kernel2vector2D());

	test = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\zero_2.jpg");
	cout << "zero_2" << endl;
	hist_cal(test, Centroids.Kernel2vector2D());

	test = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\zero_3.jpg");
	cout << "zero_3" << endl;
	hist_cal(test, Centroids.Kernel2vector2D());

	test = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\zero_4.jpg");
	cout << "zero_4" << endl;
	hist_cal(test, Centroids.Kernel2vector2D());

	test = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\zero_5.jpg");
	cout << "zero_5" << endl;
	hist_cal(test, Centroids.Kernel2vector2D());

	test = imread("G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\eight.jpg");
	cout << "eight" << endl;
	SIFT_feature(test, "G:\\569\\Homework\\HW4\\Image\\HW4_Images_JPG\\eight_Feature.jpg");
	hist_cal(test, Centroids.Kernel2vector2D());
}