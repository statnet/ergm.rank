/*  File src/wtchangestats_rank.c in package ergm.rank, part of the Statnet suite
 *  of packages for network analysis, http://statnet.org .
 *
 *  This software is distributed under the GPL-3 license.  It is free,
 *  open source, and has the attribution requirements (GPL Section 7) at
 *  http://statnet.org/attribution
 *
 *  Copyright 2008-2016 Statnet Commons
 */
#include "wtchangestats_rank.h"

WtD_CHANGESTAT_FN(d_edgecov_rank){
  OPTIMAL_RANK_D({
      Vertex v1=TAIL;
      for (Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	double v12_old=GETOLDWT2(v1,v2);
	double v12_new=GETNEWWT2OLD(v1,v2,v12_old);
	for (Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1 || 
	     (HEAD1!=v2 && HEAD1!=v3 && HEAD2!=v2 && HEAD2!=v3)) continue;
	  double v123_covdiff=INPUT_PARAM[(v1-1)*N_NODES + (v2-1)] - INPUT_PARAM[(v1-1)*N_NODES + (v3-1)];
	  if(v123_covdiff==0) continue;  // If covariate value is 0, don't bother looking up the ranking of v3 by v1.
	  double v13_old=GETOLDWT2(v1,v3);
	  double v13_new=GETNEWWT2OLD(v1,v3,v13_old);
	  if(v12_old>v13_old)
	    CHANGE_STAT[0] -= v123_covdiff;
	  if(v12_new>v13_new)
	    CHANGE_STAT[0] += v123_covdiff;
	}
      }
    },{
      Vertex v1=TAIL;
      Vertex v2=HEAD;
      double v12_old = OLDWT;
      double v12_new = NEWWT;
      for (Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v123_covdiff=INPUT_PARAM[(v1-1)*N_NODES + (v2-1)] - INPUT_PARAM[(v1-1)*N_NODES + (v3-1)];
	if(v123_covdiff==0) continue; // If covariate value is 0, don't bother looking up the ranking of v3 by v1.
	double v13_old=GETWT(v1,v3);
	if(v12_old>v13_old)
	  CHANGE_STAT[0] -= v123_covdiff;
	if(v12_old<v13_old)
	  CHANGE_STAT[0] += v123_covdiff;
	if(v12_new>v13_old)
	  CHANGE_STAT[0] += v123_covdiff;
	if(v12_new<v13_old)
	  CHANGE_STAT[0] -= v123_covdiff;
      }
    });
} 

WtS_CHANGESTAT_FN(s_edgecov_rank){
  CHANGE_STAT[0]=0;
  for (Vertex v1=1; v1 <= N_NODES; v1++){
    for (Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12=GETWT(v1,v2);
      for (Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v123_covdiff = INPUT_PARAM[(v1-1)*N_NODES + (v2-1)] - INPUT_PARAM[(v1-1)*N_NODES + (v3-1)];
	if(v123_covdiff!=0 && v12>GETWT(v1,v3)) // Short-circuit the lookup of ranking of v3 by v1 if covariate is 0.
	  CHANGE_STAT[0] += v123_covdiff;
      }
    }
  }
}


WtD_CHANGESTAT_FN(d_inconsistency_rank){
  OPTIMAL_RANK_D({
      Vertex v1=TAIL;
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;

	// For some reason completely beyond me, CPP complains if I
	// declare more than one variable in a line while inside a
	// macro.
	double v12_old = GETOLDWT2(v1,v2);
	double v12_ref = INPUT_PARAM[(v1-1)*N_NODES+(v2-1)];
	double v12_new = GETNEWWT2OLD(v1,v2,v12_old);
	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1 || 
	     (HEAD1!=v2 && HEAD1!=v3 && HEAD2!=v2 && HEAD2!=v3)) continue;
	  double v13_old= GETOLDWT2(v1,v3);
	  double v13_ref=INPUT_PARAM[(v1-1)*N_NODES+(v3-1)];
	  double v13_new= GETNEWWT2OLD(v1,v3,v13_old);
	  if((v12_old>v13_old)!=(v12_ref>v13_ref)) CHANGE_STAT[0]--;
	  if((v12_new>v13_new)!=(v12_ref>v13_ref)) CHANGE_STAT[0]++;
	}
      }
    },{
      Vertex v1=TAIL;
      Vertex v2=HEAD;
      double v12_old = OLDWT;
      double v12_ref = INPUT_PARAM[(v1-1)*N_NODES+(v2-1)];
      double v12_new = NEWWT;
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v13= GETWT(v1,v3);
	double v13_ref=INPUT_PARAM[(v1-1)*N_NODES+(v3-1)];
	if((v12_old>v13)!=(v12_ref>v13_ref)) CHANGE_STAT[0]--;
	if((v12_new>v13)!=(v12_ref>v13_ref)) CHANGE_STAT[0]++;
	if((v13>v12_old)!=(v13_ref>v12_ref)) CHANGE_STAT[0]--;
	if((v13>v12_new)!=(v13_ref>v12_ref)) CHANGE_STAT[0]++;
      }
    });
}

