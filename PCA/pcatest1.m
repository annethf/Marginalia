clc;
clear all;

% 1.训练前样本
phi = importdata('phi.txt');
% (1)在figure(1)中v1-v2-v3坐标系上绘制phi(1 <= i <= 20)  
figure(1);
plot3(phi(1,:), phi(2,:), phi(3,:),'ro');
xlabel('\it{v_{1}}'), ylabel('\it{v_{2}}'), zlabel('\it{v_{3}}');
axis equal, axis normal;
title('\fontsize{12}\fontname{黑体}     训练前样本\Phi');
legend('\it{\phi_{i}}','location','northeastoutside'), legend boxoff;
grid on;
hold on;
% (2)计算均值meanPhi
meanPhi = mean(phi,2);
meanPhi,

% (3)在figure(1)中v1-v2-v3坐标系上绘制meanPhi
figure(1);
plot3(meanPhi(1,:), meanPhi(2,:), meanPhi(3,:), 'b*');
% title('$$\bar{\phi}$$','interpreter','latex','fontsize',12,'fontname','黑体');
% h = legend('$$\bar{\phi}$$', 'location','northeastoutside');
% set(h,'interpreter','latex','FontSize',10,'FontName','黑体');
% legend boxoff;
% grid on;

% (4)计算X (Xi = phi(i) - meanPhi)
X = phi - repmat(meanPhi,1,20);
X,

% (5)在figure(2)中v1-v2-v3坐标系上绘制xi
figure(2);
plot3(X(1,:), X(2,:), X(3,:),'mo');
xlabel('\it{v_{1}}'), ylabel('\it{v_{2}}'), zlabel('\it{v_{3}}');
axis equal, axis normal;
title('\fontsize{12}\fontname{黑体}     去均值后的结果X');
legend('\it{x_{i}}','location','northeastoutside'), legend boxoff;
grid on;

% (6)计算协方差矩阵Cx
Cx = X * X';
Cx,

% (7)(8)计算Cx的特征值和特征向量
[V, D] = eigs(Cx);
D, % 特征值
V, % 特征向量

% (9)验证Cx = UTU'
tempCx = V * D * V';
tempCx,
Cx,

% (10)计算X在u1-u2-u3坐标系上的投影坐标向量。
Y = V' * X;
Y,

% (11)在figure(3)中u1-u2-u3坐标系上绘制yi
figure(3);
plot3(Y(1,:), Y(2,:), Y(3,:), 'b*');
xlabel('\it{u_{1}}'), ylabel('\it{u{2}}'), zlabel('\it{u_{3}}');
title('\fontsize{12}\fontname{黑体}     变换后的结果Y');
legend('\it{y_{i}}','location','northeastoutside'), legend boxoff;
grid on;

% 2.计算保留大主元上的投影坐标的重建误差
% (1)计算保留大主元上的投影坐标向量
Y1 = [1;0;0;] * [1 0 0] * Y;
Y1,

% (2)计算重建向量X1
X1 = V * Y1;
X1,

% (3)计算重建向量phi1
phi1 = X1 + repmat(meanPhi, 1, 20);
phi1,

% (4)在figure(4)中v1-v2-v3坐标系绘制phi和phi1
figure(4);
plot3(phi(1,:), phi(2,:), phi(3,:), 'ro');
hold on;
plot3(phi1(1,:), phi1(2,:), phi1(3, :),'b*');
xlabel('\it{v_{1}}'), ylabel('\it{v{2}}'), zlabel('\it{v_{3}}');
grid on;

% (5)计算重建误差ei
e1 = norm(phi - phi1);
e1,

% 3.计算保留小主元上的投影坐标的重建误差
% (1)计算保留小主元上的投影坐标向量
Y2 = [0; 0; 1] * [0, 0, 1] * Y;
Y2,

% (2)计算重建向量X2
X2 = V * Y2;
X2,

% (3)计算重建向量phi2
phi2 = X2 + repmat(meanPhi, 1, 20);
phi2,

% (4)在figure(5)中v1-v2-v3坐标系绘制phi和phi2
figure(5);
plot3(phi(1,:), phi(2,:), phi(3,:), 'go');
hold on;
plot3(phi2(1,:), phi2(2,:), phi2(3, :),'y*');
xlabel('\it{v_{1}}'),ylabel('\it{v{2}}'),zlabel('\it{v_{3}}');
grid on;

% (5)计算重建误差ei
e2 = norm(phi - phi2);
e2,

% (6)比较并阐释题2及题3中基于不同主元坐标重建误差的差异及其原因。

% 4.计算不同测试样本在大主元上的投影坐标的重建误差
% 给定的两个测试样本
phi21 = [-4.7852; 13.2643; 12.6948];
phi22 = [22.9841; -15.5962; -11.6873];

% (1)计算phi21和phi22在u1-u2-u3坐标系上的坐标向量y21和y22 
x21 = phi21 - meanPhi;
x22 = phi22 - meanPhi;
y21 = V' * x21;
y22 = V' * x22;
y21, y22,

% (2)计算保留大主元上的投影坐标向量
y211 = [1; 0; 0] * [1 0 0] * y21;
y221 = [1; 0; 0] * [1 0 0] * y22;
y211, y221,

% (3)计算重建向量phi211和phi221 
x211 = V * y211;
x221 = V * y221;
phi211 = x211 + meanPhi;
phi221 = x221 + meanPhi;
phi211, phi221,

% (4)在figure(6)中v1-v2-v3 坐标系绘制phi2和phi3(1 <= i <= 22)
phi2 = [phi phi21 phi22];
phi3 = [phi1 phi211 phi221];
phi2, phi3,
figure(6);
plot3(phi2(1,:), phi2(2,:), phi2(3,:), 'ro');
hold on;
plot3(phi3(1,:), phi3(2,:), phi3(3,:), 'b*');
xlabel('\it{v_{1}}'),ylabel('\it{v{2}}'),zlabel('\it{v_{3}}');
grid on;

% (5)计算重建误差e21和e22比较并阐释e21和e22的差异及其原因
e21 = norm(phi21 - phi211);
e22 = norm(phi22 - phi221);
e21, e22,












    
