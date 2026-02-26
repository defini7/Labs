man(claude).
man(jack).
man(dick).

unique([]) :- !.
unique([X | Xs]) :-
    not(member(X, Xs)), unique(Xs).

solve([X, Y, Z]) :-
    % генерируем все возможные комбинации из имен
    man(X), man(Y), man(Z), unique([X, Y, Z]),
    S = statement(X, Y, Z),
    
    % если Клод лжет, то Жак говорит правду
    (statement(claude, _, _) = S; statement(jack, _, _) = S),
    
    % если Жак лжет, то Дик говорит правду
    (statement(jack, _, _) = S; statement(dick, _, _) = S),
    
    % если Дик лжет, то либо Клод, либо Жак говорит правду
    (statement(dick, _, _) = S; (
                            statement(claude, _, _) = S;
                            statement(jack, _, _) = S)).

% ?- solve(Answer)
% первый в списке - не лжец, остальные - лжецы