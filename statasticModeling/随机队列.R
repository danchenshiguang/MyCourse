romCard=function()
{
  sucNum=0
  a=c(1:100)
  for (k in 1:100) {
    x=length(101-i)*runif(1)+1
    x=ceiling(x)
    temp=a[101-i]
    a[101-i]=a[x]
    a[x]=temp
  }
  for (i in 1:100) {
    if(a[i]==i){
             sucNum=sucNum+1
         }
  }
  return(sucNum)
}
array1=c()
for (i in 1:10000) {
  array1[i]=romCard()
  
}
mean(array1)
romCard=function()
{
  sucNum=0
  a=sample(1:100,100,replace = F,rep(1/100,100))
  for (i in 1:100) {
    if(a[i]==i){
      sucNum=sucNum+1
    }
  }
  return(sucNum)
}
