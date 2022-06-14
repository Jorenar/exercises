% Erlang2 oblicza prawd. P oczekiwania w kolejce dla danego ruch A oraz liczby kanałów C
function [P]=Erlang2(A, C)
    E=Erlang1(A, C);
    P=C*E/(C-A*(1-E));
