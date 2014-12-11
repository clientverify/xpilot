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

#ifndef XPCOMMON_H
#define XPCOMMON_H

#define checkdie(cond,msg) {if (!(cond)) {fprintf(stderr,"Condition failed: " #cond ":  %s\n",msg); exit(1);}} /* DJB */

#include "klee.h" /* rcochran */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#ifdef _WINDOWS
# define HAVE_ASSERT_H 1
# define HAVE_CTYPE_H 1
# define HAVE_ERRNO_H 1
# define HAVE_MATH_H 1
# define HAVE_SIGNAL_H 1
# define HAVE_STDARG_H 1
# define HAVE_LIMITS_H 1
# define HAVE_SETJMP_H 1
# define HAVE_STDLIB_H 1
# define HAVE_STRING_H 1
# define HAVE_SYS_STAT_H 1
# define HAVE_SYS_TYPES_H 1
# define HAVE_STRCASECMP 1
# define HAVE_STRNCASECMP 1
# define HAVE_LIBZ 1
#endif

#include <stdio.h>
#ifdef HAVE_STDARG_H
# include <stdarg.h>
#else
# error "ANSI C stdarg.h is needed to compile."
#endif

#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif

#ifdef HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif

#ifdef STDC_HEADERS
# include <stdlib.h>
# include <stddef.h>
#else
# ifdef HAVE_STDLIB_H
#  include <stdlib.h>
# endif
#endif

#ifdef HAVE_STRING_H
# if ! defined STDC_HEADERS && defined HAVE_MEMORY_H
#  include <memory.h>
# endif
# include <string.h>
#endif

#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif

#ifdef HAVE_INTTYPES_H
# include <inttypes.h>
#else
# ifdef HAVE_STDINT_H
#  include <stdint.h>
# endif
#endif

#ifdef HAVE_UNISTD_H
# include <unistd.h>
#endif

#ifdef HAVE_ASSERT_H
# include <assert.h>
#endif

#ifdef HAVE_CTYPE_H
# include <ctype.h>
#endif

#ifdef HAVE_ERRNO_H
# include <errno.h>
#endif

#ifdef HAVE_MATH_H
# include <math.h>
#endif

#ifdef HAVE_SIGNAL_H
# include <signal.h>
#endif

#ifdef TIME_WITH_SYS_TIME
# include <sys/time.h>
# include <time.h>
#else
# ifdef HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif

#ifdef HAVE_FCNTL_H
# include <fcntl.h>
#endif

#ifdef HAVE_FLOAT_H
# include <float.h>
#endif

#ifdef HAVE_LIMITS_H
# include <limits.h>
#endif

#ifdef HAVE_PWD_H
# include <pwd.h>
#endif

#ifdef HAVE_SETJMP_H
# include <setjmp.h>
#endif

#ifdef HAVE_SYS_FILE_H
# include <sys/file.h>
#endif

#ifdef HAVE_SYS_IOCTL_H
# include <sys/ioctl.h>
#endif

#ifdef HAVE_SYS_PARAM_H
# include <sys/param.h>
#endif

#ifdef HAVE_SYS_SELECT_H
# include <sys/select.h>
#endif

#ifdef HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif

#ifdef HAVE_SYS_INTTYPES_H
# include <sys/inttypes.h>
#endif

#ifdef HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif

#ifdef HAVE_ARPA_INET_H
# include <arpa/inet.h>
#endif

#ifdef HAVE_NET_IF_H
# include <net/if.h>
#endif

#ifdef HAVE_NETINET_TCP_H
# include <netinet/tcp.h>
#endif

#ifdef HAVE_NETDB_H
# include <netdb.h>
#endif

/* Platform specific hacks. */

/* SGI hack. */
#ifdef HAVE_BSTRING_H
# include <bstring.h>
#endif

/* System V R4 hacks. */
#ifdef HAVE_SYS_FILIO_H
# include <sys/filio.h>
#endif

#ifdef HAVE_SYS_SOCKIO_H
# include <sys/sockio.h>
#endif

/* Sequent hack. */
#ifdef HAVE_SYS_FCNTL_H
# include <sys/fcntl.h>
#endif

/* Sun hacks. */
#ifdef HAVE_ARPA_NAMESER_H
# include <arpa/nameser.h>
#endif

#ifdef HAVE_RESOLV_H
# include <resolv.h>
#endif

#ifdef HAVE_VALUES_H
# include <values.h>
#endif

/* Evil Windows hacks. Yuck. */
#ifdef _WINDOWS
# include "NT/winNet.h"
  /* need this for printf wrappers. */
# ifdef	_XPILOTNTSERVER_
#  include "../server/NT/winServer.h"
#  include "../server/NT/winSvrThread.h"
extern char *showtime(void);
/*# elif !defined(_XPMONNT_)
#  include "NT/winX.h"
#  include "../client/NT/winClient.h"*/
# endif
static void Win_show_error(char *errmsg);
# include <io.h>
# include <process.h>
# include "NT/winNet.h"
  /* Windows needs specific hacks for sockets: */
# undef close
# define close(x__) closesocket(x__)
# undef ioctl
# define ioctl(x__, y__, z__) ioctlsocket(x__, y__, z__)
# undef read
# define read(x__, y__, z__) recv(x__, y__, z__,0)
# undef write
# define write(x__, y__, z__) send(x__, y__, z__,0)
  /* Windows some more hacks: */
# define getpid() _getpid()
#ifdef _MSC_VER
typedef int socklen_t;
#define inline __inline
#endif
#endif

/* Common XPilot header files. */

#include "version.h"
#include "xpconfig.h"
#include "arraylist.h"
#include "astershape.h"
#include "bit.h"
#include "checknames.h"
#include "click.h"
#include "commonproto.h"
#include "const.h"
#include "error.h"
#include "item.h"
#include "keys.h"     /* DJB */
#include "list.h"
#include "metaserver.h"
#include "net.h"
#include "pack.h"
#include "packet.h"
#include "portability.h"
#include "rules.h"
#include "setup.h"
#include "shipshape.h"
#include "socklib.h"
#include "types.h"
#include "wreckshape.h"
#include "xpmap.h"

#ifdef	SOUND
# include "audio.h"
#endif

static inline double timeval_to_seconds(struct timeval *tvp)
{
    return (double)tvp->tv_sec + tvp->tv_usec * 1e-6;
}

static inline struct timeval seconds_to_timeval(double t)
{
    struct timeval tv;

    tv.tv_sec = (unsigned)t;
    tv.tv_usec = (unsigned)(((t - (double)tv.tv_sec) * 1e6) + 0.5);

    return tv;
}

/* returns 'tv2 - tv1' */
static inline int timeval_sub(struct timeval *tv2,
			      struct timeval *tv1)
{
    int s, us;

    s = tv2->tv_sec - tv1->tv_sec;
    us = tv2->tv_usec - tv1->tv_usec;

    return 1000000 * s + us;
}

typedef enum logschemeloglevel {
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  CRITICAL
} logschemelevel;

#define DEFAULTLOGSCOPE "main"
//#define LOGSCOPE DEFAULTLOGSCOPE
#define LOGSCOPE __FILE__
#define DEFAULTLOGLEVEL INFO
#define LOGLEVEL DEFAULTLOGLEVEL

#define DEBUG(...) {if (LOGLEVEL <= DEBUG) {	\
      fprintf(stderr,"%-20s",LOGSCOPE);		\
      fprintf(stderr,"%-10s","DEBUG");		\
      fprintf(stderr,__VA_ARGS__);		\
    }						\
  }
#define INFO(...) {if (LOGLEVEL <= INFO) {	\
      fprintf(stderr,"%-20s",LOGSCOPE);		\
      fprintf(stderr,"%-10s","INFO");		\
      fprintf(stderr,__VA_ARGS__);		\
    }						\
  }
#define WARNING(...) {if (LOGLEVEL <= WARNING) {	\
      fprintf(stderr,"%-20s",LOGSCOPE);			\
      fprintf(stderr,"%-10s","WARNING");		\
      fprintf(stderr,__VA_ARGS__);			\
    }							\
  }
#define ERROR(...) {if (LOGLEVEL <= ERROR) {	\
      fprintf(stderr,"%-20s",LOGSCOPE);		\
      fprintf(stderr,"%-10s","ERROR");		\
      fprintf(stderr,__VA_ARGS__);		\
    }						\
  }
#define CRITICAL(...) {if (LOGLEVEL <= CRITICAL) {	\
      fprintf(stderr,"%-20s",LOGSCOPE);			\
      fprintf(stderr,"%-10s","CRITICAL");		\
      fprintf(stderr,__VA_ARGS__);			\
    }							\
  }
#define IFDEBUG(x) {if (LOGLEVEL <= DEBUG) {x}}
#define IFINFO(x) {if (LOGLEVEL <= INFO) {x}}
#define IFWARNING(x) {if (LOGLEVEL <= WARNING) {x}}
#define IFERROR(x) {if (LOGLEVEL <= ERROR) {x}}
#define IFCRITICAL(x) {if (LOGLEVEL <= CRITICAL) {x}}

//#ifndef KLEE

static inline double djbwctime(void) {     /* DJB */
  struct timeval tv;     /* DJB */
  gettimeofday(&tv, NULL);     /* DJB */
  return (tv.tv_sec + 1E-6 * tv.tv_usec);     /* DJB */
}     /* DJB */

static inline void djbsleep(double d) {     /* DJB */
  double djbtime = djbwctime();     /* DJB */
  while (djbwctime() < djbtime+d);     /* DJB */
}     /* DJB */

