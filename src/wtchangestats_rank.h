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

WtC_CHANGESTAT_FN(c_edgecov_rank); WtS_CHANGESTAT_FN(s_edgecov_rank);

WtC_CHANGESTAT_FN(c_inconsistency_rank); WtS_CHANGESTAT_FN(s_inconsistency_rank);

WtC_CHANGESTAT_FN(c_inconsistency_cov_rank); WtS_CHANGESTAT_FN(s_inconsistency_cov_rank);

WtC_CHANGESTAT_FN(c_deference); WtS_CHANGESTAT_FN(s_deference);

WtC_CHANGESTAT_FN(c_nodeicov_rank); WtS_CHANGESTAT_FN(s_nodeicov_rank);

WtC_CHANGESTAT_FN(c_nonconformity); WtS_CHANGESTAT_FN(s_nonconformity);

WtC_CHANGESTAT_FN(c_local_nonconformity); WtS_CHANGESTAT_FN(s_local_nonconformity);

WtC_CHANGESTAT_FN(c_nonconformity_decay); WtS_CHANGESTAT_FN(s_nonconformity_thresholds);

WtC_CHANGESTAT_FN(c_nonconformity_thresholds); WtS_CHANGESTAT_FN(s_nonconformity_thresholds);

WtC_CHANGESTAT_FN(c_tiedranks); WtS_CHANGESTAT_FN(s_tiedranks);

WtC_CHANGESTAT_FN(c_rank_classes); WtS_CHANGESTAT_FN(s_rank_classes);

#endif
