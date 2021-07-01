%  File man/ergm-terms.Rd in package ergm.rank, part of the
%  Statnet suite of packages for network analysis, https://statnet.org .
%
%  This software is distributed under the GPL-3 license.  It is free,
%  open source, and has the attribution requirements (GPL Section 7) at
%  https://statnet.org/attribution .
%
%  Copyright 2008-2021 Statnet Commons
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{ergm-terms}
\alias{ergm-terms}
\alias{ergm.terms}
\alias{terms-ergm}
\alias{terms.ergm}
\docType{methods}
\title{Terms used in Exponential Family Random Graph Models for Ranks}
\description{
  This page describes the possible terms (and hence network statistics)
  included in the \code{\link[=ergm.rank-package]{ergm.rank}} package.

  See the \code{\link[ergm]{ergm-terms}} documentation in the
  \code{ergm} package for a complete description of what ERGM terms are
  and how they are used.
}

\section{Terms to represent network statistics included in the
  \code{\link[=ergm.rank-package]{ergm.rank}} pacakge}{

  All terms listed are valued. For their specific forms, see Krivitsky
  and Butts (2012).

  These terms have a specialized interpretation, and are therefore
  generally prefixed by \dQuote{\code{rank.}}, though they should take any
  valued data.
}
\references{
  \itemize{
  
\item Krivitsky P. N. (2012). Exponential-Family Random Graph Models for
Valued Networks. \emph{Electronic Journal of Statistics}, 6,
1100-1128. \doi{10.1214/12-EJS696}

\item Krivitsky PN and Butts CT (2017). Exponential-Family Random Graph Models for Rank-Order Relational Data. \emph{Sociological Methodology}, 2017, 47, 68-112. \doi{10.1177/0081175017692623}


}
}
\seealso{\code{\link[ergm:ergm-terms]{ergm-terms}} (from the \code{\link[=ergm-package]{ergm}} package), \code{\link{ergm}}, \code{\link{network}}, \code{\link{\%v\%}}, \code{\link{\%n\%}}}
\keyword{models}