static inline char * djbpackettype2str(int packettype) {     /* DJB */
  switch(packettype) {     /* DJB */
  case PKT_UNDEFINED:    return "PKT_UNDEFINED";     /* DJB */
  case PKT_VERIFY:       return "PKT_VERIFY";     /* DJB */
  case PKT_REPLY:        return "PKT_REPLY";     /* DJB */
  case PKT_PLAY:         return "PKT_PLAY";     /* DJB */
  case PKT_QUIT:         return "PKT_QUIT";     /* DJB */
  case PKT_MESSAGE:      return "PKT_MESSAGE";     /* DJB */
  case PKT_START:        return "PKT_START";     /* DJB */
  case PKT_END:  return "PKT_END";     /* DJB */
  case PKT_SELF:         return "PKT_SELF";     /* DJB */
  case PKT_DAMAGED:      return "PKT_DAMAGED";     /* DJB */
  case PKT_CONNECTOR:    return "PKT_CONNECTOR";     /* DJB */
  case PKT_REFUEL:       return "PKT_REFUEL";     /* DJB */
  case PKT_SHIP:         return "PKT_SHIP";     /* DJB */
  case PKT_ECM:  return "PKT_ECM";     /* DJB */
  case PKT_PAUSED:       return "PKT_PAUSED";     /* DJB */
  case PKT_ITEM:         return "PKT_ITEM";     /* DJB */
  case PKT_MINE:         return "PKT_MINE";     /* DJB */
  case PKT_BALL:         return "PKT_BALL";     /* DJB */
  case PKT_MISSILE:      return "PKT_MISSILE";     /* DJB */
  case PKT_SHUTDOWN:     return "PKT_SHUTDOWN";     /* DJB */
  case PKT_STRING:       return "PKT_STRING";     /* DJB */
  case PKT_DESTRUCT:     return "PKT_DESTRUCT";     /* DJB */
  case PKT_RADAR:        return "PKT_RADAR";     /* DJB */
  case PKT_TARGET:       return "PKT_TARGET";     /* DJB */
  case PKT_KEYBOARD:     return "PKT_KEYBOARD";     /* DJB */
  case PKT_SEEK:         return "PKT_SEEK";     /* DJB */
  case PKT_SELF_ITEMS:   return "PKT_SELF_ITEMS";     /* DJB */
  case PKT_TEAM_SCORE:   return "PKT_TEAM_SCORE";     /* DJB */
  case PKT_PLAYER:       return "PKT_PLAYER";     /* DJB */
  case PKT_SCORE:        return "PKT_SCORE";     /* DJB */
  case PKT_FUEL:         return "PKT_FUEL";     /* DJB */
  case PKT_BASE:         return "PKT_BASE";     /* DJB */
  case PKT_CANNON:       return "PKT_CANNON";     /* DJB */
  case PKT_LEAVE:        return "PKT_LEAVE";     /* DJB */
  case PKT_POWER:        return "PKT_POWER";     /* DJB */
  case PKT_POWER_S:      return "PKT_POWER_S";     /* DJB */
  case PKT_TURNSPEED:    return "PKT_TURNSPEED";     /* DJB */
  case PKT_TURNSPEED_S:  return "PKT_TURNSPEED_S";     /* DJB */
  case PKT_TURNRESISTANCE:       return "PKT_TURNRESISTANCE";     /* DJB */
  case PKT_TURNRESISTANCE_S:     return "PKT_TURNRESISTANCE_S";     /* DJB */
  case PKT_WAR:  return "PKT_WAR";     /* DJB */
  case PKT_MAGIC:        return "PKT_MAGIC";     /* DJB */
  case PKT_RELIABLE:     return "PKT_RELIABLE";     /* DJB */
  case PKT_ACK:  return "PKT_ACK";     /* DJB */
  case PKT_FASTRADAR:    return "PKT_FASTRADAR";     /* DJB */
  case PKT_TRANS:        return "PKT_TRANS";     /* DJB */
  case PKT_ACK_CANNON:   return "PKT_ACK_CANNON";     /* DJB */
  case PKT_ACK_FUEL:     return "PKT_ACK_FUEL";     /* DJB */
  case PKT_ACK_TARGET:   return "PKT_ACK_TARGET";     /* DJB */
  case PKT_SCORE_OBJECT:         return "PKT_SCORE_OBJECT"     /* DJB */;
  case PKT_AUDIO:        return "PKT_AUDIO";     /* DJB */
  case PKT_TALK:         return "PKT_TALK";     /* DJB */
  case PKT_TALK_ACK:     return "PKT_TALK_ACK";     /* DJB */
  case PKT_TIME_LEFT:    return "PKT_TIME_LEFT";     /* DJB */
  case PKT_LASER:        return "PKT_LASER";     /* DJB */
  case PKT_DISPLAY:      return "PKT_DISPLAY";     /* DJB */
  case PKT_EYES:         return "PKT_EYES";     /* DJB */
  case PKT_SHAPE:        return "PKT_SHAPE";     /* DJB */
  case PKT_MOTD:         return "PKT_MOTD";     /* DJB */
  case PKT_LOSEITEM:     return "PKT_LOSEITEM";     /* DJB */
  case PKT_APPEARING:    return "PKT_APPEARING";     /* DJB */
  case PKT_TEAM:         return "PKT_TEAM";     /* DJB */
  case PKT_POLYSTYLE:    return "PKT_POLYSTYLE";     /* DJB */
  case PKT_ACK_POLYSTYLE:        return "PKT_ACK_POLYSTYLE";     /* DJB */
  case PKT_NOT_USED_64:  return "PKT_NOT_USED_64";     /* DJB */
  case PKT_NOT_USED_65:  return "PKT_NOT_USED_65";     /* DJB */
  case PKT_NOT_USED_66:  return "PKT_NOT_USED_66";     /* DJB */
  case PKT_NOT_USED_67:  return "PKT_NOT_USED_67";     /* DJB */
  case PKT_MODIFIERS:    return "PKT_MODIFIERS";     /* DJB */
  case PKT_FASTSHOT:     return "PKT_FASTSHOT";     /* DJB */
  case PKT_THRUSTTIME:   return "PKT_THRUSTTIME";     /* DJB */
  case PKT_MODIFIERBANK:         return "PKT_MODIFIERBANK";     /* DJB */
  case PKT_SHIELDTIME:   return "PKT_SHIELDTIME";     /* DJB */
  case PKT_POINTER_MOVE:         return "PKT_POINTER_MOVE";     /* DJB */
  case PKT_REQUEST_AUDIO:        return "PKT_REQUEST_AUDIO";     /* DJB */
  case PKT_ASYNC_FPS:    return "PKT_ASYNC_FPS";     /* DJB */
  case PKT_TIMING:       return "PKT_TIMING";     /* DJB */
  case PKT_PHASINGTIME:  return "PKT_PHASINGTIME";     /* DJB */
  case PKT_ROUNDDELAY:   return "PKT_ROUNDDELAY";     /* DJB */
  case PKT_WRECKAGE:     return "PKT_WRECKAGE";     /* DJB */
  case PKT_ASTEROID:     return "PKT_ASTEROID";     /* DJB */
  case PKT_WORMHOLE:     return "PKT_WORMHOLE";     /* DJB */
  case PKT_NOT_USED_82:  return "PKT_NOT_USED_82";     /* DJB */
  case PKT_NOT_USED_83:  return "PKT_NOT_USED_83";     /* DJB */
  case PKT_NOT_USED_84:  return "PKT_NOT_USED_84";     /* DJB */
  case PKT_NOT_USED_85:  return "PKT_NOT_USED_85";     /* DJB */
  case PKT_NOT_USED_86:  return "PKT_NOT_USED_86";     /* DJB */
  case PKT_NOT_USED_87:  return "PKT_NOT_USED_87";     /* DJB */
  case PKT_NOT_USED_88:  return "PKT_NOT_USED_88";     /* DJB */
  case PKT_NOT_USED_89:  return "PKT_NOT_USED_89";     /* DJB */
  case PKT_FAILURE:      return "PKT_FAILURE";     /* DJB */
  case PKT_SUCCESS:      return "PKT_SUCCESS";     /* DJB */
  default: return "PKT_DEBRIS";     /* DJB */
  }     /* DJB */
}     /* DJB */
//#endif

