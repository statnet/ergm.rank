#  File R/ergm.rank-terms-index.R in package ergm.rank, part of the Statnet suite
#  of packages for network analysis, https://statnet.org .
#
#  This software is distributed under the GPL-3 license.  It is free,
#  open source, and has the attribution requirements (GPL Section 7) at
#  https://statnet.org/attribution
#
#  Copyright 2008-2021 Statnet Commons
#######################################################################

#' Terms used in Exponential Family Random Graph Models for Ranks
#'
#' @name ergmTerm
#' @aliases ergm-terms ergm.terms terms-ergm terms.ergm
#' @docType package
#' @description This page describes the possible terms (and hence network statistics)
#' included in the [`ergm.rank`][ergm.rank-package] package.
#'
#' See the [`ergm`][ergmTerm] documentation in the `ergm`
#' package for a complete description of what ERGM terms are and how they are
#' used.
#'
#' @section Terms to represent network statistics included in the [`ergm.rank`][ergm.rank-package] pacakge:
#' All terms listed are valued. For their specific forms, see Krivitsky and
#' Butts (2012).
#'
#' These terms have a specialized interpretation, and are therefore generally
#' prefixed by "`rank.`", though they should take any valued data.
#'
#' ## Term index
#' \if{latex}{\Sexpr[results=rd,stage=render]{ergm:::.formatIndexLatex(ergm:::.buildTermsDataframe("ergmTerm"))}}
#' \if{text}{\Sexpr[results=rd,stage=render]{ergm:::.formatIndexText(ergm:::.buildTermsDataframe("ergmTerm"))}}
#' \if{html}{\Sexpr[results=rd,stage=render]{ergm:::.formatIndexHtml(ergm:::.buildTermsDataframe("ergmTerm"))}}
#'
#' ## Frequently-used terms
#' \if{latex}{\Sexpr[results=rd,stage=render]{ergm:::.formatMatrixLatex(ergm:::.termMatrix("ergmTerm", categories=ergm:::FREQUENTLY_USED_TERM_CATEGORIES, only.include='frequently-used'))}}
#' \if{text}{\Sexpr[results=rd,stage=render]{ergm:::.formatMatrixText(ergm:::.termMatrix("ergmTerm", categories=ergm:::FREQUENTLY_USED_TERM_CATEGORIES, only.include='frequently-used'))}}
#' \if{html}{\Sexpr[results=rd,stage=render]{ergm:::.formatMatrixHtml(ergm:::.termMatrix("ergmTerm", categories=ergm:::FREQUENTLY_USED_TERM_CATEGORIES, only.include='frequently-used'))}}
#'
#' ## Operator terms
#' \if{latex}{\Sexpr[results=rd,stage=render]{ergm:::.formatMatrixLatex(ergm:::.termMatrix("ergmTerm", categories=ergm:::OPERATOR_CATEGORIES, only.include='operator'))}}
#' \if{text}{\Sexpr[results=rd,stage=render]{ergm:::.formatMatrixText(ergm:::.termMatrix("ergmTerm", categories=ergm:::OPERATOR_CATEGORIES, only.include='operator'))}}
#' \if{html}{\Sexpr[results=rd,stage=render]{ergm:::.formatMatrixHtml(ergm:::.termMatrix("ergmTerm", categories=ergm:::OPERATOR_CATEGORIES, only.include='operator'))}}
#'
#' ## All terms
#' \if{latex}{\Sexpr[results=rd,stage=render]{ergm:::.formatMatrixLatex(ergm:::.termMatrix("ergmTerm"))}}
#' \if{text}{\Sexpr[results=rd,stage=render]{ergm:::.formatMatrixText(ergm:::.termMatrix("ergmTerm"))}}
#' \if{html}{\Sexpr[results=rd,stage=render]{ergm:::.formatMatrixHtml(ergm:::.termMatrix("ergmTerm"))}}
#'
#' ## Terms by concept
#' \if{latex}{\Sexpr[results=rd,stage=render]{ergm:::.formatTocLatex(ergm:::.termToc("ergmTerm"))}}
#' \if{text}{\Sexpr[results=rd,stage=render]{ergm:::.formatTocText(ergm:::.termToc("ergmTerm"))}}
#' \if{html}{\Sexpr[results=rd,stage=render]{ergm:::.formatTocHtml(ergm:::.termToc("ergmTerm"))}}
#'
#' @seealso \code{\link[ergm:ergm-terms]{ergm-terms}} (from the
#' [`ergm`][ergm-package] package), [`ergm`], [`network`], `%v%`, `%n%`
#'
#' @references
#' - Krivitsky P. N. (2012). Exponential-Family Random Graph Models for
#' Valued Networks. *Electronic Journal of Statistics*, 6, 1100-1128.
#' \doi{10.1214/12-EJS696}
#'
#' - Krivitsky PN and Butts CT (2017). Exponential-Family Random Graph
#' Models for Rank-Order Relational Data. *Sociological Methodology*,
#' 2017, 47, 68-112. \doi{10.1177/0081175017692623}
#' @keywords models
NULL

#' Reference Measures for Exponential-Family Random Graph Models for Rank-Order
#' Relational Data
#'
#' @name ergmReference
#' @aliases ergm-references references-ergm ergm.references references.ergm InitWtErgmProposal.AlterSwap
#' @docType package
#' @description This page describes the possible reference measures (baseline distributions)
#' for modeling rank data found in the [`ergm.rank`][ergm.rank-package] package.
#'
#' Each of these is specified on the RHS of a one-sided formula passed as the
#' `reference` argument to [`ergm`]. See the [`ergm`] documentation for a complete description of how
#' reference measures are specified.
#'
#' @section Possible reference measures to represent baseline distributions:
#'
#' Reference measures currently available are:
#' - `DiscUnif(a,b)`: A discrete uniform distribution used as a
#' baseline distribution for ranks. See [`DiscUnif`][DiscUnif-ergmReference] documentation in the
#' [`ergm`][ergm::ergm-package] for arguments. Using
#' `reference=~DiscUnif(1,n-1)` (for network size `n`) can be used to
#' model weak orderings, though this approach is currently untested. Note that
#' it entails a specific assumption about actors' propensity to rank.
#'
#' ## Reference index
#' \if{latex}{\Sexpr[results=rd,stage=render]{ergm:::.formatIndexLatex(ergm:::.buildTermsDataframe("ergmReference"))}}
#' \if{text}{\Sexpr[results=rd,stage=render]{ergm:::.formatIndexText(ergm:::.buildTermsDataframe("ergmReference"))}}
#' \if{html}{\Sexpr[results=rd,stage=render]{ergm:::.formatIndexHtml(ergm:::.buildTermsDataframe("ergmReference"))}}
#'
#' @seealso [`ergm`][ergm-package], [`network`], `\%v\%`, `\%n\%`, `sna`, [`summary.ergm`], [`print.ergm`]
#'
#' @references
#' - Krivitsky PN (2012). Exponential-Family Random Graph Models for
#' Valued Networks. *Electronic Journal of Statistics*, 2012, 6,
#' 1100-1128. \doi{10.1214/12-EJS696}
#'
#' - Krivitsky PN and Butts CT (2017). Exponential-Family Random Graph Models for
#' Rank-Order Relational Data. \emph{Sociological Methodology}, 2017, 47,
#' 68-112. \doi{10.1177/0081175017692623}
#'
#' @keywords models
NULL
