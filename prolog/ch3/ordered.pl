ordered([_]).
ordered([X, Y| L]) :- X =< Y, ordered([Y| L]).