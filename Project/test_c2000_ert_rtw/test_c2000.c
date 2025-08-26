/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: test_c2000.c
 *
 * Code generated for Simulink model 'test_c2000'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
 * C/C++ source code generated on : Wed Aug 20 12:15:41 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "test_c2000.h"
#include "rtwtypes.h"
#include "test_c2000_private.h"
#include <string.h>

/* Block signals (default storage) */
B_test_c2000_T test_c2000_B;

/* Block states (default storage) */
DW_test_c2000_T test_c2000_DW;

/* Real-time model */
static RT_MODEL_test_c2000_T test_c2000_M_;
RT_MODEL_test_c2000_T *const test_c2000_M = &test_c2000_M_;

/* Model step function */
void test_c2000_step(void)
{
  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  test_c2000_B.PulseGenerator = ((test_c2000_DW.clockTickCounter < 1L) &&
    (test_c2000_DW.clockTickCounter >= 0L));

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  if (test_c2000_DW.clockTickCounter >= 1L) {
    test_c2000_DW.clockTickCounter = 0L;
  } else {
    test_c2000_DW.clockTickCounter++;
  }

  /* S-Function (c280xgpio_do): '<Root>/Digital Output' */
  {
    if (test_c2000_B.PulseGenerator) {
      GpioDataRegs.GPBSET.bit.GPIO34 = 1U;
    } else {
      GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1U;
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   */
  test_c2000_M->Timing.taskTime0 =
    ((time_T)(++test_c2000_M->Timing.clockTick0)) *
    test_c2000_M->Timing.stepSize0;
}

/* Model initialize function */
void test_c2000_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)test_c2000_M, 0,
                sizeof(RT_MODEL_test_c2000_T));
  rtmSetTFinal(test_c2000_M, 10.0);
  test_c2000_M->Timing.stepSize0 = 1.0;

  /* External mode info */
  test_c2000_M->Sizes.checksums[0] = (3265594692U);
  test_c2000_M->Sizes.checksums[1] = (272460554U);
  test_c2000_M->Sizes.checksums[2] = (2916071967U);
  test_c2000_M->Sizes.checksums[3] = (3352128015U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    test_c2000_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(test_c2000_M->extModeInfo,
      &test_c2000_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(test_c2000_M->extModeInfo, test_c2000_M->Sizes.checksums);
    rteiSetTFinalTicks(test_c2000_M->extModeInfo, 10);
  }

  /* block I/O */
  (void) memset(((void *) &test_c2000_B), 0,
                sizeof(B_test_c2000_T));

  /* states (dwork) */
  (void) memset((void *)&test_c2000_DW, 0,
                sizeof(DW_test_c2000_T));

  /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  test_c2000_DW.clockTickCounter = 0L;

  /* Start for S-Function (c280xgpio_do): '<Root>/Digital Output' */
  EALLOW;
  GpioCtrlRegs.GPBMUX1.all &= 0xFFFFFFCFU;
  GpioCtrlRegs.GPBDIR.all |= 0x4U;
  EDIS;
}

/* Model terminate function */
void test_c2000_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