WtS_CHANGESTAT_FN(s_inconsistency_rank){ 
  CHANGE_STAT[0]=0;
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12 = GETWT(v1,v2), v12_ref = INPUT_PARAM[(v1-1)*N_NODES+(v2-1)];
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	unsigned int 
	  v123 = v12>GETWT(v1,v3),
	  v123_ref = v12_ref>INPUT_PARAM[(v1-1)*N_NODES+(v3-1)];
	if(v123!=v123_ref) CHANGE_STAT[0]++;
      }
    }
  }
}

WtD_CHANGESTAT_FN(d_inconsistency_cov_rank){
  OPTIMAL_RANK_D({
      unsigned int cov_start = N_NODES*N_NODES;
      Vertex v1=TAIL;
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;

	// For some reason completely beyond me, CPP complains if I
	// declare more than one variable in a line while inside a
	// macro.
	double v12_old = GETOLDWT2(v1,v2);
	double v12_ref = INPUT_PARAM[(v1-1)*N_NODES+(v2-1)];
	double v12_new = GETNEWWT2OLD(v1,v2,v12_old);
	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1 || 
	     (HEAD1!=v2 && HEAD1!=v3 && HEAD2!=v2 && HEAD2!=v3)) continue;
	  double v123_cov = INPUT_PARAM[cov_start + (v1-1)*N_NODES*N_NODES + (v2-1)*N_NODES + (v3-1)];
	  if(v123_cov==0) continue;
	  double v13_old = GETOLDWT2(v1,v3);
	  double v13_ref = INPUT_PARAM[(v1-1)*N_NODES+(v3-1)];
	  double v13_new = GETNEWWT2OLD(v1,v3,v13_old);
	  if((v12_old>v13_old)!=(v12_ref>v13_ref)) CHANGE_STAT[0]-=v123_cov;
	  if((v12_new>v13_new)!=(v12_ref>v13_ref)) CHANGE_STAT[0]+=v123_cov;
	}
      }
    },{
      unsigned int cov_start = N_NODES*N_NODES;
      Vertex v1=TAIL;
      Vertex v2=HEAD;
      double v12_ref = INPUT_PARAM[(v1-1)*N_NODES+(v2-1)];
      double v12_old = OLDWT;
      double v12_new = NEWWT;
      
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v123_cov = INPUT_PARAM[cov_start + (v1-1)*N_NODES*N_NODES + (v2-1)*N_NODES + (v3-1)];
	double v132_cov = INPUT_PARAM[cov_start + (v1-1)*N_NODES*N_NODES + (v3-1)*N_NODES + (v2-1)];
	if(v123_cov!=0 || v123_cov!=0){
	  double v13=GETWT(v1,v3);
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
    });
}

WtS_CHANGESTAT_FN(s_inconsistency_cov_rank){ 
  unsigned int cov_start = N_NODES*N_NODES;
  CHANGE_STAT[0]=0;
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12 = GETWT(v1,v2), v12_ref = INPUT_PARAM[(v1-1)*N_NODES+(v2-1)];
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v123_cov = INPUT_PARAM[cov_start + (v1-1)*N_NODES*N_NODES + (v2-1)*N_NODES + (v3-1)];
	if(v123_cov==0) continue;
	unsigned int 
	  v123 = v12>GETWT(v1,v3),
	  v123_ref = v12_ref>INPUT_PARAM[(v1-1)*N_NODES+(v3-1)];
	if(v123!=v123_ref) 
	  CHANGE_STAT[0]+=v123_cov;
      }
    }
  }
}

