function [PP, AA]=Erl1_t(A1, A2, NA)
    CC=[1:1:20,25:5:50,69:10:100]
    % definicja wektora wartości liczby kanałów
    n=size(CC,2)
    step=(A2/A1).^(1/(NA-1));
    AA(1)=A1;
    for j=2:NA;
        AA(j)=AA(j-1)*step;
    end;
    for m=1:n;
        C=CC(m);
        for j=1:NA;
            A=AA(j);
            PP(m,j)=Erlang1(A,C);
        end;
    end;
