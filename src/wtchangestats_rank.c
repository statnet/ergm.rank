/*  File src/wtchangestats_rank.c in package ergm.rank, part of the
 *  Statnet suite of packages for network analysis, https://statnet.org .
 *
 *  This software is distributed under the GPL-3 license.  It is free,
 *  open source, and has the attribution requirements (GPL Section 7) at
 *  https://statnet.org/attribution .
 *
 *  Copyright 2008-2024 Statnet Commons
 */

#include "wtchangestat_rank.h"

WtC_CHANGESTAT_FN(c_edgecov_rank){
  GET_AUX_STORAGE(double *, sm);
      Vertex v1=tail;
      Vertex v2=head;
      double v12_old = sm[tail][head];
      double v12_new = weight;
      for (Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v123_covdiff=INPUT_PARAM[(v1-1)*N_NODES + (v2-1)] - INPUT_PARAM[(v1-1)*N_NODES + (v3-1)];
	if(v123_covdiff==0) continue; // If covariate value is 0, don't bother looking up the ranking of v3 by v1.
	double v13_old=sm[v1][v3];
	if(v12_old>v13_old)
	  CHANGE_STAT[0] -= v123_covdiff;
	if(v12_old<v13_old)
	  CHANGE_STAT[0] += v123_covdiff;
	if(v12_new>v13_old)
	  CHANGE_STAT[0] += v123_covdiff;
	if(v12_new<v13_old)
	  CHANGE_STAT[0] -= v123_covdiff;
      }
} 

WtS_CHANGESTAT_FN(s_edgecov_rank){
  GET_AUX_STORAGE(double *, sm);
  for (Vertex v1=1; v1 <= N_NODES; v1++){
    for (Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12=sm[v1][v2];
      for (Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v123_covdiff = INPUT_PARAM[(v1-1)*N_NODES + (v2-1)] - INPUT_PARAM[(v1-1)*N_NODES + (v3-1)];
	if(v123_covdiff!=0 && v12>sm[v1][v3]) // Short-circuit the lookup of ranking of v3 by v1 if covariate is 0.
	  CHANGE_STAT[0] += v123_covdiff;
      }
    }
  }
}


WtC_CHANGESTAT_FN(c_inconsistency_rank){
  GET_AUX_STORAGE(double *, sm);
      Vertex v1=tail;
      Vertex v2=head;
      double v12_old = sm[tail][head];
      double v12_ref = INPUT_PARAM[(v1-1)*N_NODES+(v2-1)];
      double v12_new = weight;
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v13= sm[v1][v3];
	double v13_ref=INPUT_PARAM[(v1-1)*N_NODES+(v3-1)];
	if((v12_old>v13)!=(v12_ref>v13_ref)) CHANGE_STAT[0]--;
	if((v12_new>v13)!=(v12_ref>v13_ref)) CHANGE_STAT[0]++;
	if((v13>v12_old)!=(v13_ref>v12_ref)) CHANGE_STAT[0]--;
	if((v13>v12_new)!=(v13_ref>v12_ref)) CHANGE_STAT[0]++;
      }
}

WtS_CHANGESTAT_FN(s_inconsistency_rank){ 
  GET_AUX_STORAGE(double *, sm);
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12 = sm[v1][v2], v12_ref = INPUT_PARAM[(v1-1)*N_NODES+(v2-1)];
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	unsigned int 
	  v123 = v12>sm[v1][v3],
	  v123_ref = v12_ref>INPUT_PARAM[(v1-1)*N_NODES+(v3-1)];
	if(v123!=v123_ref) CHANGE_STAT[0]++;
      }
    }
  }
}

WtC_CHANGESTAT_FN(c_inconsistency_cov_rank){
  GET_AUX_STORAGE(double *, sm);
      unsigned int cov_start = N_NODES*N_NODES;
      Vertex v1=tail;
      Vertex v2=head;
      double v12_ref = INPUT_PARAM[(v1-1)*N_NODES+(v2-1)];
      double v12_old = sm[tail][head];
      double v12_new = weight;
      
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v123_cov = INPUT_PARAM[cov_start + (v1-1)*N_NODES*N_NODES + (v2-1)*N_NODES + (v3-1)];
	double v132_cov = INPUT_PARAM[cov_start + (v1-1)*N_NODES*N_NODES + (v3-1)*N_NODES + (v2-1)];
	if(v123_cov!=0 || v123_cov!=0){
	  double v13=sm[v1][v3];
	  double v13_ref=INPUT_PARAM[(v1-1)*N_NODES+(v3-1)];

	  if(v123_cov!=0){
	    if((v12_old>v13)!=(v12_ref>v13_ref)) CHANGE_STAT[0]-=v123_cov;
	    if((v12_new>v13)!=(v12_ref>v13_ref)) CHANGE_STAT[0]+=v123_cov;
	  }

	  if(v132_cov!=0){
	    if((v13>v12_old)!=(v13_ref>v12_ref)) CHANGE_STAT[0]-=v132_cov;
	    if((v13>v12_new)!=(v13_ref>v12_ref)) CHANGE_STAT[0]+=v132_cov;
	  }
	}
      }
}

