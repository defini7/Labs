contains([], _) :- false.
contains([Head | Tail], Element) :- Element is Head, !; contains(Tail, Element).

inter([], _, []) :- !.
inter([Head | Tail], List, [Head | TailOut]) :-
    contains(List, Head), inter(Tail, List, TailOut), !.

inter([_ | Tail], List, Out) :- inter(Tail, List, Out).

% Если во втором списке есть элемент из первого, то мы его не берем, а иначе - берем
sub([], _, []) :- !.
sub([Head | Tail], List, Out) :- contains(List, Head), sub(Tail, List, Out), !.
sub([Head | Tail], List, [Head | TailOut]) :- sub(Tail, List, TailOut).

% ?- sub([2, 3, 4, 6, 7, 5, 74], [2, 3, 7, 5, 1], X)
% ?- sub([2, 3, 7, 5, 1], [2, 3, 4, 6, 7, 5, 74], X)

% Если элемент из первого встречаем во втором, то пропускаем, чтобы избежать дубликатов,
% если не встречаем, то берем.
union([], List, Out) :- sort(List, Out).
union([Head | Tail], List, Out) :- contains(List, Head), union(Tail, List, Out), !.
union([Head | Tail], List, [Head | TailOut]) :- union(Tail, List, TailOut).

% ?- union([2, 3, 4, 6, 7, 5, 74], [2, 3, 7, 5, 1], X)
% ?- union([2, 3, 7, 5, 1], [2, 3, 4, 6, 7, 5, 74], X)

% (X\Y) U (Y\X)
sym_diff(X, Y, Z) :- sub(X, Y, Xy), sub(Y, X, Yx), union(Xy, Yx, Z).

subset([], _) :- !.
subset([Head | Tail], List) :- contains(List, Head), subset(Tail, List).
