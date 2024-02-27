#齐次泊松过程模拟方法1
process=function(lamda,N){
  X=-log(runif(N))/lamda
  S=c()
  S[1]=X[1];
  for(i in 2:N){
    S[i]=S[i-1]+X[i]
  }
  return(S)
}
t=c()
for(i in 1:100000){
  data=process(3,10)
  t[i]=data[10]
}
#齐次泊松过程模拟法2
process=function(lamda,T){
  n=rpois(1,lamda*T)
  S=sort(T*runif(n))
  return(S)
}
I=c()
for(i in 1:100000){
  data=process(3,10)
  I[i]=data[1]
}

#非齐次泊松分布模拟法
process=function(lamda,T){
  N=rpois(1,lamda*T)
  S=sort(T*runif(N))
  U2=runif(N)
  keep=S[U2<=(3+4/(S+1))/lamda]
  return(keep)
}


