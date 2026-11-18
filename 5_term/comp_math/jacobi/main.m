clc;
clear;

# 1000x1000 -> 8000000 байт ~ 7.6 мбайт

N = 1000;

rand("seed", 20);

x_target = rand(N, 1);

MAX_ITERS = 10000;
EPSILON = 1e-10;

A = rand(N);
A += diag(sum(A, 2) * 2);

b = A * x_target;

D = diag(A); % вектор-столбец
B = A - diag(D);
D_inv = 1 ./ D; % быстрее, чем inv от матрицы

C = -D_inv .* B;
r = D_inv .* b;

x_prev = ones(N, 1);

tic;

for i = 1:MAX_ITERS
  x_new = C * x_prev + r;

  if (norm(x_new - x_prev) < EPSILON)
    break;
  end

  x_prev = x_new;
end

toc

printf("Итераций выполнено: %d\n", i);
printf("Относительная ошибка: %e\n", norm(x_new - x_target) / norm(x_target));
printf("Абсолютная ошибка: %e\n", norm(x_new - x_target));
