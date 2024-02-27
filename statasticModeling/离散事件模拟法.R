#单服务员的排队系统
arrival=function(lamda,s)
  #生成到达时间
{
  t=s
  t=t-log(runif(1))/lamda
  return(t)
}

##单服务员服务过程
MG=function(T,mu)
{
  t=Na=Nd=n=0
  A=c() 
  D=c()
  N=c()
#  tA=arrival(1.2,g=1,t)
  tA=t-log(runif(1))/1.2
  tD=Inf
  while(1)
  {
    if(tA<=tD & tA<=T)
    {
      
      t=tA
      Na=Na+1
      n=n+1
#     tA=arrival(1.2,g=1,t)
      tA=t-log(runif(1))/1.2
      if(n==1)
      {
        Y=-log(runif(1))/mu
        tD=t+Y
      }
      A[Na]=t
    }
    else if(tD<=tA & tD<=T){
      t=tD;n=n-1;Nd=Nd+1;
      if(n==0){tD=Inf}
      else{Y=-log(runif(1))/mu;tD=t+Y}
      D[Nd]=t;N[Nd]=n
    }
    else if(tA>T & tD>T){break}
  }
  while(1){
    if(n>0)
    {
      t=tD;n=n-1;Nd=Nd+1
      if(n>0){Y=-log(runif(1))/mu;tD=t+Y}
      D[Nd]=t;N[Nd]=n
    }else if(n<=0){break}
  }
  Tp=max(t-T,0)
  w=mean(D-A)
  gohome=Tp
  long=sum(D-A)
  
  list(w=mean(D-A),gohome=Tp,L=long/t,K=max(D))
}

w=c()
go_home=c()
L=c()
for (i in 1:1000) {
  m=MG(12,2)
  w[i]=m$w
  go_home[i]=m$gohome
  L[i]=m$L
}
mean(w)
mean(go_home)
mean(L)