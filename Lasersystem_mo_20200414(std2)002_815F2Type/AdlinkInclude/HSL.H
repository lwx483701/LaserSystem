/****************************************************************************/
/*  Copyright (c) 1995-2004, ADLink Technology Inc.  All rights reserved.   */
/*                                                                          */
/*  File Name   :   HSL.H		                                            */
/*  Purpose     :   Header file for HSL-init.C module                       */
/*  Date        :   06/25/2004                                              */
/*  Revision    :   2.00                                                    */
/*  Programmer  :   Gilbert Yen	                                            */
/****************************************************************************/

#ifndef HSL_H
#define HSL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "type_def.h"

/****************************************************************************/
/*      Function  Declerations                                              */
/****************************************************************************/
I16 FNTYPE HSL_initial(I16 card_ID);
I16 FNTYPE HSL_close(I16 card_ID);
I16 FNTYPE HSL_auto_start(I16 card_ID, I16 connect_index);
I16 FNTYPE HSL_start(I16 card_ID, I16 connect_index, I16 max_slave_No);
I16 FNTYPE HSL_stop(I16 card_ID, I16 connect_index);
I16 FNTYPE HSL_connect_status(I16 card_ID, I16 connect_index, I16 slave_No, I16 *sts_data);
I16 FNTYPE HSL_slave_live(I16 card_ID, I16 connect_index, I16 slave_No, I16 *live_data);
void FNTYPE HSL_get_irq_channel(I16 card_ID, I16 *irq_no);

I16 FNTYPE HSL_set_timer(I16 card_ID, I16 c1, I16 c2);
I16 FNTYPE HSL_enable_timer_interrupt(I16 card_ID, HANDLE *phEvent);
I16 FNTYPE HSL_disable_timer_interrupt(I16 card_ID);

// DIO
I16 FNTYPE HSL_D_write_output(I16 card_ID, I16 connect_index, I16 slave_No, U32 out_data);
I16 FNTYPE HSL_D_write_channel_output(I16 card_ID, I16 connect_index, I16 slave_No, I16 channel, U16 out_data);
I16 FNTYPE HSL_D_read_input(I16 card_ID, I16 connect_index, I16 slave_No, U32 *in_data);
I16 FNTYPE HSL_D_read_channel_input(I16 card_ID, I16 connect_index, I16 slave_No, I16 channel, U16 *in_data);
I16 FNTYPE HSL_D_read_output(I16 card_ID, I16 connect_index, I16 slave_No, U32 *out_data_in_ram);
I16 FNTYPE HSL_D_read_all_slave_input(I16 card_ID, I16 connect_index, U16 *in_data);
I16 FNTYPE HSL_D_write_all_slave_output(I16 card_ID, I16 connect_index, U16 *out_data);
I16 FNTYPE HSL_D_set_input_logic(I16 card_ID, I16 connect_index, I16 slave_No, I16 input_logic);
I16 FNTYPE HSL_D_set_output_logic(I16 card_ID, I16 connect_index, I16 slave_No, I16 output_logic);

// AIO
I16 FNTYPE HSL_A_start_read(I16 card_ID, I16 connect_index);
I16 FNTYPE HSL_A_stop_read(I16 card_ID, I16 connect_index);
I16 FNTYPE HSL_A_set_signal_range(I16 card_ID, I16 connect_index, I16 slave_No, I16 signal_range);
I16 FNTYPE HSL_A_get_signal_range(I16 card_ID, I16 connect_index, I16 slave_No, I16 *signal_range);
I16 FNTYPE HSL_A_get_input_mode(I16 card_ID, I16 connect_index, I16 slave_No, I16 *mode);
I16 FNTYPE HSL_A_set_last_channel(I16 card_ID, I16 connect_index, I16 slave_No, I16 last_channel);
I16 FNTYPE HSL_A_get_last_channel(I16 card_ID, I16 connect_index, I16 slave_No, I16 *last_channel);
I16 FNTYPE HSL_A_read_input(I16 card_ID, I16 connect_index, I16 slave_No, I16 ai_channel, F64 *ai_data);
I16 FNTYPE HSL_A_write_output(I16 card_ID, I16 connect_index, I16 slave_No, I16 ao_channel, F64 ao_data);
I16 FNTYPE HSL_A_read_output(I16 card_ID, I16 connect_index, I16 slave_No, I16 ao_channel, F64 *ao_data);
I16 FNTYPE HSL_A_sync_rw(I16 card_ID, I16 connect_index, I16 slave_No, I16 ai_channel, F64 *ai_data, I16 ao_channel, F64 ao_data);
I16 FNTYPE HSL_A_get_version(I16 card_ID, I16 connect_index, I16 slave_No, I16 *ver);

#ifdef __cplusplus
}
#endif

#endif
