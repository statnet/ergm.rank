/*  File src/wtchangestats_rank.h in package ergm.rank, part of the Statnet suite
 *  of packages for network analysis, https://statnet.org .
 *
 *  This software is distributed under the GPL-3 license.  It is free,
 *  open source, and has the attribution requirements (GPL Section 7) at
 *  https://statnet.org/attribution
 *
 *  Copyright 2008-2019 Statnet Commons
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

WtD_CHANGESTAT_FN(d_local_nonconformity); WtS_CHANGESTAT_FN(s_local_nonconformity);

WtD_CHANGESTAT_FN(d_nonconformity_decay); WtS_CHANGESTAT_FN(s_nonconformity_thresholds);

WtD_CHANGESTAT_FN(d_nonconformity_thresholds); WtS_CHANGESTAT_FN(s_nonconformity_thresholds);

#endif