static inline char * djbkeytype2str(int keytype) {     /* DJB */
  switch(keytype) {     /* DJB */
  case KEY_DUMMY:       return "KEY_DUMMY";     /* DJB */
  case KEY_LOCK_NEXT:   return "KEY_LOCK_NEXT";     /* DJB */
  case KEY_LOCK_PREV:   return "KEY_LOCK_PREV";     /* DJB */
  case KEY_LOCK_CLOSE:  return "KEY_LOCK_CLOSE";     /* DJB */
  case KEY_CHANGE_HOME: return "KEY_CHANGE_HOME";     /* DJB */
  case KEY_SHIELD:      return "KEY_SHIELD";     /* DJB */
  case KEY_FIRE_SHOT:   return "KEY_FIRE_SHOT";     /* DJB */
  case KEY_FIRE_MISSILE:        return "KEY_FIRE_MISSILE";     /* DJB */
  case KEY_FIRE_TORPEDO:        return "KEY_FIRE_TORPEDO";     /* DJB */
  case KEY_TOGGLE_NUCLEAR:      return "KEY_TOGGLE_NUCLEAR";     /* DJB */
  case KEY_FIRE_HEAT:   return "KEY_FIRE_HEAT";     /* DJB */
  case KEY_DROP_MINE:   return "KEY_DROP_MINE";     /* DJB */
  case KEY_DETACH_MINE: return "KEY_DETACH_MINE";     /* DJB */
  case KEY_TURN_LEFT:   return "KEY_TURN_LEFT";     /* DJB */
  case KEY_TURN_RIGHT:  return "KEY_TURN_RIGHT";     /* DJB */
  case KEY_SELF_DESTRUCT:       return "KEY_SELF_DESTRUCT";     /* DJB */
  case KEY_LOSE_ITEM:   return "KEY_LOSE_ITEM";     /* DJB */
  case KEY_PAUSE:       return "KEY_PAUSE";     /* DJB */
  case KEY_TANK_DETACH: return "KEY_TANK_DETACH";     /* DJB */
  case KEY_TANK_NEXT:   return "KEY_TANK_NEXT";     /* DJB */
  case KEY_TANK_PREV:   return "KEY_TANK_PREV";     /* DJB */
  case KEY_TOGGLE_VELOCITY:     return "KEY_TOGGLE_VELOCITY";     /* DJB */
  case KEY_TOGGLE_CLUSTER:      return "KEY_TOGGLE_CLUSTER";     /* DJB */
  case KEY_SWAP_SETTINGS:       return "KEY_SWAP_SETTINGS";     /* DJB */
  case KEY_REFUEL:      return "KEY_REFUEL";     /* DJB */
  case KEY_CONNECTOR:   return "KEY_CONNECTOR";     /* DJB */
  case KEY_UNUSED_26:   return "KEY_UNUSED_26";     /* DJB */
  case KEY_UNUSED_27:   return "KEY_UNUSED_27";     /* DJB */
  case KEY_UNUSED_28:   return "KEY_UNUSED_28";     /* DJB */
  case KEY_UNUSED_29:   return "KEY_UNUSED_29";     /* DJB */
  case KEY_THRUST:      return "KEY_THRUST";     /* DJB */
  case KEY_CLOAK:       return "KEY_CLOAK";     /* DJB */
  case KEY_ECM: return "KEY_ECM";     /* DJB */
  case KEY_DROP_BALL:   return "KEY_DROP_BALL";     /* DJB */
  case KEY_TRANSPORTER: return "KEY_TRANSPORTER";     /* DJB */
  case KEY_TALK:        return "KEY_TALK";     /* DJB */
  case KEY_FIRE_LASER:  return "KEY_FIRE_LASER";     /* DJB */
  case KEY_LOCK_NEXT_CLOSE:     return "KEY_LOCK_NEXT_CLOSE";     /* DJB */
  case KEY_TOGGLE_COMPASS:      return "KEY_TOGGLE_COMPASS";     /* DJB */
  case KEY_TOGGLE_MINI: return "KEY_TOGGLE_MINI";     /* DJB */
  case KEY_TOGGLE_SPREAD:       return "KEY_TOGGLE_SPREAD";     /* DJB */
  case KEY_TOGGLE_POWER:        return "KEY_TOGGLE_POWER";     /* DJB */
  case KEY_TOGGLE_AUTOPILOT:    return "KEY_TOGGLE_AUTOPILOT";     /* DJB */
  case KEY_TOGGLE_LASER:        return "KEY_TOGGLE_LASER";     /* DJB */
  case KEY_EMERGENCY_THRUST:    return "KEY_EMERGENCY_THRUST";     /* DJB */
  case KEY_TRACTOR_BEAM:        return "KEY_TRACTOR_BEAM";     /* DJB */
  case KEY_PRESSOR_BEAM:        return "KEY_PRESSOR_BEAM";     /* DJB */
  case KEY_CLEAR_MODIFIERS:     return "KEY_CLEAR_MODIFIERS";     /* DJB */
  case KEY_LOAD_MODIFIERS_1:    return "KEY_LOAD_MODIFIERS_1";     /* DJB */
  case KEY_LOAD_MODIFIERS_2:    return "KEY_LOAD_MODIFIERS_2";     /* DJB */
  case KEY_LOAD_MODIFIERS_3:    return "KEY_LOAD_MODIFIERS_3";     /* DJB */
  case KEY_LOAD_MODIFIERS_4:    return "KEY_LOAD_MODIFIERS_4";     /* DJB */
  case KEY_SELECT_ITEM: return "KEY_SELECT_ITEM";     /* DJB */
  case KEY_PHASING:     return "KEY_PHASING";     /* DJB */
  case KEY_REPAIR:      return "KEY_REPAIR";     /* DJB */
  case KEY_TOGGLE_IMPLOSION:    return "KEY_TOGGLE_IMPLOSION";     /* DJB */
  case KEY_REPROGRAM:   return "KEY_REPROGRAM";     /* DJB */
  case KEY_LOAD_LOCK_1: return "KEY_LOAD_LOCK_1";     /* DJB */
  case KEY_LOAD_LOCK_2: return "KEY_LOAD_LOCK_2";     /* DJB */
  case KEY_LOAD_LOCK_3: return "KEY_LOAD_LOCK_3";     /* DJB */
  case KEY_LOAD_LOCK_4: return "KEY_LOAD_LOCK_4";     /* DJB */
  case KEY_EMERGENCY_SHIELD:    return "KEY_EMERGENCY_SHIELD";     /* DJB */
  case KEY_HYPERJUMP:   return "KEY_HYPERJUMP";     /* DJB */
  case KEY_DETONATE_MINES:      return "KEY_DETONATE_MINES";     /* DJB */
  case KEY_DEFLECTOR:   return "KEY_DEFLECTOR";     /* DJB */
  case KEY_UNUSED_65:   return "KEY_UNUSED_65";     /* DJB */
  case KEY_UNUSED_66:   return "KEY_UNUSED_66";     /* DJB */
  case KEY_UNUSED_67:   return "KEY_UNUSED_67";     /* DJB */
  case KEY_UNUSED_68:   return "KEY_UNUSED_68";     /* DJB */
  case KEY_UNUSED_69:   return "KEY_UNUSED_69";     /* DJB */
  case KEY_UNUSED_70:   return "KEY_UNUSED_70";     /* DJB */
  case KEY_UNUSED_71:   return "KEY_UNUSED_71";     /* DJB */
  case NUM_KEYS:	return "NUM_KEYS";     /* DJB */
  default: return "Unknown key!";     /* DJB */
  }     /* DJB */
}     /* DJB */

static inline char * djbensuredirexists(char *dirname) {
  char olddir[2048];
  getcwd(olddir,2048);
  if (chdir(dirname) == -1) {
    if (errno == ENOENT) {
      /* Doesn't exist.  Create it. */
      if (mkdir(dirname,S_IRWXU|S_IRWXG) == -1) {
	perror("Couldn't make frame dir");
	exit(1);
      }
    } else {
      perror("Couldn't chdir:");
      exit(1);
    }
  } else {
    /* chdir worked.  Change back */
    if (chdir(olddir) == -1) {
      perror("Couldn't change back into original dir:");
      exit(1);
    }
  }
}

static inline char * djbplogfilename(int);

char frame_dir[1024];
static inline char * djbgetframedir(int init) {
  static int framenum = 0;
  if (init > 0) {
    framenum = init;
    djbplogfilename(1);
  }
  sprintf(frame_dir,"%s%06d",FRAME_LOGDIR,framenum);
  djbensuredirexists(frame_dir);
  return frame_dir;
}

char custom_frame_dir[1024];
static inline char * djbgetcustomframedir(int framenum) {
  sprintf(custom_frame_dir,"%s%06d",FRAME_LOGDIR,framenum);
  djbensuredirexists(custom_frame_dir);
  return custom_frame_dir;
}

char plog_file[2048];
static inline char * djbplogfilename(int reset) {
  static int packetnum = 0;
  if (reset == 1) {
    packetnum = -1;
  }
  sprintf(plog_file,"%s/%s%d",djbgetframedir(-1),PACKET_LOGFILE,packetnum++);
  //sprintf(plog_file,"%s",PACKET_LOGFILE);
  return plog_file;
}

char klog_file[1024];
static inline char * djbklogfilename(int loops) {
  static keyupdatenum = 0;

  //sprintf(klog_file,"%s/%s%06d",djbgetframedir(-1),KEY_LOGFILE,keyupdatenum++);
  sprintf(klog_file,"%s/%s%06d",djbgetcustomframedir(loops+1),KEY_LOGFILE,keyupdatenum++);
  ////sprintf(klog_file,"%s/%s%06d%s",djbgetframedir(-1),KEY_LOGFILE,keyupdatenum++,"as");
  //sprintf(klog_file,"%s/%s%06d",KEY_LOGDIR,KEY_LOGFILE,keyupdatenum++);
  //sprintf(klog_file,"%s%d",KEY_LOGDIR,keyupdatenum);
  //sprintf(plog_file,"%s",PACKET_LOGFILE);
  return klog_file;
}

#define BYTEWISE_STRING_LL_REV(ll) "0x%02x 0x%02x 0x%02x 0x%02x "	\
  "0x%02x 0x%02x 0x%02x 0x%02x ",				\
    (unsigned char)(ll),					\
    (unsigned char)((ll) >> 8),					\
    (unsigned char)((ll) >> 16),				\
    (unsigned char)((ll) >> 24),				\
    (unsigned char)((ll) >> 32),				\
    (unsigned char)((ll) >> 40),				\
    (unsigned char)((ll) >> 48),				\
    (unsigned char)((ll) >> 56)
#define BYTEWISE_STRING_LD_REV(ld) "0x%02x 0x%02x 0x%02x 0x%02x ",	\
    (unsigned char)(ld),					\
    (unsigned char)((ld) >> 8),					\
    (unsigned char)((ld) >> 16),				\
    (unsigned char)((ld) >> 24)
#define BYTEWISE_STRING_HD_REV(hd) "0x%02x 0x%02x ",		\
    (unsigned char)(hd),					\
    (unsigned char)((hd) >> 8)

#define BYTEWISE_STRING_LL(ll) "0x%02x 0x%02x 0x%02x 0x%02x "	\
  "0x%02x 0x%02x 0x%02x 0x%02x ",				\
    (unsigned char)((ll) >> 56),				\
    (unsigned char)((ll) >> 48),				\
    (unsigned char)((ll) >> 40),				\
    (unsigned char)((ll) >> 32),				\
    (unsigned char)((ll) >> 24),				\
    (unsigned char)((ll) >> 16),				\
    (unsigned char)((ll) >> 8),					\
    (unsigned char)(ll)

#define BYTEWISE_STRING_LD(ld) "0x%02x 0x%02x 0x%02x 0x%02x ",	\
    (unsigned char)((ld) >> 24),				\
    (unsigned char)((ld) >> 16),				\
    (unsigned char)((ld) >> 8),					\
    (unsigned char)(ld)

#define BYTEWISE_STRING_HD(hd) "0x%02x 0x%02x ",		\
    (unsigned char)((hd) >> 8),					\
    (unsigned char)(hd)

#define BYTEWISE_STRING_UD(ud) BYTEWISE_STRING_LD(ud)
#define BYTEWISE_STRING_UC(uc) "0x%02x ",(unsigned char)(uc)

//#define DJBLOGGING

#ifdef DJBLOGGING

