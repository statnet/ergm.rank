#  File R/InitWtErgmTerm_rank.R in package ergm.rank, part of the
#  Statnet suite of packages for network analysis, https://statnet.org .
#
#  This software is distributed under the GPL-3 license.  It is free,
#  open source, and has the attribution requirements (GPL Section 7) at
#  https://statnet.org/attribution .
#
#  Copyright 2008-2022 Statnet Commons
################################################################################

#' @templateVar name rank.deference
#' @title Deference (aversion)
#' @description Measures the
#'   amount of "deference" in the network: configurations where an ego
#'   \eqn{i} ranks an alter \eqn{j} over another alter \eqn{k}, but
#'   \eqn{j}, in turn, ranks \eqn{k} over \eqn{i} . A lower-than-chance
#'   value of this statistic and/or a negative coefficient implies a form
#'   of mutuality in the network.
#'
#' @usage
#' # valued: rank.deference
#'
#' @template ergmTerm-general
#' @concept valued
#' @concept directed
#' @concept triad-related
#' @concept ordinal
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

#' @templateVar name rank.edgecov
#' @title Dyadic covariates
#' @description Models the effect of a dyadic covariate on the propensity of an ego
#'   \eqn{i} to rank alter \eqn{j} highly.
#'
#' @usage
#' # valued: rank.edgecov(x, attrname)
#'
#' @template ergmTerm-x-attrname
#'
#' @template ergmTerm-general
#' @concept valued
#' @concept directed
#' @concept ordinal
#' @concept quantitative dyadic attribute
InitWtErgmTerm.rank.edgecov <- function(nw, arglist, ...) {
  ### Check the network and arguments to make sure they are appropriate.
  a <- check.ErgmTerm(nw, arglist, 
                      varnames = c("x", "attrname"),
                      vartypes = c("matrix,network,character", "character"),
                      defaultvalues = list(NULL, NULL),
                      required = c(TRUE, FALSE),
                      argexpr = substitute(arglist))
  l <- ergm_edgecov_args("edgecov.rank", nw, a); xm <- l$xm; cn <- l$cn

  inputs <- c(as.double(t(xm))) # Need to transpose to produce row-major arrangement.
  list(name="edgecov_rank", coef.names = cn, inputs = inputs, dependence=TRUE, soname="ergm.rank", auxiliaries=~.sociomatrix("numeric"))
}

#' @templateVar name rank.inconsistency
#' @title (Weighted) Inconsistency
#' @description Measures the amount of disagreement between rankings of the focus
#'   network and a fixed covariate network `x` , by couting the number of pairwise
#'   comparisons for which the two networks disagree.
#'
#' @usage
#' # valued: rank.inconsistency(x, attrname, weights, wtname, wtcenter)
#' @param x,attrname `x` can be a [`network`] with an edge attribute `attrname` containing the ranks or a matrix of
#'   appropriate dimension containing the ranks. If `x` is not
#'   given, it defaults to the LHS network, and if `attrname` is
#'   not given, it defaults to the `response` edge attribute.
#' @param weights optional parameter to weigh the counts. Can be either a 3D \eqn{n\times n\times n} -array
#'    whose \eqn{(i,j,k)} th element gives the weight for the
#'   comparison by \eqn{i} of \eqn{j} and \eqn{k} or a function taking
#'   three arguments, \eqn{i}, \eqn{j}, and \eqn{k}, and returning
#'   the weight of this comparison.
#' @param wtname,wtcenter If `wtcenter=TRUE` , the
#'   calculated weights will be centered around their
#'   mean. `wtname` can be used to label this term.
#'
#' @template ergmTerm-general
#' @concept valued
#' @concept directed
#' @concept ordinal
#' @concept quantitative triadic attribute
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
    coef.names <- paste("inconsistency", deparse1(sc03[[2]]), sep=".")
  
  if(!is.null(a$attrname) && length(sc03)>1){
    coef.names<-paste("inconsistency", deparse1(sc03[[2]]),
                      deparse1(a$attrname), sep = ".")
  }else if (length(sc03)>1) {
    coef.names<-paste("inconsistency", deparse1(sc03[[2]]),
                      deparse1(sys.call(0)[[3]]), sep = ".")
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
#' @templateVar name rank.nodeicov
#' @title Attractiveness/Popularity covariates
#' @description Models the effect of one or more nodal covariates on the propensity of an
#'   actor to be ranked highly by the others.
#'
#' @usage
#' # valued: rank.nodeicov(attr)
#' @template ergmTerm-attr
#'
#' @template ergmTerm-general
#' @concept valued
#' @concept directed
#' @concept ordinal
#' @concept quantitative nodal attribute
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

#' @templateVar name rank.nonconformity
#' @title Nonconformity
#' @description Measures the amount of "nonconformity" in the network: configurations where an ego
#'   \eqn{i} ranks an alter \eqn{j} over another alter \eqn{k}, but
#'   ego \eqn{l} ranks \eqn{k} over \eqn{j} .
#'
#' @usage
#' # valued: rank.nonconformity(to, par)
#' @param to which controls to whom an ego may conform:
#'   - `"all"` (the default): Nonconformity to all
#'   egos is counted. A lower-than-chance
#'   value of this statistic and/or a negative coefficient implies a
#'   degree of consensus in the network.
#'   - `"localAND"`: Nonconformity of \eqn{i} to ego \eqn{l} regarding the relative ranking
#'   of \eqn{j} and \eqn{k} is only counted if \eqn{i} ranks \eqn{l}
#'   over both \eqn{j} and \eqn{k} . A lower-than-chance
#'   value of this statistic and/or a negative coefficient implies a
#'   form of hierarchical transitivity in the network. This is the
#'   recommended form of local nonconformity (over `"local1"`
#'   and `"local2"` ).
#'   - `"local1"`: Nonconformity of \eqn{i} to ego \eqn{l} regarding the relative ranking
#'   of \eqn{j} and \eqn{k} is only counted if \eqn{i} ranks \eqn{l} over \eqn{j} .
#'   - `"local2"`: Nonconformity of \eqn{i} to ego \eqn{l} regarding the relative ranking
#'   of \eqn{j} and \eqn{k} is only counted if \eqn{i} ranks \eqn{l} over \eqn{k} .
#'   - `"thresholds"`: Nonconformity of \eqn{i} to ego \eqn{l} regarding the relative ranking
#'   of \eqn{j} and \eqn{k} is only counted if \eqn{i} ranks \eqn{l} above `par`, where `par`
#'   can be a vector with multiple thresholds.
#'   - `"geometric"`: Nonconformity of \eqn{i} to ego \eqn{l} regarding the relative ranking
#'   of \eqn{j} and \eqn{k} is weighted by `par` taken to the power of the rank of \eqn{l} by \eqn{i} , where `par`
#'   is a scalar.
#' @param par additional parameters for some types of nonconformity.
#'
#' @template ergmTerm-general
#' @concept valued
#' @concept directed
#' @concept ordinal
#' @concept triad-related
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
  }else ergm_Init_abort("Unsupported type of nonconformity: ", sQuote(to), ".")
  
  list(name=name,
       coef.names=coef.names,
       inputs=inputs,
       dependence=TRUE, auxiliaries=~.sociomatrix("numeric"))
}