WtS_CHANGESTAT_FN(s_inconsistency_cov_rank){ 
  GET_AUX_STORAGE(double *, sm);
  unsigned int cov_start = N_NODES*N_NODES;
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12 = sm[v1][v2], v12_ref = INPUT_PARAM[(v1-1)*N_NODES+(v2-1)];
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v123_cov = INPUT_PARAM[cov_start + (v1-1)*N_NODES*N_NODES + (v2-1)*N_NODES + (v3-1)];
	if(v123_cov==0) continue;
	unsigned int 
	  v123 = v12>sm[v1][v3],
	  v123_ref = v12_ref>INPUT_PARAM[(v1-1)*N_NODES+(v3-1)];
	if(v123!=v123_ref) 
	  CHANGE_STAT[0]+=v123_cov;
      }
    }
  }
}

WtC_CHANGESTAT_FN(c_deference){
  GET_AUX_STORAGE(double *, sm);
      for(Vertex v1=1; v1 <= N_NODES; v1++){
	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v1) continue;
	  double v31_old = sm[v3][v1];
	  double v13_old = sm[v1][v3];
	  double v31_new = GETNEWWTOLD_M(v3,v1,v31_old);
	  double v13_new = GETNEWWTOLD_M(v1,v3,v13_old);

	  for(Vertex v2=1; v2 <= N_NODES; v2++){
	    if(v2==v1 || v3==v2 || 
	       (tail!=v1 && tail!=v3 && 
		head!=v1 && head!=v2 && head!=v3)) continue;
	    double v32_old = sm[v3][v2];
	    double v12_old = sm[v1][v2];
	    double v32_new = GETNEWWTOLD_M(v3,v2,v32_old);
	    double v12_new = GETNEWWTOLD_M(v1,v2,v12_old);
	    if(v32_old>v31_old && v13_old>v12_old) 
	      CHANGE_STAT[0]--;
	    if(v32_new>v31_new && v13_new>v12_new) 
	      CHANGE_STAT[0]++;
	  }
	}
      }
}

WtS_CHANGESTAT_FN(s_deference){ 
  GET_AUX_STORAGE(double *, sm);
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v3=1; v3 <= N_NODES; v3++){
      if(v3==v1) continue;
      double v31 = sm[v3][v1], v13 = sm[v1][v3];
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1 || v3==v2) continue;
	if(sm[v3][v2]>v31 && v13>sm[v1][v2]) 
	  CHANGE_STAT[0]++;
      }
    }
  }
}

WtC_CHANGESTAT_FN(c_nodeicov_rank){
  unsigned int oshift = N_INPUT_PARAMS / N_CHANGE_STATS;
  GET_AUX_STORAGE(double *, sm);
      Vertex v1=tail;
      Vertex v2=head;
      double v12_old = sm[tail][head];
      double v12_new = weight;
      for (Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v13_old=sm[v1][v3];
	for(unsigned int j=0, o=0; j<N_CHANGE_STATS; j++, o+=oshift){
	  double v23_covdiff = INPUT_PARAM[v2+o-1] - INPUT_PARAM[v3+o-1];
	  if(v12_old>v13_old)
	    CHANGE_STAT[j] -= v23_covdiff;
	  if(v12_old<v13_old)
	    CHANGE_STAT[j] += v23_covdiff;
	  if(v12_new>v13_old)
	    CHANGE_STAT[j] += v23_covdiff;
	  if(v12_new<v13_old)
	    CHANGE_STAT[j] -= v23_covdiff;
	}
      }
} 

WtS_CHANGESTAT_FN(s_nodeicov_rank){ 
  unsigned int oshift = N_INPUT_PARAMS / N_CHANGE_STATS;
  GET_AUX_STORAGE(double *, sm);
  for (Vertex v1=1; v1 <= N_NODES; v1++){
    for (Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12=sm[v1][v2];
      for (Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	if(v12>sm[v1][v3]){
	  for(unsigned int j=0, o=0; j<N_CHANGE_STATS; j++, o+=oshift){
	    CHANGE_STAT[j] += INPUT_PARAM[v2+o-1] - INPUT_PARAM[v3+o-1];
	  }
	}
      }
    }
  }
}

