h1=input('wysokość anteny nadawczej [m]: ');
h2=input('wysokość anteny odbiorczej [m]: ');
f=zeros(1,3);

'Podaj 3 rozpatrywane częstotliwości fali radiowej: '
for i=1:3,
    f(i)=input('Częstotliwość [MHz]: ');
    f(i)=f(i)*10.6^6;
end;
dmin=input('Zakres odległości [m] od: ');
dmax=input('do: ');
lp=input('Liczba punktów na wykresie: ');
PrPt=zeros(3,lp);
c=3*10^8;
lam = c./f;
Gr=1.6;
Gt=1.6;

zakres=dmax-dmin;
d=dmin:zakres/(lp - 1):dmax;
hm=(h1-h2)*ones(size(d));
hp=(h1+h2)*ones(size(d));
d1=sqrt(hm.^2+d.^2);
d2=sqrt(hp.^2+d.^2);
for i=1:3,
    fi1(i,:)=-2*pi.*f(i).*d1./c;
    fi2(i,:)=-2*pi.*f(i).*d2./c;
end;

for i=1:3,
    PrPt(i,:)=abs(1./d1.*exp(j*fi1(i,:))-1./d2.*exp(j*fi2(i,:)));
    PrPt(i,:)=Gr*Gt*(lam(i)./(4*pi)).*PrPt(i,:);
end;
maxP=max(max(PrPt));
PrPt=20.*log10(PrPt/maxP);

plot(d, PrPt(1,:), d, PrPt(2,:), d, PrPt(3,:))
title('Względny spadek mocy sygnału radiowego w funkcji odległosci')
xlabel('Odległość anten [m]');
ylabel('Spadek mocy [dB]');
grid on
pause(0.5)
keyboard;
