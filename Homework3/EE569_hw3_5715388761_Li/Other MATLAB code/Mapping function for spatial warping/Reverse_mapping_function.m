% AB = xy * inv(UV)
% AB is reverse mapping funciton

x0 = 255;
y0 = 256;
x1 = 128;
y1 = 383;
x2 = 383;
y2 = 383;
x3 = 0;
y3 = 511;
x4 = 255;
y4 = 511;
x5 = 511;
y5 = 511;

u0 = x0;
u1 = x1;
u2 = x2;
u3 = x3;
u4 = x4;
u5 = x5;
v0 = y0;
v1 = y1;
v2 = y2;
v3 = y3;
v4 = 383;
v5 = y5;

uv = [1 1 1 1 1 1;u0 u1 u2 u3 u4 u5;v0 v1 v2 v3 v4 v5;u0^2 u1^2 u2^2 u3^2 u4^2 u5^2;u0*v0 u1*v1 u2*v2 u3*v3 u4*v4 u5*v5;v0^2 v1^2 v2^2 v3^2 v4^2 v5^2];
xy = [x0 x1 x2 x3 x4 x5;y0 y1 y2 y3 y4 y5];
AB = xy * inv(uv);




