clear all;
clc;

% 5.基于PCA的人脸识别 (Eigenface)
% (1)读入20幅训练图像
cd('E:\tianhuifang\matlab learning\workspace\pcatest1_tian\trainningimages');
files = dir('*.bmp');
m = size(files,1);
G = zeros([72, 64, m], 'uint8');
for i = 1 : m
    G(:,:,i) = imread(files(i).name);
end

G = double(reshape(G,4608,m));

% (2)计算均值
meanP = mean(G,2);
meanP = uint8(reshape(meanP,72,64));
% figure(8);
% imshow(meanP),

% (3)计算X
meanP = double(reshape(meanP,4608,1));
X3 = G - repmat(meanP,[1,m]);
% X3,
 
% (4)计算协方差矩阵
Cx1 = X3 * X3';
% Cx1,

% (5)计算Cx的特征值D和特征向量V,并记录计算所耗费的时间time 
tic,
[V, D] = eig(Cx1);
toc,
time = num2str(toc);
time,

% (6)计算LX
Lx = X3' * X3;
% Lx,

% (7)计算LX的特征值V1和特征向量D1,并记录计算所耗费的时间time1
tic,
[V1, D1] = eig(Lx);
toc,
time1 = num2str(toc);
time1,

% (8)计算UL,i
UL = X3 * V1 / sqrt(D1);
% UL,

% (11)在figure(i)中显示特征脸Eigenface UL,i
UL = UL * D1;
UL = uint8(reshape(UL,72,64,20));
for i = 2 : 20
    figure(i);
    imshow(UL(:,:,i));
end

% (12)计算4幅测试图像,及其在UL空间中的重建图像,
% 在figure(i)和figure(10+i)中分别显示测试图像和重建图像

% 读入测试图像
cd('E:\tianhuifang\matlab learning\workspace\pcatest1_tian\trainningimages\TestingSet');
tfiles = dir('*.bmp');
n = size(tfiles,1);
T = zeros([72, 64, n], 'uint8');
for i = 1 : n
    T(:,:,i) = imread(tfiles(i).name);
end

T = double(reshape(T,4608,n));

% 计算投影座标向量Y = UL' * X3
UL = double(reshape(UL,4608,20));
Y = UL' * X3;
Y,

% 计算大主元上的投影座标向量Y1 = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]'
% * ([1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] * Y)
Y1 = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]'*...
    ([1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] * Y);
Y1,

% 计算重建向量X1 = V1 * Y1;
X1 = UL * Y1;
X1;

% 计算重建向量phi1 = X1 + meanP;
phi1 = X1 + repmat(meanP,1,20);
phi1;

% 显示测试图像
T = uint8(reshape(T,72,64,4));
for j = 1 : 4
    figure(j);
    imshow(T(:,:,j));
end

% 显示重建图像
phi1 = uint8(reshape(phi1,72,64,20));
for p = 1 : 4
    figure(p);
    imshow(phi1(:,:,p));
end

% (13)计算4幅测试图像的重建误差
T = double(reshape(T,4608,4));
phi1 = double(reshape(phi1,4608,20));
for i = 1 : 4
    e(i) = norm(T(:,i) - phi1(:,i));
end
