function osztott(X,f)

m=length(X);
diff = zeros(m,m+1);
diff(:,1) =X;
diff(:,2) =f(X);

for j=3:m+1
    for i=1:m+2-j
        df= diff(i+1,j-1)-diff(i,j-1);
        dx= diff(i+j-2,1)-diff(i,1);
        diff(i,j) =df/dx;
    end
end
diff

end



