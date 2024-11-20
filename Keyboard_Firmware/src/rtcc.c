//
///**************************************************************************//**
// * @brief RTCC initialization
// *****************************************************************************/
//void rtccSetup(int start_time, int start_date, int alarmh_start, int alarmd_start)
//{
//  // Configure the RTCC settings
//  RTCC_Init_TypeDef rtcc = RTCC_INIT_DEFAULT;
//  rtcc.enable   = false;
//  rtcc.presc = rtccCntPresc_32768;
//  rtcc.cntMode = rtccCntModeCalendar;
//  rtcc.cntWrapOnCCV1 = true;
//
//  // Configure the compare settings
//  RTCC_CCChConf_TypeDef compare = RTCC_CH_INIT_COMPARE_DEFAULT;
//
//  // Turn on the clock for the RTCC
//  CMU_ClockEnable(cmuClock_HFLE, true);
//  CMU_ClockSelectSet(cmuClock_LFE, cmuSelect_LFXO);
//  CMU_ClockEnable(cmuClock_RTCC, true);
//
//  // Initialise RTCC with pre-defined settings
//  RTCC_Init(&rtcc);
//
//  // Set current date and time
//  RTCC_DateSet(start_date);
//  RTCC_TimeSet(start_time);
//
//  // Initialise RTCC compare with a date, the date when interrupt will occur
//  RTCC_ChannelInit(1, &compare);
//  RTCC_ChannelDateSet(1, alarmd_start);
//  RTCC_ChannelTimeSet(1,alarmh_start);
//
//  // Set channel 1 to cause an interrupt
//  RTCC_IntEnable(RTCC_IEN_CC1);
//  NVIC_ClearPendingIRQ(RTCC_IRQn);
//  NVIC_EnableIRQ(RTCC_IRQn);
//
//  // Start counter after all initialisations are complete
//  RTCC_Enable(true);
//}
//
