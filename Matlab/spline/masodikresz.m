function [v1,v2,v3,v4] = masodikresz (M,h,xv,y)
  n=size(y)(2)
  for i=1:n-1
     v1(i)=y(i);
     v2(i)=(y(i+1)-y(i))/h(i+1)-(2*M(i)+M(i+1))*h(i+1)/6;
     v3(i)=M(i)/2;
     v4(i)=(M(i+1)-M(i))/(6*h(i+1));
   endfor



endfunction
