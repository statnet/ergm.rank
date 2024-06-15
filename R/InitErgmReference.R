#  File R/InitErgmReference.R in package ergm.rank, part of the
#  Statnet suite of packages for network analysis, https://statnet.org .
#
#  This software is distributed under the GPL-3 license.  It is free,
#  open source, and has the attribution requirements (GPL Section 7) at
#  https://statnet.org/attribution .
#
#  Copyright 2008-2024 Statnet Commons
################################################################################

#' @templateVar name CompleteOrder
#' @title A uniform distribution over the possible complete orderings of the alters by each ego
#' @description A uniform distribution over the possible complete orderings of the alters by each ego
#'
#' @usage
#' # CompleteOrder
#'
#' @template ergmReference-general
#' @concept valued
#' @concept ordinal
InitErgmReference.CompleteOrder <- function(nw, arglist, ...){
  a <- check.ErgmTerm(nw, arglist)
  list(name="CompleteOrder", init_methods = c("CD","zeros"))
}