WtC_CHANGESTAT_FN(c_nonconformity){
  GET_AUX_STORAGE(double *, sm);
      Vertex v1=tail;
      
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	
	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1) continue;
	  
	  double v13_old=sm[v1][v3];
	  double v23=sm[v2][v3];
	  double v13_new = GETNEWWTOLD_M(v1,v3,v13_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 || 
	       (head!=v3 && head!=v4)) continue;
	    
	    double v14_old=sm[v1][v4];
	    double v24=sm[v2][v4];
	    double v14_new = GETNEWWTOLD_M(v1,v4,v14_old);
	    
	    if((v13_old>v14_old)!=(v23>v24)) CHANGE_STAT[0]--;
	    if((v13_new>v14_new)!=(v23>v24)) CHANGE_STAT[0]++;
	  }
	}
      }
}

WtS_CHANGESTAT_FN(s_nonconformity){ 
  GET_AUX_STORAGE(double *, sm);
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 < v1; v2++){
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v13=sm[v1][v3], v23=sm[v2][v3];
	for(Vertex v4=1; v4 <= N_NODES; v4++){
	  if(v4==v3 || v4==v2 || v4==v1) continue;
	  unsigned int
	    v134 = v13>sm[v1][v4],
	    v234 = v23>sm[v2][v4];
	  if(v134!=v234) CHANGE_STAT[0]++;
	}
      }
    }
  }
}

// From Krivitsky and Butts paper, here, v1=i, v2=j, v3=l, v4=k.
WtC_CHANGESTAT_FN(c_local1_nonconformity){
  GET_AUX_STORAGE(double *, sm);
      Vertex v1=tail;
      
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	double v12_old=sm[v1][v2];
	double v12_new=GETNEWWTOLD_M(v1,v2,v12_old);

	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1) continue;
	  double v13_old=sm[v1][v3];
	  double v13_new=GETNEWWTOLD_M(v1,v3,v13_old);

	  if(v13_old<=v12_old && v13_new<=v12_new) continue;

	  double v32_old=sm[v3][v2];
	  double v32_new=GETNEWWTOLD_M(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (head!=v4 && head!=v3 && head!=v2)) continue;

	    double v14_old=sm[v1][v4];
	    double v14_new=GETNEWWTOLD_M(v1,v4,v14_old);
	  
	    double v34_old=sm[v3][v4];
	    double v34_new=GETNEWWTOLD_M(v3,v4,v34_old);
	    
	    if(v13_old>v12_old && v12_old<=v14_old && v32_old>v34_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v12_new<=v14_new && v32_new>v34_new) CHANGE_STAT[0]++;
	  }
	}
      }

      Vertex v3=tail;
      
      for(Vertex v1=1; v1 <= N_NODES; v1++){
	if(v1==v3) continue;
	double v13_old=sm[v1][v3];
	double v13_new=GETNEWWTOLD_M(v1,v3,v13_old);
	
	for(Vertex v2=1; v2 <= N_NODES; v2++){
	  if(v2==v3 || v2==v1) continue;
	    double v12_old=sm[v1][v2];
	    double v12_new=GETNEWWTOLD_M(v1,v2,v12_old);
	    
	    if(v13_old<=v12_old && v13_new<=v12_new) continue;
	    
	    double v32_old=sm[v3][v2];
	    double v32_new=GETNEWWTOLD_M(v3,v2,v32_old);
	    
	    for(Vertex v4=1; v4 <= N_NODES; v4++){
	      if(v4==v3 || v4==v2 || v4==v1 ||
		 (head!=v4 && head!=v2 && head!=v1)) continue;
	      
	      double v14_old=sm[v1][v4];
	      double v14_new=GETNEWWTOLD_M(v1,v4,v14_old);
	      
	      double v34_old=sm[v3][v4];
	      double v34_new=GETNEWWTOLD_M(v3,v4,v34_old);
	    
	      if(v13_old>v12_old && v12_old<=v14_old && v32_old>v34_old) CHANGE_STAT[0]--;
	      if(v13_new>v12_new && v12_new<=v14_new && v32_new>v34_new) CHANGE_STAT[0]++;
	    }
	}
      }
}


