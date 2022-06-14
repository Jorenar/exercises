% Program "SPADEK3", który oblicza i przedstawia graficznie spadek mocy
% sygnału radiowego przy trójdrogowości dla trzech wybranych częstotliwości

% Dane początkowe
h1 = input("Wysokość anteny nadawczej i odbiorczej [m]: ");
h = input("Wysokość pomieszczenia [m]: ");
h2 = h-h1;
a2 = input("Współczynnik odbicia od sufitu: ");
a3 = input("Współczynnik odbicia od podłogi: ");
f = zeros(1,3);
"Podaj 3 rozpatrywane częstotliwości fali radiowej: "
for i = 1:3,
    f(i) = input("Częstotliwość [MHz] : ");
    f(i) = f(i)*10.^6;
end;
dmin = input("Zakres odległości [m] od: ");
dmax = input("do: ");
lp = input("Liczba punktów na wykresie: ");
PrPt = zeros(3,lp);
c = 3*10.^8;
lam = c./f;
Gr = 1.6;
Gt = 1.6;

% Obliczenia pomocnicze
zakres = dmax - dmin;
d = dmin:zakres/(lp-1):dmax;
d1 = d;
d2 = 2* sqrt(h2.^2+(d.^2)./4);
d3 = 2* sqrt(h1.^2+(d.^2)./4);
for i = 1:3,
    fi1(i,:) = -2*pi*f(i).*d1./c;
    fi2(i,:) = -2*pi*f(i).*d2./c;
    fi3(i,:) = -2*pi*f(i).*d3./c;
end;

% Obliczenie lp wartości względnego spadku mocy PrPt
for i = 1:3,
    PrPt(i,:) = abs(1./d1.*exp(j*fi1(i,:)) + a2./d2.*exp(j*fi2(i,:)) + a3./d3.*exp(j*fi3(i,:)));
    PrPt(i,:) = Gr*Gt*(lam(i)./(4*pi)).*PrPt(i,:);
end;
maxP = max(max(PrPt));
PrPt = 20.*log10(PrPt/maxP);

% Wykres względnego spadku mocy nadawanej sygnału w zależności od odległości z podanego zakresu
plot(d,PrPt(1,:),d,PrPt(2,:),d,PrPt(3,:), 'LineWidth',2)
title(" Względny spadek sygnału radiowego w funkcji odległości")
xlabel("Odległość anten [m] ")
ylabel("Spadek mocy [dB] ")
grid on
pause(0.5)
keyboard