#define KLOG(ch,change,ackedloops,ptr,size)				\
  {									\
    int i;								\
    FILE *klogfp = fopen(djbklogfilename(ackedloops),"a");		\
    fprintf(klogfp,"array g_klee_sent_keyv[4] : w32 -> w8 = [");	\
    fprintf(klogfp,BYTEWISE_STRING_LD_REV(0x01));			\
    fprintf(klogfp,"] # Decimal: %d\n",0x01);				\
    fprintf(klogfp,"array last_keyboard_change[8] : w32 -> w8 = [");	\
    fprintf(klogfp,BYTEWISE_STRING_LL_REV((uint64_t)(change)));			\
    fprintf(klogfp,"] # Decimal: %d\n",change);				\
    fprintf(klogfp,"array last_loops[8] : w32 -> w8 = [");		\
    fprintf(klogfp,BYTEWISE_STRING_LL_REV((uint64_t)(ackedloops)));		\
    fprintf(klogfp,"] # Decimal: %d\n",ackedloops);			\
    fprintf(klogfp,"array keyv[%d] : w32 -> w8 = [",size*8);		\
    for (i=0; i<(size*8); i++) {					\
      fprintf(klogfp,BYTEWISE_STRING_UC(BITV_ISSET(ptr,i) ? 0xFF:0x00 ));\
    }									\
    fprintf(klogfp,"]\n");						\
    fclose(klogfp);							\
  }

#define PLOGSTART(c) PLOGSTARTNN(c,rbuf.buf,rbuf.buf)

