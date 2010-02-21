#include <pthread.h>
#include "DynSPSA.h"
#include "DynSPSA_MT.h"

void MCMCDynSNR_MT_wrapper(// Observed network.
		    int *heads, int *tails, int *n_edges,
		    int *maxpossibleedges,
		    int *n_nodes, int *dflag, int *bipartite, 
		    // Ordering of formation and dissolution.
		    int *order_code, 
		    // Formation terms and proposals.
		    int *F_nterms, char **F_funnames, char **F_sonames, 
		    char **F_MHproposaltype, char **F_MHproposalpackage,
		    double *F_inputs, double *F_theta0, 
		    double *init_dev,
		    // SNR settings.
		    double *a,
		    double *alpha,
		    double *A,
		    double *c,
		    double *gamma,
		    int *iterations,
		    // Dissolution terms and proposals.
		    int *D_nterms, char **D_funnames, char **D_sonames, 
		    char **D_MHproposaltype, char **D_MHproposalpackage,
		    double *D_inputs, double *D_theta0,
		    // Degree bounds.
		    int *attribs, int *maxout, int *maxin, int *minout,
		    int *minin, int *condAllDegExact, int *attriblength,
		    // MCMC settings.
		    int *burnin, int *interval, int *dyninterval,
		    // Space for output.
		    int *maxedges,
		    // Verbosity.
		    int *fVerbose){

  Network nwp[4];
  DegreeBound *bd[2];
  Model *F_m[2], *D_m[2];
  MHproposal F_MH[2], D_MH[2];
  DynamOrder order;
  double *D_stats[2];
  
  Vertex *difftime[2], *diffhead[2], *difftail[2];
  difftime[0] = (Vertex *) calloc(*maxedges,sizeof(Vertex));
  diffhead[0] = (Vertex *) calloc(*maxedges,sizeof(Vertex));
  difftail[0] = (Vertex *) calloc(*maxedges,sizeof(Vertex));
  difftime[1] = (Vertex *) calloc(*maxedges,sizeof(Vertex));
  diffhead[1] = (Vertex *) calloc(*maxedges,sizeof(Vertex));
  difftail[1] = (Vertex *) calloc(*maxedges,sizeof(Vertex));
  
  MCMCDyn_init_common(heads, tails, *n_edges, *maxpossibleedges,
		      *n_nodes, *dflag, *bipartite, nwp,
		      *order_code, &order,
		      *F_nterms, *F_funnames, *F_sonames, F_inputs, F_m,
		      *D_nterms, *D_funnames, *D_sonames, D_inputs, D_m,
		      attribs, maxout, maxin, minout,
		      minin, *condAllDegExact, *attriblength, bd,
		      *F_MHproposaltype, *F_MHproposalpackage, F_MH,
		      *D_MHproposaltype, *D_MHproposalpackage, D_MH,
		      *fVerbose);

  D_stats[0]=calloc(D_m[0]->n_stats,sizeof(double));
  D_stats[1]=calloc(D_m[0]->n_stats,sizeof(double));
  
  MCMCSampleDynObjective_args t1args={nwp,order,F_m[0],F_MH,NULL,D_m[0],D_MH,D_theta0,bd[0],init_dev,D_stats[0],*maxedges,difftime[0],diffhead[0],difftail[0],*dyninterval,0,0,NULL,NULL,NULL,NULL};

  double *dev2=calloc(F_m[0]->n_stats,sizeof(double));
  memcpy(dev2,init_dev,F_m[0]->n_stats*sizeof(double));

  MCMCDyn_init_common(heads, tails, *n_edges, *maxpossibleedges,
		      *n_nodes, *dflag, *bipartite, nwp+2,
		      *order_code, &order,
		      *F_nterms, *F_funnames, *F_sonames, F_inputs, F_m+1,
		      *D_nterms, *D_funnames, *D_sonames, D_inputs, D_m+1,
		      attribs, maxout, maxin, minout,
		      minin, *condAllDegExact, *attriblength, bd+1,
		      *F_MHproposaltype, *F_MHproposalpackage, F_MH+1,
		      *D_MHproposaltype, *D_MHproposalpackage, D_MH+1,
		      *fVerbose);

  MCMCSampleDynObjective_args t2args={nwp+2,order,F_m[1],F_MH+1,NULL,D_m[1],D_MH+1,D_theta0,bd[1],dev2,D_stats[1],*maxedges,difftime[1],diffhead[1],difftail[1],*dyninterval,0,0,NULL,NULL,NULL,NULL};
  
  MCMCDynSNR_MT(&t1args,&t2args,F_theta0, 
		 *a, *alpha, *A, *c, *gamma, *iterations,
		 *burnin, *interval,
		 *fVerbose);
  
  MCMCDyn_finish_common(nwp, F_m[0], D_m[0], bd[0], F_MH, D_MH);
  MCMCDyn_finish_common(nwp+2, F_m[1], D_m[1], bd[1], F_MH+1, D_MH+1);

  free(difftime[0]);
  free(difftime[1]);
  free(diffhead[0]);
  free(diffhead[1]);
  free(difftail[0]);
  free(difftail[1]);
  free(D_stats[0]);
  free(D_stats[1]);
  free(dev2);
}


