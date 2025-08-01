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
#include "updown_aux.h"

// C++ shim?

WtI_CHANGESTAT_FN(i__updown){
  ALLOC_AUX_SOCIOMATRIX(Pair, udsm);
  GET_AUX_STORAGE(1, double *, R);
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

#define sm(i, j) (((i) == tail && (j) == head) ? weight : R[(i)][(j)])

WtU_CHANGESTAT_FN(u__updown){ // Recalculate look-up look-down when something changes
  GET_AUX_STORAGE(0, Pair *, udsm);
  GET_AUX_STORAGE(1, double *, sm);
  Vertex v1=tail;
  Vertex v2=head;
  double v12_old = sm[tail][head];
  double v12_new = weight;

  // Find where v2 is currently located in udsm[v1]
  Vertex old_up = udsm[v1][v2].up;
  Vertex old_down = udsm[v1][v2].down;

  // Remove v2 from its old position in udsm[v1]
  // Update the up and down pointers of the neighbors
  if (old_down != 0) {
    if (udsm[v1][old_down].up == v2) udsm[v1][old_down].up = old_up;
  }
  if (old_up != 0) {
    if (udsm[v1][old_up].down == v2) udsm[v1][old_up].down = old_down;
  }
  udsm[v1][v2].up = 0;
  udsm[v1][v2].down = 0;

  // Insert v2 with new value v12_new into udsm[v1]
  Vertex insert_above = 0, insert_below = 0;
  for (Vertex v3 = 1; v3 <= N_NODES; v3++) {
    if (v3 == v1 || v3 == v2) continue;
    double v13_old = sm[v1][v3];
    if (rank_above(v2, v12_new, v3, v13_old)) { // v2 above v3
      if (insert_below == 0 || rank_above(v3, v13_old, insert_below, sm[v1][insert_below])) insert_below = v3; // new below
    }
    if (rank_above(v3, v13_old, v2, v12_new)) { // v2 below v3
      if (insert_above == 0 || rank_above(insert_above, sm[v1][insert_above], v3, v13_old)) insert_above = v3; // new above
    }
  }
  udsm[v1][v2].down = insert_below;
  udsm[v1][v2].up = insert_above;
  if (insert_below != 0) udsm[v1][insert_below].up = v2;
  if (insert_above != 0) udsm[v1][insert_above].down = v2;
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