#define PLOGSTARTARRAY(c,n)						\
  fprintf(plogfp,"array %s[%d] : w32 -> w8 = [ ", #n, (c));

#define PLOGSTARTNN(c,n,m)						\
  FILE *plogfp = fopen(djbplogfilename(0),"a");				\
  char *djbpacketlogvar1 = #n;						\
  char *djbpacketlogvar2 = #m;						\
  int djbpacketbytecounter = c;						\
  fprintf(plogfp,"array %s[%d] : w32 -> w8 = [ ",djbpacketlogvar1,djbpacketbytecounter);
#define PLOGV(t,v) fprintf(plogfp,BYTEWISE_STRING_ ## t(v));
#define PLOGVA(t,v,l)				\
  {						\
    int i;					\
    for (i=0; i<(l); i++) {			\
      PLOGV(t,(v)[i]);				\
    }						\
  }
#define PLOGQ								\
  fprintf(plogfp,"]\n");
#define PLOGQTEMP							\
  {									\
    int i;								\
    fprintf(plogfp,"]\n(query [\n");					\
    for (i=0; i<djbpacketbytecounter; i++) {				\
      fprintf(plogfp,"\t(Eq (Read w8 %d %s) ",i,djbpacketlogvar1);	\
      fprintf(plogfp,"\t(Read w8 %d %s));\n",i,djbpacketlogvar2);	\
    }									\
    fprintf(plogfp,"       ]\n\tfalse)\n");				\
  }
#define PLOGEND {PLOGQ; fclose(plogfp);}

#define PLOG_SELF_ITEMS(m,a)						\
  {									\
    PLOGSTARTNN(NUM_ITEMS,numItems,arr2);				\
    {									\
      int i;								\
      for (i=0; i<NUM_ITEMS; i++) {					\
	if ((m) & (1 << i)) {						\
	  PLOGV(UC,(a)[i]);						\
	} else {							\
	  PLOGV(UC,0);							\
	}								\
      }									\
    }									\
    PLOGQ;								\
    PLOGSTARTARRAY(5, rbuf.buf)						\
    PLOGV(UC, PKT_SELF_ITEMS);						\
    PLOGV(LD, 0);							\
    PLOGQ;								\
    fclose(plogfp);							\
  }
    
#else // DJBLOGGING

#define KLOG(a,b,c,d,e)
#define PLOGSTART(x)
#define PLOGSTARTNN(a,b,c)
#define PLOGV(a,b)
#define PLOGVA(a,b,c)
#define PLOGQ
#define PLOGEND
#define PLOG_SELF_ITEMS(a,b)

#endif  // DJBLOGGING

/* Begin KTest */

typedef struct KTestObject KTestObject;
struct KTestObject {
  char *name;
  struct timeval timestamp;
  unsigned numBytes;
  unsigned char *bytes;
};
  
typedef struct KTest KTest;
struct KTest {
  /* file format version */
  unsigned version; 
    
  unsigned numArgs;
  char **args;

  unsigned symArgvs;
  unsigned symArgvLen;

  unsigned numObjects;
  KTestObject *objects;
};

#define KTEST_VERSION 4
#define KTEST_MAGIC_SIZE 5
#define KTEST_MAGIC "KTEST"

// for compatibility reasons
#define BOUT_MAGIC "BOUT\n"

/***/

static int read_uint32(FILE *f, unsigned *value_out) {
  unsigned char data[4];
  if (fread(data, 4, 1, f)!=1)
    return 0;
  *value_out = (((((data[0]<<8) + data[1])<<8) + data[2])<<8) + data[3];
  return 1;
}

static int write_uint32(FILE *f, unsigned value) {
  unsigned char data[4];
  data[0] = value>>24;
  data[1] = value>>16;
  data[2] = value>> 8;
  data[3] = value>> 0;
  return fwrite(data, 1, 4, f)==4;
}

static int read_uint64(FILE *f, uint64_t *value_out) {
  unsigned char data[8];
  if (fread(data, 8, 1, f)!=1)
    return 0;
  *value_out = (((((((((((( (data[0]<<8) + data[1])<<8) + data[2])<<8) + data[3])<<8) + data[4])<<8) + data[5])<<8) + data[6])<<8) + data[7];
  return 1;
}

static int write_uint64(FILE *f, uint64_t value) {
  unsigned char data[8];
  data[0] = value>>56;
  data[1] = value>>48;
  data[2] = value>>40;
  data[3] = value>>32;
  data[4] = value>>24;
  data[5] = value>>16;
  data[6] = value>> 8;
  data[7] = value>> 0;
  return fwrite(data, 1, 8, f)==8;
}

static int read_string(FILE *f, char **value_out) {
  unsigned len;
  if (!read_uint32(f, &len))
    return 0;
  *value_out = (char*) malloc(len+1);
  if (!*value_out)
    return 0;
  if (fread(*value_out, len, 1, f)!=1)
    return 0;
  (*value_out)[len] = 0;
  return 1;
}

static int write_string(FILE *f, const char *value) {
  unsigned len = strlen(value);
  if (!write_uint32(f, len))
    return 0;
  if (fwrite(value, len, 1, f)!=1)
    return 0;
  return 1;
}

/***/

/* returns the current .ktest file format version */
static unsigned kTest_getCurrentVersion() {
  return KTEST_VERSION;
}

static int kTest_checkHeader(FILE *f) {
  char header[KTEST_MAGIC_SIZE];
  if (fread(header, KTEST_MAGIC_SIZE, 1, f)!=1)
    return 0;
  if (memcmp(header, KTEST_MAGIC, KTEST_MAGIC_SIZE) &&
      memcmp(header, BOUT_MAGIC, KTEST_MAGIC_SIZE))
    return 0;
  return 1;
}

/* return true iff file at path matches KTest header */
static int kTest_isKTestFile(const char *path) {
  FILE *f = fopen(path, "rb");
  int res;

  if (!f)
    return 0;
  res = kTest_checkHeader(f);
  fclose(f);
  
  return res;
}

/* returns 1 on success, 0 on (unspecified) error */
static int kTest_toFile(KTest *bo, const char *path) {
  FILE *f = fopen(path, "wb");
  unsigned i;

  if (!f) 
    goto error;
  if (fwrite(KTEST_MAGIC, strlen(KTEST_MAGIC), 1, f)!=1)
    goto error;
  if (!write_uint32(f, KTEST_VERSION))
    goto error;
      
  if (!write_uint32(f, bo->numArgs))
    goto error;
  for (i=0; i<bo->numArgs; i++) {
    if (!write_string(f, bo->args[i]))
      goto error;
  }

  if (!write_uint32(f, bo->symArgvs))
    goto error;
  if (!write_uint32(f, bo->symArgvLen))
    goto error; 

  if (!write_uint32(f, bo->numObjects))
    goto error;
  for (i=0; i<bo->numObjects; i++) {
    KTestObject *o = &bo->objects[i];
    if (!write_string(f, o->name))
      goto error;
    if (!write_uint64(f, o->timestamp.tv_sec))
      goto error;
    if (!write_uint64(f, o->timestamp.tv_usec))
      goto error;
    if (!write_uint32(f, o->numBytes))
      goto error;
    if (fwrite(o->bytes, o->numBytes, 1, f)!=1)
      goto error;
  }   

  fclose(f);

  return 1;
 error:
  if (f) fclose(f);
  
  return 0;
}

/* returns total number of object bytes */
static unsigned kTest_numBytes(KTest *bo) {
  unsigned i, res = 0;
  for (i=0; i<bo->numObjects; i++)
    res += bo->objects[i].numBytes;
  return res;
}

static void kTest_free(KTest *bo) {
  unsigned i;
  for (i=0; i<bo->numArgs; i++)
    free(bo->args[i]);
  free(bo->args);
  for (i=0; i<bo->numObjects; i++) {
    free(bo->objects[i].name);
    free(bo->objects[i].bytes);
  }
  free(bo->objects);
  free(bo);
}

/* End KTest */

/*
 * Message Hash DB
 */

#define HASHVAL_SIZE_MAX 4

//#define HASHVALSIZE 1
//#define HASHVALMASK 0xff
#define HASHVALSIZE 2
#define HASHVALMASK 0xffff
//#define HASHVALSIZE 4
//#define HASHVALMASK 0xffffffff

#define HASHDEBUG(x)

// Return next/prev index in the circular array 
#define HASHDBNEXT(cur, sz) (((cur) + 1) % (sz))
#define HASHDBPREV(cur, sz) (((cur + sz) - 1) % (sz))

struct hashval {
	uint8_t val[HASHVALSIZE];
	uint32_t size;
};

// hashdb holds a circular array of N vals
struct hashdb {
	int currsize;
	int curridx;
	int hvsize;
	struct hashval **vals;
};

// Print a byte in binary 
static void hashdb_print_byte(FILE* out, uint8_t b) {
	int i;
	uint8_t x = b; 
	for (i=0;i<8;i++)
	{
		if (i%4 == 0) fprintf(out, " ");
		if ((x & 0x01) != 0)
			fprintf(out, "1 ");
		else
			fprintf(out, "0 ");

		x = x >> 1;
	}
}

// Print a byte in binary 
static void hashdb_print_byte_offset(FILE* out, uint8_t b, int offset) {
	int i;
	uint8_t x = b; 
	for (i=0;i<8;i++)
	{
		if (i%4 == 0) fprintf(out, " ");
		if (i==offset) {
			if ((x & 0x01) != 0)
				fprintf(out, "1 ");
			else
				fprintf(out, "0 ");
		} else {
			fprintf(out, ". ");
		}
		x = x >> 1;
	}
}


// Print a hashval
static void hashdb_print_hashval(FILE* out, struct hashval *hv) {
	int i=0;
	for (i=0;i<HASHVALSIZE;i++) {
		hashdb_print_byte(out, hv->val[i]);
	}
}

// Print a hashval
static void hashdb_print_hashval_offset(FILE* out, struct hashval *hv, int offset) {
	int i=0;
	for (i=0;i<HASHVALSIZE;i++) {
		if (offset >= (i*8) && offset < ((i+1)*8)) {
			hashdb_print_byte_offset(out, hv->val[i], offset%8);
		} else {
			hashdb_print_byte_offset(out, hv->val[i], -1);
		}
	}
}


// Print a hashdb
static void hashdb_print_hashdb(FILE* out, struct hashdb *db) {
	fprintf(out, "hashdb 0x%x\n\tsize=%d, currindex=%d\n",
			db, db->currsize, db->curridx);
	fprintf(out, "\n\thash values:");
	int i,nextidx=HASHDBPREV(db->curridx, db->currsize);

	for (i=0;i<db->currsize;i++) {
		if (i%4 == 0) fprintf(out, "\n");
		fprintf(out, "\n\t[%02d] ", nextidx);
		//hashdb_print_hashval_offset(out, db->vals[nextidx], i);
		hashdb_print_hashval(out, db->vals[nextidx]);
		nextidx = HASHDBPREV(nextidx, db->currsize);
	}
	fprintf(out, "\n");


}

// Set a hashval to zero
static void hashdb_clear_hashval(struct hashval *hv) {
	int i;
	for (i=0;i<hv->size;i++) {
		hv->val[i] = 0;
	}
}

// Create a hashval
static struct hashval* hashdb_create_hashval(uint32_t size) {
	struct hashval *hv = (struct hashval*)malloc(sizeof(struct hashval));
	hv->size = size;
	hashdb_clear_hashval(hv);
	return hv;
}

// Delete a hashval
static void hashdb_delete_hashval(struct hashval *hv) {
	free(hv);
}

// Create a hashdb
static struct hashdb* hashdb_create_hashdb(uint32_t size, uint32_t hvsize) {
	struct hashdb *db = (struct hashdb*)malloc(sizeof(struct hashdb));
	db->currsize=size;
	db->hvsize = hvsize;
	db->curridx = 0;
	db->vals = (struct hashval**)malloc(db->currsize * sizeof(struct hashval*));

	int i;
	for (i=0;i<db->currsize;i++) {
		db->vals[i] = hashdb_create_hashval(hvsize);
	}

	return db;
}

// Delete a hashdb
static void hashdb_delete_hashdb(struct hashdb *db) {
	int i;
	for (i=0;i<db->currsize;i++) {
		hashdb_delete_hashval(db->vals[i]);
	}
	free(db);
}

// Compare two hash values, return 0 if equal
static int hashdb_hash_compare(struct hashval *hv1, struct hashval *hv2) {
	if (hv1->size != hv2->size) return -1;

	int i;
	for (i=0;i<hv1->size;++i)
		if (hv1->val[i] != hv2->val[i]) 
			return hv1->val[i]-hv2->val[i];

	return 0;
}

// Increment current index
static void hashdb_increment_index(struct hashdb *db) {
	db->curridx = HASHDBNEXT(db->curridx, db->currsize);
}

// Compute the hash of a given buffer 
static void hashdb_compute_hash(struct hashval *hv, uint8_t *buf, uint32_t size) {

	// The checksum mod 2^32
	uint32_t i,checksum = 0;	

	// Compute rotating checksum of buf
	for (i=0;i<size;i++) {
		checksum = (checksum >> 1) + ((checksum & 1) << ((8*HASHVALSIZE)-1));
		checksum += buf[i];
		// Keep it within bounds
		checksum &= HASHVALMASK; 
	}

	for (i=0;i<HASHVALSIZE;i++)
		hv->val[i] = (uint8_t)(checksum >> (i*8));
}

// Add a summary value to a hashdb, used to reconstruct
static void hashdb_reconstruct_from_summary(struct hashdb *db, 
		struct hashval *summary) {
	// summary = from i=0 to i=N: ith bit of the ith hashval
	uint32_t j, i, nextidx=db->curridx;

	// Zero oldest hashval, it was completed last round
	hashdb_clear_hashval(db->vals[HASHDBPREV(db->curridx,db->currsize)]);

	for (i=0;i<db->hvsize;i++) {
		uint8_t mask = 0x01;
		for (j=0;j<8;j++) {
			nextidx = HASHDBPREV(nextidx, db->currsize);
			if (mask & summary->val[i]) {
				// if jth bit is set...
				db->vals[nextidx]->val[i] |= mask;
			} else {
				// if jth bit is not set...
				db->vals[nextidx]->val[i] &= ~mask;
			}
			mask = mask << 1;
		}
	}
}

// Update the current summary after adding a new message hash
static void hashdb_summarize(struct hashdb *db, struct hashval *summary) {
	// summary = from i=0 to i=N: ith bit of the ith hashval

	if (summary == NULL) return;

	hashdb_clear_hashval(summary);

	uint32_t j, i, nextidx=db->curridx;

	for (i=0;i<db->hvsize;i++) {
		uint8_t mask = 0x01;
		summary->val[i] = 0;
		for (j=0;j<8;j++) {
			nextidx = HASHDBPREV(nextidx, db->currsize);
			summary->val[i] ^= (mask & db->vals[nextidx]->val[i]); 
			mask = mask << 1;
		}
	}
}

// Replace oldest hashval in db with the hash of the new message (buf). 
static void hashdb_add_message(struct hashdb *db, uint8_t *buf, uint32_t size) {
	hashdb_compute_hash(db->vals[db->curridx], buf, size);
}

static void hashdb_test() {
	int i=0,j=0; 
	int message_count=64;
	int message_max_size=1023;
	int message_min_size=128;

	struct hashdb *db = hashdb_create_hashdb(HASHVALSIZE*8,HASHVALSIZE);
	struct hashdb *reconstructed_db = hashdb_create_hashdb(HASHVALSIZE*8,HASHVALSIZE);

	char *buf = malloc(message_max_size+1);

	struct hashval* summary = hashdb_create_hashval(db->hvsize);

	// build hashdb
	for (i=0;i<message_count;i++)
	{

		fprintf(stdout, "\n");
		hashdb_print_hashdb(stdout, db);

		fprintf(stdout, "\ns. hv: ");
		hashdb_summarize(db, summary);
		hashdb_print_hashval(stdout, summary);

		fprintf(stdout, "\n\n");

		fprintf(stdout, "reconstructed_db: \n");
		hashdb_reconstruct_from_summary(reconstructed_db, summary);
		hashdb_print_hashdb(stdout, reconstructed_db);
		hashdb_increment_index(reconstructed_db);

		int size = ((uint32_t)randomMT()+message_min_size) % message_max_size;
		for (j=0;j<size;j++) {
			buf[j] = randomMT();
		}

		hashdb_add_message(db, buf, size);
		hashdb_increment_index(db);

		fprintf(stdout, "\n----------------------------------------\n\n");
	}
	free(buf);
	hashdb_delete_hashdb(db);
	hashdb_delete_hashval(summary);
}

/*
 * KEYV / FRAME ACKING
 */

struct keydbval {
  int type;
  int ID;
  long loopID;
};

struct keydb {
  int kbseq;
  int smseq;
  int arrsize;
  int currsize;
  int curridx;
  struct keydbval *vals;
#ifdef C2S_HASHING
	struct hashdb *hdb;
#endif
};

#define KEYDBARRAYSTARTSIZE 1024
#define KEYDBARRAYSIZEADJ 2

struct keyackmsg {
  int size;
  unsigned char *msg;
};

struct ackedmsg {
  long ID;
  long size;
  struct timeval timestamp;
  unsigned char *msg;
  struct ackedmsg *next;
};

struct ackedmsgdb {
  struct ackedmsg *msghead;
};

static void keydb_init(struct keydb *db) {
  db->arrsize = KEYDBARRAYSTARTSIZE;
  db->currsize = 1;
  db->curridx = 0;
  db->vals = (struct keydbval *)malloc(db->arrsize*sizeof(struct keydbval));
  db->vals[0].type = 0;
  db->vals[0].ID = 0; // This value could be anything.
  db->vals[0].loopID = 0; // This value could be anything.
  db->kbseq = 0;
  db->smseq = 0;
#ifdef C2S_HASHING
	db->hdb = hashdb_create_hashdb(HASHVALSIZE*8,HASHVALSIZE);
#endif
}

static void keydb_print(struct keydb *db) {
  checkdie(db->currsize==0||db->vals[db->curridx].type==0,"Must start w/ row!");
  if (db->currsize == 0) {
    fprintf(stderr,"KeyDB is empty\n");
    return;
  }
  int i;
  for (i=0; i<db->currsize; i++) {
    int idx = (db->curridx+i) % db->arrsize;
    if (db->vals[idx].type == 0) {
      // Row entry
      if (i != 0) {
	fprintf(stderr,"\n");
      }
      fprintf(stderr,"Row:  kbseq=%d (0x%02x)(%d):",db->vals[idx].ID,db->vals[idx].ID,db->vals[idx].loopID);
      if (i != db->currsize-1 
	  && db->vals[(db->curridx+i+1)%db->arrsize].type == 0) {
	fprintf(stderr,"\tNo frames");
      }
    } else if (db->vals[idx].type == 1) {
      fprintf(stderr,"\t%ld(%d)",db->vals[idx].ID,db->vals[idx].loopID);
    } else {
      checkdie(0,"type must be 0 or 1");
    }
  }
  fprintf(stderr,"\n");
}

static void keydb_fixsize(struct keydb *db) {
  checkdie(db->currsize <= db->arrsize,"currsize should never be > arrsize!");
  checkdie(db->currsize==0||db->vals[db->curridx].type==0,"Must start w/ row!");
  if (db->currsize == db->arrsize) {
    //fprintf(stderr,"needs resizing.\n");
    // Resize
    db->arrsize *= KEYDBARRAYSIZEADJ;
    db->vals = (struct keydbval *)realloc(db->vals,
					  db->arrsize*sizeof(struct keydbval));

    // Move the "wrapped" part of the buffer to where it belongs
    int i;
    int numtomove = db->currsize-(db->arrsize/KEYDBARRAYSIZEADJ-db->curridx);
    for (i=0; i<numtomove; i++) {
      int toidx = db->arrsize/KEYDBARRAYSIZEADJ+i;
      db->vals[toidx] = db->vals[i];
    }
  } else {
    //fprintf(stderr,"size was fine.\n");
  }
  checkdie(db->currsize==0||db->vals[db->curridx].type==0,"Must start w/ row!");
}

static long keydb_maxframe(struct keydb *db) {
  int i, idx;
  long maxframe = 0;
  for (i=0; i<db->currsize; i++) {
    idx = (db->curridx+i) % db->arrsize;
    if (db->vals[idx].type == 1 && db->vals[idx].ID > maxframe) {
      maxframe = db->vals[idx].ID;
    }
  }
  return maxframe;
}

static void keydb_addrow(struct keydb *db, long kbseq, long loopID) {
  //keydb_print(db);
  int idx = (db->curridx+db->currsize) % db->arrsize;
  db->vals[idx].type = 0;
  db->vals[idx].ID = kbseq;
  db->vals[idx].loopID = loopID;
  db->currsize++;
  keydb_fixsize(db);
  //keydb_print(db);
  checkdie(db->currsize==0||db->vals[db->curridx].type==0,"Must start w/ row!");
}

static void keydb_addframe(struct keydb *db, long frameID, long loopID) {
  //keydb_print(db);
  checkdie(db->currsize==0||db->vals[db->curridx].type==0,"Must start w/ row!");
  checkdie(frameID>=keydb_maxframe(db),"Out-of-order frame!");
  int idx = (db->curridx+db->currsize) % db->arrsize;
  db->vals[idx].type = 1;
  db->vals[idx].ID = frameID;
  db->vals[idx].loopID = loopID;
  db->currsize++;
  keydb_fixsize(db);
  //keydb_print(db);
  checkdie(db->currsize==0||db->vals[db->curridx].type==0,"Must start w/ row!");
}

static void keydb_poprow(struct keydb *db) {
  // Remove the row entry
  checkdie(db->currsize==0||db->vals[db->curridx].type==0,
	   "Must start with a row!");
  if (db->currsize > 0) {
    db->curridx = (db->curridx+1) % db->arrsize;
    db->currsize--;
  }

  // Remove the frames entries
  while (db->currsize > 0 && db->vals[db->curridx].type == 1) {
    db->curridx = (db->curridx+1) % db->arrsize;
    db->currsize--;
  }
  checkdie(db->currsize==0||db->vals[db->curridx].type==0,"Must start w/ row!");
}

static void keydb_clear(struct keydb *db) {
  while (db->currsize > 0) {
    keydb_poprow(db);
  }
  checkdie(db->currsize==0||db->vals[db->curridx].type==0,"Must start w/ row!");
}

static void keydb_popuntil(struct keydb *db, long kbseq) {
  while (db->currsize > 0 && db->vals[db->curridx].ID < kbseq) {
    keydb_poprow(db);
  }
  checkdie(db->currsize==0||db->vals[db->curridx].type==0,"Must start w/ row!");
}

static struct keyackmsg * keyackmsg_init(int size) {
  struct keyackmsg *kam = (struct keyackmsg *)malloc(sizeof(struct keyackmsg));
  kam->size = size;
  kam->msg = (unsigned char *)malloc(kam->size);

  return kam;
}

static void keyackmsg_print(struct keyackmsg *kam) {
  int flc;
  fprintf(stderr,"Size %d:  ",kam->size);
  for (flc = 0; flc < kam->size; flc++) {
    fprintf(stderr," %02x",kam->msg[flc]);
  }
  fprintf(stderr,"\n");
}

#define UCPTOINT(buf) (((*(buf))<<24) + ((*((buf)+1))<<16) + ((*((buf)+2))<<8) + (*((buf)+3)))

#define INTTOUCP(buf,n) {\
    (buf)[0] = (unsigned char)((n) >> 24);	\
    (buf)[1] = (unsigned char)((n) >> 16);	\
    (buf)[2] = (unsigned char)((n) >> 8);	\
    (buf)[3] = (unsigned char)(n);		\
}

