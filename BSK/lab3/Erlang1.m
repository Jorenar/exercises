% funkcja Erlang1 oblicza prawd.
%    Blokady P dla danego natężenia ruchu A i liczby kanałów
function [P] = Erlang1(A, C)
    sum = 0;
    for k = 0:C;
        mul = A.^(k-C);
        for i = 1k+1:C;
            mul = mul*i;
        end;
        sum= sum + mul;
    end;
    P = 1/sum;
end