/*********************
 void MCMCDynSNR
*********************/
void MCMCDynSNR_MT(MCMCSampleDynObjective_args *t1args,
		    MCMCSampleDynObjective_args *t2args,
		    double *F_theta, 
		    double a, double alpha, double A, double c, double gamma, unsigned int iterations,
		    unsigned int burnin, unsigned int interval,
		    int fVerbose){


  unsigned int n_par=t1args->F_m->n_stats,
    n_stats=t1args->F_m->n_stats;

  pthread_t t1;

  double F_DobjDtheta, F_D2objDtheta2,
    *delta=malloc(sizeof(double)*n_par),
    objPU,objPD,obj0U,obj0D,
    *F_theta_acc=calloc(n_par,sizeof(double)),
    *F_theta2_acc=calloc(n_par,sizeof(double)),
    *F_theta_sd=calloc(n_par,sizeof(double));

  t1args->F_stats_acc=malloc(sizeof(double)*n_stats);
  t1args->F_stats2_acc=malloc(sizeof(double)*n_stats);
  t1args->F_theta=malloc(sizeof(double)*n_par);
  t1args->obj=&objPU;

  t2args->F_stats_acc=malloc(sizeof(double)*n_stats);
  t2args->F_stats2_acc=malloc(sizeof(double)*n_stats);
  t2args->F_theta=malloc(sizeof(double)*n_par);
  t2args->obj=&objPD;


  int use_var[2]={-20,-20},use_var_old[2];

  t1args->use_var=use_var;
  t2args->use_var=use_var+1;

  // Burn-in
  t1args->burnin=t2args->burnin=burnin;
  t1args->S=t2args->S=interval;
  memcpy(t1args->F_theta,F_theta,n_par*sizeof(double));
  memcpy(t2args->F_theta,F_theta,n_par*sizeof(double));
  pthread_create(&t1,  NULL, MCMCSampleDynObjective_MT, (void *)t1args);
  MCMCSampleDynObjective_MT((void *)t2args);
  
  pthread_join(t1,NULL);

  t1args->burnin=t2args->burnin=interval;
  t1args->S=t2args->S=interval;

  for(unsigned int i=0; i<iterations; i++){
    double gain=a/pow(A+i+1,alpha);
    double diff=c/pow(i+1,gamma);
    
    if(fVerbose){
      Rprintf("\nIteration %d/%d: gain=%f diff=%f\n",i+1,iterations,gain,diff);
      Rprintf("F_theta=[ ");
      for(unsigned int k=0; k<n_par; k++) Rprintf("%f ",F_theta[k]);
      Rprintf("]\n");
    }

    for(unsigned int k=0; k<n_par; k++){
      F_theta_acc[k]+=F_theta[k];
      F_theta2_acc[k]+=F_theta[k]*F_theta[k];
      if(i)
	F_theta_sd[k]=sqrt((F_theta2_acc[k]-F_theta_acc[k]*F_theta_acc[k]/(i+1))/(i+1));
      else
	F_theta_sd[k]=1;
    }

    // Evaluate the objective at theta
    memcpy(t1args->F_theta,F_theta,n_par*sizeof(double));
    memcpy(t2args->F_theta,F_theta,n_par*sizeof(double));
    memcpy(use_var_old,use_var,2*sizeof(int));
    pthread_create(&t1,  NULL, MCMCSampleDynObjective_MT, (void *)t1args);
    MCMCSampleDynObjective_MT((void *)t2args);
    pthread_join(t1,NULL);

    memcpy(use_var,use_var_old,2*sizeof(int));

    obj0U=objPU;
    obj0D=objPD;

    // Generate delta
    if(runif(0,1)<0.5)
      for(unsigned int k=0; k<n_par; k++) delta[k]=rnorm(0,1)*F_theta_sd[k];
    else
      for(unsigned int k=0; k<n_par; k++) delta[k]=rnorm(0,1);
    
    double delta_mag=0;
    for(unsigned int k=0; k<n_par; k++) delta_mag+=delta[k]*delta[k];
    delta_mag=sqrt(delta_mag);

    if(fVerbose) Rprintf("Perturbation direction : [ ");
    for(unsigned int k=0; k<n_par; k++){
      delta[k]/=delta_mag;
      if(fVerbose) Rprintf("%f ", delta[k]);     
    }
    if(fVerbose) Rprintf("]\n");
    
    // Compute theta perturbed "up"
    for(unsigned int k=0; k<n_par; k++){
      t1args->F_theta[k]=F_theta[k]+delta[k]*diff;
    }
    // Evaluate the objective function with theta perturbed "up"
    pthread_create(&t1,  NULL, MCMCSampleDynObjective_MT, (void *)t1args);

    // Concurrently...
    // Compute theta perturbed "down"
    for(unsigned int k=0; k<n_par; k++){
      t2args->F_theta[k]=F_theta[k]-delta[k]*diff;
    }
    // Evaluate the objective function with theta perturbed "down"
    // in the main thread.
    MCMCSampleDynObjective_MT((void *)t2args);

    // Wait for Thread 1 to finish.
    pthread_join(t1,NULL);

    if(use_var[0]==0 && use_var[1]==0){
      if(fVerbose) Rprintf("\n\n\nSwitching to variance-normalized objective function!\n\n\n\n");
    }else if(use_var[0]==0 && use_var[1]<0){
      use_var[0]--;
    }else if(use_var[1]==0 && use_var[0]<0){
      use_var[1]--;
    }

    double objM=(objPD+obj0D+obj0U+objPU)/4;
    if(fVerbose) Rprintf("Observed objective functions: mean=%f and [%f %f %f]\n",objM,objPD-objM,(obj0D+obj0U)/2-objM,objPU-objM);

    // Estimate the gradient, and make the step
    F_DobjDtheta=(objPU-objPD)/diff/2;
    if(fVerbose) Rprintf("Estimated gradient in delta direction: %f\n",F_DobjDtheta);
    F_D2objDtheta2=((objPU-obj0U)/diff - (obj0D-objPD)/diff)/diff;
    if(fVerbose) Rprintf("Estimated hessian in delta direction: %f\n",F_D2objDtheta2);
    if(F_D2objDtheta2<0){
      if(fVerbose) Rprintf("Estimated hessian negative!\n");
      F_D2objDtheta2=+0.00001;
    }

    double stepsize=gain*fmin(fabs(F_DobjDtheta/F_D2objDtheta2),10)*sign(F_DobjDtheta);
    if(fVerbose) Rprintf("Change in F_theta: [");
    for(unsigned int k=0; k<n_par; k++){
      double dF_theta=-stepsize*delta[k];
      if(fVerbose) Rprintf("%f ", dF_theta);
      F_theta[k]=F_theta[k]+dF_theta;
    }
    if(fVerbose){
      Rprintf("]\n");
      Rprintf("F_theta=[ ");
      for(unsigned int k=0; k<n_par; k++) Rprintf("%f ",F_theta[k]);
      Rprintf("]\n");

      Rprintf("mean F_theta=[ ");
      for(unsigned int k=0; k<n_par; k++) Rprintf("%f ",F_theta_acc[k]/(i+1));
      Rprintf("]\n");
    }
  }


  free(t1args->F_stats_acc);
  free(t1args->F_stats2_acc);
  free(t1args->F_theta);

  free(t2args->F_stats_acc);
  free(t2args->F_stats2_acc);
  free(t2args->F_theta);

  free(F_theta_sd);
  free(delta);
}


