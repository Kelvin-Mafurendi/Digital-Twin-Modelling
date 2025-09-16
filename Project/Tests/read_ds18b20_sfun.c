#define S_FUNCTION_NAME read_ds18b20_sfun
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"

// Built-in simulation function - no external dependencies
static float read_ds18b20_temperature_sim(void) {
    static int counter = 0;
    counter++;
    return 25.0f + (counter % 10) * 0.1f;  // 25.0-25.9°C range
}

static void mdlInitializeSizes(SimStruct *S) {
    ssSetNumSFcnParams(S, 0);
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumInputPorts(S, 0);
    ssSetNumOutputPorts(S, 1);
    ssSetOutputPortWidth(S, 0, 1);
    ssSetNumSampleTimes(S, 1);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S) {
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}

static void mdlOutputs(SimStruct *S, int_T tid) {
    real_T *y = ssGetOutputPortRealSignal(S, 0);
    
#ifdef MATLAB_MEX_FILE
    // Simulation mode
    *y = (real_T)read_ds18b20_temperature_sim();
#else
    // Hardware mode - call external function
    extern float read_ds18b20_temperature(void);
    *y = (real_T)read_ds18b20_temperature();
#endif
}

static void mdlTerminate(SimStruct *S) { }

#ifdef MATLAB_MEX_FILE
#include "simulink.c"
#else
#include "cg_sfun.h"
#endif