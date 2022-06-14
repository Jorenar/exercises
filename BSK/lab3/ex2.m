function [PP,AA]=Erl1_tp(A1,A2,NA,P1,P2)
    CC = [1:1:20,25:5:50,60:10:100]
    AA=[1:1:20,25:5:50,60:10:100]
    PP=[1:1:20,25:5:50,60:10:100]
    n=size(CC,2)
    step=(A2/A1)^(1/(NA-1));
    for j=2:NA;
        AA(j)=AA(j-1)*step;
    end;
    for m=1:n;
        C=CC(m);
        for j=1:NA;
            A=AA(j);
            PP(m,j)=Erlang1p(A,C,P1,P2);
        end;
    end;

loglog(AA,PP,'k-')
xlabel('Natężenie ruchu [erl]')
ylabel('Prawdopodobieństwo blokady (GOS)')
title('Liczba kanałów ')
keyboard;
