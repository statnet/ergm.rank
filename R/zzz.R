.onAttach <- function(lib, pkg){
  sm <- statnetStartupMessage("ergm.rank",c("statnet"),FALSE)
  if(!is.null(sm)) packageStartupMessage(sm)

  .RegisterMHPs()
  .RegisterConstraintImplications()
  .RegisterInitMethods()
}

.RegisterMHPs <- function(){
  ergm.MHP.table("c", "DescRank", "",  0, "random", "DescRank")
  ergm.MHP.table("c", "DescRank", "ranks",  0, "random", "DescRankEquivalent")

  ergm.MHP.table("c", "StdNormal", "ranks",  0, "random", "StdNormalRank")
}

.RegisterConstraintImplications <- function(){
}

.RegisterInitMethods <- function(){
  ergm.init.methods("DescRank", c("CD","zeros"))
}
