D = dir('G:\569\Homework\HW2\Image\Enhance\*.jpg');
for i = 1:21
    ori = imread(['G:\569\Homework\HW2\Image\Enhance\',D(i).name]);
    enhance = im2bw(ori,0.88);
    imwrite(enhance,['G:\569\Homework\HW2\Image\Enhanced\',D(i).name]);
end