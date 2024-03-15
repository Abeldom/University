##f =@(x) cos(x)-x;
##fd = @(x) -sin(x)-1;
##epsz = eps;
##maxit = 5;
##
##x=0:0.05:pi/4;
##%plot(x,f(x));
##%hold on;
##
##x0=pi/4;
##raphson_fuggv(f,fd, x0,epsz,maxit);
##
##x0=0.5
##x1=pi/4;
##szelo_fuggv(f,x0,x1,epsz,maxit);


f =@(x) x.^2;
fd = @(x) 2*x;
epsz = 0.01;
maxit = 10;

x=0:0.05:3;
plot(x,f(x));
hold on;

x0=3;
raphson_fuggv(f,fd, x0,epsz,maxit);
