% Program "SPADEK" obliczający i przedstawiający w sposób graficzny
% względny spadek mocy nadawanej sygnału radiowego przy trójdrogowości

% Dane początkowe
h1 = input("Wysokość anteny nadawczej i odbiorczej [m]: ");
h = input("Wysokość pomieszczenia [m]: ");
h2 = h - h1;
a2 = input("Współczynnik odbicia od sufitu: ");
a3 = input("Współczynnik odbicia od podłogi: ");
f = input("Częstotliwość fali radiowej [MHz]: ");
f = f* 0.^6;
dmin = input("Zakres odległości [m] od: ");
dmax = input("do: ");
lp = input("Liczba punktów na wykresie: ");
c = 3*10.^8;

% Obliczenia pomocnicze
zakres = dmax - dmin;
d = dmin:zakres/(lp-1):dmax;
d1 = d;
d2 = 2* sqrt(h2.^2+(d.^2)./4);
d3 = 2* sqrt(h1.^2+(d.^2)./4);
fi1 = -2*pi*f.*d1./c;
fi2 = -2*pi*f.*d2./c;
fi3 = -2*pi*f.*d3./c;

% Obliczenie lp wartości względnego spadku mocy PrP0
PrP0 = abs(1./d1.*exp(j*fi1)+a2./d2.*exp(j*fi2) + a3./d3.*exp(j*fi3));
PrP0 = 20.*log10(PrP0);

% Wykres względnego spadku mocy nadawanej sygnału w zależności od odległości z podanego zakresu
plot(d, PrP0, 'LineWidth',2)
title("Względny spadek mocy sygnału radiowego w funkcji odległości ")
xlabel("Odległość anten [m] ")
ylabel("Spadek mocy [dB] ")
grid on
keyboard;
