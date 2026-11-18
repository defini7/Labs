import numpy as np
import scipy.linalg as la
import time


N = 1000

MAX_ITERS = 10000
EPSILON = 1e-10

np.random.seed(20)
x_target = np.random.rand(N)

A = np.random.rand(N, N)

indices = np.arange(N)
row_sums = np.sum(A, axis=1)

np.fill_diagonal(A, row_sums * 2)

b = A @ x_target

D_vec = np.diag(A)
D_inv = 1.0 / D_vec

B = A - np.diag(D_vec)

# (N,)=(1, N) -> (N, 1)
C = -D_inv[:, None] * B
r = D_inv * b

x_prev = np.ones(N)

start = time.time()

for i in range(MAX_ITERS):
    x_new = C @ x_prev + r

    if la.norm(x_new - x_prev) < EPSILON:
        break

    x_prev = x_new

elapsed = time.time() - start

print(f"Итераций выполнено: {i + 1}")
print(f"Относительная ошибка: {la.norm(x_new - x_target) / la.norm(x_target):e}")
print(f"Абсолютная ошибка: {la.norm(x_new - x_target):e}")
print(f"Время выполнения: {elapsed:.6f} секунд")
