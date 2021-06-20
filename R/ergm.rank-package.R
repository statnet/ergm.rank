#  File R/ergm.rank-package.R in package ergm.rank, part of the
#  Statnet suite of packages for network analysis, https://statnet.org .
#
#  This software is distributed under the GPL-3 license.  It is free,
#  open source, and has the attribution requirements (GPL Section 7) at
#  https://statnet.org/attribution .
#
#  Copyright 2008-2021 Statnet Commons
################################################################################
#' Fit, Simulate and Diagnose Exponential-Family Models for Rank-Order
#' Relational Data
#' 
#' \code{\link[=ergm.rank-package]{ergm.rank}} is a set of extensions to
#' package \code{\link[=ergm-package]{ergm}} to fit and simulate from
#' exponential-family random graph models for networks whose edge weights are
#' ranks. For a list of functions type \code{help(package='ergm')} and
#' \code{help(package='ergm.rank')}
#' 
#' Mainly, it implements the \code{CompleteOrder} reference measure for valued
#' ERGMs (\link[=ergm-references]{documented here}), and provides some
#' rank-order change statistics (\link[=ergm-terms]{documented here}).
#' 
#' For a complete list of the functions, use \code{library(help="ergm")} and
#' \code{library(help="ergm.rank")} or read the rest of the manual.
#' 
#' When publishing results obtained using this package, please cite the
#' original authors as described in \code{citation(package="ergm.rank")}.
#' 
#' All programs derived from this package must cite it.
#' 
#' This package contains functions specific to using \code{\link{ergm}} to
#' model networks whose dyad values are ranks. Examples include preferences,
#' valued ties reduced to ranks, etc..
#' 
#' For detailed information on how to download and install the software, go to
#' the Statnet project website: \url{https://statnet.org}. A tutorial, support
#' newsgroup, references and links to further resources are provided there.
#' 
#' @name ergm.rank-package
#' @docType package
#' @author Pavel N. Krivitsky \email{pavel@@statnet.org}
#' @seealso \code{\link{ergm-terms}}, \code{\link{ergm-references}}
#' @references Krivitsky PN (2012). Exponential-Family Random Graph Models for
#' Valued Networks. \emph{Electronic Journal of Statistics}, 2012, 6,
#' 1100-1128. c("\\Sexpr[results=rd,stage=build]{tools:::Rd_expr_doi(\"#1\")}",
#' "doi:10.1214/12-EJS696")\Sexpr{tools:::Rd_expr_doi("doi:10.1214/12-EJS696")}
#' 
#' Krivitsky PN and Butts CT (2017). Exponential-Family Random Graph
#' Models for Rank-Order Relational Data. \emph{Sociological
#' Methodology}, 2017, 47, 68-112. \doi{10.1177/0081175017692623}
#' @keywords package
NULL