WtD_CHANGESTAT_FN(d_deference){
  OPTIMAL_RANK_D({
      for(Vertex v1=1; v1 <= N_NODES; v1++){
	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v1) continue;
	  double v31_old = GETOLDWT2(v3,v1);
	  double v13_old = GETOLDWT2(v1,v3);
	  double v31_new = GETNEWWT2OLD(v3,v1,v31_old);
	  double v13_new = GETNEWWT2OLD(v1,v3,v13_old);

	  for(Vertex v2=1; v2 <= N_NODES; v2++){
	    if(v2==v1 || v3==v2 || 
	       (TAIL!=v1 && TAIL!=v3 && 
		HEAD1!=v1 && HEAD1!=v2 && HEAD1!=v3 &&
		HEAD2!=v1 && HEAD2!=v2 && HEAD2!=v3)) continue;
	    double v32_old = GETOLDWT2(v3,v2);
	    double v12_old = GETOLDWT2(v1,v2);
	    double v32_new = GETNEWWT2OLD(v3,v2,v32_old);
	    double v12_new = GETNEWWT2OLD(v1,v2,v12_old);
	    if(v32_old>v31_old && v13_old>v12_old) 
	      CHANGE_STAT[0]--;
	    if(v32_new>v31_new && v13_new>v12_new) 
	      CHANGE_STAT[0]++;
	  }
	}
      }
    },{
      for(Vertex v1=1; v1 <= N_NODES; v1++){
	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v1) continue;
	  double v31_old = GETOLDWT(v3,v1);
	  double v13_old = GETOLDWT(v1,v3);
	  double v31_new = GETNEWWTOLD(v3,v1,v31_old);
	  double v13_new = GETNEWWTOLD(v1,v3,v13_old);

	  for(Vertex v2=1; v2 <= N_NODES; v2++){
	    if(v2==v1 || v3==v2 || 
	       (TAIL!=v1 && TAIL!=v3 && 
		HEAD!=v1 && HEAD!=v2 && HEAD!=v3)) continue;
	    double v32_old = GETOLDWT(v3,v2);
	    double v12_old = GETOLDWT(v1,v2);
	    double v32_new = GETNEWWTOLD(v3,v2,v32_old);
	    double v12_new = GETNEWWTOLD(v1,v2,v12_old);
	    if(v32_old>v31_old && v13_old>v12_old) 
	      CHANGE_STAT[0]--;
	    if(v32_new>v31_new && v13_new>v12_new) 
	      CHANGE_STAT[0]++;
	  }
	}
      }
    });
}

WtS_CHANGESTAT_FN(s_deference){ 
  CHANGE_STAT[0]=0;
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v3=1; v3 <= N_NODES; v3++){
      if(v3==v1) continue;
      double v31 = GETWT(v3,v1), v13 = GETWT(v1,v3);
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1 || v3==v2) continue;
	if(GETWT(v3,v2)>v31 && v13>GETWT(v1,v2)) 
	  CHANGE_STAT[0]++;
      }
    }
  }
}

WtD_CHANGESTAT_FN(d_nodeicov_rank){
  OPTIMAL_RANK_D({
      Vertex v1=TAIL;
      for (Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	double v12_old=GETOLDWT2(v1,v2);
	double v12_new=GETNEWWT2OLD(v1,v2,v12_old);
	for (Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1 || 
	     (HEAD1!=v2 && HEAD1!=v3 && HEAD2!=v2 && HEAD2!=v3)) continue;
	  double v23_covdiff=INPUT_PARAM[v2-1] - INPUT_PARAM[v3-1];
	  if(v23_covdiff==0) continue;  // If covariate value is 0, don't bother looking up the ranking of v3 by v1.
	  double v13_old=GETOLDWT2(v1,v3);
	  double v13_new=GETNEWWT2OLD(v1,v3,v13_old);
	  if(v12_old>v13_old)
	    CHANGE_STAT[0] -= v23_covdiff;
	  if(v12_new>v13_new)
	    CHANGE_STAT[0] += v23_covdiff;
	}
      }
    },{
      Vertex v1=TAIL;
      Vertex v2=HEAD;
      double v12_old = OLDWT;
      double v12_new = NEWWT;
      for (Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v23_covdiff=INPUT_PARAM[v2-1] - INPUT_PARAM[v3-1];
	if(v23_covdiff==0) continue; // If covariate value is 0, don't bother looking up the ranking of v3 by v1.
	double v13_old=GETWT(v1,v3);
	if(v12_old>v13_old)
	  CHANGE_STAT[0] -= v23_covdiff;
	if(v12_old<v13_old)
	  CHANGE_STAT[0] += v23_covdiff;
	if(v12_new>v13_old)
	  CHANGE_STAT[0] += v23_covdiff;
	if(v12_new<v13_old)
	  CHANGE_STAT[0] -= v23_covdiff;
      }
    });
} 

