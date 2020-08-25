/****************************************************************************
 *
 *   Copyright (C) 2014-2020 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * UAVCAN Node ID.
 *
 * Read the specs at http://uavcan.org to learn more about Node ID.
 *
 * @min 1
 * @max 125
 * @group UAVCAN
 */
PARAM_DEFINE_INT32(CANNODE_NODE_ID, 120);

/**
 * UAVCAN CAN bus bitrate.
 *
 * @min 20000
 * @max 1000000
 * @group UAVCAN
 */
PARAM_DEFINE_INT32(CANNODE_BITRATE, 1000000);

/**
 * UAVCANNODE ESC control enable.
 *
 * @reboot_required true
 *
 * @boolean
 * @group UAVCANNODE
 */
PARAM_DEFINE_INT32(CANNODE_ESC_EN, 0);

/**
 * Bitmask which sets the number of ESCs controlled by the cannode. Each
 * bit in the mask corresponds to one of the 8 actuator outputs.
 *
 * eg: cannode controls actuator 1,2,3,4 :: CANNODE_ESC_MASK = 15 (00001111)
 *
 * @min 0
 * @max 255
 * @group UAVCAN
 */
PARAM_DEFINE_INT32(CANNODE_ESC_MASK, 15);


/**
 * Integer which controls mapping of incoming actuator index to
 * the proper output channel.
 *
 * eg: if CANNODE_ESC0_MAP = 5 then RawCommand[0] ==> actuator_output[5]
 *
 * @min 0
 * @max 15
 * @group UAVCAN
 */
PARAM_DEFINE_INT32(CANNODE_ESC0_MAP, 0);
PARAM_DEFINE_INT32(CANNODE_ESC1_MAP, 1);
PARAM_DEFINE_INT32(CANNODE_ESC2_MAP, 2);
PARAM_DEFINE_INT32(CANNODE_ESC3_MAP, 3);
PARAM_DEFINE_INT32(CANNODE_ESC4_MAP, 4);
PARAM_DEFINE_INT32(CANNODE_ESC5_MAP, 5);
PARAM_DEFINE_INT32(CANNODE_ESC6_MAP, 6);
PARAM_DEFINE_INT32(CANNODE_ESC7_MAP, 7);
