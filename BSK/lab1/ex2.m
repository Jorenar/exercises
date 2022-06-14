% Dane początkowe:
hl=input('Wysokość anteny nadawczej [m] : ');
h2=input('Wysokość anteny odbiorczej [m] : ');
f=input('Częstotliwość fali radiowej [MHz]: ');
f=f*10.^6;
dmin=input('Zakres odległości [m] od: ');
dmax=input('do: ');
lp=input('Liczba punktów na wykresie: ');
c=3*10.^8;

% Obliczenia pomocnicze
zakres=dmax-dmin;

d=dmin:zakres/(lp-1):dmax;
hm=(hl-h2)*ones(size(d));
hp=(hl+h2)*ones(size(d));
dl=sqrt(hm.^2+d.^2);
d2=sqrt(hp.^2+d.^2);
fil=-2*pi*f.*dl./c;
fi2=-2*pi*f.*d2./c;

% Obliczanie lp wartości względnego spadku mocy Pro
PrP0=abs(1./d1.*exp(j*fil)-1./d2.*exp(j*fi2));
PrP0=20.*log10(Pro);

% Wykres względnego spadku mocy nadawanej sygnału
% w zależności od odległości z podanego zakresu
plot(d,PrPO)
title('Względny spadek mocy sygnału radiowego w funkcji odle-
głości')
xlabel('Odległość anten [m]')
ylabel('Spadek mocy [dB]')
grid on
keyboard;
