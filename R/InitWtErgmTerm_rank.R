#  File R/InitWtErgmTerm_rank.R in package ergm.rank, part of the
#  Statnet suite of packages for network analysis, https://statnet.org .
#
#  This software is distributed under the GPL-3 license.  It is free,
#  open source, and has the attribution requirements (GPL Section 7) at
#  https://statnet.org/attribution .
#
#  Copyright 2008-2021 Statnet Commons
################################################################################
InitWtErgmTerm.rank.deference<-function(nw, arglist, ...) {
  a <- check.ErgmTerm(nw, arglist, directed=TRUE,
                      varnames = NULL,
                      vartypes = NULL,
                      defaultvalues = list(),
                      required = NULL)

  list(name="deference",
       coef.names="deference",
       inputs=NULL,
       dependence=TRUE, auxiliaries=~.sociomatrix("numeric"))
}

InitWtErgmTerm.rank.edgecov <- function(nw, arglist, ...) {
  ### Check the network and arguments to make sure they are appropriate.
  a <- check.ErgmTerm(nw, arglist, 
                      varnames = c("x", "attrname"),
                      vartypes = c("matrix,network,character", "character"),
                      defaultvalues = list(NULL, NULL),
                      required = c(TRUE, FALSE))
  ### Process the arguments
  if(is.network(a$x))
    xm<-as.matrix.network(a$x,matrix.type="adjacency",a$attrname)
  else if(is.character(a$x))
    xm<-get.network.attribute(nw,a$x)
  else
    xm<-as.matrix(a$x)
  ### Construct the list to return
  if(!is.null(a$attrname)) {
    # Note: the sys.call business grabs the name of the x object from the 
    # user's call.  Not elegant, but it works as long as the user doesn't
    # pass anything complicated.
    cn<-paste("edgecov", as.character(sys.call(0)[[3]][2]), 
              as.character(a$attrname), sep = ".")
  } else {
    cn<-paste("edgecov", as.character(sys.call(0)[[3]][2]), sep = ".")
  }

  inputs <- c(as.double(t(xm))) # Need to transpose to produce row-major arrangement.
  list(name="edgecov_rank", coef.names = paste(cn,"rank",sep="."), inputs = inputs, dependence=TRUE, soname="ergm.rank", auxiliaries=~.sociomatrix("numeric"))
}


InitWtErgmTerm.rank.inconsistency<-function (nw, arglist, ...) {
  a <- check.ErgmTerm(nw, arglist, directed=TRUE,
                     varnames = c("x","attrname","weights","wtname","wtcenter"),
                     vartypes = c("matrix,network","character","array,function","character","logical"),
                     defaultvalues = list(nw,nw%ergmlhs%"response",NULL,NULL,FALSE),
                     required = c(FALSE,FALSE,FALSE,FALSE,FALSE))

  name<-"inconsistency_rank"
  
    ## Process hamming network ##
  if(is.network(a$x)){ # Arg to hamming is a network
    xm<-as.matrix.network(a$x,matrix.type="adjacency",a$attrname)
  }else if(is.character(a$x)){ # Arg to hamming is the name of an attribute in nw
    xm<-get.network.attribute(nw,a$x)
    xm<-as.matrix.network(xm,matrix.type="adjacency")
  }else{
    xm<-as.matrix(a$x) # Arg to hamming is anything else; attempts to coerce
  }
  ## Process case without dyadcov (i.e. unweighted) ##
  sc03 <- sys.call(0)[[3]]
  coef.names <- "inconsistency"  # This might be modified later
  if (length(sc03)>1) 
    coef.names <- paste("inconsistency", as.character(sc03[[2]]), sep=".")
  
  if(!is.null(a$attrname) && length(sc03)>1){
    coef.names<-paste("inconsistency", as.character(sc03[2]),
                      as.character(a$attrname), sep = ".")
  }else if (length(sc03)>1) {
    coef.names<-paste("inconsistency", as.character(sc03[2]),
                      as.character(sys.call(0)[[3]][3]), sep = ".")
  }

  # A column-major matrix of choices.
  inputs <- c(t(xm))

  if(!is.null(a$weights)){
    name<-"inconsistency_cov_rank"
    if(!is.null(a$wtname)) coef.names<-paste(coef.names,":",a$wtname,if(a$wtcenter)"c"else"",sep="")

    if(is.function(a$weights)){
      mk.inconsist.cov<-function(n,FUN)
        aperm(array(unlist(sapply(seq_len(n),
                                  function(i)
                                  sapply(seq_len(n),
                                         function(j1)
                                         sapply(seq_len(n),
                                                function(j2)
                                                if(i==j1||i==j2||j1==j2) NA
                                                else FUN(i,j1,j2),
                                                simplify=FALSE),
                                         simplify=FALSE),
                                  simplify=FALSE)),
                    c(n,n,n)),
              3:1)
      a$weights<-mk.inconsist.cov(network.size(nw),a$weights)
    }

#' @importFrom stats na.omit
    if(a$wtcenter) a$weights <- a$weights - mean(na.omit(c(a$weights)))

    a$weights[is.na(a$weights)] <- 0
    
    inputs<-c(inputs,aperm(a$weights,c(3,2,1)))
  }
  
  list(name=name, coef.names=coef.names, #name and coef.names: required 
       inputs = inputs, dependence = FALSE, auxiliaries=~.sociomatrix("numeric"))
}

