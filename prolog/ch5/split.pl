split([], [], []).
split([E| L], [E| P], N) :- E >= 0, !, split(L, P, N).
split([E| L], P, [E| N]) :- split(L, P, N).