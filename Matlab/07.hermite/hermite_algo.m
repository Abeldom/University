fuggveny = @(x) 2.^x-3.*x;
derfuggveny = @(x) (2.^x).* log(2)-3;
xb=[1 2 3]'

fb = feval(fuggveny,xb)

derfb = feval(derfuggveny,xb)

f1ben = hermite_fuggv(xb,fb,derfb,1)
f2ben = hermite_fuggv(xb,fb,derfb,2)
f3ban = hermite_fuggv(xb,fb,derfb,3)

##xb=[1.3 1.6 1.9]';
##fb=[0.6200860 04554022 0.2818186]';
##derfb=[-0.5220232 -0.5698959 -0.5811571]';

xfelosztas=0:0.1:3.5;
for i=1:36
  yhermite(i)=hermite_fuggv(xb,fb,derfb,xfelosztas(i));
endfor

#hermite fuggveny
plot(xfelosztas,yhermite);
hold on

#igazi fuggveny
plot(xfelosztas,feval(fuggveny,xfelosztas))
hold on

#csomopontok
plot(xb,fb,'o')
hold on

legend({'hermite fuggveny','2^x-3*x','csomopontok'})


# Megj. magamnak: kell figyelni a vektorok definialasara es
# mereteire mikor hasznalom oket
