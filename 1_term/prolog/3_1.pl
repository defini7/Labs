% не работает, а почему - не смог разобраться %

student(a).
student(e).
student(c).
student(p).

day(tuesday).
day(wednesday).
day(thursday).
day(friday).

unique([]) :- !.
unique([Head | Tail]) :-
    not(member(Head, Tail)), unique(Tail).

rule1(People) :-
    (member(visitor(c, wednesday), People); member(visitor(p, thursday), People)) ->
    	member(visitor(e, friday), People).

rule2(People) :-
    not(member(visitor(a, thursday), People)) -> member(visitor(e, wednesday), People).

rule3(People) :-
    (member(visitor(a, wednesday), People); member(visitor(p, wednesday), People)) ->
        member(visitor(c, friday), People).

rule4(People) :-
    not(member(visitor(p, friday), People)) ->
    	(member(visitor(a, tuesday), People), member(visitor(c, wednesday), People)).

rules(People) :-
    not(member(visitor(c, tuesday), People)),
    not(member(visitor(p, tuesday), People)),
    
    rule1(People),
    rule2(People),
    rule3(People),
    rule4(People).

solve(People) :-
    student(X), student(Y), student(Z), student(W), unique([X, Y, Z, W]),
    day(DayX), day(DayY), day(DayZ), day(DayW), unique([DayX, DayY, DayZ, DayW]),
    
    People = [visitor(X, DayX), visitor(Y, DayY), visitor(Z, DayZ), visitor(W, DayW)],
    
    rules(People).

% solve(Answer).
    