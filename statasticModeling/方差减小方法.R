U=runif(100000)
x=exp(U)
mean(x)
var(x)
#对偶变量法增加估计的精确性（降低模拟次数）
U1=runif(100000)
#U2=runif(100000)
U2=1-U1
x1=exp(U1)
x2=exp(U2)
X=(x1+x2)/2
mean(X)
var(X)

#作业
U1=runif(100000)
t1=6-1/U1
t2=6-1/(1-U1)
x1=1/(sqrt(2*pi)*U1^2)*exp(-t1^2/2)
x2=1/(sqrt(2*pi)*(1-U1)^2)*exp(-t2^2/2)
X=(x1+x2)/2
mean(X)
var(X)

U1=runif(5000)
U2=1-U1
x1=5/(sqrt(2*pi))*exp(-(5*U1)^2/2)
x2=5/(sqrt(2*pi))*exp(-(5*U2)^2/2)
X=(x1+x2)/2
mean(X+0.5)
var(X)

U1=runif(10000)
x1=5/(sqrt(2*pi))*exp(-(5*U1)^2/2)
mean(x1+0.5)
var(x1)
1-var(X)/var(x1)

#控制变量法
U=runif(10000)
T1=exp(U)
T2=exp(U)+(U-0.5)*(-12+6*(exp(1)-1))
mean(T1)
mean((T2))
(var(T1)-var(T2))/(var(T1))

#作业
U=runif(10000)
T1=exp(-U)/(1+U^2)
fx=exp(-0.5)/(1+U^2)
T2=exp(-U)/(1+U^2)+(exp(-0.5)/(1+U^2)-exp(-0.5)*pi/4)*(-cov(T1,fx)/var(fx))
mean(T1)
mean(T2)
(var(T1)-var(T2))/(var(T1))

