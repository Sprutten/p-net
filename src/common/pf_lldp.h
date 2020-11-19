/*********************************************************************
 *        _       _         _
 *  _ __ | |_  _ | |  __ _ | |__   ___
 * | '__|| __|(_)| | / _` || '_ \ / __|
 * | |   | |_  _ | || (_| || |_) |\__ \
 * |_|    \__|(_)|_| \__,_||_.__/ |___/
 *
 * www.rt-labs.com
 * Copyright 2018 rt-labs AB, Sweden.
 *
 * This software is dual-licensed under GPLv3 and a commercial
 * license. See the file LICENSE.md distributed with this software for
 * full license information.
 ********************************************************************/

/**
 * @file
 * @brief Periodical transmission outgoing LLDP frames
 *        Reception of incoming LLDP frames
 */

#ifndef PF_LLDP_H
#define PF_LLDP_H

#ifdef __cplusplus
extern "C" {
#endif

#define PF_LLDP_SUBTYPE_MAC              4
#define PF_LLDP_SUBTYPE_LOCALLY_ASSIGNED 7

/**
 * Get list of local ports.
 *
 * This is the list of physical ports on the local interface.
 * The management port is not included.
 *
 * @param net              In:    The p-net stack instance.
 * @param p_list           Out:   List of local ports.
 */
void pf_lldp_get_port_list (pnet_t * net, pf_lldp_port_list_t * p_list);

/**
 * Initialise iterator for iterating over local ports.
 *
 * This iterator may be used for iterating over all physical ports
 * on the local interface. The management port is not included.
 * See pf_lldp_get_next_port().
 *
 * @param net              In:    The p-net stack instance.
 * @param p_iterator       Out:   Port iterator.
 */
void pf_lldp_init_port_iterator (pnet_t * net, pf_port_iterator_t * p_iterator);

/**
 * Get next local port.
 *
 * If no more ports are available, 0 is returned.
 *
 * @param p_iterator       InOut: Port iterator.
 * @return Local port number for next port on local interface.
 *         If no more ports are available, 0 is returned.
 */
int pf_lldp_get_next_port (pf_port_iterator_t * p_iterator);

/**
 * Get time when new information about remote device was received.
 *
 * @param net              In:    The p-net stack instance.
 * @param loc_port_num     In:    Local port number for port directly
 *                                connected to the remote device.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 *                                See pf_lldp_get_port_list().
 * @param p_timestamp_10ms Out:   Time when the LLDP packet with the info
 *                                was first received, in units of
 *                                10 milliseconds with system startup
 *                                as the zero point (as in SNMP sysUpTime).
 *                                Note that if an LLDP packet with identical
 *                                info is received, the timestamp is not
 *                                updated.
 * @return  0 if the operation succeeded.
 *         -1 if an error occurred (no info from remote device received).
 */
int pf_lldp_get_peer_timestamp (
   pnet_t * net,
   int loc_port_num,
   uint32_t * p_timestamp_10ms);

/**
 * Get LLDP port configuration for a port.
 *
 * @param net              InOut: The p-net stack instance
 * @param loc_port_num     In:    Local port number.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 * @param pp_port_cfg      Out:   LLDP port configuration, or NULL if not
 *                                found.
 */
void pf_lldp_get_port_config (
   pnet_t * net,
   int loc_port_num,
   const pnet_lldp_port_cfg_t ** pp_port_cfg);

/**
 * Get Chassis ID of local device.
 *
 * See IEEE 802.1AB-2005 (LLDPv1) ch. 9.5.2 "Chassis ID TLV".
 *
 * @param net              In:    The p-net stack instance.
 * @param p_chassis_id     Out:   Chassis ID of local device.
 */
void pf_lldp_get_chassis_id (pnet_t * net, pf_lldp_chassis_id_t * p_chassis_id);

/**
 * Get Chassis ID for remote device connected to local port.
 *
 * See IEEE 802.1AB-2005 (LLDPv1) ch. 9.5.2 "Chassis ID TLV".
 *
 * @param net              In:    The p-net stack instance.
 * @param loc_port_num     In:    Local port number for port directly
 *                                connected to the remote device.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 *                                See pf_lldp_get_port_list().
 * @param p_chassis_id     Out:   Chassis ID of remote device.
 * @return  0 if the operation succeeded.
 *         -1 if an error occurred (no info from remote device received).
 */
int pf_lldp_get_peer_chassis_id (
   pnet_t * net,
   int loc_port_num,
   pf_lldp_chassis_id_t * p_chassis_id);

/**
 * Get Port ID for local port.
 *
 * See IEEE 802.1AB-2005 (LLDPv1) ch. 9.5.3 "Port ID TLV".
 *
 * @param net              In:    The p-net stack instance.
 * @param loc_port_num     In:    Local port number.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 *                                See pf_lldp_get_port_list().
 * @param p_port_id        Out:   Port ID of local port.
 */
void pf_lldp_get_port_id (
   pnet_t * net,
   int loc_port_num,
   pf_lldp_port_id_t * p_port_id);

/**
 * Get Port ID for remote port.
 *
 * Note that the remote device may have multiple ports. Only the remote
 * port connected to the local port is relevant here.
 *
 * See IEEE 802.1AB-2005 (LLDPv1) ch. 9.5.3 "Port ID TLV".
 *
 * @param net              In:    The p-net stack instance.
 * @param loc_port_num     In:    Local port number for port directly
 *                                connected to the remote device.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 *                                See pf_lldp_get_port_list().
 * @param p_port_id        Out:   Port ID of remote port.
 * @return  0 if the operation succeeded.
 *         -1 if an error occurred (no info from remote device received).
 */
int pf_lldp_get_peer_port_id (
   pnet_t * net,
   int loc_port_num,
   pf_lldp_port_id_t * p_port_id);

/**
 * Get port description for local port.
 *
 * See IEEE 802.1AB-2005 (LLDPv1) ch. 9.5.5 "Port Description TLV".
 *
 * @param net              In:    The p-net stack instance.
 * @param loc_port_num     In:    Local port number.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 *                                See pf_lldp_get_port_list().
 * @param p_port_desc      Out:   Port description of local port.
 */
void pf_lldp_get_port_description (
   pnet_t * net,
   int loc_port_num,
   pf_lldp_port_description_t * p_port_desc);

/**
 * Get port description for remote port.
 *
 * See IEEE 802.1AB-2005 (LLDPv1) ch. 9.5.5 "Port Description TLV".
 *
 * @param net              In:    The p-net stack instance.
 * @param loc_port_num     In:    Local port number for port directly
 *                                connected to the remote device.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 *                                See pf_lldp_get_port_list().
 * @param p_port_desc      Out:   Port description of remote port.
 * @return  0 if the operation succeeded.
 *         -1 if an error occurred (no info from remote device received).
 */
int pf_lldp_get_peer_port_description (
   pnet_t * net,
   int loc_port_num,
   pf_lldp_port_description_t * p_port_desc);

/**
 * Get Management Address for local interface.
 *
 * The management address should usually be the IP address for the local
 * interface the local ports belong to. It could also be the MAC address of
 * the local interface in case no IP address has been assigned.
 *
 * See IEEE 802.1AB-2005 (LLDPv1) ch. 9.5.9 "Management Address TLV".
 *
 * @param net              In:    The p-net stack instance.
 * @param p_man_address    Out:   Management address of local interface.
 */
void pf_lldp_get_management_address (
   pnet_t * net,
   pf_lldp_management_address_t * p_man_address);

/**
 * Get Management Address for remote interface connected to local port.
 *
 * The management address should usually be the IP address for the remote
 * interface the remote port belongs to. It could also be the MAC address of
 * the remote interface in case no IP address has been assigned.
 *
 * Note that the remote device may have multiple interfaces. Only the remote
 * interface connected to the local port is relevant here.
 *
 * See IEEE 802.1AB-2005 (LLDPv1) ch. 9.5.9 "Management Address TLV".
 *
 * @param net              In:    The p-net stack instance.
 * @param loc_port_num     In:    Local port number for port directly
 *                                connected to the remote device.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 *                                See pf_lldp_get_port_list().
 * @param p_man_address    Out:   Management address of remote interface.
 * @return  0 if the operation succeeded.
 *         -1 if an error occurred (no info from remote device received).
 */
int pf_lldp_get_peer_management_address (
   pnet_t * net,
   int loc_port_num,
   pf_lldp_management_address_t * p_man_address);

/**
 * Get ManAddrIfId for local interface.
 *
 * See IEEE 802.1AB-2005 (LLDPv1) ch. 9.5.9 "Management Address TLV".
 *
 * @param net              In:    The p-net stack instance.
 * @param p_man_port_index Out:   Index in IfTable for Management port.
 */
void pf_lldp_get_management_port_index (
   pnet_t * net,
   pf_lldp_management_port_index_t * p_man_port_index);

/**
 * Get ManAddrIfId for remote interface connected to local port.
 *
 * Note that the remote device may have multiple interfaces. Only the remote
 * interface connected to the local port is relevant here.
 *
 * See IEEE 802.1AB-2005 (LLDPv1) ch. 9.5.9 "Management Address TLV".
 *
 * @param net              In:    The p-net stack instance.
 * @param loc_port_num     In:    Local port number for port directly
 *                                connected to the remote device.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 *                                See pf_lldp_get_port_list().
 * @param p_man_port_index Out:   Index in remote IfTable for Management port.
 * @return  0 if the operation succeeded.
 *         -1 if an error occurred (no info from remote device received).
 */
int pf_lldp_get_peer_management_port_index (
   pnet_t * net,
   int loc_port_num,
   pf_lldp_management_port_index_t * p_man_port_index);

/**
 * Get remote station name for remote interface connected to local port.
 *
 * The station name is usually a string, but may also be the MAC address of
 * the remote interface in case no string has been assigned.
 *
 * Note that the remote device may have multiple interfaces. Only the remote
 * interface connected to the local port is relevant here.
 *
 * @param net              In:    The p-net stack instance.
 * @param loc_port_num     In:    Local port number for port directly
 *                                connected to the remote device.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 *                                See pf_lldp_get_port_list().
 * @param p_station_name   Out:   Station name of remote interface.
 * @return  0 if the operation succeeded.
 *         -1 if an error occurred (no info from remote device received).
 */
int pf_lldp_get_peer_station_name (
   pnet_t * net,
   int loc_port_num,
   pf_lldp_station_name_t * p_station_name);

/**
 * Get measured signal delays on local port.
 *
 * If a signal delay was not measured, its value is zero.
 *
 * See IEC CDV 61158-6-10 (PN-AL-Protocol): LLDP_PNIO_DELAY.
 *
 * @param net              In:    The p-net stack instance.
 * @param loc_port_num     In:    Local port number.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 *                                See pf_lldp_get_port_list().
 * @param p_delays         Out:   Measured signal delays on local port.
 */
void pf_lldp_get_signal_delays (
   pnet_t * net,
   int loc_port_num,
   pf_lldp_signal_delay_t * p_delays);

/**
 * Get measured signal delays on remote port.
 *
 * If a signal delay was not measured, its value is zero.
 *
 * See IEC CDV 61158-6-10 (PN-AL-Protocol): LLDP_PNIO_DELAY.
 *
 * @param net              In:    The p-net stack instance.
 * @param loc_port_num     In:    Local port number for port directly
 *                                connected to the remote device.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 *                                See pf_lldp_get_port_list().
 * @param p_delays         Out:   Measured signal delays on remote port.
 * @return  0 if the operation succeeded.
 *         -1 if an error occurred (no info from remote device received).
 */
int pf_lldp_get_peer_signal_delays (
   pnet_t * net,
   int loc_port_num,
   pf_lldp_signal_delay_t * p_delays);

/**
 * Get link status of local port.
 *
 * See IEEE 802.1AB-2005 (LLDPv1) Annex G.2 "MAC/PHY Configuration/Status TLV".
 *
 * @param net              In:    The p-net stack instance.
 * @param loc_port_num     In:    Local port number.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 *                                See pf_lldp_get_port_list().
 * @param p_link_status    Out:   Link status of local port.
 */
void pf_lldp_get_link_status (
   pnet_t * net,
   int loc_port_num,
   pf_lldp_link_status_t * p_link_status);

/**
 * Get link status of remote port.
 *
 * See IEEE 802.1AB-2005 (LLDPv1) Annex G.2 "MAC/PHY Configuration/Status TLV".
 *
 * @param net              In:    The p-net stack instance.
 * @param loc_port_num     In:    Local port number for port directly
 *                                connected to the remote device.
 *                                Valid range: 1 .. N, where N is the total
 *                                number of local ports used by p-net stack.
 *                                See pf_lldp_get_port_list().
 * @param p_link_status    Out:   Link status of remote port.
 * @return  0 if the operation succeeded.
 *         -1 if an error occurred (no info from remote device received).
 */
int pf_lldp_get_peer_link_status (
   pnet_t * net,
   int loc_port_num,
   pf_lldp_link_status_t * p_link_status);

/**
 * Initialize the LLDP component.
 *
 * This function initializes the LLDP component and
 * sends the initial LLDP message.
 * @param net              InOut: The p-net stack instance
 */
void pf_lldp_init (pnet_t * net);

/**
 * Build and send LLDP message on relevant ports.
 * @param net              InOut: The p-net stack instance
 */
void pf_lldp_send (pnet_t * net);

/**
 * Restart LLDP transmission timer and optionally send LLDP frame.
 * @param net              InOut: The p-net stack instance
 * @param send             In: Send LLDP message
 */
void pf_lldp_tx_restart (pnet_t * net, bool send);

/**
 * Receive an LLDP message.
 *
 * Parse LLDP tlv format and store selected information.
 * Trigger alarms if needed.
 * @param net              InOut: The p-net stack instance
 * @param p_frame_buf      In:    The Ethernet frame
 * @param offset           In:    The offset to start of LLDP data
 * @return  0     If the frame was NOT handled by this function.
 *          1     If the frame was handled and the buffer freed.
 */
int pf_lldp_recv (pnet_t * net, pnal_buf_t * p_frame_buf, uint16_t offset);

/************ Internal functions, made available for unit testing ************/

int pf_lldp_generate_alias_name (
   const char * port_id,
   const char * chassis_id,
   char * alias,
   uint16_t len);

#ifdef __cplusplus
}
#endif

#endif /* PF_LLDP_H */
