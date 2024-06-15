#  File R/ergm.rank-package.R in package ergm.rank, part of the
#  Statnet suite of packages for network analysis, https://statnet.org .
#
#  This software is distributed under the GPL-3 license.  It is free,
#  open source, and has the attribution requirements (GPL Section 7) at
#  https://statnet.org/attribution .
#
#  Copyright 2008-2024 Statnet Commons
################################################################################
#' Fit, Simulate and Diagnose Exponential-Family Models for Rank-Order
#' Relational Data
#' 
#' \code{\link[=ergm.rank-package]{ergm.rank}} is a set of extensions
#' to package \code{\link[=ergm-package]{ergm}} to fit and simulate
#' from exponential-family random graph models for networks whose edge
#' weights are ranks. Mainly, it implements the
#' \code{\link[=CompleteOrder-ergmReference]{CompleteOrder}} reference
#' measure for valued ERGMs \insertCite{Kr12e,KrHu23e}{ergm.rank} and provides some rank-order change
#' statistics (`search.ergmTerms("ordinal")` for a list) \insertCite{KrBu17e}{ergm.rank}.
#' 
#' When publishing results obtained using this package, please cite the
#' original authors as described in \code{citation(package="ergm.rank")}.
#' 
#' All programs derived from this package must cite it.
#' 
#' This package contains functions specific to using
#' \code{\link{ergm}} to model networks whose dyad values are
#' ranks. Examples include preferences, valued ties reduced to ranks,
#' etc.. These terms have a specialized interpretation, and are
#' therefore generally prefixed by "`rank.`", though they should take
#' any valued data.
#'
#' For detailed information on how to download and install the software, go to
#' the Statnet project website: \url{https://statnet.org}. A tutorial, support
#' newsgroup, references and links to further resources are provided there.
#' 
#' @name ergm.rank-package
#' @references  \insertAllCited{}
"_PACKAGE"