WtS_CHANGESTAT_FN(s_nodeicov_rank){ 
  CHANGE_STAT[0]=0;
  for (Vertex v1=1; v1 <= N_NODES; v1++){
    for (Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12=GETWT(v1,v2);
      for (Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	if(v12>GETWT(v1,v3)) 
	  CHANGE_STAT[0] += INPUT_PARAM[v2-1] - INPUT_PARAM[v3-1];
      }
    }
  }
}

WtD_CHANGESTAT_FN(d_nonconformity){
  OPTIMAL_RANK_D({
      Vertex v1=TAIL;
      
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	
	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1) continue;
	  
	  double v13_old=GETOLDWT2(v1,v3);
	  double v23=GETWT(v2,v3);
	  double v13_new = GETNEWWT2OLD(v1,v3,v13_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 || 
	       (HEAD1!=v3 && HEAD1!=v4 && HEAD2!=v3 && HEAD2!=v4)) continue;
	    
	    double v14_old=GETOLDWT2(v1,v4);
	    double v24=GETWT(v2,v4);
	    double v14_new = GETNEWWT2OLD(v1,v4,v14_old);
	    
	    if((v13_old>v14_old)!=(v23>v24)) CHANGE_STAT[0]--;
	    if((v13_new>v14_new)!=(v23>v24)) CHANGE_STAT[0]++;
	  }
	}
      }
    },{
      Vertex v1=TAIL;
      
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	
	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1) continue;
	  
	  double v13_old=GETOLDWT(v1,v3);
	  double v23=GETWT(v2,v3);
	  double v13_new = GETNEWWTOLD(v1,v3,v13_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 || 
	       (HEAD!=v3 && HEAD!=v4)) continue;
	    
	    double v14_old=GETOLDWT(v1,v4);
	    double v24=GETWT(v2,v4);
	    double v14_new = GETNEWWTOLD(v1,v4,v14_old);
	    
	    if((v13_old>v14_old)!=(v23>v24)) CHANGE_STAT[0]--;
	    if((v13_new>v14_new)!=(v23>v24)) CHANGE_STAT[0]++;
	  }
	}
      }
    });
}

WtS_CHANGESTAT_FN(s_nonconformity){ 
  CHANGE_STAT[0]=0;
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 < v1; v2++){
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v13=GETWT(v1,v3), v23=GETWT(v2,v3);
	for(Vertex v4=1; v4 <= N_NODES; v4++){
	  if(v4==v3 || v4==v2 || v4==v1) continue;
	  unsigned int
	    v134 = v13>GETWT(v1,v4),
	    v234 = v23>GETWT(v2,v4);
	  if(v134!=v234) CHANGE_STAT[0]++;
	}
      }
    }
  }
}

