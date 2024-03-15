
#feladat
x=c(3.84 , 3.79 , 3.78 , 4.00 , 3.83, 3.84)
y=c( 3.90 , 4.05 , 3.8 , 4.01 , 3.81 , 3.9)
t.test(x,y,paired=T,alternative="l")

#feladat
diak=read.table("http://zempleni.elte.hu/diak_23.csv",sep=",",header=T,dec=".",fileEncoding = "UTF-8")
#####

xdat=diak[diak[,4]=="f",1]
t.test(xdat,mu=175,alternative="g") 

ydat=diak[diak[,4]=="n",1]

t.test(xdat,ydat,mu=10,alternative="g")
var.test(xdat,ydat)
#b/
p.v=rep(0,times=15)
for (i in 1:15)
{test=(length(ydat)-1)*var(ydat)/(i^2)
p.v[i]=2*min(1-pchisq(test,length(ydat)-1),pchisq(test,length(ydat)-1))} #k?toldali, H1:sigma\ne i
 plot(p.v,type="l")
abline(h=0.05,col=2)


p.v=rep(0,times=20)
for (i in 1:20)
{test=(length(ydat)-1)*var(ydat)/(i^2)
p.v[i]=1-pchisq(test,length(ydat)-1)} #egyoldali, H1:sigma>i
 plot(p.v,type="l")
for (i in 1:20)
{test=(length(ydat)-1)*var(ydat)/(i^2)
p.v[i]=pchisq(test,length(ydat)-1)} #egyoldali, H1:sigma<i
lines(p.v,col=4)
abline(h=0.05,col=2)


#2 mint?s t vs Welch
x=rnorm(100,0,1)
y=rnorm(100.2,0,1)
t.test(x,y)
t.test(x,y,var.equal=T)

#feladat
n=c(10,20,50,100,200)
ism=5000
terj=rep(0,times=length(n))
for (i in 1:length(n))
{for (j in 1:ism)
{if (t.test(rnorm(n[i]))$p.value<0.05) terj[i]=terj[i]+1}
}
100*terj/ism

n=c(10,20,50,100,200,2000)
ism=500
terj=rep(0,times=length(n))
for (i in 1:length(n))
{for (j in 1:ism)
{if (t.test(rexp(n[i]),mu=1)$p.value<0.05) terj[i]=terj[i]+1}
}
terj/ism



###############
#Wilcoxon proba
###############

x=rnorm(50)
y=rnorm(50,0.5)
t.test(x,y)

wilcox.test(x, y)

##de: valtoztassuk meg az adatokat
y[50]=100

t.test(x,y)

wilcox.test(x, y)


# feladat
x=c(4.3, 2.0, 5.6, 8.1 ,3.2 ,0.6 ,5.4, 8.9, 7.5 ,9.3,
9.6, 6.7, 4.4 ,2.9 ,1.0, 6.5, 4.0 ,6.6, 4.2 ,1.9)
plot(10*c(1:length(x))/(length(x)+1),sort(x),type="l",main="QQ plot",sub="egyenletes")
abline(a=0,b=1,col=2)
points(10*c(1:length(x))/(length(x)+1),sort(x))

plot(c(1:length(x))/(length(x)+1),sort(x)/10,type="l",main="PP plot",sub="egyenletes")
abline(a=0,b=1,col=2)

points(c(1:length(x))/(length(x)+1),sort(x)/10)


ks.test(x,"punif",0,10)

plot(qnorm(c(1:length(x))/(length(x)+1),5,5/sqrt(3)),sort(x),type="l",main="QQ plot",sub="norm")
abline(a=0,b=1,col=2)
points(qnorm(c(1:length(x))/(length(x)+1),5,5/sqrt(3)),sort(x))




plot(c(1:length(x))/(length(x)+1),pnorm(sort(x),5,5/sqrt(3)),type="l",main="PP plot",sub="norm")
abline(a=0,b=1,col=2)
points(c(1:length(x))/(length(x)+1),pnorm(sort(x),5,5/sqrt(3)))

ks.test(x,"pnorm",5,5/sqrt(3))


#############
#chi-negyzet
#############

#tavalyi adatok
diak=read.table("http://zempleni.elte.hu/diak_23.csv",sep=",",header=T,dec=".",fileEncoding = "UTF-8")
#nem
#H0: egyenletes elo.
chisq.test(table(diak[,4]))
#tovabbi komponensek
chisq.test(table(diak[,4]))$observed
chisq.test(table(diak[,4]))$expected
chisq.test(table(diak[,4]))$residuals

#szimulalt krit ertekkel (kis mintaelemsz?mn?l ?rdemes haszn?lni)
chisq.test(table(diak[,4]),simulate.p.value=T)

#feladat
ert=c(0,1,2,3,4,5,7)
gyak=c(45 , 35 , 12 , 5 , 1 , 1 , 1)
lbecs=sum(ert*gyak)/sum(gyak)
#?ssze kell vonni az utols? oszt?lyokat
gyak=c(45 , 35 , 12 , 8 )
elmgyak=sum(gyak)*c(dpois(0,lbecs),dpois(1,lbecs),dpois(2,lbecs),1-dpois(0,lbecs)-dpois(1,lbecs)-dpois(2,lbecs))
chi=sum((gyak-elmgyak)^2/elmgyak)
1-pchisq(chi,2) #elfogadhat? a Poisson elo.

#normalitasvizsgalat a sajat adatainkra
#itt nincs tablazat
par(mfrow=c(2,2))

u1=hist(diak[,6],xlab="perc",ylab="gyakoris?g",main="Ut.id?",breaks=30*c(1:9)-15)
hist(diak[,5],xlab="?ra",ylab="gyakoris?g",main="Tan.id\u151",breaks=c(0:7)*5-1/2)
hist(diak[,1],xlab="cm",ylab="gyakoris?g",main="Testmagass?g",breaks=5*c(0:11)+152.5)
hist(diak[,3],xlab="",ylab="gyakoris?g",main="Cip\u151m?ret",breaks=c(1:13)+69/2)

n<-4;j<-1 #magass?g
 #intervallum: 4 db ill. a valtozo sorszama
 q<-c(1:n)/n
 h<-c(-Inf,qnorm(q))
 mu<-mean(diak[,j])
sig=sd(diak[,j])
 h<-h*sig+mu
 #ezek hataroljak 
 nu<-rep(0,times=n)
 for (i in 1:n)
 nu[i]<-
  sum((diak[,j]<h[i+1]) & (diak[,j]>=h[i]))


 #vart gyak:
 np<-sum(nu)*rep(1/n,times=n)
 chi<-sum((nu-np)^2/np)


 #a p-ertek:
 p<-1-pchisq(chi,n-3)
 p

nu 
np 
h

#17.feladat

tab1=c( 399 , 261 , 284 , 263 , 393 , 531 , 502)
tab2=c( 119 , 72 , 97 , 51 , 143 , 145 , 150 )
tab3=c( 39 , 50 , 20 , 15 , 41 , 97 , 86 )

tabl=rbind(tab1,tab2,tab3)
c1=chisq.test(tabl)
c1
round(c1$expected)
tabw=tabl[2:3,] 

tabl=rbind(tab1,apply(tabw,FUN=sum,MARGIN=2)) #?sszevontuk a h?tv?g?t
c1=chisq.test(tabl) #kev?sb? eros az ?sszef?gg?s
c1

