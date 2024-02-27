accept= function(n)
{
  p=c(0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1)
  data=c()
  for (i in 1:n) {
    u1=runif(1)
    u2=runif(1)
    y=floor(10*u1)+1
    while(u2>p[y]/0.1)
    {
      u1=runif(1)
      u2=runif(1)
      y=floor(10*u1)+1
    }
    data[i]=y
  }
  return(data)
}
x=1:10
fx=table(sample(x,50,replace = T))
p=as.numeric(fx/50)
m=max(p)
u1=floor(10*runif(100000))+1
barplot(table(u1))
u2=runif(100000)
accept_data=u1[u2<=p[u1]/m]
length(accept_data)
plot(x,p,ylim=c(0,m))
par(new=TRUE)
plot(table(accept_data)/length(accept_data))

op=par(mfrow=c(2,2))
barplot(p,main="Original distribution")
barplot(table(accept_data)/length(accept_data),main="simulated random number")
plot(x,p,ylim = c(0,m))
plot(table(accept_data)/length(accept_data))
par(op)