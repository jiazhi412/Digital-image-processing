D = dir('G:\569\Homework\HW2\Image\Reverse\*.jpg');
for i = 1:30
    ori = imread(['G:\569\Homework\HW2\Image\Reverse\',D(i).name]);
    reverse = 255 - ori;
    imwrite(reverse,['G:\569\Homework\HW2\Image\Reversed\',D(i).name]);
end