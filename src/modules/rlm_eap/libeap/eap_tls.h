/*
 * eap_tls.h
 *
 * Version:     $Id$
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * Copyright 2001  hereUare Communications, Inc. <raghud@hereuare.com>
 * Copyright 2003  Alan DeKok <aland@freeradius.org>
 * Copyright 2006  The FreeRADIUS server project
 */
#ifndef _EAP_TLS_H
#define _EAP_TLS_H

RCSIDH(eap_tls_h, "$Id$")
USES_APPLE_DEPRECATED_API	/* OpenSSL API has been deprecated by Apple */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <fcntl.h>
#include <signal.h>

#include <ctype.h>
#include <sys/time.h>
#include <arpa/inet.h>

#ifdef HAVE_UNISTD_H
#  include <unistd.h>
#endif

#include <freeradius-devel/radiusd.h>
#include <freeradius-devel/tls.h>

#include "eap.h"

/*
 *	Externally exported TLS functions.
 */
fr_tls_status_t eap_tls_process(eap_session_t *eap_session);

int	eap_tls_start(eap_session_t *eap_session) CC_HINT(nonnull);
int	eap_tls_success(eap_session_t *eap_session) CC_HINT(nonnull);
int	eap_tls_fail(eap_session_t *eap_session) CC_HINT(nonnull);
int	eap_tls_request(eap_session_t *eap_session) CC_HINT(nonnull);


/* MPPE key generation */
void	eap_tls_gen_mppe_keys(REQUEST *request, SSL *s, char const *prf_label);
void	eap_ttls_gen_challenge(SSL *s, uint8_t *buffer, size_t size);
void	eap_tls_gen_eap_key(RADIUS_PACKET *packet, SSL *s, uint32_t header);

#define BUFFER_SIZE 1024

typedef enum tls_op {
	EAP_TLS_START	= 1,
	EAP_TLS_ACK	= 2,
	EAP_TLS_SUCCESS	= 3,
	EAP_TLS_FAIL	= 4,
	EAP_TLS_ALERT	= 9
} tls_op_t;

#define TLS_HEADER_LEN	  4
#define TLS_HEADER_LENGTH_FIELD_LEN 4

typedef struct tls_data_t {
	uint8_t		flags;
	uint8_t		data[1];
} eap_tls_data_t;

/* EAP-TLS framework */
tls_session_t		*eap_tls_session_init(eap_session_t *eap_session, fr_tls_server_conf_t *tls_conf, bool client_cert);


fr_tls_server_conf_t	*eap_tls_conf_parse(CONF_SECTION *cs, char const *key);

#endif /*_EAP_TLS_H*/
