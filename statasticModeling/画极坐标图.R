#圆
plot.new()
plot.window(xlim=c(-20,20),ylim = c(-20,20))
t=seq(0,10*pi,by=pi/100)

  x=r*cos(t)
  y=r*sin(t)

  polygon(x,y,col = 'pink' ,border = 'red')
#玫瑰图
plot.new()
plot.window(xlim=c(-5,5),ylim = c(-5,5))
t=seq(0,4*pi,by=pi/100)
r=2*sin(4*t)
  x=r*cos(t)
  y=r*sin(t)
  lines(x,y)
#阿基米德悬线
  plot.new()
  plot.window(xlim=c(-20,20),ylim = c(-20,20))
  t=seq(0,4*pi,by=pi/100)
  r=0.3+2*t
  x=r*cos(t)
  y=r*sin(t)
  lines(x,y)
  
#心型线
  plot.new()
  plot.window(xlim=c(-2,2),ylim = c(-2,2))
  t=seq(0,10*pi,by=pi/100)
  r=1-sin(t)
  x=r*cos(t)
  y=r*sin(t)
  lines(x,y)
  polygon(x,y,col = 'pink' ,border = 'red')
#  
  plot.new()
  plot.window(xlim=c(-5,5),ylim = c(-5,5))
  t=seq(0,10*pi,by=pi/100)
  x=16*(sin(t)^3)
  y=13*cos(t)-5*cos(2*t)-2*cos(3*t)-cos(4*t)
  lines(x,y) 
  
  
  
  n <- 100
  xx <- c(0:n, n:0)   #生成202个元素的向量，其中前面101与后面101数字对称
  yy <- c(c(0, cumsum(stats::rnorm(n))), rev(c(0, cumsum(stats::rnorm(n)))))
  plot   (xx, yy, type = "n", xlab = "Time", ylab = "Distance")
  polygon(xx, yy, col = "red", border = "red")

  
