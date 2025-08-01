#ifndef _UPDOWN_AUX_H_
#define _UPDOWN_AUX_H_

typedef struct {
  Vertex up;
  Vertex down;
} Pair;

static inline bool rank_above(Vertex j, double r_j, Vertex k, double r_k) {
  return(r_j > r_k || (r_j == r_k && j > k));
}

#endif
