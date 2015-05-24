clc;
clear all;

% 1.ѵ��ǰ����
phi = importdata('phi.txt');
% (1)��figure(1)��v1-v2-v3����ϵ�ϻ���phi(1 <= i <= 20)  
figure(1);
plot3(phi(1,:), phi(2,:), phi(3,:),'ro');
xlabel('\it{v_{1}}'), ylabel('\it{v_{2}}'), zlabel('\it{v_{3}}');
axis equal, axis normal;
title('\fontsize{12}\fontname{����}     ѵ��ǰ����\Phi');
legend('\it{\phi_{i}}','location','northeastoutside'), legend boxoff;
grid on;
hold on;
% (2)�����ֵmeanPhi
meanPhi = mean(phi,2);
meanPhi,

% (3)��figure(1)��v1-v2-v3����ϵ�ϻ���meanPhi
figure(1);
plot3(meanPhi(1,:), meanPhi(2,:), meanPhi(3,:), 'b*');
% title('$$\bar{\phi}$$','interpreter','latex','fontsize',12,'fontname','����');
% h = legend('$$\bar{\phi}$$', 'location','northeastoutside');
% set(h,'interpreter','latex','FontSize',10,'FontName','����');
% legend boxoff;
% grid on;

% (4)����X (Xi = phi(i) - meanPhi)
X = phi - repmat(meanPhi,1,20);
X,

% (5)��figure(2)��v1-v2-v3����ϵ�ϻ���xi
figure(2);
plot3(X(1,:), X(2,:), X(3,:),'mo');
xlabel('\it{v_{1}}'), ylabel('\it{v_{2}}'), zlabel('\it{v_{3}}');
axis equal, axis normal;
title('\fontsize{12}\fontname{����}     ȥ��ֵ��Ľ��X');
legend('\it{x_{i}}','location','northeastoutside'), legend boxoff;
grid on;

% (6)����Э�������Cx
Cx = X * X';
Cx,

% (7)(8)����Cx������ֵ����������
[V, D] = eigs(Cx);
D, % ����ֵ
V, % ��������

% (9)��֤Cx = UTU'
tempCx = V * D * V';
tempCx,
Cx,

% (10)����X��u1-u2-u3����ϵ�ϵ�ͶӰ����������
Y = V' * X;
Y,

% (11)��figure(3)��u1-u2-u3����ϵ�ϻ���yi
figure(3);
plot3(Y(1,:), Y(2,:), Y(3,:), 'b*');
xlabel('\it{u_{1}}'), ylabel('\it{u{2}}'), zlabel('\it{u_{3}}');
title('\fontsize{12}\fontname{����}     �任��Ľ��Y');
legend('\it{y_{i}}','location','northeastoutside'), legend boxoff;
grid on;

% 2.���㱣������Ԫ�ϵ�ͶӰ������ؽ����
% (1)���㱣������Ԫ�ϵ�ͶӰ��������
Y1 = [1;0;0;] * [1 0 0] * Y;
Y1,

% (2)�����ؽ�����X1
X1 = V * Y1;
X1,

% (3)�����ؽ�����phi1
phi1 = X1 + repmat(meanPhi, 1, 20);
phi1,

% (4)��figure(4)��v1-v2-v3����ϵ����phi��phi1
figure(4);
plot3(phi(1,:), phi(2,:), phi(3,:), 'ro');
hold on;
plot3(phi1(1,:), phi1(2,:), phi1(3, :),'b*');
xlabel('\it{v_{1}}'), ylabel('\it{v{2}}'), zlabel('\it{v_{3}}');
grid on;

% (5)�����ؽ����ei
e1 = norm(phi - phi1);
e1,

% 3.���㱣��С��Ԫ�ϵ�ͶӰ������ؽ����
% (1)���㱣��С��Ԫ�ϵ�ͶӰ��������
Y2 = [0; 0; 1] * [0, 0, 1] * Y;
Y2,

% (2)�����ؽ�����X2
X2 = V * Y2;
X2,

% (3)�����ؽ�����phi2
phi2 = X2 + repmat(meanPhi, 1, 20);
phi2,

% (4)��figure(5)��v1-v2-v3����ϵ����phi��phi2
figure(5);
plot3(phi(1,:), phi(2,:), phi(3,:), 'go');
hold on;
plot3(phi2(1,:), phi2(2,:), phi2(3, :),'y*');
xlabel('\it{v_{1}}'),ylabel('\it{v{2}}'),zlabel('\it{v_{3}}');
grid on;

% (5)�����ؽ����ei
e2 = norm(phi - phi2);
e2,

% (6)�Ƚϲ�������2����3�л��ڲ�ͬ��Ԫ�����ؽ����Ĳ��켰��ԭ��

% 4.���㲻ͬ���������ڴ���Ԫ�ϵ�ͶӰ������ؽ����
% ������������������
phi21 = [-4.7852; 13.2643; 12.6948];
phi22 = [22.9841; -15.5962; -11.6873];

% (1)����phi21��phi22��u1-u2-u3����ϵ�ϵ���������y21��y22 
x21 = phi21 - meanPhi;
x22 = phi22 - meanPhi;
y21 = V' * x21;
y22 = V' * x22;
y21, y22,

% (2)���㱣������Ԫ�ϵ�ͶӰ��������
y211 = [1; 0; 0] * [1 0 0] * y21;
y221 = [1; 0; 0] * [1 0 0] * y22;
y211, y221,

% (3)�����ؽ�����phi211��phi221 
x211 = V * y211;
x221 = V * y221;
phi211 = x211 + meanPhi;
phi221 = x221 + meanPhi;
phi211, phi221,

% (4)��figure(6)��v1-v2-v3 ����ϵ����phi2��phi3(1 <= i <= 22)
phi2 = [phi phi21 phi22];
phi3 = [phi1 phi211 phi221];
phi2, phi3,
figure(6);
plot3(phi2(1,:), phi2(2,:), phi2(3,:), 'ro');
hold on;
plot3(phi3(1,:), phi3(2,:), phi3(3,:), 'b*');
xlabel('\it{v_{1}}'),ylabel('\it{v{2}}'),zlabel('\it{v_{3}}');
grid on;

% (5)�����ؽ����e21��e22�Ƚϲ�����e21��e22�Ĳ��켰��ԭ��
e21 = norm(phi21 - phi211);
e22 = norm(phi22 - phi221);
e21, e22,












    
