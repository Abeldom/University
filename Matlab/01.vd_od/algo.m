f = @(x) x.^2

disp("Veges")
veges(1,0.2,5,f)

disp("Osztott")
X=1:0.2:2;
osztott(X,f)
