exam=function(d)
{
  X=rnorm(100);k=100
  while(sd(X)/sqrt(k)>=d)
  {
    k=k+1
    X[k]=rnorm(1)
  }
  return(k-1)
}
system.time(exam(0.01))

#计算样本方差
exam1=function(d)
{
  X=rnorm(100);k=100
  ss=0;xbar=X[1]
  for (j in 1:(k-1)) 
  {
    xbar[j+1]=xbar[j]+(X[j+1]-xbar[j]/(j+1))
    ss[j+1]=(1-1/j)*ss[j]+(j+1)*(xbar[j+1]-xbar[j])^2
  }
  while(sqrt(ss[k])/sqrt(k)>d)
  {
    k=k+1
    X[k]=rnorm(1)
    xbar[k]=xbar[k-1]+(X[k]-xbar[k-1])/k
    ss[k]=(1-1/(k-1))*ss[k-1]+k*(xbar[k]-xbar[k-1])^2
    
  }
  list(xbar=mean(X),N=k,Var=ss[k])
}
system.time(exam1(0.01))

#估计单服务员排队模型中的模拟精度
exam2=function(d)
{
  X=c()
  m_time=c()
  for (i in 1:100) {
    m=MG(12,2)$K
    m_time[i]=m
    if(m>12.5)
    {
      X[i]=1
    }
    else
    {
      X[i]=0
    }
  }
  k=100
  while (sqrt(mean(X)*(1-mean(X))/k)>d){
    k=k+1
    m=MG(12,2)$K
    m_time[k]=m
    if(m>12.5)
    {
      X[k]=1
    }
    else
    {
      X[k]=0
    }
  }
  list(N=k-1-10,mean_time=mean(m_time),mean_X=mean(X))
}


#bootstrap估计方法
L=c(576,635,558,578,666,580,555,661,651,605,653,575,545,572,594)
G=c(339,330,281,303,344,307,300,343,336,313,312,274,276,288,296)
pr=rep(1/15,15)
cor_fx=function(x)
{
  y=c()
  for (i in 1:length(x))
  {
    y[i]=G[which(L==x[i])]
  }
  return(y)
}

boot=function(L,pr,fboot,B)
{
  Tboot=0
  for(i in 1:B)
  {
    Y=sample(L,length(L),prob = pr,replace = TRUE)
    Tboot[i]=fboot(Y,cor_fx(Y))
  }
  return(Tboot)
}
T=boot(L,pr,cor,1000)
mean(T)
var(T)