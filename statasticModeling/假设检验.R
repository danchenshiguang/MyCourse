#卡方检测
data=c(20,7,23,17,12,21)
mean=100/6
df=6-1
T=sum((data-mean)^2)/mean
p=1-pchisq(T,df)

#用蒙的卡罗检测
exam=function(m,T)
{
  T0=9
  mean=100/6
  for (i in 1:m) {
    Y=sample(1:6,100,reeplace=T)
    N=c()
    for (i in 1:6) {
      N=c(n,length(Y[Y==i]))
    }
    T0[i]=sum(((N-mean)^2)/mean)
  }
  length(T0[T0>=T])/m
}


#ks检测
D=function(X)
{
  Y=sort(X)
  M=0
  L=length(X)
  for (i in 1:L) {
    M[i]=max(i/L-pexp(Y[i],1/100),pexp(Y[i],1/100)-(i-1)/L)
  }
  d=max(M)
  return(d)
}

X=c(71,198,139,145,21,31,47,122,146,109)
D(X)

Ks_pValue=function(n,d,X)
{
  D=c()
  L=length(X)
  for (i in 1:n) {
    D[i]=D(runif(L))
  }
  length(D[D>=d])
}

KsPvalue=function(n,d,X)
{
  D=0;M=0;L=length(X)
  for (i in 1:n) {
    V=sort(runif(L))
    for (j in 1:L) {
      M[j]=max(j/L-V[j],V[j]-(j-1)/L)
    }
    D[i]=max(M)
  }
  length(D[D>=d])/n
}

