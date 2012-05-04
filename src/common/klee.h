#ifndef KLEE_H
#define KLEE_H

#define DJB_NETLOG
//#define DJBLOGGING

//#define C2S_HASHING
//#undef C2S_HASHING

//#define OLDSKOOL

#ifdef KLEE

#define DEBUG_PRINTF
//#define DEBUG_PRINTF printf
//#define DEBUG_PRINTF(x) printf(x "\n")
//#define DEBUG_PRINTF klee_warning 
#define NUKI(x) x

#ifdef KLEEIFY_EVENTS 
#define KLEEIFY
#define KLEEIFY_PREPARE_LOOPS 1
extern unsigned g_kleeify_events; /* == 1 after KLEEIFY_PREPARE_LOOPS */
#endif

#ifdef KLEEIFY_NET_PACKET
#define KLEEIFY
#define KLEEIFY_PREPARE_LOOPS 1
extern unsigned g_kleeify_net_packet; /* == 1 after KLEEIFY_PREPARE_LOOPS */
#endif

#ifdef KLEEIFY_NET_FRAME
#define KLEEIFY
#define KLEEIFY_PREPARE_LOOPS 1
extern unsigned g_kleeify_net_frame; /* == 1 after KLEEIFY_PREPARE_LOOPS */
#endif

#ifdef KLEEIFY_INIT
#define KLEEIFY
#define KLEEIFY_PREPARE_LOOPS 1
#endif

#ifdef KLEEIFY
extern unsigned g_klee_sent_keyv; /* set to 1 if Send_keyboard() is called */
#else
#define KLEEIFY_PREPARE_LOOPS 0
#endif

//#define error(str) printf("ERROR: %s:%d %s\n", __FILE__, __LINE__, str)
//#define warn(str) printf("WARNING: %s:%d %s\n", __FILE__, __LINE__, str)

#define IFKLEE(x) x
#define IFNKLEE(x)
#define IFNUKLEAR(x) 

//#define KLEE_PRINTF
//#define KLEE_PRINTF(x) printf(x "\n")
#define KLEE_PRINTF klee_warning

#define KLEE_PRINTF_FAIL 
//#define KLEE_PRINTF_FAIL klee_warning

