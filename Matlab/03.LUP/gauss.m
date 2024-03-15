function gauss(A,b)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
[n,m]=size(A);

if n~=m
    disp("mehecc")
    return
end


for i=1:n-1
    %legnagyobb elem indexenek megtalalasa
   legnelem=abs(A(i,i));
   legnindex=i;
   for j=i+1:n
       if legnelem < abs(A(j,i))
           legnelem=abs(A(j,i));
           legnindex=j;
       end
   end
   %legnindex

   %disp("ket sor kicserelese");
   A([i,legnindex],:) = A([legnindex,i],:);
   b([i legnindex])=b([legnindex i]);

   %ha 0 a legnagyobb akkor mehet
   if A(i,i)==0
       disp("mehecc")
       return
   end

   %kivonas
   %disp("kivonas utan");
   for s=i+1:n
       k=A(s,i)/A(i,i);%szorzando
       for o=i:n
          A(s,o) = A(s,o)-A(i,o)*k;
       end
       %b kivonas
       b(s,1)=b(s,1)-b(i,1)*k;
   end
end

x=zeros(n,1);
x(n,1)=b(n,1)/A(n,n);

for i=n-1:-1:1
   s=0;
   for j=i+1:n
       s=s+x(j,1)*A(i,j);%osszeg kiszamolasa
   end
   x(i,1)= (b(i,1)- s)/A(i,i);%ismeretlenek kiszamolasa

end




