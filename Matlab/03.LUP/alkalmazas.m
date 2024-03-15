A = randi([-5,5], [10,10])
B = randi([-5,5], [10,1])

tic
[L,U,P] = LUP(A,b)
toc

P*A
L*U

tic
gauss(A,B);
toc
