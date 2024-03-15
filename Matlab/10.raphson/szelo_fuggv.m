function szelo_fuggv (f,x0,x1,epsz, maxit)
  xlast = x1
  xllast = x0;
  xnext=0;
  %grid on;
  for i=1:maxit
     xnext=xlast-f(xlast)*(xlast-xllast)/(f(xlast)-f(xllast))
     line([xlast xnext],[f(xlast) f(x0)]);
     hold on;
     if abs(xnext-xlast)<=epsz
         fprintf(' Elertuk a kivant pontossagot %d iteracio alatt \n',i);
         return;
     endif
     xllast=xlast;
     xlast=xnext;
  endfor

  disp("elertuk a maximalis iteracioszamot, de nem ertuk el a kivant pontossagot");




endfunction
