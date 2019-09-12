clear all;
clc;
namelist = dir('..\Uniform\*.txt');



len = length(namelist);
for i = 1:len
    file_name{i}=namelist(i).name;
    x(i)= load(file_name{i});
end

for i = 1:4
    z(i) = x(5+i);
end

for i = 5:9
    z(i) = x(i+1-5);
end

y = [3:2:19];
plot(y,z);
ylabel("PSNR(dB)");
xlabel("Window size");