#' @importFrom utils packageVersion
InitWtErgmTerm.rank.nodeicov<-function (nw, arglist, ..., ergm.rank.version=packageVersion("ergm.rank")) {
  if(ergm.rank.version <= as.package_version("1.2.0")){
    ### Check the network and arguments to make sure they are appropriate.
    a <- check.ErgmTerm(nw, arglist, directed=TRUE,
                        varnames = c("attrname","transform","transformname"),
                        vartypes = c("character","function","character"),
                        defaultvalues = list(NULL,function(x)x,""),
                        required = c(TRUE,FALSE,FALSE))
    ### Process the arguments
    attrname<-a$attrname
    f<-a$transform
    f.name<-a$transformname
    coef.names <- paste(paste("nodeicov.rank",f.name,sep=""),attrname,sep=".")
    nodecov <- f(get.node.attr(nw, attrname, "nodeicov", numeric=TRUE))
  }else{
    ### Check the network and arguments to make sure they are appropriate.
    a <- check.ErgmTerm(nw, arglist, directed=TRUE,
                        varnames = c("attr"),
                        vartypes = c(ERGM_VATTR_SPEC),
                        defaultvalues = list(NULL),
                        required = c(TRUE))
    ### Process the arguments
    nodecov <- ergm_get_vattr(a$attr, nw, accept="numeric", multiple="matrix")
    coef.names <- paste("nodeicov.rank",attr(nodecov, "name"),sep=".")
    if(is.matrix(nodecov)) coef.names <- paste(coef.names, NVL(colnames(nodecov), seq_len(ncol(nodecov))), sep=".")
  }
  list(name="nodeicov_rank", soname="ergm.rank",
       coef.names=coef.names,
       inputs=c(nodecov),
       dependence=TRUE, auxiliaries=~.sociomatrix("numeric"))
}

InitWtErgmTerm.rank.nonconformity<-function(nw, arglist, ...) {
  a <- check.ErgmTerm(nw, arglist, directed=TRUE,
                      varnames = c("to","par"),
                      vartypes = c("character","numeric"),
                      defaultvalues = list("all",NULL),
                      required = c(FALSE,FALSE))

  to<-match.arg(a$to,c("all","thresholds","geometric","local1","local2","localAND"))

  if(to=="all"){
    inputs <- NULL
    coef.names <- "nonconformity"
    name <- "nonconformity"
  }else if(to=="thresholds"){
    inputs <- sort(as.numeric(a$par),decreasing=TRUE)
    coef.names <- paste("nonconformity.over",inputs,sep=".")
    name <- "nonconformity_thresholds"
  }else if(to=="geometric"){
    inputs <- c(a$par,max(nw %e% (nw%ergmlhs%"response")))
    coef.names <- paste("nonconformity.gw.",a$par,sep=".")
    name <- "nonconformity_decay"
  }else if(to=="local1"){
    inputs <- NULL
    coef.names <- "nonconformity.local1"
    name <- "local1_nonconformity"
  }else if(to=="local2"){
    inputs <- NULL
    coef.names <- "nonconformity.local2"
    name <- "local2_nonconformity"
  }else if(to=="localAND"){
    inputs <- NULL
    coef.names <- "nonconformity.localAND"
    name <- "localAND_nonconformity"
  }
  
  list(name=name,
       coef.names=coef.names,
       inputs=inputs,
       dependence=TRUE, auxiliaries=~.sociomatrix("numeric"))
}
