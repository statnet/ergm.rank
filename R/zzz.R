#  File R/zzz.R in package ergm.rank, part of the
#  Statnet suite of packages for network analysis, https://statnet.org .
#
#  This software is distributed under the GPL-3 license.  It is free,
#  open source, and has the attribution requirements (GPL Section 7) at
#  https://statnet.org/attribution .
#
#  Copyright 2008-2021 Statnet Commons
################################################################################
#' @useDynLib ergm.rank
#' @import statnet.common ergm network
.onAttach <- function(libname, pkgname){
  sm <- statnetStartupMessage("ergm.rank",c("statnet"),FALSE)
  if(!is.null(sm)) packageStartupMessage(sm)
}

.onLoad <- function(libname, pkgname){
  .RegisterProposals()
}

.RegisterProposals <- function(){
  ergm_proposal_table("c", "CompleteOrder", "",  0, "random", "AlterSwap")
}
