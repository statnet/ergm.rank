#ifndef _WTCHANGESTATS_RANK_AUX_H_
#define _WTCHANGESTATS_RANK_AUX_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  Vertex up;
  Vertex down;
} Pair;

#define rank_above(j, r_j, k, r_k) ((r_j) > (r_k) || ((r_j) == (r_k) && (j) > (k)))

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

// Iterator for up/down traversal
class UpDownIterator {
public:
  UpDownIterator(Vertex v1, Vertex v2, double **sm, Pair **udsm, double v12_old, double v12_new, bool end = false)
    : v1_(v1), v2_(v2), sm_(sm), udsm_(udsm), v12_old_(v12_old), v12_new_(v12_new), up_(v12_new > v12_old) {
    if(end) {
      v3_ = 0;
      return;
    }
    v3_ = v2_;
    if(up_) {
      while (udsm_[v1_][v3_].down && sm_[v1_][udsm_[v1_][v3_].down] == v12_old_) {
        v3_ = udsm_[v1_][v3_].down;
      }
      advance_to_valid_up();
    } else {
      while (udsm_[v1_][v3_].up && sm_[v1_][udsm_[v1_][v3_].up] == v12_old_) {
        v3_ = udsm_[v1_][v3_].up;
      }
      advance_to_valid_down();
    }
  }
  Vertex operator*() const { return v3_; }
  UpDownIterator& operator++() {
    if(up_) {
      v3_ = udsm_[v1_][v3_].up;
      advance_to_valid_up();
    } else {
      v3_ = udsm_[v1_][v3_].down;
      advance_to_valid_down();
    }
    return *this;
  }
  bool operator!=(const UpDownIterator& other) const { return v3_ != other.v3_; }
private:
  // These iterate in their respective direction until one of three
  // things:
  //
  // 1. We run off the end of the list (v3_ == 0).
  // 2. We pass v12_new.
  // 3. We reach an alter distinct from v2_.
  //
  // In case of 3, iteration continues. Otherwise, it must terminate.
  void advance_to_valid_up() {
    bool more = true;
    while (v3_ && (more = sm_[v1_][v3_] <= v12_new_) && v3_ == v2_) {
      v3_ = udsm_[v1_][v3_].up;
    }
    if (!more) v3_ = 0;
  }
  void advance_to_valid_down() {
    bool more = true;
    while (v3_ && (more = sm_[v1_][v3_] >= v12_new_) && v3_ == v2_) {
      v3_ = udsm_[v1_][v3_].down;
    }
    if (!more) v3_ = 0;
  }
  Vertex v1_, v2_, v3_;
  double **sm_;
  Pair **udsm_;
  double v12_old_, v12_new_;
  bool up_;
};

class UpDownRange {
public:
  UpDownRange(Vertex v1, Vertex v2, double **sm, Pair **udsm, double v12_old, double v12_new)
    : v1_(v1), v2_(v2), sm_(sm), udsm_(udsm), v12_old_(v12_old), v12_new_(v12_new) {}
  UpDownIterator begin() const { return UpDownIterator(v1_, v2_, sm_, udsm_, v12_old_, v12_new_, false); }
  UpDownIterator end() const { return UpDownIterator(v1_, v2_, sm_, udsm_, v12_old_, v12_new_, true); }
private:
  Vertex v1_, v2_;
  double **sm_;
  Pair **udsm_;
  double v12_old_, v12_new_;
};

#endif // _cplusplus

#endif // _WTCHANGESTATS_RANK_AUX_H_
