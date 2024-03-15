function fuggvenyertek = kiertekel(pont,xx,v1,v2,v3,v4)
  n=length(xx);
  hold on;
  for i=1:n-1
    if pont<=xx(i+1) && pont>=xx(i)
      fuggveny =@(x) v1(i)+v2(i)*(x-xx(i))+v3(i)*(x-xx(i))^2+v4(i)*(x-xx(i))^3;
      fuggvenyertek = fuggveny(pont);
      return;
    endif
  endfor
  fuggvenyertek=0;
  return;

endfunction