// From Krivitsky and Butts paper, here, v1=i, v2=j, v3=l, v4=k.
WtD_CHANGESTAT_FN(d_local1_nonconformity){
  OPTIMAL_RANK_D({
      Vertex v1=TAIL;

      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	double v12_old=GETOLDWT2(v1,v2);
	double v12_new=GETNEWWT2OLD(v1,v2,v12_old);
	
	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1) continue;
	  double v13_old=GETOLDWT2(v1,v3);
	  double v13_new=GETNEWWT2OLD(v1,v3,v13_old);
	  
	  if(v13_old<=v12_old && v13_new<=v12_new) continue;

	  double v32_old=GETOLDWT2(v3,v2);
	  double v32_new=GETNEWWT2OLD(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (HEAD1!=v2 && HEAD2!=v2 && HEAD1!=v3 && HEAD2!=v3 && HEAD1!=v4 && HEAD2!=v4)) continue;
	    
	    double v14_old=GETOLDWT2(v1,v4);
	    double v14_new=GETNEWWT2OLD(v1,v4,v14_old);
	    
	    double v34_old=GETOLDWT2(v3,v4);
	    double v34_new=GETNEWWT2OLD(v3,v4,v34_old);
	    
	    
	    if(v13_old>v12_old && v12_old<=v14_old && v32_old>v34_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v12_new<=v14_new && v32_new>v34_new) CHANGE_STAT[0]++;
	  }
	}
      }

      Vertex v3=TAIL;
      
      for(Vertex v1=1; v1 <= N_NODES; v1++){
	if(v1==v3) continue;
	double v13_old=GETOLDWT2(v1,v3);
	double v13_new=GETNEWWT2OLD(v1,v3,v13_old);

	for(Vertex v2=1; v2 <= N_NODES; v2++){
	  if(v2==v3 || v2==v1) continue;
	  double v12_old=GETOLDWT2(v1,v2);
	  double v12_new=GETNEWWT2OLD(v1,v2,v12_old);

	  if(v13_old<=v12_old && v13_new<=v12_new) continue;

	  double v32_old=GETOLDWT2(v3,v2);
	  double v32_new=GETNEWWT2OLD(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (HEAD1!=v4 && HEAD2!=v4 && HEAD1!=v2 && HEAD2!=v2 && HEAD1!=v1 && HEAD2!=v1)) continue;
	    
	    double v14_old=GETOLDWT2(v1,v4);
	    double v14_new=GETNEWWT2OLD(v1,v4,v14_old);
	  
	    double v34_old=GETOLDWT2(v3,v4);
	    double v34_new=GETNEWWT2OLD(v3,v4,v34_old);
	    
	    if(v13_old>v12_old && v12_old<=v14_old && v32_old>v34_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v12_new<=v14_new && v32_new>v34_new) CHANGE_STAT[0]++;
	  }
	}
      }
    },{
      Vertex v1=TAIL;
      
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	double v12_old=GETOLDWT(v1,v2);
	double v12_new=GETNEWWTOLD(v1,v2,v12_old);

	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1) continue;
	  double v13_old=GETOLDWT(v1,v3);
	  double v13_new=GETNEWWTOLD(v1,v3,v13_old);

	  if(v13_old<=v12_old && v13_new<=v12_new) continue;

	  double v32_old=GETOLDWT(v3,v2);
	  double v32_new=GETNEWWTOLD(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (HEAD!=v4 && HEAD!=v3 && HEAD!=v2)) continue;

	    double v14_old=GETOLDWT(v1,v4);
	    double v14_new=GETNEWWTOLD(v1,v4,v14_old);
	  
	    double v34_old=GETOLDWT(v3,v4);
	    double v34_new=GETNEWWTOLD(v3,v4,v34_old);
	    
	    if(v13_old>v12_old && v12_old<=v14_old && v32_old>v34_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v12_new<=v14_new && v32_new>v34_new) CHANGE_STAT[0]++;
	  }
	}
      }

      Vertex v3=TAIL;
      
      for(Vertex v1=1; v1 <= N_NODES; v1++){
	if(v1==v3) continue;
	double v13_old=GETOLDWT(v1,v3);
	double v13_new=GETNEWWTOLD(v1,v3,v13_old);
	
	for(Vertex v2=1; v2 <= N_NODES; v2++){
	  if(v2==v3 || v2==v1) continue;
	    double v12_old=GETOLDWT(v1,v2);
	    double v12_new=GETNEWWTOLD(v1,v2,v12_old);
	    
	    if(v13_old<=v12_old && v13_new<=v12_new) continue;
	    
	    double v32_old=GETOLDWT(v3,v2);
	    double v32_new=GETNEWWTOLD(v3,v2,v32_old);
	    
	    for(Vertex v4=1; v4 <= N_NODES; v4++){
	      if(v4==v3 || v4==v2 || v4==v1 ||
		 (HEAD!=v4 && HEAD!=v2 && HEAD!=v1)) continue;
	      
	      double v14_old=GETOLDWT(v1,v4);
	      double v14_new=GETNEWWTOLD(v1,v4,v14_old);
	      
	      double v34_old=GETOLDWT(v3,v4);
	      double v34_new=GETNEWWTOLD(v3,v4,v34_old);
	    
	      if(v13_old>v12_old && v12_old<=v14_old && v32_old>v34_old) CHANGE_STAT[0]--;
	      if(v13_new>v12_new && v12_new<=v14_new && v32_new>v34_new) CHANGE_STAT[0]++;
	    }
	}
      }
    });
}


// From Krivitsky and Butts paper, here, v1=i, v2=j, v3=l, v4=k.
WtS_CHANGESTAT_FN(s_local1_nonconformity){ 
  CHANGE_STAT[0]=0;
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12=GETWT(v1,v2);
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v13=GETWT(v1,v3);
	if(v13<=v12) continue;	
	double v32=GETWT(v3,v2);
	for(Vertex v4=1; v4 <= N_NODES; v4++){
	  if(v4==v3 || v4==v2 || v2==v1) continue;
	  double v14=GETWT(v1,v4);
	  double v34=GETWT(v3,v4);
	  if(v32>v34 && v12<=v14) CHANGE_STAT[0]++;
	}
      }
    }
  }
}


