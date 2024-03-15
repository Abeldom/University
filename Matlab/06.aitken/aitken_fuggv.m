function aitken_fuggv(xv, fv, x0, e)
 m=size(xv)(2)
  masol=xv;

  [xv,idx]=sort(abs(xv-x0),'ascend');
  fv=fv(idx);
  xv=masol(idx)

  Q=zeros(m,m);

  for i=1:m
    Q(i,1)=fv(i);
  endfor

  kozelit=false;

  for j=2:m  %oszloponkent megyek elore
    s=0;
    for k=1:j %osszeg
      % lkx nevezo es szamlalo
      nev=1;
      szaml=1;
      for l=1:m
        if l~=k
          szaml=szaml*(x0-xv(l));
          nev=nev*(xv(k)-xv(l));
        endif
      endfor
      s=s+fv(k)*  szaml/nev;
    endfor

    %Q(j,j) = s;



    for i=j:m % j a sorra kell vonatkozzon
      Q(i,j)=(((xv(i)-x0)*Q(j-1,j-1))-((xv(j-1)-x0)*Q(i,j-1)))/(xv(i)-xv(j-1));
    endfor

    if abs(Q(j,j)-Q(j-1,j-1))<e
      Q(j,j)
      kozelit = true;
      break
    endif

  endfor

  Q

  if kozelit == false
    disp("Nem elegendo adat all rendelkezesre")
  endif

endfunction
