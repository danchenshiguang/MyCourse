possion1=function(n)
{
  u=runif(1)
  i=0
  p=exp(-n)
  F=p
  while (F<=u) {
    p=n*p/(i+1)
    F=F+p
    i=i+1
  }
  return(i)
}
possion=c()
for (i in 1:10000) {
  possion[i]=possion1(4)
  
}
plot(table(possion)/10000,xlim=c(1,10))
par(new=TRUE)
plot(x,y,xlim=c(1,10))
lamda=4.3
x=1:10
y=dpois(x,lamda)
plot(x,y,type="p")