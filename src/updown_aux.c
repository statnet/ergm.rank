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

typedef Vertex Pair[2];

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



WtI_CHANGESTAT_FN(i__updown){
  double R[N_NODES][N_NODES];
  // Now, populate the sociomatrix.
  EXEC_THROUGH_NET_EDGES(t, h, e, w, {
      R[t][h] = w;
    });

  ALLOC_AUX_SOCIOMATRIX(Pair, udsm);
  for (Vertex t = 1; t <= N_NODES; t++) { // Initialisation of look-up look-down structure
    for (Vertex j = 1; j <= N_NODES; j++) {
      if (t == j || R[t][j] == 0) continue;

      double r_j = R[t][j];
      Vertex below = 0;
      Vertex above = 0;
      double min_above = INFINITY;
      double min_below = INFINITY;
      for (Vertex k = 1; k <= N_NODES; k++) {
        if (k == t || k == j || R[t][k] == 0) continue;

        else if (R[t][k] > r_j) {
          if (R[t][k] - r_j < min_below) { // New difference between R[t][k] and R[t][j] that's smaller but below
              min_below = R[t][k] - r_j;
              below = k;
          }
        }
        else if (R[t][k] < r_j) {
          if (r_j - R[t][k] < min_above) { // New difference between R[t][k] and R[t][j] that's smaller but above
            min_above = r_j - R[t][k];
            above = k;
          }
        }
      }
      udsm[t][j][0] = below;
      udsm[t][j][1] = above;
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