WtD_CHANGESTAT_FN(d_local2_nonconformity){
  OPTIMAL_RANK_D({
      Vertex v1=TAIL;
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	double v12_old=GETOLDWT2(v1,v2);
	double v12_new=GETNEWWT2OLD(v1,v2,v12_old);
	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1) continue;
	  double v13_old=GETOLDWT2(v1,v3);
	  double v13_new=GETNEWWT2OLD(v1,v3,v13_old);
	  
	  if(v13_old<=v12_old && v13_new<=v12_new) continue;
	  
	  double v32_old=GETOLDWT2(v3,v2);
	  double v32_new=GETNEWWT2OLD(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (HEAD1!=v2 && HEAD2!=v2 && HEAD1!=v3 && HEAD2!=v3 && HEAD1!=v4 && HEAD2!=v4)) continue;
	    double v14_old=GETOLDWT2(v1,v4);
	    double v14_new=GETNEWWT2OLD(v1,v4,v14_old);
	    double v34_old=GETOLDWT2(v3,v4);
	    double v34_new=GETNEWWT2OLD(v3,v4,v34_old);
	    
	    if(v13_old>v12_old && v14_old<=v12_old && v34_old>v32_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v14_new<=v12_new && v34_new>v32_new) CHANGE_STAT[0]++;
	  }
	}
      }
    
      for(Vertex v1=1; v1 <= N_NODES; v1++){
	for(Vertex v2=1; v2 <= N_NODES; v2++){
	  if(v2==v1) continue;
	  double v12_old=GETOLDWT2(v1,v2);
	  double v12_new=GETNEWWT2OLD(v1,v2,v12_old);
	  Vertex v3=TAIL;
	  if(v3==v2 || v3==v1) continue;
	  double v13_old=GETOLDWT2(v1,v3);
	  double v13_new=GETNEWWT2OLD(v1,v3,v13_old);
	  
	  if(v13_old<=v12_old && v13_new<=v12_new) continue;
	  
	  double v32_old=GETOLDWT2(v3,v2);
	  double v32_new=GETNEWWT2OLD(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (HEAD1!=v2 && HEAD2!=v2 && HEAD1!=v3 && HEAD2!=v3 && HEAD1!=v4 && HEAD2!=v4)) continue;
	    double v14_old=GETOLDWT2(v1,v4);
	    double v14_new=GETNEWWT2OLD(v1,v4,v14_old);
	    double v34_old=GETOLDWT2(v3,v4);
	    double v34_new=GETNEWWT2OLD(v3,v4,v34_old);
	    
	    if(v13_old>v12_old && v14_old<=v12_old && v34_old>v32_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v14_new<=v12_new && v34_new>v32_new) CHANGE_STAT[0]++;
	  }
	}
      }
    },{
      Vertex v1=TAIL;
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	double v12_old=GETOLDWT(v1,v2);
	double v12_new=GETNEWWTOLD(v1,v2,v12_old);
	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1) continue;
	  double v13_old=GETOLDWT(v1,v3);
	  double v13_new=GETNEWWTOLD(v1,v3,v13_old);
	  
	  if(v13_old<=v12_old && v13_new<=v12_new) continue;
	  
	  double v32_old=GETOLDWT(v3,v2);
	  double v32_new=GETNEWWTOLD(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (HEAD!=v2 && HEAD!=v3 && HEAD!=v4)) continue;
	    double v14_old=GETOLDWT(v1,v4);
	    double v14_new=GETNEWWTOLD(v1,v4,v14_old);
	    double v34_old=GETOLDWT(v3,v4);
	    double v34_new=GETNEWWTOLD(v3,v4,v34_old);
	    
	    if(v13_old>v12_old && v14_old<=v12_old && v34_old>v32_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v14_new<=v12_new && v34_new>v32_new) CHANGE_STAT[0]++;
	  }
	}
      }
    
      for(Vertex v1=1; v1 <= N_NODES; v1++){
	for(Vertex v2=1; v2 <= N_NODES; v2++){
	  if(v2==v1) continue;
	  double v12_old=GETOLDWT(v1,v2);
	  double v12_new=GETNEWWTOLD(v1,v2,v12_old);
	  Vertex v3=TAIL;
	  if(v3==v2 || v3==v1) continue;
	  double v13_old=GETOLDWT(v1,v3);
	  double v13_new=GETNEWWTOLD(v1,v3,v13_old);
	  
	  if(v13_old<=v12_old && v13_new<=v12_new) continue;
	  
	  double v32_old=GETOLDWT(v3,v2);
	  double v32_new=GETNEWWTOLD(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (HEAD!=v2 && HEAD!=v3 && HEAD!=v4)) continue;
	    double v14_old=GETOLDWT(v1,v4);
	    double v14_new=GETNEWWTOLD(v1,v4,v14_old);
	    double v34_old=GETOLDWT(v3,v4);
	    double v34_new=GETNEWWTOLD(v3,v4,v34_old);
	    
	    if(v13_old>v12_old && v14_old<=v12_old && v34_old>v32_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v14_new<=v12_new && v34_new>v32_new) CHANGE_STAT[0]++;
	  }
	}
      }
    });
}