// From Krivitsky and Butts paper, here, v1=i, v2=j, v3=l, v4=k.
WtS_CHANGESTAT_FN(s_local1_nonconformity){ 
  GET_AUX_STORAGE(double *, sm);
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12=sm[v1][v2];
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v13=sm[v1][v3];
	if(v13<=v12) continue;	
	double v32=sm[v3][v2];
	for(Vertex v4=1; v4 <= N_NODES; v4++){
	  if(v4==v3 || v4==v2 || v2==v1) continue;
	  double v14=sm[v1][v4];
	  double v34=sm[v3][v4];
	  if(v32>v34 && v12<=v14) CHANGE_STAT[0]++;
	}
      }
    }
  }
}


WtC_CHANGESTAT_FN(c_local2_nonconformity){
  GET_AUX_STORAGE(double *, sm);
      Vertex v1=tail;
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	double v12_old=sm[v1][v2];
	double v12_new=GETNEWWTOLD_M(v1,v2,v12_old);
	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1) continue;
	  double v13_old=sm[v1][v3];
	  double v13_new=GETNEWWTOLD_M(v1,v3,v13_old);
	  
	  if(v13_old<=v12_old && v13_new<=v12_new) continue;
	  
	  double v32_old=sm[v3][v2];
	  double v32_new=GETNEWWTOLD_M(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (head!=v2 && head!=v3 && head!=v4)) continue;
	    double v14_old=sm[v1][v4];
	    double v14_new=GETNEWWTOLD_M(v1,v4,v14_old);
	    double v34_old=sm[v3][v4];
	    double v34_new=GETNEWWTOLD_M(v3,v4,v34_old);
	    
	    if(v13_old>v12_old && v14_old<=v12_old && v34_old>v32_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v14_new<=v12_new && v34_new>v32_new) CHANGE_STAT[0]++;
	  }
	}
      }
    
      for(Vertex v1=1; v1 <= N_NODES; v1++){
	for(Vertex v2=1; v2 <= N_NODES; v2++){
	  if(v2==v1) continue;
	  double v12_old=sm[v1][v2];
	  double v12_new=GETNEWWTOLD_M(v1,v2,v12_old);
	  Vertex v3=tail;
	  if(v3==v2 || v3==v1) continue;
	  double v13_old=sm[v1][v3];
	  double v13_new=GETNEWWTOLD_M(v1,v3,v13_old);
	  
	  if(v13_old<=v12_old && v13_new<=v12_new) continue;
	  
	  double v32_old=sm[v3][v2];
	  double v32_new=GETNEWWTOLD_M(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (head!=v2 && head!=v3 && head!=v4)) continue;
	    double v14_old=sm[v1][v4];
	    double v14_new=GETNEWWTOLD_M(v1,v4,v14_old);
	    double v34_old=sm[v3][v4];
	    double v34_new=GETNEWWTOLD_M(v3,v4,v34_old);
	    
	    if(v13_old>v12_old && v14_old<=v12_old && v34_old>v32_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v14_new<=v12_new && v34_new>v32_new) CHANGE_STAT[0]++;
	  }
	}
      }
}

WtS_CHANGESTAT_FN(s_local2_nonconformity){ 
  GET_AUX_STORAGE(double *, sm);
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12=sm[v1][v2];
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v13=sm[v1][v3];
	if(v13<=v12) continue;
	double v32=sm[v3][v2];
	for(Vertex v4=1; v4 <= N_NODES; v4++){
	  if(v4==v3 || v4==v2 || v4==v1) continue;
	  double v14=sm[v1][v4];
	  double v34=sm[v3][v4];
	  if(v14<=v12 && v34>v32) CHANGE_STAT[0]++;
	}
      }
    }
  }
}


