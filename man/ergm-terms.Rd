%  File man/ergm-terms.Rd in package ergm.rank, part of the Statnet suite
%  of packages for network analysis, https://statnet.org .
%
%  This software is distributed under the GPL-3 license.  It is free,
%  open source, and has the attribution requirements (GPL Section 7) at
%  https://statnet.org/attribution
%
%  Copyright 2008-2019 Statnet Commons
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{ergm-terms}
\alias{ergm-terms}
\alias{ergm.terms}
\alias{terms-ergm}
\alias{terms.ergm}
\alias{rank.deference}
\alias{rank.edgecov}
\alias{rank.inconsistency}
\alias{rank.nodeicov}
\alias{rank.nonconformity}
\alias{InitWtErgmTerm.rank.deference}
\alias{InitWtErgmTerm.rank.edgecov}
\alias{InitWtErgmTerm.rank.inconsistency}
\alias{InitWtErgmTerm.rank.nodeicov}
\alias{InitWtErgmTerm.rank.nonconformity}
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
  
  \describe{
    
    \item{\code{rank.deference}}{\emph{Deference (aversion):} Measures the
      amount of ``deference'' in the network: configurations where an ego
      \eqn{i} ranks an alter \eqn{j} over another alter \eqn{k}, but
      \eqn{j}, in turn, ranks \eqn{k} over \eqn{i}. A lower-than-chance
      value of this statistic and/or a negative coefficient implies a form
      of mutuality in the network.  
    }

    \item{\code{rank.edgecov(x, attrname)}}{\emph{Dyadic covariates:}
      Models the effect of a dyadic covariate on the propensity of an ego
      \eqn{i} to rank alter \eqn{j} highly. See the
      \code{\link[ergm]{edgecov}} ERGM term documentation for arguments.
    }

    \item{\code{rank.inconsistency(x, attrname, weights, wtname,
      wtcenter)}}{\emph{(Weighted) Inconsistency:}
      Measures the amount of disagreement between rankings of the focus
      network and a fixed covariate network \code{x}, by couting the number of pairwise
      comparisons for which the two networks disagree. \code{x} can be a \code{\link{network}} with an edge
      attribute \code{attrname} containing the ranks or a matrix of
      appropriate dimension containing the ranks. If \code{x} is not
      given, it defaults to the LHS network, and if \code{attrname} is
      not given, it defaults to the \code{response} edge attribute.

      Optionally, the count can be weighted by the \code{weights}
      argument, which can be either a 3D \eqn{n\times n\times n}-array
      whose \eqn{(i,j,k)}th element gives the weight for the
      comparison by \eqn{i} of \eqn{j} and \eqn{k} or a function taking
      three arguments,  \eqn{i}, \eqn{j}, and \eqn{k}, and returning
      the weight of this comparison. If \code{wtcenter=TRUE}, the
      calculated weights will be centered around their
      mean. \code{wtname} can be used to label this term.
    }

    \item{\code{rank.nodeicov(attrname, transform, transformname)}}{\emph{Attractiveness/Popularity covariates:}
      Models the effect of a nodal covariate on the propensity of an
      actor to be ranked highly by the others. See the
      \code{\link[ergm]{nodeicov}} ERGM term documentation for arguments.
    }

    \item{\code{rank.nonconformity(to, par)}}{\emph{Nonconformity:}
      Measures the amount of ``nonconformity'' in the network: configurations where an ego
      \eqn{i} ranks an alter \eqn{j} over another alter \eqn{k}, but
      ego \eqn{l} ranks \eqn{k} over \eqn{j}.

      This statistic has an argument \code{to}, which controls
      to whom an ego may conform:
      \describe{
	\item{\code{"all"} (the default)}{Nonconformity to all
	  egos is counted.       A lower-than-chance
	  value of this statistic and/or a negative coefficient implies a
	  degree
	  of consensus in the network.}
	\item{\code{"localAND"}}{
	  Nonconformity of \eqn{i} to ego \eqn{l} regarding the relative ranking
	  of \eqn{j} and \eqn{k} is only counted if \eqn{i} ranks \eqn{l}
	  over both \eqn{j} and \eqn{k}. A lower-than-chance
	  value of this statistic and/or a negative coefficient implies a
	  form of hierarchical transitivity in the network. This is the
	  recommended form of local nonconformity (over \code{"local1"}
	  and \code{"local2"}).}
	\item{\code{"local1"}}{
	  Nonconformity of \eqn{i} to ego \eqn{l} regarding the relative ranking
	  of \eqn{j} and \eqn{k} is only counted if \eqn{i} ranks \eqn{l}
	  over \eqn{j}.}
	\item{\code{"local2"}}{
	  Nonconformity of \eqn{i} to ego \eqn{l} regarding the relative ranking
	  of \eqn{j} and \eqn{k} is only counted if \eqn{i} ranks \eqn{l}
	  over \eqn{k}.}
      }
    }  
  }
}
\references{
  \itemize{
    \item Handcock M. S., Hunter D. R., Butts C. T., Goodreau S. G.,
      Krivitsky P. N. and Morris M.
(2012). _Fit, Simulate and Diagnose Exponential-Family Models for
Networks_. Version 3.1.  Project home
page at <URL: http://www.statnet.org>, <URL:
CRAN.R-project.org/package=ergm>.
  
\item Krivitsky P. N. (2012). Exponential-Family Random Graph Models for
Valued Networks. \emph{Electronic Journal of Statistics}, 2012, 6,
1100-1128. \doi{doi:10.1214/12-EJS696}

\item Krivitsky PN and Butts CT (2012). Exponential-Family Random Graph Models for Rank-Order Relational Data. \url{http://arxiv.org/abs/1210.0493}


}
}
\seealso{\code{\link[ergm:ergm-terms]{ergm-terms}} (from the \code{\link[=ergm-package]{ergm}} package), \code{\link{ergm}}, \code{\link{network}}, \code{\link{\%v\%}}, \code{\link{\%n\%}}}
\keyword{models}
