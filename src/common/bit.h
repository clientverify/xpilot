/* 
 * XPilot NG, a multiplayer space war game.
 *
 * Copyright (C) 1991-2001 by
 *
 *      Bjørn Stabell        <bjoern@xpilot.org>
 *      Ken Ronny Schouten   <ken@xpilot.org>
 *      Bert Gijsbers        <bert@xpilot.org>
 *      Dick Balaska         <dick@xpilot.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef	BIT_H
#define	BIT_H

typedef unsigned char bitv_t;
#define SET_BIT(w, bit)		( (w) |= (bit) )
#define CLR_BIT(w, bit)		( (w) &= ~(bit) )
#define BIT(w, bit)		( (w) & (bit) )
#define TOGGLE_BIT(w, bit)	( (w) ^= (bit) )

#define BITV_SIZE	(8 * sizeof(bitv_t))

// Original Macros
#define _BITV_SIZE		(8 * sizeof(bitv_t))
#define _BITV_DECL(X,N)		bitv_t (X)[((N) + BITV_SIZE - 1) / BITV_SIZE]
#define _BITV_SET(X,N)		((X)[(N) / BITV_SIZE] |= 1 << (N) % BITV_SIZE)
#define _BITV_CLR(X,N)		((X)[(N) / BITV_SIZE] &= ~(1 << (N) % BITV_SIZE))
#define _BITV_ISSET(X,N)	((X)[(N) / BITV_SIZE] & (1 << (N) % BITV_SIZE))
#define _BITV_TOGGLE(X,N)	((X)[(N) / BITV_SIZE] ^= 1 << (N) % BITV_SIZE)

// Klee char array macros
#define KLEE_BITV_DECL(X,N)	bitv_t (X)[(N)]
#define KLEE_BITV_SET(X,N)	((X)[(N)] = 0xFF)
#define KLEE_BITV_CLR(X,N)	((X)[(N)] = 0)
#define KLEE_BITV_ISSET(X,N)	((X)[(N)])
#define KLEE_BITV_TOGGLE(X,N)	((X)[(N)] = (X)[(N)] ? 0 : 0xFF)

//#ifdef KLEE
//
//#define BITV_DECL 	KLEE_BITV_DECL
//#define BITV_SET 	KLEE_BITV_SET
//#define BITV_CLR 	KLEE_BITV_CLR
//#define BITV_ISSET 	KLEE_BITV_ISSET
//#define BITV_TOGGLE 	KLEE_BITV_TOGGLE
//
//#else

#define BITV_DECL 	_BITV_DECL
#define BITV_SET 	_BITV_SET
#define BITV_CLR 	_BITV_CLR
#define BITV_ISSET 	_BITV_ISSET
#define BITV_TOGGLE 	_BITV_TOGGLE

//#endif

#endif
