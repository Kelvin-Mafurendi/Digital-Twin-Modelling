/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: test_c2000.c
 *
 * Code generated for Simulink model 'test_c2000'.
 *
 * Model version                  : 2.27
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Tue Sep 16 13:46:31 2025
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
static void rate_monotonic_scheduler(void);

#ifndef __TMS320C28XX_CLA__

uint16_T MW_adcAInitFlag = 0;

#endif

#ifndef __TMS320C28XX_CLA__

uint16_T MW_adcDInitFlag = 0;

#endif

/*
 * Set which subrates need to run this base step (base rate always runs).
 * This function must be called prior to calling the model step function
 * in order to remember which rates need to run this base step.  The
 * buffering of events allows for overlapping preemption.
 */
void test_c2000_SetEventsForThisBaseStep(boolean_T *eventFlags)
{
  /* Task runs when its counter is zero, computed via rtmStepTask macro */
  eventFlags[1] = ((boolean_T)rtmStepTask(test_c2000_M, 1));
}

/*
 *         This function updates active task flag for each subrate
 *         and rate transition flags for tasks that exchange data.
 *         The function assumes rate-monotonic multitasking scheduler.
 *         The function must be called at model base rate so that
 *         the generated code self-manages all its subrates and rate
 *         transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (test_c2000_M->Timing.TaskCounters.TID[1])++;
  if ((test_c2000_M->Timing.TaskCounters.TID[1]) > 149) {/* Sample time: [15.0s, 0.0s] */
    test_c2000_M->Timing.TaskCounters.TID[1] = 0;
  }
}

/* Model step function for TID0 */
void test_c2000_step0(void)            /* Sample time: [0.1s, 0.0s] */
{
  {                                    /* Sample time: [0.1s, 0.0s] */
    rate_monotonic_scheduler();
  }

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

  /* S-Function (c2802xadc): '<Root>/ADC1' */
  {
    /*  Internal Reference Voltage : Fixed scale 0 to 3.3 V range.  */
    /*  External Reference Voltage : Allowable ranges of VREFHI(ADCINA0) = 3.3 and VREFLO(tied to ground) = 0  */
    AdcdRegs.ADCSOCFRC1.bit.SOC0 = 1U;

    /* Wait for the period of Sampling window and EOC result to be latched after trigger */
#ifndef __TMS320C28XX_CLA__

    asm(" RPT #75|| NOP");

#endif

#ifdef __TMS320C28XX_CLA__

    real32_T wait_index;
    for (wait_index= 12; wait_index > 0; wait_index--)
      __mnop();

#endif

    test_c2000_B.ADC1 = (AdcdResultRegs.ADCRESULT0);
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.1, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  test_c2000_M->Timing.clockTick0++;
}

/* Model step function for TID1 */
void test_c2000_step1(void)            /* Sample time: [15.0s, 0.0s] */
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

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 15.0, which is the step size
   * of the task. Size of "clockTick1" ensures timer will not overflow during the
   * application lifespan selected.
   */
  test_c2000_M->Timing.clockTick1++;
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
  test_c2000_M->Sizes.checksums[0] = (1910967596U);
  test_c2000_M->Sizes.checksums[1] = (2603525985U);
  test_c2000_M->Sizes.checksums[2] = (2393139549U);
  test_c2000_M->Sizes.checksums[3] = (2617223481U);

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
