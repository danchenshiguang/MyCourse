pt=function()
{
  u1=runif(1)
  u2=runif(1)
  x=0
  if(u1<0.9)
  {
    x=floor(10*u2)+5
  }
  else
  {
    x=floor(5*u2)*2+5
  }
  return(x)
}

b=c()
for (i in 1:1000) {
  b[i]=pt()
}
p=as.numeric(table(b)/1000)
x=5:14
plot(x,p)