man(adam).
man(peter).
man(paul).
man(shaung).
man(joe).
man(ken).
man(bob).
man(paul).
man(jordan).
man(michale).

woman(eve).
woman(marry).
woman(daphne).
woman(katty).
woman(kate).
woman(may).
woman(kris).
woman(vivian).
woman(evelyn).
woman(kris).
woman(jill).
woman(avril).

parent(daphne, shaung).
parent(shaung, adam).
parent(shaung, evelyn).
parent(vivan, adam).
parent(vivan, evelyn).
parent(adam, peter).
parent(adam, marry).
parent(eve, peter).
parent(eve, marry).
parent(evelyn, kate).
parent(joe, kate).
parent(kate, paul).
parent(jordan, paul).
parent(marry, kris).
parent(bob, kris).
parent(peter, ken).
parent(may, ken).
parent(ken, avril).
parent(jill, avril).
parent(michale, kayle).
parent(avril, kayle).


father(F, C):- man(F), parent(F, C).
mother(M, C):- woman(M), parent(M, C).
child(C, F) :- parent(F, C).
cousin(C, F) :- father(F, C).

is_father(F):- father(F, _).
is_mother(M):- mother(M, _).
same_parent(A, B) :- parent(_,A), parent(_,B).










