/*  File src/wtchangestats_rank.h in package ergm.rank, part of the Statnet suite
 *  of packages for network analysis, http://statnet.org .
 *
 *  This software is distributed under the GPL-3 license.  It is free,
 *  open source, and has the attribution requirements (GPL Section 7) at
 *  http://statnet.org/attribution
 *
 *  Copyright 2008-2016 Statnet Commons
 */
#ifndef WTCHANGESTATS_RANK_H
#define WTCHANGESTATS_RANK_H

#include "wtchangestat_rank.h"

WtD_CHANGESTAT_FN(d_edgecov_rank); WtS_CHANGESTAT_FN(s_edgecov_rank);

WtD_CHANGESTAT_FN(d_inconsistency_rank); WtS_CHANGESTAT_FN(s_inconsistency_rank);

WtD_CHANGESTAT_FN(d_inconsistency_cov_rank); WtS_CHANGESTAT_FN(s_inconsistency_cov_rank);

WtD_CHANGESTAT_FN(d_deference); WtS_CHANGESTAT_FN(s_deference);

WtD_CHANGESTAT_FN(d_nodeicov_rank); WtS_CHANGESTAT_FN(s_nodeicov_rank);

WtD_CHANGESTAT_FN(d_nonconformity); WtS_CHANGESTAT_FN(s_nonconformity);

WtD_CHANGESTAT_FN(d_local1_nonconformity); WtS_CHANGESTAT_FN(s_local1_nonconformity);

WtD_CHANGESTAT_FN(d_local2_nonconformity); WtS_CHANGESTAT_FN(s_local2_nonconformity);

WtD_CHANGESTAT_FN(d_localAND_nonconformity); WtS_CHANGESTAT_FN(s_localAND_nonconformity);

#endif