static void ackedmsg_print(struct ackedmsg *am) {
  int flc;
  fprintf(stderr,"\tackedmsg (%d) size %d:",am->ID,am->size);
  for (flc=0; flc<am->size; flc++) {
    fprintf(stderr,"  %02x",am->msg[flc]);
  }
  fprintf(stderr,"\n");
}

static void printbuffer(unsigned char *buf, int len) {
  assert(buf != NULL);
  fprintf(stderr,"Buffer, len: %d (0x%x):\n         ",len,len);
  int flc;
  for (flc=0; flc<len; flc++) {
    fprintf(stderr," %02x",buf[flc]);
    if ((flc+1) % 10 == 0) {
      fprintf(stderr," ");
    }
    if ((flc+1) % 50 == 0) {
      fprintf(stderr,"\n         ");
    }
  }
  fprintf(stderr,"\n");
}

static void printbitbuffer(unsigned char *buf, int len) {
  assert(buf != NULL);
  fprintf(stderr,"Bit buffer, len: %d (0x%x):\n         ",len,len);
  int flc;
  for (flc=0; flc<len; flc++) {
    if (BITV_ISSET(buf,flc)) {
      fprintf(stderr,"1");
    } else {
      fprintf(stderr,"0");
    }
    if ((flc+1) % 2 == 0) {
      fprintf(stderr," ");
    }
    if ((flc+1) % 8 == 0) {
      fprintf(stderr,"   ");
    }
    if ((flc+1) % 32 == 0) {
      fprintf(stderr,"\n         ");
    }
  }
  fprintf(stderr,"\n");
}

static struct keyackmsg * keydb_makemsg(struct keydb *db) {
  DEBUG("Making ACK msg...\n");
  int i, idx;
  long kbseq0, smseq0, cloop0;
  long kbseq, smseq, cloop;

  // Sanity checks
  checkdie(db->currsize>0,"kdb must be non-empty to makemsg");
  checkdie(db->currsize==0||db->vals[db->curridx].type==0,
	   "Must start with a row!");

  // Set starting values
  kbseq0 = db->vals[db->curridx].ID;
  cloop0 = db->vals[db->curridx].loopID;
  smseq0 = 0;
  for (i=0; i<db->currsize; i++) {
    idx = (db->curridx+i) % db->arrsize;
    if (db->vals[idx].type == 1) {
      smseq0 = db->vals[idx].ID;
      break;
    }
  }
  int acksize = 4*4*8; // For kbseq, smseq, cloop.  3 values, 4 bytes, 8 bits
  int offset = acksize;

  // Get size
  kbseq = kbseq0;
  smseq = smseq0;
  cloop = cloop0;
  DEBUG("Making message that starts with (%d,%d,%d)\n",kbseq,smseq,cloop);
  DEBUG("DB is size %d\n",db->currsize);

  for (i=0; i<db->currsize; i++) {
    idx = (db->curridx+i) % db->arrsize;
    struct keydbval kv = db->vals[idx];

    checkdie(kv.loopID>=cloop,"Loops out of order?!");
    while (kv.loopID > cloop) {
      cloop++;
      acksize += 2;
    }
    if (kv.type == 0) {
      acksize += 2;
    } else if (kv.type == 1) {
      checkdie(kv.ID>=smseq,"Out of order frames");
      while (kv.ID > smseq) {
	smseq++;
	acksize += 2;
      }
      smseq++;
      acksize += 2;
    }
  }
  DEBUG("acksize = %d\n",acksize);
  
  struct keyackmsg *kam = keyackmsg_init((acksize+7)/8);
  memset(kam->msg,0,(acksize+7)/8);
  unsigned char *buf = kam->msg;
  INTTOUCP(buf,kbseq0);
  buf += 4;
  INTTOUCP(buf,smseq0);
  buf += 4;
  INTTOUCP(buf,cloop0);
  buf += 4;
  INTTOUCP(buf,acksize);
  buf += 4;

  IFDEBUG(printbitbuffer(kam->msg,acksize);)
  kbseq = kbseq0;
  smseq = smseq0;
  cloop = cloop0;
  int currbit = 0;
  for (i=0; i<db->currsize; i++) {
    checkdie(acksize < 1024,"ACK grew too large!");
    idx = (db->curridx+i) % db->arrsize;
    struct keydbval kv = db->vals[idx];
    DEBUG("kv.type,kv.ID,kv.cliloopID = %d,%d,%d\n",kv.type,kv.ID,kv.loopID);
    DEBUG("k,s,c = (%d,%d,%d)\n",kbseq,smseq,cloop);

    checkdie(kv.loopID>=cloop,"Loops out of order?!");
    while (kv.loopID > cloop) {
      DEBUG("\t\tloop.\t\t0 0\n");
      BITV_CLR(buf,currbit);
      BITV_CLR(buf,currbit+1);
      currbit += 2;      
      cloop++;
    }
    if (kv.type == 0) {
      DEBUG("\t\trow.\t\t1 1\n");
      BITV_SET(buf,currbit);
      BITV_SET(buf,currbit+1);
      currbit += 2;      
    } else if (kv.type == 1) {
      checkdie(kv.ID>=smseq,"Out of order frames");
      while (kv.ID > smseq) {
	DEBUG("\t\tmissed frame.\t0 1\n");
	BITV_CLR(buf,currbit);
	BITV_SET(buf,currbit+1);
	currbit += 2;      
	smseq++;
      }
      DEBUG("\t\tnormal frame.\t1 0\n");
      BITV_SET(buf,currbit);
      BITV_CLR(buf,currbit+1);
      currbit += 2;      
      smseq++;
    }
  }
  IFDEBUG(printbuffer(kam->msg,kam->size);)
  IFDEBUG(printbitbuffer(kam->msg,acksize);)
  return kam;
}

