function veges(a,h,m,f)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
%f=@(x)x.^2-10*x+7

diff = zeros(m+1,m+2);
A=(a:h:a+m*h)';
diff(:,1) =A;
diff(:,2) =f(A);

for j=3:m+2
    for i=1:m+3-j
        diff(i,j)=diff(i+1,j-1)-diff(i,j-1);
    end
end
diff

end

