function kozelit = newton_fuggv (xv,yv,x0)
  n=size(xv)(2);

  od=zeros(n); % osztott differencia tablazat
  od(:,1)=yv;

  for j = 1:n-1 % oszlop
    for i= 1:n-j % sor
      od(i,j+1)= (od(i+1,j)-od(i,j))/(xv(i+j)-xv(i));
    endfor
  endfor

  kozelit=0;

  for i=1:n
    s=1;
    for j=1:i-1
      s=s*(x0-xv(j));
    endfor
    kozelit=kozelit+s*od(1,i);
  endfor
  x0;
  kozelit;

endfunction
