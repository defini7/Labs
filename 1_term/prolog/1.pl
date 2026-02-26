% Вычитаем из B единицу и прибавляем к A, пока B не 0
add(A, 0, A) :- !.
add(A, succ(0), succ(A)) :- !.
add(A, succ(B), C) :- add(succ(A), B, C).

% Вычитаем из B единицу, пока B не 1, и к C прибавляем A
multiply(_, 0, 0) :- !.
multiply(A, succ(0), A) :- !.
multiply(A, succ(B), C) :- multiply(A, B, Sum), add(Sum, A, C).

% Вычитаем из A и B по единице, пока правая часть не ноль
greaterThan(succ(_), 0) :- !.
greaterThan(succ(A), succ(B)) :- greaterThan(A, B).

% Используем встроенные функции :0
divMod(_, 0, _, _) :- false.
divMod(A, B, Quot, Rem) :- Quot is A div B, Rem is A mod B.

% Алгоритм Евклида (B - последний остаток, A - остаток перед B)
% https://en.wikipedia.org/wiki/Euclidean_algorithm
% r(k−2) = q(k) * r(k−1) + r(k) <=> r(k) = r(k-2) mod r(k-1)
gcd(A, 0, A) :- !.
gcd(A, B, Gcd) :- B > A, gcd(B, A, Gcd).
gcd(A, B, Gcd) :- Rem is A mod B, gcd(B, Rem, Gcd).

% Простое число - это число большее 1 и число, которое не может быть получено произведением двух меньших чисел
prime(N) :- N > 1, not((High is N div 2, between(2, High, Divisor), 0 is mod(N, Divisor))).

% Prime - первое простое число после Current
nextPrime(Current, Prime) :- Next is Current + 1,
    (prime(Next), Prime is Next; nextPrime(Next, Prime)).

nthPrime(1, 2) :- !.
nthPrime(N, Prime) :- N > 1, PredN is N - 1,
    nthPrime(PredN, PredPrime), nextPrime(PredPrime, Prime).

fibonacci(1, 0) :- !.
fibonacci(2, 1) :- !.
fibonacci(N, Fib) :- N1 is N - 1, N2 is N - 2,
    fibonacci(N1, Fib1), fibonacci(N2, Fib2), Fib is Fib1 + Fib2.

fibonacciListReversed(0, []) :- !.
fibonacciListReversed(N, [Head | Tail]) :- N > 0, PrevN is N - 1,
    fibonacciListReversed(PrevN, Tail), fibonacci(N, Head).

fibonacciList(0, []) :- !.
fibonacciList(N, List) :- fibonacciListReversed(N, Reversed), reverse(Reversed, List).
