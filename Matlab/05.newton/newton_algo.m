xv = [ -2 -1 0 3 4]

fv = [ 0.2 0.5 1 0.1 0.058]

x0=1;
y0=newton_fuggv(xv,fv,x0);

x=-5:0.1:5;

for i=1:101
  y(i)=newton_fuggv(xv,fv,x(i));
endfor

plot(x,y);
hold on

runga=1./(1+x.^2);
plot(x,runga);
hold on

plot(xv,fv,'o')
hold on

plot(x0,y0,'x')
legend({'newtonpol','runga','kozospontok','kozelites'})

