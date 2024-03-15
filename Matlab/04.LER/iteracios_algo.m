A=[ 10 -1 2 0; -1 11 -1 3; 2 -1 10 -1; 0 3 -1  8]
b=[6 25 -11 15]'

iteracioszam=5
disp('');

megoldas_jacobi = iteracios_jacobi_fuggv(A,b,iteracioszam)
megoldas_gaussiedel = iteracios_gaussiedel_fuggv(A,b,iteracioszam)
