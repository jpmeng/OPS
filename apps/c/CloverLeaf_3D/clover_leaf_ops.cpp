//
// auto-generated by ops.py
//



void ops_init_backend();
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include  "ops_lib_core.h"




#include "data.h"

#include "definitions.h"


void initialise();
void field_summary();
void timestep();
void PdV(int predict);
void accelerate();
void flux_calc();
void advection(int);
void reset_field();




float   g_version = 1.0;
int     g_ibig = 640000;
double  g_small = 1.0e-16;
double  g_big  = 1.0e+21;
int     g_name_len_max = 255 ,
        g_xdir = 1,
        g_ydir = 2,
        g_zdir = 3;

int     number_of_states;

int     CHUNK_LEFT    = 1,
        CHUNK_RIGHT   = 2,
        CHUNK_BOTTOM  = 3,
        CHUNK_TOP     = 4,
        CHUNK_BACK    = 5,
        CHUNK_FRONT   = 6,
        EXTERNAL_FACE = -1;

FILE    *g_out, *g_in;

int     g_cube=1,
        g_sphe=2,
        g_point=3;

state_type * states;

grid_type grid;

field_type field;

int step ;
int advect_x;
int error_condition;
int test_problem;
int profiler_on;
int state_max;
int complete;

int fields[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

double dtold, dt, clover_time, dtinit, dtmin, dtmax, dtrise, dtu_safe, dtv_safe, dtw_safe, dtc_safe,
       dtdiv_safe, dtc, dtu, dtv, dtdiv;


double end_time;
int end_step;
int visit_frequency;
int summary_frequency;
int checkpoint_frequency;
int use_vector_loops;

int jdt, kdt, ldt;

void start();

#include "cloverleaf_ops_vars.h"
#include "profile.cpp"


int main(int argc, const char **argv) {


  ops_init(argc,argv,1);
  ops_init_backend();
  ops_printf(" Clover version %f\n", g_version);



  initialise();


  ops_decl_const2( "g_small",1, "double",&g_small);
  ops_decl_const2( "g_big",1, "double",&g_big);
  ops_decl_const2( "dtc_safe",1, "double",&dtc_safe);
  ops_decl_const2( "dtu_safe",1, "double",&dtu_safe);
  ops_decl_const2( "dtv_safe",1, "double",&dtv_safe);
  ops_decl_const2( "dtw_safe",1, "double",&dtw_safe);
  ops_decl_const2( "dtdiv_safe",1, "double",&dtdiv_safe);
  ops_decl_const2( "field",1, "field_type",&field);
  ops_decl_const2( "grid",1, "grid_type",&grid);
  ops_decl_const2( "states",number_of_states, "state_type",states);
  ops_decl_const2( "number_of_states",1, "int",&number_of_states);
  ops_decl_const2( "g_sphe",1, "int",&g_sphe);
  ops_decl_const2( "g_point",1, "int",&g_point);
  ops_decl_const2( "g_cube",1, "int",&g_cube);
  ops_decl_const2( "dt",1, "double",&dt);

  start();

  double ct0, ct1, et0, et1;
  ops_timers(&ct0, &et0);

  ops_checkpointing_initphase_done();
  while(1) {

    step = step + 1;

    timestep();

    PdV(TRUE);

    accelerate();

    PdV(FALSE);

    flux_calc();

    advection(step);

    ops_dat list[5] = {density1, energy1, xvel1, yvel1, zvel1};

    double tosave[4] = {clover_time, dt, (double)step, (double)advect_x};


    if (step%checkpoint_frequency==0) {
      if(ops_checkpointing_manual_datlist_fastfw_trigger(5, list, 4*sizeof(double), (char*)tosave)) {
        clover_time = tosave[0];
        dt = tosave[1];
        step = (int)tosave[2];
        advect_x = (int)tosave[3];
      }
    }

    reset_field();

    if (advect_x == TRUE) advect_x = FALSE;
    else advect_x = TRUE;

    clover_time = clover_time + dt;

    if(summary_frequency != 0)
      if((step%summary_frequency) == 0)
        field_summary();

    if((clover_time+g_small) > end_time || (step >= end_step)) {
      complete=TRUE;
      field_summary();
      ops_fprintf(g_out,"\n\n Calculation complete\n");
      ops_fprintf(g_out,"\n Clover is finishing\n");
      break;
    }

     if(step == 70) {




     }

  }

  ops_timers(&ct1, &et1);
  if(profiler_on == 1) {
    ops_timing_output(std::cout);

    process_profile();
  }

  ops_printf("\nTotal Wall time %lf\n",et1-et0);
  ops_fprintf(g_out,"\nTotal Wall time %lf\n",et1-et0);

  fclose(g_out);
  ops_exit();
  return 0;
}
