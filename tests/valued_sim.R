library(statnet.common)
library(ergm)

## ## StdNormal-reference with rank constraint
## cat("Standard-normal-reference ERGM with rank constraint\n")
## load("testrank3d.RData")

## s.full<-simulate(testrank3d~sum, nsim=1000, reference=~StdNormal, response="w", coef=0, statsonly=FALSE,
##                  constraints=~ranks, control=control.simulate(MCMC.burnin=10000))
## s.cells<-sapply(s.full, function(x) as.matrix(x,m="a",a="w"), simplify=FALSE)
## ref.sample<-pmax(rnorm(10000),rnorm(10000))

## cat("Simulated means (target[1:2,]=+-",mean(ref.sample),";target[3,]=0):\n",sep="")
## print(matrix(c(NA,
##   mean(sapply(s.cells,"[",1,2)),
##   mean(sapply(s.cells,"[",1,3)),
##   mean(sapply(s.cells,"[",2,1)),
##   NA,
##   mean(sapply(s.cells,"[",2,3)),
##   mean(sapply(s.cells,"[",3,1)),
##   mean(sapply(s.cells,"[",3,2)),
##   NA),3,3,byrow=TRUE))

## cat("Simulated vars (target[1:2,]=+-",var(ref.sample),";target[3,]=0):\n",sep="")
## print(matrix(c(NA,
##   var(sapply(s.cells,"[",1,2)),
##   var(sapply(s.cells,"[",1,3)),
##   var(sapply(s.cells,"[",2,1)),
##   NA,
##   var(sapply(s.cells,"[",2,3)),
##   var(sapply(s.cells,"[",3,1)),
##   var(sapply(s.cells,"[",3,2)),
##   NA),3,3,byrow=TRUE))
