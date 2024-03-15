function [h,nu,lambda,c,d,M] = elsoresz (x, y)
  n= size(x)(2)
  c=zeros(n)

  for i=1:n-1
      h(i+1)=x(i+1)-x(i);
  end
  h

  d(1)=0;
  d(n)=0;
  lambda(1)=1;
  lambda(n)=0;
  nu(1)=0;
  nu(n)=1;

  for i=2:n-1
    lambda(i)=h(i+1)/(h(i)+h(i+1));
    nu(i)=1-lambda(i);
    d(i)=(6/(h(i)+h(i+1)))*((y(i+1)-y(i))/h(i+1)-(y(i)-y(i-1))/h(i));
  end

  c(1,1)=2;
  c(1,2)=lambda(1);
  c(n,n-1)=nu(n);
  c(n,n)=2;
  for i=2:n
    c(i,i)=2;
    c(i,i-1)=nu(i);
    c(i,i+1)=lambda(i);
  end

  M=c\d';
  %M(1)=0;
  %M(2)=d(1)/lambda(1);
  %M(n)=0;
  %for i=3:n
   % M(i)=(d(i-1)-nu(i-1)*M(i-2)-2*M(i-1))/lambda(i-1);
  %endfor

endfunction
