function [P]=Erlang2p(A, C, P1, P2)
    % Erlang2p oblicza prawd. Oczekiwania w kolejce P na dla danego natężenia ruchu A %
    % oraz liczby kanałów C. Jeżeli P wykracza poza przedział P1 – P2, to przyjmowana jest
    % jest wartość skrajna
    P11=(C-A)/(C/P1-A);
    P22=(C-A)/(C/P2-A);
    E=Erlang1p(A,C,P11,P22);
    P=C*E/(C-A*(1-E));
