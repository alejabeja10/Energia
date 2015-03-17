/*
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  ======== PowerMSP432.h ========
 *
 */

#ifndef ti_drivers_power_PowerMSP432__include
#define ti_drivers_power_PowerMSP432__include

#include <stdint.h>
#include <ti/drivers/ports/ListP.h>

/* driverlib header files */
#include <pcm.h>
#include <cs.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! latency times in microseconds */
#define PowerMSP432_RESUMETIMESLEEP           32
#define PowerMSP432_TOTALTIMESLEEP            8
#define PowerMSP432_RESUMETIMEDEEPSLEEP_0     16
#define PowerMSP432_TOTALTIMEDEEPSLEEP_0      40
#define PowerMSP432_RESUMETIMEDEEPSLEEP_1     16
#define PowerMSP432_TOTALTIMEDEEPSLEEP_1      40

/*! Power resources */
#define PowerMSP432_PERIPH_ADC14              0
#define PowerMSP432_PERIPH_DMA                1
#define PowerMSP432_PERIPH_EUSCI_A0           2
#define PowerMSP432_PERIPH_EUSCI_A1           3
#define PowerMSP432_PERIPH_EUSCI_A2           4
#define PowerMSP432_PERIPH_EUSCI_A3           5
#define PowerMSP432_PERIPH_EUSCI_B0           6
#define PowerMSP432_PERIPH_EUSCI_B1           7
#define PowerMSP432_PERIPH_EUSCI_B2           8
#define PowerMSP432_PERIPH_EUSCI_B3           9
#define PowerMSP432_PERIPH_TIMER_A0           10
#define PowerMSP432_PERIPH_TIMER_A1           11
#define PowerMSP432_PERIPH_TIMER_A2           12
#define PowerMSP432_PERIPH_TIMER_A3           13
#define PowerMSP432_PERIPH_TIMER_T32          14

/*!
 *  @brief  Power constraints for MSP432
 *
 *  Each constraint must be a power of two and must be sequential
 *  without any gaps.
 */
#define PowerMSP432_DISALLOW_SLEEP          0
#define PowerMSP432_DISALLOW_DEEPSLEEP_0    1
#define PowerMSP432_DISALLOW_DEEPSLEEP_1    2
#define PowerMSP432_DISALLOW_SHUTDOWN       3
#define PowerMSP432_DISALLOW_PERFLEVEL_0    4
#define PowerMSP432_DISALLOW_PERFLEVEL_1    5
#define PowerMSP432_DISALLOW_PERFLEVEL_2    6
#define PowerMSP432_DISALLOW_PERFLEVEL_3    7
#define PowerMSP432_DISALLOW_PERFLEVEL_4    8
#define PowerMSP432_NUMCONSTRAINTS          9

/*!
 *  @brief  Power events
 *
 *  Each event must be a power of two and must be sequential
 *  without any gaps.
 */
#define PowerMSP432_ENTERING_SLEEP          0x1
#define PowerMSP432_ENTERING_DEEPSLEEP      0x2
#define PowerMSP432_ENTERING_SHUTDOWN       0x4
#define PowerMSP432_AWAKE_SLEEP             0x8
#define PowerMSP432_AWAKE_DEEPSLEEP         0x10
#define PowerMSP432_START_CHANGE_PERF_LEVEL 0x20
#define PowerMSP432_DONE_CHANGE_PERF_LEVEL  0x40
#define PowerMSP432_NUMEVENTS               7

/*! Power sleep states */
#define PowerMSP432_SLEEP                   0x1
#define PowerMSP432_DEEPSLEEP_0             0x2
#define PowerMSP432_DEEPSLEEP_1             0x4

/*! Power shutdown states */
#define PowerMSP432_SHUTDOWN_0              0x0
#define PowerMSP432_SHUTDOWN_1              0x1

/*! Active states */
#define AM_DCDC_VCORE0        PCM_AM_DCDC_VCORE0
#define AM_DCDC_VCORE1        PCM_AM_DCDC_VCORE1
#define AM_LDO_VCORE0         PCM_AM_LDO_VCORE0
#define AM_LDO_VCORE1         PCM_AM_LDO_VCORE1
#define AM_LF_VCORE0          PCM_AM_LPR_VCORE0
#define AM_LF_VCORE1          PCM_AM_LPR_VCORE1

typedef struct PowerMSP432_PerfLevel {
    unsigned int activeState;
    unsigned int VCORE;
    unsigned int clockSource;
    unsigned int DCORESEL;
    unsigned int DIVM;
    unsigned int DIVHS;
    unsigned int DIVS;
    unsigned int flashWaitStates;
    bool         enableFlashBuffer;
    unsigned int MCLK;
    unsigned int HSMCLK;
    unsigned int SMCLK;
    unsigned int ACLK;
} PowerMSP432_PerfLevel;

typedef struct PowerMSP432_Freqs {
    unsigned int MCLK;
    unsigned int HSMCLK;
    unsigned int SMCLK;
    unsigned int ACLK;
} PowerMSP432_Freqs;

typedef void (*PowerMSP432_SchedDisableFxn)(void);
typedef void (*PowerMSP432_SchedRestoreFxn)(void);
typedef void (*PowerMSP432_UpdateFreqsFxn)(PowerMSP432_Freqs *freqs);

/*! @brief Power global configuration */
typedef struct PowerMSP432_Config {
    Power_PolicyInitFxn policyInitFxn;    /*! Init function for power policy */
    Power_PolicyFxn policyFxn;            /*! The power policy function */
    PowerMSP432_SchedDisableFxn schedDisableFxn; /*! OS scheduler disable fxn */
    PowerMSP432_SchedRestoreFxn schedRestoreFxn; /*! OS scheduler restore fxn */
    PowerMSP432_UpdateFreqsFxn freqsFxn;  /*! OS frequency update function */
    unsigned int initialPerfLevel;        /*! initial performance level */
    bool enablePolicy; /*! Enables power policy function to run in idle loop */
    bool enablePerf;   /*! Enables performance level control */
} PowerMSP432_Config;

/*! Module_State */
typedef struct PowerMSP432_Module_State {
    ListP_List notifyList;
    uint32_t constraintMask;
    unsigned int state;
    unsigned int currentPerfLevel;
    bool enablePolicy;
    bool perfInitialized;
    uint8_t constraintCounts[PowerMSP432_NUMCONSTRAINTS];
} PowerMSP432_Module_State;

/*! default policy init function for config structure */
void PowerMSP432_policyInitFxn(void);

/*! default power policy function for config structure */
void PowerMSP432_policyFxn(void);

/*! default frequency update policy function for config structure */
void PowerMSP432_updateFreqs(PowerMSP432_Freqs *freqs);

/*! default scheduling disable function for config structure */
void PowerMSP432_schedulerDisable(void);

/*! default scheduler restore function for config structure */
void PowerMSP432_schedulerRestore(void);

#define Power_getDependencyCount(resourceId)  0
#define Power_releaseDependency(resourceId)
#define Power_setDependency(resourceId)

#ifdef __cplusplus
}
#endif

#endif /* ti_drivers_PowerMSP432_PowerMSP432__include */
