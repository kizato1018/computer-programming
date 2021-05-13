set_difference([], _, []).
set_difference([E| S1], S2, D) :- member(E, S2), !, set_difference(S1, S2, D).
set_difference([E| S1], S2, [E| D]) :- set_difference(S1, S2, D).

| ?- set_difference([a,b,c,d],[b,d,e,f], L).

L = [a,c]

yes
| ?- set_difference([a,b,c,d],[], L).

L = [a,b,c,d]

yes
| ?- set_difference([a,b,c,d],[a,b,c,d], L).

L = []

yes