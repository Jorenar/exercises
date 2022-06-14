function [P]=Erlang1p(A,C,P1,P2)
    P1=1/P1;
    P2=1/P2;
    sum=0;
    k=0;
    while k<=C & sum<=P1;
        mul=A.^(k-C);
        for i=k+1:C;
            mul=mul*i;
        end;
        sum=sum+mul;
        k=k+1;
    end;
    if sum>P1, sum=P1;
    end;
    if sum<P2, sum=P2;
    end;
    P=1/sum;
