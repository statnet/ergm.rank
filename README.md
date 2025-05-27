# `ergm.rank`: Fit, Simulate and Diagnose Exponential-Family Models for Rank-Order Relational Data

[![rstudio mirror downloads](https://cranlogs.r-pkg.org/badges/ergm.rank?color=2ED968)](https://cranlogs.r-pkg.org/)
[![cran version](https://www.r-pkg.org/badges/version/ergm.rank)](https://cran.r-project.org/package=ergm.rank)
[![Coverage status](https://codecov.io/gh/statnet/ergm.rank/branch/master/graph/badge.svg)](https://codecov.io/github/statnet/ergm.rank?branch=master)
[![R build status](https://github.com/statnet/ergm.rank/workflows/R-CMD-check/badge.svg)](https://github.com/statnet/ergm.rank/actions)

A set of extensions for the 'ergm' package to fit weighted networks whose edge weights are ranks. See Krivitsky and Butts (2017) <doi:10.1177/0081175017692623> and Krivitsky, Hunter, Morris, and Klumb (2023) <doi:10.18637/jss.v105.i06>.

## Public and Private repositories

To facilitate open development of the package while giving the core developers an opportunity to publish on their developments before opening them up for general use, this project comprises two repositories:
* A public repository `statnet/ergm.rank`
* A private repository `statnet/ergm.rank-private`

The intention is that all developments in `statnet/ergm.rank-private` will eventually make their way into `statnet/ergm.rank` and onto CRAN.

Developers and Contributing Users to the Statnet Project should read https://statnet.github.io/private/ for information about the relationship between the public and the private repository and the workflows involved.

## Latest Windows and MacOS binaries

A set of binaries is built after every commit to the repository. We strongly encourage testing against them before filing a bug report, as they may contain fixes that have not yet been sent to CRAN. They can be downloaded through the following links:

* [MacOS binary (a `.tgz` file in a `.zip` file)](https://nightly.link/statnet/ergm.rank/workflows/R-CMD-check.yaml/master/macOS-rrelease-binaries.zip)
* [Windows binary (a `.zip` file in a `.zip` file)](https://nightly.link/statnet/ergm.rank/workflows/R-CMD-check.yaml/master/Windows-rrelease-binaries.zip)

You will need to extract the MacOS `.tgz` or the Windows `.zip` file from the outer `.zip` file before installing. These binaries are usually built under the latest version of R and their operating system and may not work under other versions.

You may also want to install the corresponding latest binaries for packages on which `ergm.rank` depends, in particular [`network`](https://github.com/statnet/network), [`statnet.common`](https://github.com/statnet/statnet.common), and [`ergm`](https://github.com/statnet/ergm).