static void keydb_loadfrommsg(struct keydb *db, struct keyackmsg *kam) {
  int i,k,s,c,acksize;
  unsigned char *buf = kam->msg;
  k = UCPTOINT(buf);
  buf += 4;
  s = UCPTOINT(buf);
  buf += 4;
  c = UCPTOINT(buf);
  buf += 4;
  acksize = UCPTOINT(buf);
  buf += 4;
  int offset = 4*4*8;

  DEBUG("vals are %d,%d,%d\n",k,s,c);
  int cb = 0;
  keydb_clear(db);

  IFDEBUG(printbitbuffer(buf,acksize-offset);)
  for (i=0; i<acksize-offset; i+=2) {
    if (BITV_ISSET(buf,i)) {
      if (BITV_ISSET(buf,i+1)) {
	DEBUG("row\t\t%d,%d,%d\n",k,s,c);
	keydb_addrow(db,k,c);
	k++;
      } else {
	DEBUG("normal frame\t%d,%d,%d\n",k,s,c);
	keydb_addframe(db,s,c);
	s++;
      }
    } else {
      if (BITV_ISSET(buf,i+1)) {
	DEBUG("missed frame\t%d,%d,%d\n",k,s,c);
	s++;
      } else {
	DEBUG("loop\t\t%d,%d,%d\n",k,s,c);
	c++;
      }
    }
  }
}

static void keydb_freemsg(struct keyackmsg *kam) {
  free(kam->msg);
  free(kam);
}

static bool keydb_equal(struct keydb *db1, struct keydb *db2) {
  if (db1->currsize != db2->currsize) {
    return false;
  }

  int i, idx1, idx2;
  for (i=0; i<db1->currsize; i++) {
    idx1 = (db1->curridx+i) % db1->arrsize;
    idx2 = (db2->curridx+i) % db2->arrsize;

    if (db1->vals[idx1].type != db2->vals[idx2].type
	|| db1->vals[idx1].ID != db2->vals[idx2].ID
	|| db1->vals[idx1].loopID != db2->vals[idx2].loopID) {
      return false;
    }
  }
  return true;
}

// Merge info from db2 into db1
static struct keydb keydb_mergeinto(struct keydb *db1, struct keydb *db2) {
  int *ileft;
  struct keydb *dbleft;
  int i1=0, i2=0, idx, idx1, idx2;
  
  struct keydb out;
  keydb_init(&out);
  keydb_clear(&out);
  out.kbseq = (db1->kbseq > db2->kbseq) ? db1->kbseq : db2->kbseq;
  out.smseq = (db1->smseq > db2->smseq) ? db1->smseq : db2->smseq;

  while (true) {
    // Check for end of both db's
    if (i1 == db1->currsize && i2 == db2->currsize) {
      //fprintf(stderr,"Both are now empty.  Exiting.\n");
      return out;
    }

    // Check for end of just one db
    if (i1 == db1->currsize || i2 == db2->currsize) {
      //fprintf(stderr,"Just one's empty now.\n");
      if (i1 == db1->currsize) {
	ileft = &i2;
	dbleft = db2;
      } else {
	ileft = &i1;
	dbleft = db1;
      }
      while (*ileft < dbleft->currsize) {
	idx = (dbleft->curridx+*ileft) % dbleft->arrsize;
	if (dbleft->vals[idx].type == 0) {
	  keydb_addrow(&out,dbleft->vals[idx].ID,dbleft->vals[idx].loopID);
	} else if (dbleft->vals[idx].type == 1) {
	  keydb_addframe(&out,dbleft->vals[idx].ID,dbleft->vals[idx].loopID);
	} else {
	  checkdie(0,"type must be 0 or 1");
	}
	*ileft = *ileft+1;
      }
      return out;
    }

    // Neither db is ended.  

    //fprintf(stderr,"Neither is empty yet.\n");
    idx1 = (db1->curridx+i1) % db1->arrsize;
    idx2 = (db2->curridx+i2) % db2->arrsize;
    /* This is very ID-based, without much regard for loopID.  Might 
       need to resolve that... */
    if (db1->vals[idx1].ID != db2->vals[idx2].ID) {
      //fprintf(stderr,"Head rows are different.\n");
      // The head rows are different.  Read and add the smallest row.
      if (db1->vals[idx1].ID < db2->vals[idx2].ID) {
	ileft = &i1;
	dbleft = db1;
      } else {
	ileft = &i2;
	dbleft = db2;
      }

      // Add the row
      idx = (dbleft->curridx+*ileft) % dbleft->arrsize;
      keydb_addrow(&out,dbleft->vals[idx].ID,dbleft->vals[idx].loopID);
      *ileft = *ileft+1;
      idx = (dbleft->curridx+*ileft) % dbleft->arrsize;
      // Add the frames
      while (*ileft != dbleft->currsize && dbleft->vals[idx].type != 0) {
	keydb_addframe(&out,dbleft->vals[idx].ID,dbleft->vals[idx].loopID);
	*ileft = *ileft+1;
	idx = (dbleft->curridx+*ileft) % dbleft->arrsize;
      }
    } else {
      //fprintf(stderr,"Head rows are the same.\n");
      // The head rows are the same.  Add one.
      idx1 = (db1->curridx+i1) % db1->arrsize;
      keydb_addrow(&out,db1->vals[idx1].ID,db1->vals[idx1].loopID);
      i1++;
      i2++;

      // Merge the frames.
      while (true) {
	// Check for end of both frame lists.
	idx1 = (db1->curridx+i1) % db1->arrsize;
	idx2 = (db2->curridx+i2) % db2->arrsize;
	if ((i1 == db1->currsize || db1->vals[idx1].type == 0)
	    && (i2 == db2->currsize || db2->vals[idx2].type == 0)) {
	  //fprintf(stderr,"\tBoth frame lists are empty.\n");
	  break;
	}

	// Check for end of just one frame list
	if ((i1 == db1->currsize || db1->vals[idx1].type == 0)
	    || (i2 == db2->currsize || db2->vals[idx2].type == 0)) {
	  //fprintf(stderr,"\tOne frame list is empty.\n");
	  if (i1 == db1->currsize || db1->vals[idx1].type == 0) {
	    ileft = &i2;
	    dbleft = db2;
	  } else {
	    ileft = &i1;
	    dbleft = db1;
	  }
	  idx = (dbleft->curridx+*ileft) % dbleft->arrsize;
	  while (*ileft != dbleft->currsize && dbleft->vals[idx].type != 0) {
	    keydb_addframe(&out,dbleft->vals[idx].ID,dbleft->vals[idx].loopID);
	    *ileft = *ileft+1;
	    idx = (dbleft->curridx+*ileft) % dbleft->arrsize;
	  }
	  break;
	}
	
	// Neither frame list has ended
	//fprintf(stderr,"\tNeither frame list is empty.\n");
	idx1 = (db1->curridx+i1) % db1->arrsize;
	idx2 = (db2->curridx+i2) % db2->arrsize;
	//fprintf(stderr,"\t\ti1 = %d, i2 = %d, ID1 = %d, ID2 = %d\n",
	//       i1,i2,db1->vals[idx1].ID,db2->vals[idx2].ID);
	if (db1->vals[idx1].ID != db2->vals[idx2].ID) {
	  //fprintf(stderr,"\tFrame ID's don't match\n");
	  // Frame ID's don't match.  Add the smaller.
	  if (db1->vals[idx1].ID < db2->vals[idx2].ID) {
	    ileft = &i1;
	    dbleft = db1;
	    //fprintf(stderr,"\t\t1<2\n");
	  } else {
	    ileft = &i2;
	    dbleft = db2;
	    //fprintf(stderr,"\t\t2<1\n");
	  }
	  idx = (dbleft->curridx+*ileft) % dbleft->arrsize;
	  keydb_addframe(&out,dbleft->vals[idx].ID,dbleft->vals[idx].loopID);
	  //fprintf(stderr,"\t\ti1 = %d, i2 = %d, *ileft = %d\n",i1,i2,*ileft);
	  *ileft = *ileft+1;
	  //fprintf(stderr,"\t\ti1 = %d, i2 = %d, *ileft = %d\n",i1,i2,*ileft);
	} else {
	  //fprintf(stderr,"\tFrame ID's match\n");
	  // Frame ID's match.  Add.
	  keydb_addframe(&out,db1->vals[idx1].ID,db1->vals[idx1].loopID);
	  i1++;
	  i2++;
	}
      }
    }
  }
  //keydb_print(&out);
  //exit(1);
}

static void ackedmsgdb_init(struct ackedmsgdb *amdb) {
  amdb->msghead = NULL;
}

static void ackedmsgdb_addmsg(struct ackedmsgdb *amdb, long ID, long size, unsigned char *msg) {
  // Create new ackedmsg
  struct ackedmsg *newmsg = (struct ackedmsg *)malloc(sizeof(struct ackedmsg));
  newmsg->ID = ID;
  newmsg->size = size;

  gettimeofday(&(newmsg->timestamp), NULL);

  newmsg->msg = (unsigned char *)malloc(size);
  int flc;
  for (flc=0; flc<size; flc++) {
    newmsg->msg[flc] = msg[flc];
  }
  newmsg->next = NULL;

  // Add to db
  struct ackedmsg *am = amdb->msghead;
  if (am == NULL) {
    // This is the first ackedmsg.
    amdb->msghead = newmsg;
  } else {
    // This is not the first ackedmsg.  Find where to insert.
    while (am->next != NULL && am->next->ID < ID) {
      am = am->next;
    }
    // Now either am is last or am->next->ID >= ID
    checkdie(am->next == NULL || am->next->ID != ID,"Can't re-insert msg");
    // Now either am is last or am->next->ID > ID
    newmsg->next = am->next;
    am->next = newmsg;
  }
}

