clear all;
clc;
namelist = dir('..\Gaussian\*.txt');


len = length(namelist);
for i = 1:len
    file_name{i}=namelist(i).name;
    x(i)= load(file_name{i});
end

for i = 1:9 %size
    for j = 1:10 %sigma
        temp(i,j) = x(i+9*(j-1));
    end
end

for j = 1:9
    
    for i = 1:5
        z(i) = temp(j,5+i);
    end
    
    for i = 5:10
        z(i) = temp(j,i-5+1);
    end
    
    y = [3:2:21];
    plot(y,z);
    hold on;
end
ylabel("PSNR(dB)");
xlabel("Window size");
legend('sigma = 0.5','sigma = 1.0','sigma = 1.5','sigma = 2.0','sigma = 2.5','sigma = 3.0','sigma = 3.5','sigma = 4.0','sigma = 4.5');
