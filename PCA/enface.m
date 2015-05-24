clear all;
clc;

% 5.����PCA������ʶ�� (Eigenface)
% (1)����20��ѵ��ͼ��
cd('E:\tianhuifang\matlab learning\workspace\pcatest1_tian\trainningimages');
files = dir('*.bmp');
m = size(files,1);
G = zeros([72, 64, m], 'uint8');
for i = 1 : m
    G(:,:,i) = imread(files(i).name);
end

G = double(reshape(G,4608,m));

% (2)�����ֵ
meanP = mean(G,2);
meanP = uint8(reshape(meanP,72,64));
% figure(8);
% imshow(meanP),

% (3)����X
meanP = double(reshape(meanP,4608,1));
X3 = G - repmat(meanP,[1,m]);
% X3,
 
% (4)����Э�������
Cx1 = X3 * X3';
% Cx1,

% (5)����Cx������ֵD����������V,����¼�������ķѵ�ʱ��time 
tic,
[V, D] = eig(Cx1);
toc,
time = num2str(toc);
time,

% (6)����LX
Lx = X3' * X3;
% Lx,

% (7)����LX������ֵV1����������D1,����¼�������ķѵ�ʱ��time1
tic,
[V1, D1] = eig(Lx);
toc,
time1 = num2str(toc);
time1,

% (8)����UL,i
UL = X3 * V1 / sqrt(D1);
% UL,

% (11)��figure(i)����ʾ������Eigenface UL,i
UL = UL * D1;
UL = uint8(reshape(UL,72,64,20));
for i = 2 : 20
    figure(i);
    imshow(UL(:,:,i));
end

% (12)����4������ͼ��,������UL�ռ��е��ؽ�ͼ��,
% ��figure(i)��figure(10+i)�зֱ���ʾ����ͼ����ؽ�ͼ��

% �������ͼ��
cd('E:\tianhuifang\matlab learning\workspace\pcatest1_tian\trainningimages\TestingSet');
tfiles = dir('*.bmp');
n = size(tfiles,1);
T = zeros([72, 64, n], 'uint8');
for i = 1 : n
    T(:,:,i) = imread(tfiles(i).name);
end

T = double(reshape(T,4608,n));

% ����ͶӰ��������Y = UL' * X3
UL = double(reshape(UL,4608,20));
Y = UL' * X3;
Y,

% �������Ԫ�ϵ�ͶӰ��������Y1 = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]'
% * ([1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] * Y)
Y1 = [1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0]'*...
    ([1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0] * Y);
Y1,

% �����ؽ�����X1 = V1 * Y1;
X1 = UL * Y1;
X1;

% �����ؽ�����phi1 = X1 + meanP;
phi1 = X1 + repmat(meanP,1,20);
phi1;

% ��ʾ����ͼ��
T = uint8(reshape(T,72,64,4));
for j = 1 : 4
    figure(j);
    imshow(T(:,:,j));
end

% ��ʾ�ؽ�ͼ��
phi1 = uint8(reshape(phi1,72,64,20));
for p = 1 : 4
    figure(p);
    imshow(phi1(:,:,p));
end

% (13)����4������ͼ����ؽ����
T = double(reshape(T,4608,4));
phi1 = double(reshape(phi1,4608,20));
for i = 1 : 4
    e(i) = norm(T(:,i) - phi1(:,i));
end
