%%
function raphson_fuggv (f, fd, x0, epsz, maxit)
  xelozo=x0
  format long;
  for i=1:maxit
     xkov=xelozo-f(xelozo)/fd(xelozo)
     line([xkov xelozo],[0 f(xelozo)]);
     pause(2)
     hold on;
     if abs(xkov-xelozo)<=epsz
         fprintf(' Elertuk a kivant pontossagot %d iteracio alatt \n',i);
         return;
     endif
     xelozo=xkov;
  endfor

  disp("elertuk a maximalis iteracioszamot, de nem ertuk el a kivant pontossagot");
endfunction
