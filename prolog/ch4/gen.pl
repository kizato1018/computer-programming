gen( N1, N2, _, []) :- N1 > N2.
gen( N1, N2, Step, [N1|List]) :- N1 =< N2,  M is N1+Step,  gen(M, N2, Step, List).