WtS_CHANGESTAT_FN(s_local2_nonconformity){ 
  CHANGE_STAT[0]=0;
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12=GETWT(v1,v2);
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v13=GETWT(v1,v3);
	if(v13<=v12) continue;
	double v32=GETWT(v3,v2);
	for(Vertex v4=1; v4 <= N_NODES; v4++){
	  if(v4==v3 || v4==v2 || v4==v1) continue;
	  double v14=GETWT(v1,v4);
	  double v34=GETWT(v3,v4);
	  if(v14<=v12 && v34>v32) CHANGE_STAT[0]++;
	}
      }
    }
  }
}


// From Krivitsky and Butts paper, here, v1=i, v2=j, v3=l, v4=k.
WtD_CHANGESTAT_FN(d_localAND_nonconformity){
  OPTIMAL_RANK_D({
      Vertex v1=TAIL;

      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	double v12_old=GETOLDWT2(v1,v2);
	double v12_new=GETNEWWT2OLD(v1,v2,v12_old);
	
	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1) continue;
	  double v13_old=GETOLDWT2(v1,v3);
	  double v13_new=GETNEWWT2OLD(v1,v3,v13_old);
	  
	  if(v13_old<=v12_old && v13_new<=v12_new) continue;

	  double v32_old=GETOLDWT2(v3,v2);
	  double v32_new=GETNEWWT2OLD(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (HEAD1!=v2 && HEAD2!=v2 && HEAD1!=v3 && HEAD2!=v3 && HEAD1!=v4 && HEAD2!=v4)) continue;
	    
	    double v14_old=GETOLDWT2(v1,v4);
	    double v14_new=GETNEWWT2OLD(v1,v4,v14_old);

	    if(v13_old<=v14_old && v13_new<=v14_new) continue;
	    
	    double v34_old=GETOLDWT2(v3,v4);
	    double v34_new=GETNEWWT2OLD(v3,v4,v34_old);
	    
	    
	    if(v13_old>v12_old && v13_old>v14_old && v12_old<=v14_old && v32_old>v34_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v13_new>v14_new && v12_new<=v14_new && v32_new>v34_new) CHANGE_STAT[0]++;
	  }
	}
      }

      Vertex v3=TAIL;
      
      for(Vertex v1=1; v1 <= N_NODES; v1++){
	if(v1==v3) continue;
	double v13_old=GETOLDWT2(v1,v3);
	double v13_new=GETNEWWT2OLD(v1,v3,v13_old);

	for(Vertex v2=1; v2 <= N_NODES; v2++){
	  if(v2==v3 || v2==v1) continue;
	  double v12_old=GETOLDWT2(v1,v2);
	  double v12_new=GETNEWWT2OLD(v1,v2,v12_old);

	  if(v13_old<=v12_old && v13_new<=v12_new) continue;

	  double v32_old=GETOLDWT2(v3,v2);
	  double v32_new=GETNEWWT2OLD(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (HEAD1!=v4 && HEAD2!=v4 && HEAD1!=v2 && HEAD2!=v2 && HEAD1!=v1 && HEAD2!=v1)) continue;
	    
	    double v14_old=GETOLDWT2(v1,v4);
	    double v14_new=GETNEWWT2OLD(v1,v4,v14_old);

	    if(v13_old<=v14_old && v13_new<=v14_new) continue;
	    
	    double v34_old=GETOLDWT2(v3,v4);
	    double v34_new=GETNEWWT2OLD(v3,v4,v34_old);
	    
	    if(v13_old>v12_old && v13_old>v14_old && v12_old<=v14_old && v32_old>v34_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v13_new>v14_new && v12_new<=v14_new && v32_new>v34_new) CHANGE_STAT[0]++;
	  }
	}
      }
    },{
      Vertex v1=TAIL;
      
      for(Vertex v2=1; v2 <= N_NODES; v2++){
	if(v2==v1) continue;
	double v12_old=GETOLDWT(v1,v2);
	double v12_new=GETNEWWTOLD(v1,v2,v12_old);

	for(Vertex v3=1; v3 <= N_NODES; v3++){
	  if(v3==v2 || v3==v1) continue;
	  double v13_old=GETOLDWT(v1,v3);
	  double v13_new=GETNEWWTOLD(v1,v3,v13_old);

	  if(v13_old<=v12_old && v13_new<=v12_new) continue;

	  double v32_old=GETOLDWT(v3,v2);
	  double v32_new=GETNEWWTOLD(v3,v2,v32_old);
	  
	  for(Vertex v4=1; v4 <= N_NODES; v4++){
	    if(v4==v3 || v4==v2 || v4==v1 ||
	       (HEAD!=v4 && HEAD!=v3 && HEAD!=v2)) continue;

	    double v14_old=GETOLDWT(v1,v4);
	    double v14_new=GETNEWWTOLD(v1,v4,v14_old);

	    if(v13_old<=v14_old && v13_new<=v14_new) continue;
	    
	    double v34_old=GETOLDWT(v3,v4);
	    double v34_new=GETNEWWTOLD(v3,v4,v34_old);
	    
	    if(v13_old>v12_old && v13_old>v14_old && v12_old<=v14_old && v32_old>v34_old) CHANGE_STAT[0]--;
	    if(v13_new>v12_new && v13_new>v14_new && v12_new<=v14_new && v32_new>v34_new) CHANGE_STAT[0]++;
	  }
	}
      }

      Vertex v3=TAIL;
      
      for(Vertex v1=1; v1 <= N_NODES; v1++){
	if(v1==v3) continue;
	double v13_old=GETOLDWT(v1,v3);
	double v13_new=GETNEWWTOLD(v1,v3,v13_old);
	
	for(Vertex v2=1; v2 <= N_NODES; v2++){
	  if(v2==v3 || v2==v1) continue;
	    double v12_old=GETOLDWT(v1,v2);
	    double v12_new=GETNEWWTOLD(v1,v2,v12_old);
	    
	    if(v13_old<=v12_old && v13_new<=v12_new) continue;
	    
	    double v32_old=GETOLDWT(v3,v2);
	    double v32_new=GETNEWWTOLD(v3,v2,v32_old);
	    
	    for(Vertex v4=1; v4 <= N_NODES; v4++){
	      if(v4==v3 || v4==v2 || v4==v1 ||
		 (HEAD!=v4 && HEAD!=v2 && HEAD!=v1)) continue;
	      
	      double v14_old=GETOLDWT(v1,v4);
	      double v14_new=GETNEWWTOLD(v1,v4,v14_old);

	      if(v13_old<=v14_old && v13_new<=v14_new) continue;
	      
	      double v34_old=GETOLDWT(v3,v4);
	      double v34_new=GETNEWWTOLD(v3,v4,v34_old);
	    
	      if(v13_old>v12_old && v13_old>v14_old && v12_old<=v14_old && v32_old>v34_old) CHANGE_STAT[0]--;
	      if(v13_new>v12_new && v13_new>v14_new && v12_new<=v14_new && v32_new>v34_new) CHANGE_STAT[0]++;
	    }
	}
      }
    });
}


// From Krivitsky and Butts paper, here, v1=i, v2=j, v3=l, v4=k.
WtS_CHANGESTAT_FN(s_localAND_nonconformity){ 
  CHANGE_STAT[0]=0;
  for(Vertex v1=1; v1 <= N_NODES; v1++){
    for(Vertex v2=1; v2 <= N_NODES; v2++){
      if(v2==v1) continue;
      double v12=GETWT(v1,v2);
      for(Vertex v3=1; v3 <= N_NODES; v3++){
	if(v3==v2 || v3==v1) continue;
	double v13=GETWT(v1,v3);
	if(v13<=v12) continue;	
	double v32=GETWT(v3,v2);
	for(Vertex v4=1; v4 <= N_NODES; v4++){
	  if(v4==v3 || v4==v2 || v2==v1) continue;
	  double v14=GETWT(v1,v4);
	  if(v13<=v14) continue;	
	  double v34=GETWT(v3,v4);
	  if(v32>v34 && v12<=v14) CHANGE_STAT[0]++;
	}
      }
    }
  }
}


