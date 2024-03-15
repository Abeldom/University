function [L, U, P] = LUP(A,b)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
[n,m]=size(A);

if n~=m
    disp("mehecc")
    return
end

L= zeros(n,n);
U= zeros(n,n);
P= eye(n,n);

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
   P([i legnindex],:)=P([legnindex i],:);

   %ha 0 a legnagyobb akkor mehet
   if A(i,i)==0
       disp("nem lehet felbontani LUP szerint")
       return
   end

   %kivonas
   for s=i+1:n
       k=A(s,i)/A(i,i);%szorzando
       for o=i:n
          A(s,o) = A(s,o)-A(i,o)*k;
       end
       A(s,i)=k;
       %b kivonas
       b(s,1)=b(s,1)-b(i,1)*k;
   end
end

% L, U szerkesztese
for i=1:n
    for j=i:n
        L(j,i)=A(j,i);
        U(i,j)=A(i,j);
    end
end

% L atlojanak beallitasa
for i=1:n
    L(i,i)=1;
end






