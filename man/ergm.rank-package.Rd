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

Mainly, it implements Poisson, binomial, geometric, and discrete uniform
dyadwise reference measures for valued ERGMs (\link[=ergm-references]{documented here}), and provides some
count-specific change statistics (\link[=ergm-terms]{documented here}).

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
Pavel N. Krivitsky \email{krivitsky@uow.edu.au}
}
\references{
Handcock MS, Hunter DR, Butts CT, Goodreau SG, Krivitsky PN and Morris M
(2012). _Fit, Simulate and Diagnose Exponential-Family Models for
Networks_. Version 3.1.  Project home
page at <URL: http://www.statnet.org>, <URL:
CRAN.R-project.org/package=ergm>.

Krivitsky PN (2012). Exponential-Family Random Graph Models for Valued Networks. \emph{Electronic Journal of Statistics}, 2012, 6, 1100-1128. \href{http://dx.doi.org/10.1214/12-EJS696}{\code{doi:10.1214/12-EJS696}}

}
\keyword{ package }
\keyword{ models }