#define KLEE_MAKE_SYMBOLIC_PTR(ptr)						\
  if (ptr != NULL) { 								\
  KLEE_PRINTF("KLEE_MAKE_SYMBOLIC_PTR( " #ptr " )"); 				\
  klee_make_symbolic_unknown_size(ptr, #ptr );					\
  } else KLEE_PRINTF_FAIL("KLEE_MAKE_SYMBOLIC_PTR( " #ptr " ) FAILED.");

#define KLEE_MAKE_SYMBOLIC_VAR(var) 						\
  KLEE_PRINTF("KLEE_MAKE_SYMBOLIC_VAR( " #var " )"); 				\
  klee_make_symbolic_unknown_size(&var, #var );

#define KLEE_COPY_PTR_NAME(ptr)							\
  if (ptr != NULL) {								\
  KLEE_PRINTF("KLEE_COPY_PTR_NAME( " #ptr " )");				\
  klee_ptr_copy[ENUM_ ## ptr ] = (void*) klee_duplicate_symbolic(ptr, #ptr );	\
  } else KLEE_PRINTF_FAIL("KLEE_COPY_PTR_NAME( " #ptr " ) FAILED.");

#define KLEE_COPY_VAR_NAME(var) 						\
  KLEE_PRINTF("KLEE_COPY_VAR_NAME( " #var " )"); 				\
  klee_ptr_copy[ENUM_ ## var ] = (void*) klee_duplicate_symbolic(&var, #var );

#define KLEE_COPY_PTR(ptr)							\
  if (ptr != NULL) {								\
  KLEE_PRINTF("KLEE_COPY_PTR( " #ptr " )");					\
  klee_ptr_copy[ENUM_ ## ptr ] = (void*) klee_duplicate_symbolic(ptr);		\
  } else KLEE_PRINTF_FAIL("KLEE_COPY_PTR( " #ptr " ) FAILED.");

#define KLEE_COPY_VAR(var) 							\
  KLEE_PRINTF("KLEE_COPY_VAR( " #var " )\n"); 					\
  klee_ptr_copy[ENUM_ ## var ] = (void*) klee_duplicate_symbolic(&var);

#define KLEE_EQUAL_PTR(ptr) 							\
  if (ptr != NULL) { 								\
  KLEE_PRINTF("KLEE_EQUAL_PTR( " #ptr " )"); 					\
  klee_equal(ptr, klee_ptr_copy[ENUM_ ## ptr ] ); 				\
  } else KLEE_PRINTF_FAIL("KLEE_EQUAL_PTR( " #ptr " ) FAILED.");

#define KLEE_EQUAL_VAR(var) 							\
  KLEE_PRINTF("KLEE_EQUAL_VAR( " #var " )"); 					\
  klee_equal(&var, klee_ptr_copy[ENUM_ ## var] );

#define KLEE_VAR_SIMPLE(var) 							\
  KLEE_PRINTF("KLEE_VAR_SIMPLE( " #var " )"); 					\
  klee_make_symbolic_unknown_size(&var, #var );

#define KLEE_STOP 								\
  KLEE_PRINTF("klee_write_constraints()"); 					\
  klee_write_constraints(); 							\
  _exit(1);

#define KLEE_EXTERNAL_MEM(type, addr) 						\
  KLEE_PRINTF("klee_add_external_object( " #addr ", sizeof(" #type "))");	\
  klee_add_external_object(addr, sizeof(type) );

#elif defined(NUKLEAR)

//#define KLEE_DISABLE_PAINT 1
#define RECV_WINDOW_SIZE 1

int nuklear_merge();
int nuklear_checkpoint(int x);

// Functions to ignore:
//Expose_about_window
//DrawShadowText
//Expose_button_window
//About
//Widget_event

//#define HACK_HOSTNAME "meropis-cs"

#ifdef OLDSKOOL
#define HACK_HOSTNAME "brawn.cs.unc.edu"
#else
#define HACK_HOSTNAME "kudzoo.cs.unc.edu"
#endif

#define HACK_WIDTH_WANTED 542
#define HACK_HEIGHT_WANTED 600 

//#define DEBUG_PRINTF klee_warning
//#define DEBUG_PRINTF printf
#define DEBUG_PRINTF

#define NUKI(x) nuklear_ ##x
#define IFKLEE(x) 
#define IFNUKLEAR(x) x
#define IFNKLEE(x)
#define KLEE_VAR(x)
#define KLEE_VAR_SIMPLE(var)
#define KLEE_MEM(x)
#define KLEE_EXTERNAL_MEM(type, addr)
#define KLEE_STOP(x)
#define KLEE_DEBUG(x)

#else

#define NUKI(x) x

#ifdef DJB_NETLOG
#define DEBUG_PRINTF(__x) do { \
  FILE *debug_printf_logfp = fopen(NETWORK_LOGFILE,"a"); \
  fprintf(debug_printf_logfp, __FILE__ ": ");            \
  fprintf(debug_printf_logfp, __x);                      \
  fprintf(debug_printf_logfp, "\n");                     \
  fclose(debug_printf_logfp);                            \ 
} while(0);
#else
#define DEBUG_PRINTF(__x) do { printf(__FILE__ ": "); printf(__x); printf("\n"); } while(0);
#endif

#define IFKLEE(x) 
#define IFNKLEE(x) x
#define IFNUKLEAR(x) 
#define KLEE_VAR(x)
#define KLEE_VAR_SIMPLE(var)
#define KLEE_MEM(x)
#define KLEE_EXTERNAL_MEM(type, addr)
#define KLEE_STOP(x)
#define KLEE_DEBUG(x)

#endif 

#ifndef DJB_NETLOG
#define IFDJBNETLOG(x)
#else
#define IFDJBNETLOG(x) IFNKLEE(x)
#endif

#ifdef NUKLEAR
#define NUK_TIME(x) __time(x)
#else
#define NUK_TIME(x) time(x)
#endif


#endif /* KLEE_H */
