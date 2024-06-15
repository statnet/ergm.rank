/*  File src/wtchangestat_rank.h in package ergm.rank, part of the
 *  Statnet suite of packages for network analysis, https://statnet.org .
 *
 *  This software is distributed under the GPL-3 license.  It is free,
 *  open source, and has the attribution requirements (GPL Section 7) at
 *  https://statnet.org/attribution .
 *
 *  Copyright 2008-2024 Statnet Commons
 */
#ifndef WTCHANGESTAT_RANK_H
#define WTCHANGESTAT_RANK_H

#include "ergm_wtedgetree.h"
#include "ergm_wtchangestat.h"
#include "ergm_storage.h"

// Case 1: One ego swaps the values of two alters.
// Case 2: The alters are adjacent?
// Otherwise, run the toggle loop with code wherein one ego changes the value of one alter.

#define GETOLDWT2(a,b) (SAMEDYAD(TAIL,HEAD1,a,b) ? OLDWT1 : (SAMEDYAD(TAIL,HEAD2,a,b) ? OLDWT2 : GETWT(a,b)))
#define GETNEWWT2(a,b) (SAMEDYAD(TAIL,HEAD1,a,b) ? NEWWT1 : (SAMEDYAD(TAIL,HEAD2,a,b) ? NEWWT2 : GETWT(a,b)))
#define GETNEWWT2OLD(a,b,old) (SAMEDYAD(TAIL,HEAD1,a,b) ? NEWWT1 : (SAMEDYAD(TAIL,HEAD2,a,b) ? NEWWT2 : (old)))

#define GETNEWWTOLD_M(a,b,old) (SAMEDYAD(tail,head,a,b)?weight:old)

#define EXEC_THROUGH_FOUTDYADS(a,e,v,w,subroutine){		\
  Vertex v = BIPARTITE?BIPARTITE:1;				\
  for(Edge e=MIN_OUTEDGE(a);OUTVAL(e)!=0;e=NEXT_OUTEDGE(e)){	\
    while(v < OUTVAL(e)){					\
      if(v==a) continue;					\
      double w=0;						\
      {subroutine}						\
      v++;							\
    }/* Now, v==OUTVAL(e), so */				\
    double w=OUTWT(e);						\
    {subroutine}						\
    v++;							\
  } /* Now, there are no more edges. */				\
  while(v<=N_NODES){						\
    if(v==a) continue;						\
    double w=0;							\
    {subroutine}						\
    v++;							\
  }

#define EXEC_THROUGH_FINDYADS(a,e,v,w,subroutine){		\
  Vertex v = 1;							\
  for(Edge e=MIN_INEDGE(a);INVAL(e)!=0;e=NEXT_INEDGE(e)){	\
    while(v < INVAL(e)){					\
      if(v==a) continue;					\
      double w=0;						\
      {subroutine}						\
      v++;							\
    }/* Now, v==INVAL(e), so */					\
    double w=INWT(e);						\
    {subroutine}						\
    v++;							\
  } /* Now, there are no more edges. */				\
  while(v<=(BIPARTITE?BIPARTITE-1:N_NODES)){			\
    if(v==a) continue;						\
    double w=0;							\
    {subroutine}						\
    v++;							\
  }


#define OPTIMAL_RANK_D(case1sub,defaultsub){				\
    if(ntoggles==2 && tails[0]==tails[1]){				\
      Vertex TAIL=tails[0], HEAD1=heads[0], HEAD2=heads[1];		\
      double OLDWT1=GETWT(TAIL, HEAD1), OLDWT2=GETWT(TAIL, HEAD2);	\
      double NEWWT1=weights[0], NEWWT2=weights[1];			\
      if(NEWWT1==OLDWT2 && NEWWT2==OLDWT1){				\
	ZERO_ALL_CHANGESTATS();						\
	{case1sub};							\
      }									\
    }else{								\
      ZERO_ALL_CHANGESTATS();						\
      EXEC_THROUGH_TOGGLES({defaultsub});				\
    }									\
  };									

#endif
