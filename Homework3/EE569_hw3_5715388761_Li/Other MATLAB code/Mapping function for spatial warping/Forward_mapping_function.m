% AB = UV * inv(xy)
% AB is foward mapping funciton

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

xy = [1 1 1 1 1 1;x0 x1 x2 x3 x4 x5;y0 y1 y2 y3 y4 y5;x0^2 x1^2 x2^2 x3^2 x4^2 x5^2;x0*y0 x1*y1 x2*y2 x3*y3 y4*y4 x5*y5;y0^2 y1^2 y2^2 y3^2 y4^2 y5^2];
UV = [u0 u1 u2 u3 u4 u5;v0 v1 v2 v3 v4 v5];
AB = UV * inv(xy);

pab = pinv(AB);

%% For verifying

xy0 = [1;x0;y0;x0^2;x0*y0;y0^2];
xy1 = [1;x1;y1;x1^2;x1*y1;y1^2];
xy2 = [1;x2;y2;x2^2;x2*y2;y2^2];
xy3 = [1;x3;y3;x3^2;x3*y3;y3^2];
xy4 = [1;x4;y4;x4^2;x4*y4;y4^2];
xy5 = [1;x5;y5;x5^2;x5*y5;y5^2];
uv0 = AB * xy0
uv1 = AB * xy1
uv2 = AB * xy2
uv3 = AB * xy3
uv4 = AB * xy4
uv5 = AB * xy5


xt = 128;
yt = 383;
xyt = [1;xt;yt;xt^2;xt*yt;yt^2];
uvt = AB * xyt
