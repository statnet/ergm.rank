%  File man/ergm-references.Rd in package ergm.rank, part of the
%  Statnet suite of packages for network analysis, https://statnet.org .
%
%  This software is distributed under the GPL-3 license.  It is free,
%  open source, and has the attribution requirements (GPL Section 7) at
%  https://statnet.org/attribution .
%
%  Copyright 2008-2021 Statnet Commons
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{ergm-references}
\alias{ergm-references}
\alias{references-ergm}
\alias{ergm.references}
\alias{references.ergm}
\alias{InitWtErgmProposal.AlterSwap}
\docType{methods}

\title{Reference Measures for Exponential-Family Random Graph Models for
  Rank-Order Relational Data}

\description{
  This page describes the possible reference measures (baseline distributions)
  for modeling rank data found in the \code{\link[=ergm.rank-package]{ergm.rank}} package.

  Each of these is specified on the RHS of a one-sided formula passed as
  the \code{reference} argument to \code{\link[ergm]{ergm}}. 
  See the \code{\link[ergm]{ergm}} documentation for a complete
  description of how reference measures are specified.

}

\section{Possible reference measures to represent baseline
  distributions}{

  Reference measures currently available are:
  \describe{
    
    \item{\code{DiscUnif(a,b)}}{
      A discrete uniform distribution used as a baseline distribution
      for ranks. See \code{\link[ergm:ergm-references]{DiscUnif}}
      documentation in the \code{\link[ergm:ergm-package]{ergm}} for arguments. Using
      \code{reference=~DiscUnif(1,n-1)} (for network size \code{n}) can
      be used to model weak orderings, though this approach is currently
      untested. Note that it entails a specific assumption about actors'
      propensity to rank.
    }

  }
}

\references{
Krivitsky PN (2012). Exponential-Family Random Graph Models for Valued
Networks. \emph{Electronic Journal of Statistics}, 2012, 6,
1100-1128. \doi{10.1214/12-EJS696}

Krivitsky PN and Butts CT (2017). Exponential-Family Random Graph Models for Rank-Order Relational Data. \emph{Sociological Methodology}, 2017, 47, 68-112. \doi{10.1177/0081175017692623}
}

\seealso{ergm, network, \%v\%, \%n\%, sna,
         summary.ergm, print.ergm}
\keyword{models}