// From Krivitsky and Butts paper, here, v1=i, v2=j, v3=l, v4=k.
WtC_CHANGESTAT_FN(c_localAND_nonconformity){
  GET_AUX_STORAGE(double *, sm);
      Vertex v1=tail;
      
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	double v12_old=sm[v1][v2];
	double v12_new=GETNEWWTOLD_M(v1,v2,v12_old);

	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1) continue;
	  double v13_old=sm[v1][v3];
	  double v13_new=GETNEWWTOLD_M(v1,v3,v13_old);

	  if(v13_old<=v12_old && v13_new<=v12_new) continue;

	  double v32_old=sm[v3][v2];
	  double v32_new=GETNEWWTOLD_M(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (head!=v4 && head!=v3 && head!=v2)) continue;

	    double v14_old=sm[v1][v4];
	    double v14_new=GETNEWWTOLD_M(v1,v4,v14_old);

	    if(v13_old<=v14_old && v13_new<=v14_new) continue;
	    
	    double v34_old=sm[v3][v4];
	    double v34_new=GETNEWWTOLD_M(v3,v4,v34_old);
	    
	    if(v13_old>v12_old && v13_old>v14_old && v12_old<=v14_old && v32_old>v34_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v13_new>v14_new && v12_new<=v14_new && v32_new>v34_new) CHANGE_STAT[0]++;
	  }
	}
      }

      Vertex v3=tail;
      
      for(Vertex v1=1; v1 <= N_NODES; v1++){
	if(v1==v3) continue;
	double v13_old=sm[v1][v3];
	double v13_new=GETNEWWTOLD_M(v1,v3,v13_old);
	
	for(Vertex v2=1; v2 <= N_NODES; v2++){
	  if(v2==v3 || v2==v1) continue;
	    double v12_old=sm[v1][v2];
	    double v12_new=GETNEWWTOLD_M(v1,v2,v12_old);
	    
	    if(v13_old<=v12_old && v13_new<=v12_new) continue;
	    
	    double v32_old=sm[v3][v2];
	    double v32_new=GETNEWWTOLD_M(v3,v2,v32_old);
	    
	    for(Vertex v4=1; v4 <= N_NODES; v4++){
	      if(v4==v3 || v4==v2 || v4==v1 ||
		 (head!=v4 && head!=v2 && head!=v1)) continue;
	      
	      double v14_old=sm[v1][v4];
	      double v14_new=GETNEWWTOLD_M(v1,v4,v14_old);

	      if(v13_old<=v14_old && v13_new<=v14_new) continue;
	      
	      double v34_old=sm[v3][v4];
	      double v34_new=GETNEWWTOLD_M(v3,v4,v34_old);
	    
	      if(v13_old>v12_old && v13_old>v14_old && v12_old<=v14_old && v32_old>v34_old) CHANGE_STAT[0]--;
	      if(v13_new>v12_new && v13_new>v14_new && v12_new<=v14_new && v32_new>v34_new) CHANGE_STAT[0]++;
	    }
	}
      }
}


// From Krivitsky and Butts paper, here, v1=i, v2=j, v3=l, v4=k.
WtS_CHANGESTAT_FN(s_localAND_nonconformity){ 
  GET_AUX_STORAGE(double *, sm);
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12=sm[v1][v2];
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v13=sm[v1][v3];
	if(v13<=v12) continue;	
	double v32=sm[v3][v2];
	for(Vertex v4=1; v4 <= N_NODES; v4++){
	  if(v4==v3 || v4==v2 || v2==v1) continue;
	  double v14=sm[v1][v4];
	  if(v13<=v14) continue;	
	  double v34=sm[v3][v4];
	  if(v32>v34 && v12<=v14) CHANGE_STAT[0]++;
	}
      }
    }
  }
}



WtD_FROM_S_FN(d_nonconformity_decay)

WtS_CHANGESTAT_FN(s_nonconformity_decay){ 
  GET_AUX_STORAGE(double *, sm);
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double e = pow(INPUT_PARAM[0],INPUT_PARAM[1]-sm[v1][v2]);
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v13=sm[v1][v3], v23=sm[v2][v3];
	for(Vertex v4=1; v4 <= N_NODES; v4++){
	  if(v4==v3 || v4==v2 || v4==v1) continue;
	  unsigned int
	    v134 = v13>sm[v1][v4],
	    v234 = v23>sm[v2][v4];
	  if(v134!=v234) CHANGE_STAT[0]+=e;
	}
      }
    }
  }
}

WtD_FROM_S_FN(d_nonconformity_thresholds)

WtS_CHANGESTAT_FN(s_nonconformity_thresholds){ 
  GET_AUX_STORAGE(double *, sm);
    for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12 = sm[v1][v2];
      unsigned int i;
      for(i=0; i<N_CHANGE_STATS; i++) if(v12>=INPUT_PARAM[i]) break;
      if(i==N_CHANGE_STATS) continue;
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v13=sm[v1][v3], v23=sm[v2][v3];
	for(Vertex v4=1; v4 <= N_NODES; v4++){
	  if(v4==v3 || v4==v2 || v4==v1) continue;
	  unsigned int
	    v134 = v13>sm[v1][v4],
	    v234 = v23>sm[v2][v4];
	  if(v134!=v234) CHANGE_STAT[i]+=1;
	}
      }
    }
  }
}
