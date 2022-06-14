h1 = input('Wysokosc anteny nadawczej [m]');
h2 = input('Wysokosc anteny odbiorczej [m]');
dmin = input('Zakres odleglosci [m] od: ');
dmax = input('do: ');
lp = input('Liczba punktow na wykresie: ');
c=3*10.^8;

zakres = dmax-dmin;
d = dmin:zakres/(lp - 1):dmax;
hm = (h1-h2)*ones(size(d));
hp = (h1+h2)*ones(size(d));
d1 = sqrt(hm.^2+d.^2);
d2 = sqrt(hp.^2+d.^2);

dd = (d2-d1)./c;

plot(d,dd);
title('Roznica opoznien dwoch sciezek sygnalu w funkcji odleglosci');
xlabel('Odleglosc anten [m]');
ylabel('Roznica opoznien [s]');
grid on;
keyboard;

h1 = input('Wysokosc anteny nadawczej [m]');
h2 = input('Wysokosc anteny odbiorczej [m]');
dmin = input('Zakres odleglosci [m] od: ');
dmax = input('do: ');
lp = input('Liczba punktow na wykresie: ');
c=3*10.^8;

zakres = dmax-dmin;
d = dmin:zakres/(lp - 1):dmax;
hm = (h1-h2)*ones(size(d));
hp = (h1+h2)*ones(size(d));
d1 = sqrt(hm.^2+d.^2);
d2 = sqrt(hp.^2+d.^2);

drms = d1.*d2.*(d2-d1)./(c*(d1.^2+d2.^2));

plot(d, drms)
title('Pierwiastek ze sredniokwadratowego rozrzutu opoznien dwoch sciezek sygnalu w funkcji odleglosci')
xlabel('Odleglosc anten [m]');
ylabel('Rozrzut opoznien rms[s]');
grid on;
keyboard;
