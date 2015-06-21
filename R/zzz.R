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
  ergm.MHP.table("c", "CompleteOrder", "ranks",  0, "random", "DescRankEquivalent")

  ergm.MHP.table("c", "StdNormal", "ranks",  0, "random", "StdNormalRank")
}

.RegisterConstraintImplications <- function(){
}

.RegisterInitMethods <- function(){
  ergm.init.methods("CompleteOrder", c("CD","zeros"))
}
