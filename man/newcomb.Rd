%  File man/newcomb.Rd in package ergm.rank, part of the Statnet suite
%  of packages for network analysis, http://statnet.org .
%
%  This software is distributed under the GPL-3 license.  It is free,
%  open source, and has the attribution requirements (GPL Section 7) at
%  http://statnet.org/attribution
%
%  Copyright 2008-2018 Statnet Commons
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{newcomb}
\title{Newcomb's Fraternity Networks}
\alias{newcomb}
\description{
These 14 networks record weekly sociometric preference rankings
from 17 men attending the University of Michigan in the fall
of 1956; Data were collected longitudinally over 15 weeks,
although data from week 9 are missing.

The men were recruited to live in off-campus (fraternity)
housing, rented for them as part of the Michigan Group Study
Project supervised by Theodore Newcomb from 1953 to 1956. All
were incoming transfer students with no prior acquaintance of
one another.

The data set, derived from one in the unreleased \code{netdata} package,
contains a network list \code{newcomb} with 14 networks. Each network is
complete and contains two edge attributes:
\describe{
  \item{\code{rank}}{the preference of the \eqn{i}th man for the \eqn{j}th
man from \code{1} through \code{16}, with \code{1} being the highest preference.}
  \item{\code{descrank}}{the same, but \code{1} indicates
    lowest preference.}
}
}
\usage{data(newcomb)}
\source{\url{http://vlado.fmf.uni-lj.si/pub/networks/data/ucinet/ucidata.htm#newfrat}}
\references{See the link above. 
Newcomb T. (1961). The acquaintance process. New York: Holt, Reinhard
and Winston.

Nordlie P. (1958). A longitudinal study of interpersonal attraction in a
natural group setting. Unpublished doctoral dissertation, University of
Michigan.

White H., Boorman S. and Breiger R. (1977). Social structure from multiple networks, I. Blockmodels of roles and positions. American Journal of Sociology, 81, 730-780. 
}
\keyword{datasets}
\section{Licenses and Citation}{
If the source of the data set does not specified otherwise,
this data set is protected by the Creative Commons License
\url{http://creativecommons.org/licenses/by-nc-nd/2.5/}.

When publishing results obtained using this data set the original authors
should be cited.  In addition this should be cited as:

Mark S. Handcock, David Hunter, Carter T. Butts, Steven M. Goodreau,
and Martina Morris. 2003 
\emph{statnet: An R package for the Statistical Modeling of Social Networks}
\cr
\url{http://www.statnet.org}
and the source should be cited as:

Vladimir Batagelj and Andrej Mrvar (2006): \emph{Pajek datasets}
\cr
\url{http://vlado.fmf.uni-lj.si/pub/networks/data/} 
}

\examples{
\donttest{
# Note: This takes a long time.
data(newcomb)

# Fit a model for the transition between initial (time 0) ranking and
# ranking after one week (time 1). Note that MCMC interval has been
# decreased to save time.
newcomb.1.2.fit <- ergm(newcomb[[2]]~
                        rank.inconsistency(newcomb[[1]],"descrank")+
                        rank.deference+rank.nonconformity("all")+
                        rank.nonconformity("localAND"),
                        response="descrank", reference=~CompleteOrder,
                        control=control.ergm(MCMLE.trustregion=10000,
                                             MCMC.interval=10))
# Check MCMC diagnostics (barely adequate).
mcmc.diagnostics(newcomb.1.2.fit)
summary(newcomb.1.2.fit)
}
}