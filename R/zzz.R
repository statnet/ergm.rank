.onAttach <- function(lib, pkg){
  sm <- statnetStartupMessage("ergm.rank",c("statnet"),FALSE)
  if(!is.null(sm)) packageStartupMessage(sm)
}

.onLoad <- function(lib, pkg){
  .RegisterMHPs()
  .RegisterConstraintImplications()
  .RegisterInitMethods()
}

.RegisterMHPs <- function(){
  ergm.MHP.table("c", "CompleteOrder", "",  0, "random", "AlterSwap")
}

.RegisterConstraintImplications <- function(){
}

.RegisterInitMethods <- function(){
  ergm.init.methods("CompleteOrder", c("CD","zeros"))
}
