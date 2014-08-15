# Overrides ordinary WtErgmTerms with their ranked counterparts.

InitWtErgmTerm.edgecov <- function(nw, arglist, response, ...) {
  ### Check the network and arguments to make sure they are appropriate.
  a <- check.ErgmTerm(nw, arglist, 
                      varnames = c("x", "attrname", "form"),
                      vartypes = c("matrix,network,character", "character", "character"),
                      defaultvalues = list(NULL, NULL, "sum"),
                      required = c(TRUE, FALSE, FALSE))
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

  form<-match.arg(a$form,c("sum","nonzero","rank"))
  
  inputs <- c(as.double(xm))
  list(name=paste("edgecov",form,sep="_"), coef.names = paste(cn,form,sep="."), inputs = inputs, dependence=form=="rank")
}

InitWtErgmTerm.nodeicov<-function (nw, arglist, response, ...) {
  a <- check.ErgmTerm(nw, arglist, directed=TRUE,
                     varnames = c("attrname","transform","transformname","form"),
                     vartypes = c("character","function","character","character"),
                     defaultvalues = list(NULL,identity,"","sum"),
                     required = c(TRUE,FALSE,FALSE,FALSE))
  form<-match.arg(a$form,c("sum","nonzero","rank"))
  attrname<-a$attrname
  f<-a$transform
  f.name<-a$transformname
  coef.names <- paste("nodeicov",form,f.name,attrname,sep=".")
  nodecov <- f(get.node.attr(nw, attrname, "nodeicov", numeric=TRUE))
  list(name=paste("nodeicov",form,sep="_"), soname="ergm",
       coef.names=coef.names,
       inputs=c(nodecov),
       dependence=(form=="rank"))
}
