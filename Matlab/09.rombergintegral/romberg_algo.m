fg=  @(x) x^2-x;
n=20 %pontossag

hatv2=2;% hatvanyok kiszamitasa

a=0;
b=4;
h=b-a;
epszilon=0.001;

hatv2
elozo=(h/2)*(fg(a)+fg(b))
for i=2:n
    s=0;
    for j=1:hatv2
      s=s+fg(a+(2*j-1)*h/(hatv2*2));
    endfor
    kovetkezo=elozo/2+(h/(hatv2*2))*s
    if abs(kovetkezo-elozo)<epszilon
      disp('Elertuk a kivant pontossagot')
      return
    endif
    elozo=kovetkezo;
    hatv2=hatv2*2;
endfor
disp('Nem ertuk el a kivant pontossagot')
