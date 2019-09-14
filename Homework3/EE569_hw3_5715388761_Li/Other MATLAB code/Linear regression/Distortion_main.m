clear all;
clc;

path_read = 'G:\569\Homework\HW3\Image\HW3_images_JPG\classroom.jpg';

image = imread(path_read);
[m,n] = size(image);

% static final magic number
k1 = -0.3536;
k2 = 0.1730;
k3 = 0;
fx = 600;
fy = 600;
uc = n/2;
vc = m/2;

% ud vd distortion image in Image coordinate

% u v correction image in Image coordinate
u = 1:1:n;
v = 1:1:m;

% x y correction image in camera coordinate
x = (u - uc)/fx;
y = (v - vc)/fy;

% xd yd camera coordinate
xd=zeros(1,m*n);
yd=zeros(1,m*n);
index = 1;
for i = 1:n
    for j = 1:m
        r = sqrt(x(i)^2 + y(j)^2);
        xd(index) = x(i)*(1+k1*r^2+k2*r^4+k3*r^6);
        yd(index) = y(j)*(1+k1*r^2+k2*r^4+k3*r^6);
        index = index + 1;
    end
end

x_forplot=zeros(1,m*n);
y_forplot=zeros(1,m*n);
for i = 1:n
    for j = 1:m
        y_forplot((i-1)*712+j) = y(j);
        x_forplot((i-1)*712+j) = x(i);
    end
end

xx_forplot = xd .* xd;
yy_forplot = yd .* yd;
xy_forplot = xd .* yd;

% xd(1:1000)\x_forplot(1:1000);

%% Plot different term in (x,y) space
figure(1);
scatter3(x_forplot,y_forplot,xd);
xlabel('X');ylabel('Y');zlabel('Xd');
figure(2);
scatter3(x_forplot,y_forplot,yd);
xlabel('X');ylabel('Y');zlabel('Yd');

figure(3);
scatter3(x_forplot,y_forplot,xx_forplot);
xlabel('X');ylabel('Y');zlabel('Xd^2');

figure(4);
scatter3(x_forplot,y_forplot,yy_forplot);
xlabel('X');ylabel('Y');zlabel('Yd^2');

figure(5);
scatter3(x_forplot,y_forplot,xy_forplot);
xlabel('X');ylabel('Y');zlabel('Xd * Yd');

%% Figure out the coefficient of different linear term
polyfit(x_forplot,xd,1)
polyfit(y_forplot,xd,1)

polyfit(x_forplot,yd,1) 
polyfit(y_forplot,yd,1)

polyfit(xx_forplot,xd,1)
polyfit(yy_forplot,xd,1)

polyfit(xx_forplot,yd,1)
polyfit(yy_forplot,yd,1)

polyfit(xy_forplot,xd,1)
polyfit(xy_forplot,yd,1)

%% Generate the linear reverse mapping function
x = (xd - 0.686 * 0.001)/0.8601;
y = (yd - 0.7144 * 0.001)/0.8819;

u = x * 600 + 536;
v = y * 600 + 356;

image_new = zeros(m,n);


%% linear regression
% for i = 1:n
%     for j = 1:m
%         x_d = (i - uc)/fx;
%         y_d = (j - vc)/fy;
%         x_actual = (x_d - 0.686 * 0.001)/0.8601 ;
%         y_actual = (y_d - 0.7144 * 0.001)/0.8819 ;
% %         if(x_d == 0)
% %             continue;
% %         end
% %         y_actual = x_actual / x_d * y_d;
%         
%         u = x_actual * fx + uc+90;
%         v = y_actual * fy + vc+90;
%         
%         image_new(round(v),round(u)) = image(j,i);
%     end
% end

%% Reverse mapping

for i = 1:n+85+50
    for j = 1:m+51+50
        x = (i - uc-85)/fx;
        y = (j - vc-51)/fy;        
        r = sqrt(x^2 + y^2);
        x_d = x*(1+k1*r^2+k2*r^4+k3*r^6);
        y_d = y*(1+k1*r^2+k2*r^4+k3*r^6);
        u = x_d* fx + uc;
        v = y_d* fy + vc;        
        image_new(j,i) = image(round(v),round(u));
    end
end

figure(6);
imshow(image);
figure(7);
imshow(uint8(image_new));