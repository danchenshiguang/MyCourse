#分层抽样实例
g=function(x)
{
  exp(-x)/(1+x^2)
  
}

m=1000
T2=c()
estimates=matrix(0,10,2)
for (i in 1:10) {
  T1=mean(g(runif(m)))
  T2[1]=mean(g(runif(m/4,0,0.25)))
  T2[2]=mean(g(runif(m/4,0.25,0.5)))
  T2[3]=mean(g(runif(m/4,0.5,0.75)))
  T2[4]=mean(g(runif(m/4,0.75,1)))
  estimates[i,2]=mean(T2)
  estimates[i,1]=T1
}
estimates
apply(estimates,2,mean)
apply(estimates,2,var)

apply(estimates,1,mean)
