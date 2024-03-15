xx=[-5:1:5]  %felosztas

runge =@(x) 1./(1+x.^2)

yy = runge(xx)

n= size(xx)(2)-1 %intervallumok szama

[h,nu,lambda,c,d,M] = elsoresz(xx,yy) %C kiszamitasa

[v1,v2,v3,v4] = masodikresz(M,h,xx,yy) %momentumok kiszamitasa



pontok = -5:0.1:5;
for i=1:length(pontok)
  y(i)=kiertekel(pontok(i),xx,v1,v2,v3,v4);
end

plot(pontok,y);
hold on;
pause(2);
plot(pontok,runge(pontok));

%harmadikresz(v1,v2,v3,v4,xx,runge);

