%  File inst/NEWS.Rd in package ergm.rank, part of the Statnet suite
%  of packages for network analysis, https://statnet.org .
%
%  This software is distributed under the GPL-3 license.  It is free,
%  open source, and has the attribution requirements (GPL Section 7) at
%  https://statnet.org/attribution
%
%  Copyright 2008-2019 Statnet Commons
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
\name{NEWS}
\title{NEWS file for the \code{\link[=ergm.rank-package]{ergm.rank}} package}
\encoding{UTF-8}

% When a release is forked, copy the sections to a new release and
% delete unused sections.
%% \section{Changes in version 3.1.1}{

  % \subsection{NEW FEATURES}{
  %   \itemize{
  %   }
  % }

  %% \subsection{OTHER USER-VISIBLE CHANGES}{
  %%   \itemize{
  %%   }
  %% }

  % \subsection{C-LEVEL FACILITIES}{
  %   \itemize{
  %     \item It is not clear that we need a subsection called "C-LEVEL FACILITIES".
  %   }
  % }

  % \subsection{UTILITIES}{
  %   \itemize{
  %     \item Likewise, "UTILITIES" is probably unnecessary.
  %   }
  % }

  % \subsection{INSTALLATION}{
  %   \itemize{
  %     \item ... as is "INSTALLATION".
  %   }
  % }

  % \subsection{PACKAGE INSTALLATION}{
  %   \itemize{
  %     \item ditto.
  %   }
  % }

  % \subsection{DEPRECATED & DEFUNCT}{
  %   \itemize{
  %   }
  % }

  % \subsection{BUG FIXES}{
  %   \itemize{
  %   }
  % }
%% }


\section{Changes in version 1.2.0}{

  \subsection{BUG FIXES}{
    \itemize{
      \item Updated for \code{\link[ergm:ergm-package]{ergm}} 3.10 API changes.
    }
  }
}





\section{Changes in version 1.1.0}{

  \subsection{NEW FEATURES}{
    \itemize{
      \item Package development has been migrated to GitHub.
    }
  }

  \subsection{OTHER USER-VISIBLE CHANGES}{
    \itemize{
      \item \code{statnet.common} is now Imported rather than Depended-on.
    }
  }

  \subsection{BUG FIXES}{
    \itemize{
      \item Updated for \code{\link[ergm:ergm-package]{ergm}} 3.9 API changes.

      \item Symbol registration added.
    }
  }
}


\section{Changes in version 1.0.0}{

  \subsection{NEW FEATURES}{
    \itemize{
      \item This is an initial public release.

      \item A number of reference measures and statistics for rank data have been
      implemented. See \code{? 'ergm.rank-package'} and \code{? 'ergm-references'} for help.
    }
  }
}
