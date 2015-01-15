library(ergm.rank)

local1.nonconformity <- function(m){
  n <- nrow(m)
  sum(sapply(1:n, function(i) sapply(1:n, function(j) sapply(1:n, function(k) sapply(1:n, function(l) if(length(unique(c(i,j,k,l)))==4) (m[i,l]>m[i,j])*(m[l,j]>m[l,k])*(1-(m[i,j]>m[i,k])) else 0 )))))
}
local2.nonconformity <- function(m){
  n <- nrow(m)
  sum(sapply(1:n, function(i) sapply(1:n, function(j) sapply(1:n, function(k) sapply(1:n, function(l) if(length(unique(c(i,j,k,l)))==4) (m[i,l]>m[i,k])*(m[l,j]>m[l,k])*(1-(m[i,j]>m[i,k])) else 0 )))))
}
localAND.nonconformity <- function(m){
  n <- nrow(m)
  sum(sapply(1:n, function(i) sapply(1:n, function(j) sapply(1:n, function(k) sapply(1:n, function(l) if(length(unique(c(i,j,k,l)))==4) (m[i,l]>m[i,k] && m[i,l]>m[i,j])*(m[l,j]>m[l,k])*(1-(m[i,j]>m[i,k])) else 0 )))))
}
global.nonconformity <- function(m){
  n <- nrow(m)
  sum(sapply(1:n, function(i) sapply(1:n, function(j) sapply(1:n, function(k) sapply(1:n, function(l) if(length(unique(c(i,j,k,l)))==4) (m[l,j]>m[l,k])*(1-(m[i,j]>m[i,k])) else 0 )))))
}
deference <- function(m){
  n <- nrow(m)
  sum(sapply(1:n, function(i) sapply(1:n, function(j) sapply(1:n, function(l) if(length(unique(c(i,j,l)))==3) (m[l,j]>m[l,i])*(m[i,l]>m[i,j]) else 0 ))))
}

n <- 13
S <- 20

nw0 <- network.initialize(n,dir=TRUE)

nws <- simulate(nw0~nonconformity("all")+nonconformity("local1")+nonconformity("local2")+nonconformity("localAND")+deference, coef=rep(0,5),response="r", reference=~DiscUnif(1, n-1), nsim=S, statsonly=FALSE)

d.stats <- attr(nws,"stats")

c.stats <- t(sapply(lapply(nws,as.matrix,attrname="r"),function(m) c(global.nonconformity(m), local1.nonconformity(m), local2.nonconformity(m), localAND.nonconformity(m), deference(m))))

s.stats <- summary(nws~nonconformity("all")+nonconformity("local1")+nonconformity("local2")+nonconformity("localAND")+deference, response="r")

stopifnot(all.equal(d.stats,c.stats,check.attributes=FALSE),
          all.equal(d.stats,s.stats,check.attributes=FALSE),
          all.equal(s.stats,c.stats,check.attributes=FALSE))

nw1 <- nws[[length(nws)]]

nws <- simulate(nw1~nonconformity("all")+nonconformity("local1")+nonconformity("local2")+nonconformity("localAND")+deference, coef=rep(0,5),response="r", reference=~DescRank, nsim=S, statsonly=FALSE)

d.stats <- attr(nws,"stats")

c.stats <- t(sapply(lapply(nws,as.matrix,attrname="r"),function(m) c(global.nonconformity(m), local1.nonconformity(m), local2.nonconformity(m), localAND.nonconformity(m), deference(m))))

s.stats <- summary(nws~nonconformity("all")+nonconformity("local1")+nonconformity("local2")+nonconformity("localAND")+deference, response="r")

stopifnot(all.equal(d.stats,c.stats,check.attributes=FALSE),
          all.equal(d.stats,s.stats,check.attributes=FALSE),
          all.equal(s.stats,c.stats,check.attributes=FALSE))
