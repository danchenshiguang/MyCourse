a=c(1,2,3,5,9)
b=c(0.5,0.5,0.5,1.0,2.0)
c=c("green","red","blue","yellow","purple")
for (i in 1:5) {
  curve((b[i]^a[i])*x^(a[i]-1)*exp(-b[i]*x)/gamma(a[i]),0,20,ylim=c(0,1),col=c[i])
  par(new=T)
}

#伽马函数的画法
u1=runif(100000)
u2=runif(100000)
k=2/sqrt(pi)
y=(-3/2)*log(u1)
c=(3^1.5)/(2*pi*exp(1))^0.5
accept=y[u2<=(k*(y^0.5)*exp(-y))/(c*(2/3)*exp(-2*y/3))]
hist(accept,breaks=seq(0,100,0.1),xlim=c(0,10),freq=F)
par(new=T)
#plot(10*u1,((10*u1)^0.5)*exp(-u1*10)*2/sqrt(pi))
curve((x^0.5)*exp(x)*2/sqrt(pi),ylim=c(0,0.5))

#作业伽马函数抽样
curve((x*exp(-x))/(6*exp(-5)),5,10,ylim=c(0,1),col="yellow",xlim = c(0,10))
par(new=T)
curve((1/2)*exp(-(x-5)/2),5,10,ylim=c(0,1),col="green",xlim = c(0,10))
par(new=T)
curve((5/3)*(1/2)*exp(-(x-5)/2),5,10,ylim=c(0,1),col="red",xlim=c(0,10))
par(new=T)
u1=runif(100000)
u2=runif(100000)
y=5-2*log(u1)
accept=y[u2<=(exp(5/2)/3)*y*exp(-y/2)]
hist(accept,breaks=seq(0,100,0.05),xlim=c(0,10),ylim=c(0,1),freq=F)

#作业beta分布
curve(30*(x^2)*(1-x)^2,0,1,ylim=c(0,2),col="green")
par(new=T)
curve(30*(x^2)*(1-x)^2,0,1,ylim=c(0,2),col="red")

par(new=T)

u1=runif(100000)
u2=runif(100000)
accept=u1[u2<=(16*(u1^2)*(1-u1)^2)]
#plot(u1,30*(u1^2)*(1-u1)^2)
hist(accept,breaks=seq(0,1,0.02),freq=F,ylim=c(0,2))
par(new=T)
abline(a=1,b=0,col="green")
par(new=T)
abline(a=15/8,b=0,col="yellow")
par(new=T)
curve(30*(x^2)*(1-x)^2,0,1,ylim=c(0,2),col="red")