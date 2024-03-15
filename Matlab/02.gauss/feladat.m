function feladat()

A = [];
for i = 1 : 5
  for j = 1 : 5
    A(i,j)=1/(i+1)^(j-1);
  end
end

b=[1;1;1;1;1];

reszlegesgauss(A,b);

e = [0.01; 0.02; 0; -0.01; 0.01];

b = b + e;

reszlegesgauss(A,b);

disp("Azért változik meg nagyon a megoldás, mert a vandermonde mátrix rosszul kondicionált.(magas a kondíciószáma) ");

endfunction
