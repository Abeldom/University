function kozelites = hermite_fuggv(x,f,derf,x0)
n=size(x,1);
Q=zeros(2*n);

% Q elso ket oszlopanak feltoltese
for i=1:n
    xoszlop(2*i,1)=x(i,1);
    xoszlop(2*i-1,1)=x(i,1);

    Q(2*i-1,1) = f(i,1);
    Q(2*i,1)=f(i,1);

    Q(2*i,2)=derf(i,1);


end

for i=1:n-1
  Q(2*i+1,2)=(Q(2*i+1,1)-Q(2*i,1))/(xoszlop(2*i+1,1)-xoszlop(2*i,1));
end
Q;
xoszlop;


%tobbi ertek kiszamolasa
for j=3:2*n
   for i=j:2*n
    Q(i,j)=(Q(i,j-1)-Q(i-1,j-1))/(xoszlop(i,1)-xoszlop(i-j+1,1));
   end
end
Q;


%fuggveny meghatarozasa
kozelites=Q(1,1);
szorzotenyezo=1;
for i=2:2*n
    szorzotenyezo=szorzotenyezo*(x0-xoszlop(i-1,1));
    kozelites=kozelites+szorzotenyezo*Q(i,i);
end
kozelites;


end
