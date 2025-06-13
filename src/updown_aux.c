/*  File src/wtchangestats_test.c in package ergm, part of the
 *  Statnet suite of packages for network analysis, https://statnet.org .
 *
 *  This software is distributed under the GPL-3 license.  It is free,
 *  open source, and has the attribution requirements (GPL Section 7) at
 *  https://statnet.org/attribution .
 *
 *  Copyright 2003-2025 Statnet Commons
 */
#include "ergm_wtedgetree.h"
#include "ergm_wtchangestat.h"
#include "ergm_storage.h"
#include <math.h>

typedef struct {
  Vertex up;
  Vertex down;
} Pair;

/*WtC_CHANGESTAT_FN(c_test_abs_sum_minus_5){
  GET_STORAGE(double, stored_sum_ptr);
  double sum = *stored_sum_ptr;
    CHANGE_STAT[0] = -fabs(sum-5);
    CHANGE_STAT[0] += fabs(sum-5 + weight - edgestate);
}

WtI_CHANGESTAT_FN(i_test_abs_sum_minus_5){
  ALLOC_STORAGE(1, double, sum);
  *sum = 0;
  EXEC_THROUGH_NET_EDGES(tail, e1, head, y, {
      *sum+=y;
      head=head; e1=e1; // Prevent a compiler warning.
    });
}

WtU_CHANGESTAT_FN(u_test_abs_sum_minus_5){
  GET_STORAGE(double, sum);
  *sum += weight-edgestate;
}

WtS_CHANGESTAT_FN(s_test_abs_sum_minus_5){
  GET_STORAGE(double, sum);
  // Storage uninitialized: compute from scratch.
  if(!sum){
    double sum = 0;
    EXEC_THROUGH_NET_EDGES(tail, e1, head, y, {
	sum+=y;
	head=head; e1=e1; // Prevent a compiler warning.
      });
    CHANGE_STAT[0] = fabs(sum-5);
  }else{ // Storage initialized: use it.
    CHANGE_STAT[0] = fabs(*sum-5);
  }
}

WtC_CHANGESTAT_FN(c_test_abs_sum_minus_5_no_s){c_test_abs_sum_minus_5(tail, head, weight, mtp, nwp, edgestate);}
WtI_CHANGESTAT_FN(i_test_abs_sum_minus_5_no_s){i_test_abs_sum_minus_5(mtp, nwp);}
WtU_CHANGESTAT_FN(u_test_abs_sum_minus_5_no_s){u_test_abs_sum_minus_5(tail, head, weight, mtp, nwp, edgestate);}*/

static inline Rboolean rank_above(Vertex j, double r_j, Vertex k, double r_k) {
  return(r_j>r_k || (r_j == r_k && j > k));
} 

WtI_CHANGESTAT_FN(i__updown){
  GET_AUX_STORAGE(1, double *, R);

  ALLOC_AUX_SOCIOMATRIX(Pair, udsm);
  for (Vertex t = 1; t <= N_NODES; t++) { // Initialisation of look-up look-down structure
    for (Vertex j = 1; j <= N_NODES; j++) {
      if (t == j) continue;

      double r_j = R[t][j];
      Vertex below = 0;
      Vertex above = 0;
      for (Vertex k = 1; k <= N_NODES; k++) {
        if (k == t || k == j) continue;

        double r_k = R[t][k];

        if (below == 0 && rank_above(j, r_j, k, r_k)) {below = k; continue;} // Take first below
        if (above == 0 && rank_above(k, r_k, j, r_j)) {above = k; continue;} // Take first above

        if (rank_above(j, r_j, k, r_k)) {
          if (rank_above(k, r_k, below, R[t][below])) below = k; // This k is 'closer' from below
        }
        if (rank_above(k, r_k, j, r_j)) {
          if (rank_above(above, R[t][above], k, r_k)) above = k; // This k is 'closer' from above
        }
      }
      udsm[t][j].down = below;
      udsm[t][j].up = above;
    }
  }
}

WtU_CHANGESTAT_FN(u__updown){
  GET_AUX_STORAGE(Pair, udsm);
}

WtF_CHANGESTAT_FN(f__updown){
  FREE_AUX_SOCIOMATRIX;
}

/*
WtC_CHANGESTAT_FN(c_dsociomatrix){
  GET_AUX_STORAGE(double *, sm);
  
      Dyad pos = tail-1 + (head-1)*N_NODES;
      CHANGE_STAT[pos] = weight - sm[tail][head];
}


WtI_CHANGESTAT_FN(i__sum){
  ALLOC_AUX_STORAGE(1, double, sum);
  *sum = 0;
  EXEC_THROUGH_NET_EDGES(tail, e1, head, y, {
      *sum+=y;
      (void) head; (void) e1; // Prevent a compiler warning.
    });
}

WtU_CHANGESTAT_FN(u__sum){
  GET_AUX_STORAGE(double, sum);
  *sum += weight-edgestate;
}

WtC_CHANGESTAT_FN(c_test_abs_sum_minus_5_aux){
  GET_AUX_STORAGE(double, stored_sum_ptr);
  double sum = *stored_sum_ptr;
    CHANGE_STAT[0] = -fabs(sum-5);
    CHANGE_STAT[0] += fabs(sum-5 + weight - edgestate);
}*/