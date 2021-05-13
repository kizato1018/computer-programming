addp([], [], _).
addp([X| List1], [Y| List2], N) :- Y is X+N, N1 is N+1, addp(List1, List2, N1).
addposition(List1, List2) :- addp(List1, List2, 1).