static struct ackedmsg * ackedmsgdb_popmsg(struct ackedmsgdb *amdb, int ID) {
  struct ackedmsg *p = amdb->msghead;
  struct ackedmsg *out;

  // amdb empty
  if (p == NULL) {
    return NULL;
  }

  if (p->ID == ID) {
    // ID is the first entry
    amdb->msghead = p->next;
    return p;
  }

  // Search for ID.
  while (p->next != NULL) {
    if (p->next->ID == ID) {
      // Pop this element
      out = p->next;
      // ID is the last element
      if (p->next->next == NULL) {
	p->next = NULL;
      } else {
	p->next = p->next->next;
      }
      return out;
    }
    p = p->next;
  }

  // Didn't find it.
  return NULL;
}

static void ackedmsg_free(struct ackedmsg *am) {
  free(am->msg);
  free(am);
}

static void ackedmsgdb_print(struct ackedmsgdb *amdb) {
  struct ackedmsg *am = amdb->msghead;
  fprintf(stderr,"Acked msg db:\n");
  while (am != NULL) {
    ackedmsg_print(am);
    am = am->next;
  }
}

static int keydb_sizeof(struct keydb *kdb) {
  return kdb->currsize;
}

static int keydb_srvhandlerecv(unsigned char *bigbuf, unsigned char *buf, 
		int len, struct keydb *db, struct ackedmsgdb *amdb) {

  if (len == 0) {
    return 0;
  }

	unsigned char *bigbufptr = bigbuf;

  // Read the kbseq
	long kbseq = UCPTOINT(bigbufptr);
  db->kbseq = kbseq;  // Update last-seen kbseq
  INFO("\tGOT kbseq = %d\n",kbseq);
	bigbufptr += 4;

#ifdef C2S_HASHING
	// Skip the hash summary (not used by the server)
	bigbufptr += HASHVALSIZE;

	// Skip the message hash (not used by the server)
	bigbufptr += HASHVALSIZE;
#endif

	// Read the ack length and init keyackmsg
	struct keyackmsg *kam = keyackmsg_init(UCPTOINT(bigbufptr));
	bigbufptr += 4;

	// Copy the ack message body 
	memcpy(kam->msg, bigbufptr, kam->size);
	bigbufptr += kam->size;

  // Merge the ack
  struct keydb inkdb;
  keydb_init(&inkdb);
  keydb_loadfrommsg(&inkdb,kam);
  *db = keydb_mergeinto(db,&inkdb);

  // Copy the packet
	int buf_len = len - (bigbufptr - bigbuf);
	memcpy(buf, bigbufptr, buf_len);
  keydb_freemsg(kam);

  // Log this message
  //fprintf(stderr,"buf is:\t");
	//printbuffer(buf, buf_len);
  //fprintf(stderr,"bigbuf is:\t");
  //printbuffer(bigbuf,len);
  DEBUG("Logging this msg.  amdb now:\n");
  //ackedmsgdb_print(amdb);
  ackedmsgdb_addmsg(amdb,kbseq,len,bigbuf);
  DEBUG("After logging this msg.  amdb now:\n");
  //ackedmsgdb_print(amdb);

#ifndef KLEE
#ifndef NUKLEAR
#ifdef DJB_NETLOG
  FILE *logfp = fopen(SERVER_LOGFILE,"a");
  fprintf(logfp,"MSGINFO %f c2s %d %d\n", djbwctime(), len, buf_len);
  fclose(logfp);
#endif
#endif
#endif

	return buf_len;
}

static unsigned char * keydb_clihandlesend(unsigned char *buf, 
		int len, int *bigbuflen, int *retlen, 
		struct keydb *db, long cliloopID) {

  // Update db
  (db->kbseq)++;
  keydb_addrow(db,db->kbseq,cliloopID);

  // Make kbseq
  unsigned char kbseqbuf[4];
  INTTOUCP(kbseqbuf,db->kbseq);

  // Make ack length
  unsigned char acklen[4];
  struct keyackmsg *kam = keydb_makemsg(db);
  INTTOUCP(acklen,kam->size);

#ifdef C2S_HASHING
	// Get hashval length
	int32_t hv_len = db->hdb->hvsize;

	// Alloc a hashval for the summary
	struct hashval* summary_hv = hashdb_create_hashval(db->hdb->hvsize);

	// Create summary of current hashdb 
	hashdb_summarize(db->hdb, summary_hv);

	// Alloc a hashval for the message hash 
	struct hashval* msg_hv = hashdb_create_hashval(db->hdb->hvsize);

	// Compute message hash
	hashdb_compute_hash(msg_hv, buf, len);
#endif

	// Compute length of prefix
	int message_len = 
		4 +						/* kb sequence number (db->kbseq) */
#ifdef C2S_HASHING
		hv_len +	    /* message hash summary (summary_hv) */
		hv_len +	    /* message hash (msg_hv) */
#endif
		4 +						/* ack message length number (kam->size) */
		kam->size +   /* ack message (kam->msg) */
		len; 					/* original message buffer (buf) */

	// Allocate larger buffer
	unsigned char *bigbuf = (unsigned char *)malloc(message_len);

	// Write to larger buffer
	unsigned char *bigbufptr = bigbuf; /* track position in buffer */
	memcpy(bigbufptr, kbseqbuf, 4);				 	           bigbufptr += 4;
#ifdef C2S_HASHING
	memcpy(bigbufptr, &(summary_hv->val[0]),  hv_len); bigbufptr += hv_len;
	memcpy(bigbufptr, &(msg_hv->val[0]),  hv_len);     bigbufptr += hv_len;
#endif
	memcpy(bigbufptr, acklen,   4);			 	 	           bigbufptr += 4;
	memcpy(bigbufptr, kam->msg, kam->size);            bigbufptr += kam->size;
	memcpy(bigbufptr, buf,      len);

	// Set return lengths
	*bigbuflen = message_len;
	*retlen = len;
      
	// Free up memory
  keydb_freemsg(kam);
#ifdef C2S_HASHING
	hashdb_delete_hashval(summary_hv);
	hashdb_delete_hashval(msg_hv);

	// Finally add message to hashdb. Hash of buf will be included in future
	// messages from the client.
	// TODO: replace db->hdb[db->curridx] with msg_hv rather than recalculating...
	hashdb_add_message(db->hdb, buf, len);
	hashdb_increment_index(db->hdb);
#endif

#ifndef KLEE
#ifndef NUKLEAR
#ifdef DJB_NETLOG
  FILE *logfp = fopen(CLIENT_LOGFILE,"a");
  fprintf(logfp,"MSGINFO %f c2s %d %d\n", djbwctime(), message_len, len);
  fclose(logfp);
#endif
#endif
#endif

  return bigbuf;
}

static int keydb_clihandlerecv(unsigned char *bigbuf, unsigned char *buf, int len, struct keydb *db, long cliloopID) {
  if (len == 0) {
    return 0;
  }

  // Read the smseq
  long smseq = UCPTOINT(bigbuf);
  DEBUG("\tGOT smseq = %d (0x%x)\n",smseq,smseq);
  keydb_addframe(db,smseq,cliloopID);

  // Read the last kbseq seen by the server
  long kbseq = UCPTOINT(bigbuf+4);
  DEBUG("\tGOT last kbseq = %d (0x%x)\n",kbseq,kbseq);
  keydb_popuntil(db,kbseq);

  // Copy the packet
  int count = len-4-4;
  memcpy(buf,bigbuf+4+4,count);

#ifndef KLEE
#ifndef NUKLEAR
#ifdef DJB_NETLOG
  FILE *logfp = fopen(CLIENT_LOGFILE,"a");
  fprintf(logfp,"MSGINFO %f s2c %d %d\n", djbwctime(), len, count);
  fclose(logfp);
#endif
#endif
#endif

  return count;
}

static unsigned char * keydb_srvhandlesend(unsigned char *buf, int len, int *bigbuflen, int *retlen, struct keydb *db, struct ackedmsgdb *amdb) {
  // Update db
  (db->smseq)++;

  // Write smseq
  unsigned char smseqbuf[4];
  INTTOUCP(smseqbuf,db->smseq);

  // Write lastkbseq
  unsigned char kbseqbuf[4];
  INTTOUCP(kbseqbuf,db->kbseq);

  unsigned char *bigbuf = (unsigned char *)malloc(len+8);
  memcpy(bigbuf,smseqbuf,4);
  memcpy(bigbuf+4,kbseqbuf,4);
  memcpy(bigbuf+4+4,buf,len);
  *bigbuflen = len+4+4;
  *retlen = *bigbuflen-4-4;

  // Log this message
  //fprintf(stderr,"buf is:\t");
  //printbuffer(buf,len);
  //fprintf(stderr,"Logging this msg.  amdb was:\n");
  //ackedmsgdb_print(amdb);
  ackedmsgdb_addmsg(amdb,db->smseq,*bigbuflen,bigbuf);
  //fprintf(stderr,"Logged this msg.  amdb now:\n");
  //ackedmsgdb_print(amdb);
  
#ifndef KLEE
#ifndef NUKLEAR
#ifdef DJB_NETLOG
  FILE *logfp = fopen(SERVER_LOGFILE,"a");
  fprintf(logfp,"MSGINFO %f s2c %d %d\n", djbwctime(), len+4+4, len);
  fclose(logfp);
#endif
#endif
#endif

  return bigbuf;
}

struct keydb kdb;
static long kbseq = 0;
int isserver;
long cliloopID;
static int serverpacketcount = 0;
struct ackedmsgdb srvamdb;
struct ackedmsgdb cliamdb;

// TODO: keyv logging
// TODO: Use same name as client in packetlog and keyboardlog files


// Function Prototypes (nuklear)


// override inline assembly version of FD_ZERO from
// /usr/include/x86_64-linux-gnu/bits/select.h
#ifdef FD_ZERO
#undef FD_ZERO
#endif
#define FD_ZERO(p)        memset((char *)(p), 0, sizeof(*(p)))

#endif /* XPCOMMON_H */
