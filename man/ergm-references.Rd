\name{ergm-references}
\alias{ergm-references}
\alias{references-ergm}
\alias{ergm.references}
\alias{references.ergm}

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
  
  \subsection{Parameter space constraints}{
    
    Poisson- and geometric-reference ERGMs have an unbouded sample
    space. This means that the parameter space may be constrained in
    complex ways that depend on the terms used in the model. At this
    time \code{\link{ergm}} has no way to detect when a parameter
    configuration had strayed outside of the parameter space, but it may
    be noticeable on a runtime trace plot (activated via
    \code{MCMC.runtime.traceplot} control parameter), when the simulated
    values keep climbing upwards. (See Krivitsky (2012) for a further
    discussion.)

    A possible remedy if this appears to occur is to try lowering the
    control parameter \code{MCMLE.steplength}.

  }

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
    
    \item{}{\emph{-reference ERGM:}
    }

  }
}

\references{
Krivitsky PN (2012). Exponential-Family Random Graph Models for Valued Networks. \emph{Electronic Journal of Statistics}, 2012, 6, 1100-1128. \href{http://dx.doi.org/10.1214/12-EJS696}{\code{doi:10.1214/12-EJS696}}

}

\seealso{ergm, network, \%v\%, \%n\%, sna,
         summary.ergm, print.ergm}
\keyword{models}