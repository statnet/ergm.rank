%  File man/ergm-references.Rd in package ergm.rank, part of the Statnet suite
%  of packages for network analysis, http://statnet.org .
%
%  This software is distributed under the GPL-3 license.  It is free,
%  open source, and has the attribution requirements (GPL Section 7) at
%  http://statnet.org/attribution
%
%  Copyright 2008-2018 Statnet Commons
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{ergm-references}
\alias{ergm-references}
\alias{references-ergm}
\alias{ergm.references}
\alias{references.ergm}
\alias{CompleterOrder}
\alias{InitErgmReference.CompleteOrder}
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

\section{Known issues}{
  
  \subsection{\code{\link[ergm:control.ergm]{MCMLE.trustregion}}}{

    Because Monte Carlo MLE's approximation to the likelihood becomes less
    accurate as the estimate moves away from the one used for the
    sample, \code{\link{ergm}} limits how far the optimization can move
    the estimate for every iteration: the log-likelihood may not change
    by more than \code{\link[ergm:control.ergm]{MCMLE.trustregion}} control
    parameter, which defaults to 20. This is an adequate value for
    binary ERGMs, but because each dyad in a valued ERGM contains more
    information, this number may be too small, resulting in
    unnecessarily many iterations needed to find the MLE.

    Automatically setting \code{\link[ergm:control.ergm]{MCMLE.trustregion}} is
    work in progress, but, in the meantime, you may want to set it to a
    high number (e.g., 1000).
    
  }
  
}


\section{Possible reference measures to represent baseline
  distributions}{

  Reference measures currently available are:
  \describe{
    
    \item{\code{CompleteOrder}}{A uniform distribution over the possible
      complete orderings of the alters by each ego.
    }

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
1100-1128. \doi{doi:10.1214/12-EJS696}

Krivitsky, PN and Butts, CT (2012). Exponential-Family Random Graph Models for Rank-Order Relational Data. \url{http://arxiv.org/abs/1210.0493}
}

\seealso{ergm, network, \%v\%, \%n\%, sna,
         summary.ergm, print.ergm}
\keyword{models}