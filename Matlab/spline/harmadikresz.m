function harmadikresz (v1,v2,v3,v4,xx,runge)
  n=length(xx);
  fplot(runge,[xx(1),xx(n)])
  hold on;
  for i=1:n-1
    fuggveny = @(x) v1(i)+v2(i)*(x-xx(i))+v3(i)*(x-xx(i)).^2+v4(i)*(x-xx(i)).^3
    fplot(fuggveny(xx),[xx(i),xx(i+1)])
    %xv=xx(i):0.1:xx(i+1);
    %plot(xv,fuggveny(xv))

  endfor

endfunction
