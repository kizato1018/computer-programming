member1( X, [X| Tail]).

member1( X, [Head| Tail]) :- member1( X, Tail).