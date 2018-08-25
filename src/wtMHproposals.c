/*  File src/wtMHproposals.c in package ergm.rank, part of the Statnet suite
 *  of packages for network analysis, http://statnet.org .
 *
 *  This software is distributed under the GPL-3 license.  It is free,
 *  open source, and has the attribution requirements (GPL Section 7) at
 *  http://statnet.org/attribution
 *
 *  Copyright 2008-2018 Statnet Commons
 */
#include "wtMHproposals.h"

/* Shorthand. */
#define Mtail (MHp->toggletail)
#define Mhead (MHp->togglehead)
#define Mweight (MHp->toggleweight)

/*********************
 void MH_AlterSwap

 Default MH algorithm for ERGM over complete orderings
*********************/
void MH_AlterSwap(WtMHproposal *MHp, WtNetwork *nwp)  {  
  Vertex tail, head1, head2;
  
  if(MHp->ntoggles == 0) { // Initialize AlterSwap 
    MHp->ntoggles=2;
    return;
  }

  unsigned int trytoggle;

  for(trytoggle=0; trytoggle<MAX_TRIES; trytoggle++){
  
    GetRandDyad(&tail, &head1, nwp);
    
    if(nwp->bipartite){
      head2 = 1 + nwp->bipartite + unif_rand() * (nwp->nnodes - nwp->bipartite - 1);
      if(head2 >= head1) head2++;
    }else{
      head2 = 1 + unif_rand() * (nwp->nnodes - 2);
      if(head2 >= tail) head2++;
      if(head2 >= head1){
	head2++;
	if(head2 == tail) head2++; // Increment if landed on top of tail. Note that head2 must have started out < tail, so there is no possibility of head2 being incremented 3 times.
      }
    }
    
    Mtail[0] = Mtail[1] = tail;
    Mhead[0] = head1;
    Mhead[1] = head2;
    
    Mweight[1] = WtGetEdge(Mtail[0],Mhead[0],nwp);
    Mweight[0] = WtGetEdge(Mtail[1],Mhead[1],nwp);

    if(Mweight[0]!=Mweight[1]) break;
  }
  if(trytoggle>=MAX_TRIES){
    MHp->toggletail[0]=MH_FAILED;
    MHp->togglehead[0]=MH_UNSUCCESSFUL;	
  }
}
