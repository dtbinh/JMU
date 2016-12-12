%
% Lab 17 Solution
% C. Fox
%

size([],0).
size([_|T],N) :- size(T,M), N is M+1.

test_size :- size([],0), size([1],1), size([1,3,2],3), !.

end([],_) :- fail.
end([X],X).
end([_|T],X) :- end(T,X).

test_end :- \+end([],_), end([1],1), end([1,3,2],2), !.

max([],_) :- fail.
max([X],X).
max([H|T],H) :- max(T,N), N=<H.
max([H|T],N) :- max(T,N), H<N.

test_max :- \+max([],_), max([1],1), max([1,3,2],3), !.

concatenate([],B,B).
concatenate([H|T],B,[H|C]) :- concatenate(T,B,C).

test_concatenate :- concatenate([],[],[]), concatenate([1,2,3],[4,5,6],[1,2,3,4,5,6]).

flattn(X,[X]) :- \+list(X).
flattn([],[]).
flattn([H|T],[H|R]) :- \+list(H), flattn(T,R).
flattn([H|T],R) :- flattn(H,G), flattn(T,F), append(G,F,R).

test_flattn :- flattn([[]],[]), flattn([[a],[b]],[a,b]),
               flattn([[a],[],[b,c],[d],[]],[a,b,c,d]),
               flattn(a,[a]), flattn([a,b,c],[a,b,c]),
               flattn([a,[b,c],[],[[]],[d,[e,f],g]],[a,b,c,d,e,f,g]).

prefix_all(_,[],[]).
prefix_all(X,[H|T],[[X|H]|R]) :- prefix_all(X,T,R).

test_prefix_all :- prefix_all(1,[],[]), prefix_all(1,[[2]],[[1,2]]),
                   prefix_all(1,[[2],[3],[4]],[[1,2],[1,3],[1,4]]).

power_set([],[[]]).
power_set([H|T],P) :- power_set(T,R1), prefix_all(H,R1,R2), append(R2,R1,P).

test_power_set :- power_set([],[[]]), power_set([a],[[a],[]]),
                  power_set([1,2,3],P), sort(P,Q), Q==[[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]].

test :- test_size, test_end, test_max, test_concatenate, test_flattn, test_prefix_all, test_power_set, !.

