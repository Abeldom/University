## Created: 2023-04-29

function megold = iteracios_jacobi_fuggv (A,b,itszam)
  D=zeros(size(A));%foatlomatrix
  L=zeros(size(A));%also haromszogmatrix
  U=zeros(size(A));%felso haromszogmatrix
  n=size(A)(1);%matrix merete

  %LUD felbontasa az A matrixnak
  for i=1:n
    for j=1:i-1
      L(i,j)=-A(i,j);
    endfor

    for j=i+1:n
      U(i,j)=-A(i,j);
    endfor

    D(i,i)=A(i,i);
  endfor

  %megoldas kozelitese
  iteracios_matrix= (D^-1)*(L+U);
  szabad_tag = (D^-1)*b;

  megold = zeros(size(b));% nullvektor kezdetben a megoldasvektor
  for i=1:itszam
    megold=iteracios_matrix*megold+szabad_tag;
  endfor

    %konvergencia vizsgalat
  feltetel=sum(abs(A'))-sum(abs(D));
  for i=1:n
    if feltetel(i)<=0
      disp('nem konvergens az eljaras')
      return
    endif
  endfor

  disp('konvergens a jacobi eljaras')
  disp('')

endfunction
