clf
xx=[0.1:0.1,2:1:10,20:10:100];
yy=[0.01:0.01:0.1,0.2:0.1:1];
loglog(AA,PP,'-k')
stx=['0.1';' ';' ';' ';' ';' ';' ';' ';' ';'1.0';
     ' ';' ';' ';' ';' ';' ';' ';' ';' 10';
     ' ';' ';' ';' ';' ';' ';' ';' ';'100'];
set(gca,'XTick',xx,'XTickMode','manual','XGrid','on','XTickLabels',
stx,'XTickLabelMode','manual')
sty=['.01';' ';' ';' ';' ';' ';' ';' ';
     ' ';'.1 ';
     ' ';' ';' ';' ';' ';' ';' ';' ';'1 '];
set(gca,'YTick',yy,'YTickMode','manual','YGrid','on','YTickLabels',
sty,'YTickLabelMode','manual')
xlabel(' Natężenie ruchu [erl]')
ylabel(' Prawdopodobieństwo oczekiwania w kolejce (GOS)' )
title(' Liczba kanałów ')
keyboards;
