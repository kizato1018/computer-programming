family(
       person( john, cohen, date(17,may,1990), unemployed),
       person( lily, cohen, date(9,may,1990), unemployed),
              [ ] ).

family(
       person( john, armstrong, date(7,may,1988), unemployed),
       person( lily, armstrong, date(29,may,1961), unemployed),
              [ ] ).

family(
       person( eric, baily, date(7,may,1963), works( bbc, 2200)),
       person( grace, baily, date(9,may,1965), works( ntu, 1000)),
              [ person( louie, baily, date(25,may,1983), unemployed) ] ).

family(
       person( eric, baily, date(7,may,1963), works( acc, 21200)),
       person( grace, baily, date(9,may,1965), works( ntnu, 12000)),
              [ person( louie, baily, date(25,may,1983), unemployed) ] ).

family(
       person( eric, fox, date(27,may,1970), works( bbc, 25200)),
       person( grace, fox, date(9,may,1971), works( ntbu, 13000)),
              [ person( louie, fox, date(5,may,1993), unemployed) ] ).

family(
       person( tom, cohen, date(7,may,1960), works( bcd, 15200)),
       person( ann, cohen, date(29,may,1961), unemployed),
              [ person( pat, cohen, date(5,may,1983),  works( bcd, 15200)),
                person( jim, cohen, date(5,may,1983),  works( bcd, 15200)) ] ).

family(
       person( bob, armstrong, date(12,oct,1977), works( ntnu, 12000)),
       person( liz,armstrong, date(6,oct,1975), unemployed),
              [ person( bob, armstrong, date(6,oct,1999), unemployed),
                person( sam,armstrong, date(8,oct,1998), unemployed) ] ).

family(
       person( tony, oliver, date(7,may,1960), works( bbc, 35200)),
       person( anny, oliver, date(9,may,1961), unemployed),
              [ person( patty, oliver, date(8,may,1984), unemployed),
                person( jimey, oliver, date(5,may,1983), unemployed) ] ).

family(
       person( jack, fox, date(27,may,1940), unemployed),
       person( jane, fox, date(9,aug,1941), works( ntu, 13050)),
              [ person( andy, fox, date(5,aug,1967), works( com, 12000)),
                person( kai, fox, date(5,jul,1969), unemployed) ] ).

family(
       person( jamie, baily, date(27,may,1960), works( bcc, 15100)),
       person( ann, baily, date(29,may,1961), unemployed),
              [ person( pat, baily, date(4,may,1983), unemployed),
                person( jim, baily, date(5,may,1983), unemployed) ] ).

family(
       person( bob, oliver, date(12,oct,1922), works( ntnu, 10213)),
       person( liz, oliver, date(6,oct,1965), unemployed),
              [ person( bob, oliver, date(8,oct,1988), unemployed),
                person( sam, oliver, date(7,oct,1990), unemployed) ] ).

family(
       person( jack, baily, date(17,may,1930), works( ntcu, 12100)),
       person( jane, baily, date(19,aug,1931), works( ntcu, 18000)),
              [ person( andy, baily, date(15,aug,1963), works( com, 9000) ),
                person( kai, baily, date(15,jul,1963),  works( com, 9000)) ] ).

family(
       person( jamie, lee, date(7,may,1963), unemployed),
       person( ann,  lee, date(19,may,1965), works( ffc, 32100)),
              [ person( pat,  lee, date(5,may,1983), unemployed),
                person( jim,  lee, date(5,may,1983), unemployed),
                person( john, lee, date(15,may,1988), unemployed) ] ).

family(
       person( tom, martin, date(7,may,1973), works( vvd, 23200)),
       person( ann,  martin, date(19,may,1975), works( vvd, 23100)),
              [ person( andy,  martin, date(5,aug,1993), unemployed),
                person( anne,  martin, date(5,aug,1993), unemployed),
                person( lily, martin, date(5,aug,1993), unemployed) ] ).
              
family(
       person( clive, frank, date(7,may,1973), works( nbc,13200)),
       person( lily,   frank, date(19,may,1975), works( nbc,13200)),
              [ person( andy_1,  frank, date(11,aug,1994), unemployed),
                person( andy_2,  frank, date(11,aug,1994), unemployed),
                person( anne_1,  frank, date(22,oct,1996), unemployed),
                person( anne_2,  frank, date(22,oct,1996), unemployed) ] ).

family(
       person( clive, lewis, date(7,may,1973), unemployed),
       person( ko,  lewis, date(19,may,1975), works( ncc, 35200)),
              [ person( pat_1,  lewis, date(1,aug,1991), unemployed),
                person( pat_2,  lewis, date(1,aug,1991), unemployed),
                person( andy,  lewis, date(22,oct,2000), unemployed),
                person( kai,  lewis, date(2,oct,2010), unemployed) ] ).

husband( X) :- family( X,  _,  _).
wife( X) :- family( _,  X,  _).
child( X) :- family( _,  _,  Children),  member( X,  Children).
dateofbirth( person(_,  _,  Date,  _),  Date).
twins(Child1, Child2) :- family(_, _, C), member(Child1, C), member(Child2, C), dateofbirth(Child1, Date), dateofbirth(Child2, Date), Child1 \= Child2.
children(family(_, _, ChildList), ChildList).
nth_member(1, [Child | _], Child).
nth_member(N, [_ | ChildList], Child) :- N > 1, M is N-1, nth_member(M, ChildList, Child). 
% nthchild( N,  Family,  Child) :- children( Family,  ChildList),  nth_member( N,  ChildList,  Child).

