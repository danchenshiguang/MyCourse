more_than_1=function(n)
{
  if(n>0)
  {
    return(1)
  }
  else
  {
    return(0)
  }
}
Num_12= function(n)
{
  num_array=c()
  result=0
  count_array=c()
  for (i in 1:12) {
    count_array[i]=0
  }
  for (i in 1:n) 
    {
      a=ceiling(6*runif(1))
      b=ceiling(6*runif(1))
      num_array[i]=a+b
  }
  for (i in 1:n)
  {
      count_array[num_array[i]]=count_array[num_array[i]]+1
      count_array[num_array[i]]=more_than_1(count_array[num_array[i]])
      if(sum(count_array)==6)
      {
        result=i
        return(result)
      }
  }
}
result_array=c()
for (i in 1:10000) {
  result_array[i]=Num_12(10000)
}
mean(result_array)
var(result_array)