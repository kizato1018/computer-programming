readfile(X, Y) :- see('testa.txt'), get(X), seen, see('testb.txt'), get(Y), seen.
writefile(X, Y) :- tell('test1.txt'), put(X), put(Y), told.
