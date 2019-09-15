x = [-0.24;-0.16;0.51;0.009;-0.225;0.004;-0.226;-0.138;0.224;0.143;0.187;-0.089];
y = [0.041;0.078;0.0338;-0.107;-0.0107;-0.114;-0.008;0.072;0.098;0.091;-0.139;-0.036];
z = [0.0599;-0.08;-0.08;-0.0679;-.0011;-0.04;-0.0055;-0.0582;0.05;0.086;0.085;0.054];

figure(1);
scatter3(x,y,z);
xlabel('1st principle component');
ylabel('2nd principle component');
zlabel('3rd principle component');
title('Feature vector');

figure(2);
scatter(x,y);
xlabel('1st principle component');
ylabel('2nd principle component');

figure(3);
scatter(x,z);
xlabel('1st principle component');
ylabel('3rd principle component');

