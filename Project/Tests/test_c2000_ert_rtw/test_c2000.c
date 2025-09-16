/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: test_c2000.c
 *
 * Code generated for Simulink model 'test_c2000'.
 *
 * Model version                  : 2.28
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Tue Sep 16 13:54:40 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "test_c2000.h"
#include "rtwtypes.h"
#include "test_c2000_private.h"

/* Block signals (default storage) */
B_test_c2000_T test_c2000_B;

/* Real-time model */
static RT_MODEL_test_c2000_T test_c2000_M_;
RT_MODEL_test_c2000_T *const test_c2000_M = &test_c2000_M_;

#ifndef __TMS320C28XX_CLA__

uint16_T MW_adcAInitFlag = 0;

#endif

/* Model step function */
void test_c2000_step(void)
{
  /* S-Function (c2802xadc): '<Root>/ADC' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    AdcaRegs.ADCSOCFRC1.bit.SOC0 = 1U;

    /* Wait for the period of Sampling window and EOC result to be latched after trigger */
#ifndef __TMS320C28XX_CLA__

    asm(" RPT #75|| NOP");

#endif

#ifdef __TMS320C28XX_CLA__

    real32_T wait_index;
    for (wait_index= 12; wait_index > 0; wait_index--)
      __mnop();

#endif

    test_c2000_B.ADC = (AdcaResultRegs.ADCRESULT0);
  }

  /* Gain: '<Root>/Gain' */
  test_c2000_B.Gain = 20485L * test_c2000_B.ADC;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.1, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  test_c2000_M->Timing.clockTick0++;
}

/* Model initialize function */
void test_c2000_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)test_c2000_M, 0,
                sizeof(RT_MODEL_test_c2000_T));
  rtmSetTFinal(test_c2000_M, 200.0);

  /* External mode info */
  test_c2000_M->Sizes.checksums[0] = (2960722187U);
  test_c2000_M->Sizes.checksums[1] = (86047731U);
  test_c2000_M->Sizes.checksums[2] = (3060731395U);
  test_c2000_M->Sizes.checksums[3] = (2828814771U);

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
    rteiSetTFinalTicks(test_c2000_M->extModeInfo, 2000);
  }

  /* block I/O */
  (void) memset(((void *) &test_c2000_B), 0,
                sizeof(B_test_c2000_T));
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
