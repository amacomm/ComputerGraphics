% (с) Сошников Даниил 6409. Вариант 5
clear all;

global lambda = 0.532; % мкм
global k = 2*pi/lambda;
NA = 0.95; %[0.65 0.8 0.95]
n = 1;
global alpha = asin(NA/n);
global beta = 1;
global z = 0;

global x = linspace(-1, 1, 151);
global X;
global Y;
[X, Y] = meshgrid(x, x);
[PHI, R] = cart2pol(X, Y);

function y = l(teta, g)
  global alpha beta;
  y = g(teta).*exp(-(beta*g(teta)/g(alpha)).^2);
endfunction

% для апланатического объекта
function y = T_apl(teta)
  y = cos(teta).^0.5;
endfunction

% для дифракционной линзы
function y = T_dif(teta)
  y = cos(teta).^-1.5;
endfunction

function [Er, Ez] = getfield_int(R, T, l)
  global k z alpha;
  Er = integral(@(teta) l(teta).*T(teta).*exp(i*k*z*cos(teta)).* ...
  sin(2*teta).*besselj(1, k*R.*sin(teta)), 0, alpha, 'ArrayValued', true);
  Ez = 2*i*integral(@(teta) l(teta).*T(teta).*exp(i*k*z*cos(teta)).* ...
  sin(teta).^2.*besselj(0, k*R.*sin(teta)), 0, alpha, 'ArrayValued', true);
endfunction

function [Er, Ez] = getfield_sum(R, T, l)
  global k z alpha;
  Er = zeros(size(R, 1), size(R, 2));
  Ez = Er;

  N = 256; % число разбиения интеграла
  dteta = alpha / N;
  for teta=dteta/2:dteta:alpha
    tmp = l(teta).*T(teta).*exp(i*k*z*cos(teta));
    Er = Er + tmp.*sin(2*teta).*besselj(1, k*R.*sin(teta));
    Ez = Ez + tmp.*sin(teta).^2.*besselj(0, k*R.*sin(teta));
  endfor
  Er= Er * dteta;
  Ez = Ez * 2*i*dteta;
endfunction

%вывод интенсивности на экран
function show(I, name) 
  global X Y x lambda;
  figure;
  imagesc(X, Y, I);
  colorbar();
  title(cstrcat('Intensity ', name));
  xlabel("x, мкм");
  ylabel("y, мкм");
  axis('xy');
  axis('square');

  nx = linspace(-1, 1, 1000);
  f = interp1(x, I((end+1)/2, :), nx, 'linear');
  mf = max(f);
  figure;
  hold on;
  plot(nx, f);
  plot(nx, (f >= mf/2)*mf/2);
  title(name);
  xlabel("x, мкм");
  ylabel("Intensity");

  % ширина фокусного пятна в длиннах волн
  (sum(f >= mf/2)-1)*(nx(2)-nx(1))/lambda
endfunction

tic;
[Er, Ez] = getfield_int(R, @T_apl, @(x) l(x, @sin));
toc
show(abs(Er).^2 + abs(Ez).^2, 'apl');

tic;
[Er, Ez] = getfield_sum(R, @T_dif, @(x) l(x, @tan));
toc
show(abs(Er).^2 + abs(Ez).^2, 'dif');
