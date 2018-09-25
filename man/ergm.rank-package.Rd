%  File man/ergm.rank-package.Rd in package ergm.rank, part of the Statnet suite
%  of packages for network analysis, http://statnet.org .
%
%  This software is distributed under the GPL-3 license.  It is free,
%  open source, and has the attribution requirements (GPL Section 7) at
%  http://statnet.org/attribution
%
%  Copyright 2008-2018 Statnet Commons
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{ergm.rank-package}
\alias{ergm.rank-package}
\docType{package}
\title{
Fit, Simulate and Diagnose Exponential-Family Models for Rank-Order
Relational Data 
}
\description{
\code{\link[=ergm.rank-package]{ergm.rank}} is a set of extensions to
\R package \code{\link[=ergm-package]{ergm}} to fit and simulate from exponential-family random 
graph models for networks whose edge weights are ranks. For a list of
functions type \code{help(package='ergm')} and
\code{help(package='ergm.rank')}

Mainly, it implements the \code{CompleteOrder} reference measure for valued ERGMs (\link[=ergm-references]{documented here}), and provides some
rank-order change statistics (\link[=ergm-terms]{documented here}).

For a complete list of the functions, use \code{library(help="ergm")} and \code{library(help="ergm.rank")} 
or read the rest of the manual. 

When publishing results obtained using this package, please cite the
original authors as described in \code{citation(package="ergm.rank")}.

All programs derived from this package must cite it.

}
\details{
This package contains functions specific to using \code{\link{ergm}} to
model networks whose dyad values are ranks. Examples include
preferences, valued ties reduced to ranks, etc..

For detailed information on how to download and install the software,
go to the Statnet project website:
\url{statnet.org}.
A tutorial, support newsgroup, references and links to further resources are provided there.
}

\seealso{\code{\link{ergm-terms}}, \code{\link{ergm-references}}}

\author{
Pavel N. Krivitsky \email{pavel@uow.edu.au}
}
\references{
Krivitsky PN (2012). Exponential-Family Random Graph Models for Valued Networks. \emph{Electronic Journal of Statistics}, 2012, 6, 1100-1128. \doi{doi:10.1214/12-EJS696}

Krivitsky PN and Butts CT (2012). Exponential-Family Random Graph Models for Rank-Order Relational Data. \url{http://arxiv.org/abs/1210.0493}


}
\keyword{ package }
\keyword{ models }
