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

#include "xpclient_x11.h"

/* ============================================================= */

#define MAX_INPUT_FILENAME_LEN 1024
double simulated_loss_rate = 0;
int simulated_burst_loss_start = 0;
int simulated_burst_loss_count = 0;
int simulated_burst_loss_size = 0;
int simulated_burst_loss_active = 0;
int quit_round = 0;
double simulated_burst_loss_rate = 25.0f;

bool play_input = false;
bool record_input = false;
char play_input_filename[MAX_INPUT_FILENAME_LEN];
char record_input_filename[MAX_INPUT_FILENAME_LEN];

static bool Set_input_filename(xp_option_t *opt, const char *val) {
	char *buf = (char*)Option_get_private_data(opt);
	assert(val != NULL);
	strlcpy(buf, val, MAX_INPUT_FILENAME_LEN);
	return true;
}

static bool Set_play_input_filename(xp_option_t *opt, const char *val) {
	Set_input_filename(opt, val);
	if (strcmp(val, "None")) 
		play_input = true;
	return true;
}

static bool Set_record_input_filename(xp_option_t *opt, const char *val) {
	Set_input_filename(opt, val);
	if (strcmp(val, "None")) 
		record_input = true;
	return true;
}

static bool Set_simulated_loss_rate(xp_option_t *opt, double val) {
	UNUSED_PARAM(opt);
	simulated_loss_rate = val;
	if (val > 0) 
		printf("Simulating client to server packet loss of %f%\n", val);
	return true;
}

static bool Set_simulated_burst_loss_count(xp_option_t *opt, int val) {
	UNUSED_PARAM(opt);
	simulated_burst_loss_count = val;
	return true;
}

static bool Set_simulated_burst_loss_size(xp_option_t *opt, int val) {
	UNUSED_PARAM(opt);
	simulated_burst_loss_size = val;
	return true;
}

static bool Set_simulated_burst_loss_start(xp_option_t *opt, int val) {
	UNUSED_PARAM(opt);
	simulated_burst_loss_start = val;
	return true;
}

static bool Set_quit_round(xp_option_t *opt, int val) {
	UNUSED_PARAM(opt);
	quit_round = val;
	return true;
}

static int Get_simulated_loss_rate() {
	return simulated_loss_rate;
}

bool is_simulated_loss() {

	//printf("XPILOT: Round %d: is_simulated_loss()\n", cliloopID);

	if (cliloopID > 1) { // Don't drop any packets before or during the first round.

		// We are currently dropping a burst of packets
		if (simulated_burst_loss_active > 0) {
			simulated_burst_loss_active--;
			INFO("\tRound %d: Dropped a packet. (burst)\n", cliloopID);
			if (simulated_burst_loss_active == 0)
				INFO("\tRound %d: Ending simulated burst loss of %d packets.\n",
						cliloopID, simulated_burst_loss_size);
			return true;
		}

		// Any remaining burst losses? 
		if (simulated_burst_loss_count > 0) {

			bool drop_packet = false;
			if (simulated_burst_loss_start == 0) {

				double rand = 100.0f*drand48();
				if (rand <= simulated_burst_loss_rate) {
					INFO("\tRound %d: Randomly generated # %f is > %f. (burst)\n", 
							cliloopID, rand, simulated_burst_loss_rate);
					drop_packet = true;
				}

			} else if (cliloopID >= simulated_burst_loss_start) {
				INFO("\tRound %d: Round is > burst_loss_start=%d. (burst)\n", 
						cliloopID, simulated_burst_loss_start);
				drop_packet = true;
			}

			if (drop_packet) {
				INFO("\tRound %d: Starting simulated burst loss of %d packets.\n",
						cliloopID, simulated_burst_loss_size);

				// Start burst loss
				simulated_burst_loss_active = simulated_burst_loss_size-1;

				// Decrement count of burst losses
				simulated_burst_loss_count--;

				INFO("\tXPILOT: Round %d: Dropped a packet. (burst)\n", cliloopID);
				return true;
			}
		}

		if (simulated_loss_rate > 0) {
			double rand = 100.0f*drand48();

			if (rand <= simulated_loss_rate) {
				INFO("\tRound %d: Dropped a packet.\n", cliloopID);
				return true;
			}
		}
	}

	return false;
}

static xp_option_t nuklear_options[] = {
	XP_STRING_OPTION(
			"recordInputFile",
			"None",
			record_input_filename,
			MAX_INPUT_FILENAME_LEN,
			Set_record_input_filename,
			record_input_filename, 
			NULL,
			XP_OPTFLAG_DEFAULT,
			"Record user input to filename.\n"),
	XP_STRING_OPTION(
			"playInputFile",
			"None",
			play_input_filename,
			MAX_INPUT_FILENAME_LEN,
			Set_play_input_filename, 
			play_input_filename, 
			NULL,
			XP_OPTFLAG_DEFAULT,
			"Play back user input from filename.\n"),
	XP_DOUBLE_OPTION(
			"simulatedLossRate",
			0.0f,
			0.0f,
			100.0f,
			&simulated_loss_rate,
			Set_simulated_loss_rate,
			XP_OPTFLAG_DEFAULT,
			"Simulate a packet loss rate (only client-to-server losses).\n"),
	XP_INT_OPTION(
			"simulatedBurstLossCount",
			0,
			0,
			1000,
			&simulated_burst_loss_count,
			Set_simulated_burst_loss_count,
			XP_OPTFLAG_DEFAULT,
			"Simulate a burst of consecutively lost packets.\n"),
	XP_INT_OPTION(
			"simulatedBurstLossSize",
			0,
			0,
			1000,
			&simulated_burst_loss_size,
			Set_simulated_burst_loss_size,
			XP_OPTFLAG_DEFAULT,
			"Simulate a burst of consecutively lost packets.\n"),
	XP_INT_OPTION(
			"simulatedBurstLossStart",
			0,
			0,
			INT_MAX,
			&simulated_burst_loss_start,
			Set_simulated_burst_loss_start,
			XP_OPTFLAG_DEFAULT,
			"Simulate a burst of consecutively lost packets at this round.\n"),
	XP_INT_OPTION(
			"quitRound",
			0,
			0,
			INT_MAX,
			&quit_round,
			Set_quit_round,
			XP_OPTFLAG_DEFAULT,
			"Quit game at round X.\n")
};

/* ============================================================= */

typedef struct{
	struct timeval tv_time;
	struct timespec ts_wait_time;
	int loop_id;
	unsigned int class;
	unsigned int type;
	KeySym key;
} input_event_t;


bool playback_active = false;
unsigned int curr_input_event = 0;
unsigned int num_input_events = 0;
unsigned int max_input_events = 0;
input_event_t** input_events = NULL;
struct timeval tv_loop_start;

enum {INPUT_EVENT_START=0, 
	INPUT_EVENT_KEYBOARD, 
	INPUT_EVENT_MOUSE, 
	INPUT_EVENT_NETWORK, 
	INPUT_EVENT_END};

char* input_event_class_str[] = 
{"START", "KEYBOARD", "MOUSE", "NETWORK", "END"};

input_event_t* add_input_event(unsigned int class, 
		unsigned int type, 
		unsigned int key) {

	input_event_t* ie 
		= (input_event_t*)malloc(sizeof(input_event_t));

	gettimeofday(&(ie->tv_time), NULL);
	ie->loop_id = cliloopID;
	ie->class = class;
	ie->type = type;
	ie->key = key;
	ie->ts_wait_time.tv_sec = ie->tv_time.tv_sec - tv_loop_start.tv_sec;
	int wait_usec = (ie->tv_time.tv_sec - tv_loop_start.tv_sec)*1000000;
	wait_usec -= tv_loop_start.tv_usec;
	wait_usec += ie->tv_time.tv_usec;
	ie->ts_wait_time.tv_sec = wait_usec / 1000000;
	ie->ts_wait_time.tv_nsec = (wait_usec % 1000000)*1000;

	STORE(input_event_t*, input_events, 
			num_input_events, max_input_events, ie);
}

int get_input_events_queued() {
	int index = curr_input_event;

	while (index < num_input_events && input_events[index]->loop_id == cliloopID) {
		index++;
	}
	return index - curr_input_event;
}

int my_XEventsQueued(Display *display, int mode) {
	int result = 0;
	if (play_input && playback_active) {
		result = get_input_events_queued();
	} else {
		result = NUKI(XEventsQueued)(display, mode);
	}
	return result;
}

KeySym my_XLookupKeysym(XKeyEvent *event, int index) {

	KeySym result = NoSymbol;
	if (record_input) {
		result = NUKI(XLookupKeysym)(event, index);
	} else if (play_input && playback_active) {
		result = input_events[curr_input_event-1]->key;
	} else {
		result = NUKI(XLookupKeysym)(event, index);
	}
	return result;
}

int my_XNextEvent(Display *display, XEvent *event_return) {

	int result;
	if (record_input) {
		result = NUKI(XNextEvent)(display, event_return);
		if (event_return->type == KeyPress ||
				event_return->type == KeyRelease) {
			KeySym ks = NUKI(XLookupKeysym)(&event_return->xkey, 0);
			add_input_event(INPUT_EVENT_KEYBOARD, event_return->type, ks);
		}
	} else if (play_input && playback_active) {
		event_return->type = input_events[curr_input_event]->type;
		event_return->xkey.window = topWindow;
		curr_input_event++;
	} else {
		result = NUKI(XNextEvent)(display, event_return);
	}
	return result;
}

void print_input_event(FILE* out, input_event_t* e) {
	fprintf(out, "Round %d:\t%d.%d (%d.%d)\t%s\t%d\t%d\n",
			e->loop_id,
			e->tv_time.tv_sec, 
			e->tv_time.tv_usec,
			e->ts_wait_time.tv_sec,
			e->ts_wait_time.tv_nsec,
			input_event_class_str[e->class],
			e->type,
			e->key);
}

void print_input_events() {
	printf("Input events\n");
	int i;
	for (i=0;i<num_input_events;i++) {
		print_input_event(stdout, input_events[i]);
	}
}

void Store_nuklear_options() {
#ifndef KLEE
#ifndef NUKLEAR
	//srand48((unsigned)time(NULL) * Get_process_id());
	srand48( 4357U );
#endif
#endif
	STORE_OPTIONS(nuklear_options);
}

int write_input_events() {
	FILE *f = NULL;
	if (record_input) {
		char* path = record_input_filename;
		int i, count = num_input_events;

		f = fopen(path, "wb");
		if (!f)
			goto error;

		if (fwrite(&count, sizeof(count), 1, f)!=1)
			goto error;

		for (i=0;i<count;i++) {
			if (fwrite(input_events[i], sizeof(input_event_t), 1, f)!=1)
				goto error;
		}

		fclose(f);

		return 1;
	}

error:
	error("write_input_events()");
	if (f) fclose(f);
	return 0;
}

int read_input_events() {
	FILE *f = NULL;
	if (play_input) {
		char* path = play_input_filename;
		int i, count;

		f = fopen(path, "rb");

		if (!f)
			goto error;

		if (fread(&count, sizeof(count), 1, f)!=1)
			goto error;

		for (i=0;i<count;i++) {
			input_event_t* ie 
				= (input_event_t*)malloc(sizeof(input_event_t));

			if (fread(ie, sizeof(input_event_t), 1, f)!=1)
				goto error;

			STORE(input_event_t*, input_events, 
					num_input_events, max_input_events, ie);
		}

		fclose(f);

		return 1;
	}

error:
	error("read_input_events()");
	if (f) fclose(f);
	return 0;
}

void input_events_cleanup() {
	if (record_input) {
		print_input_events();
		write_input_events();
	}
}

/* ============================================================= */

int Net_packet(); /* rcochran */
#ifdef NUKLEAR
//int nuklear_merge() {/*DEBUG_PRINTF("merge")*/; return 0;}
int nuklear_checkpoint(int x) {/*DEBUG_PRINTF("checkpoint")*/; return 0;}
#endif

#ifdef KLEEIFY_NET_PACKET
unsigned g_kleeify_net_packet = 0;
#endif

#ifdef KLEEIFY_EVENTS
unsigned g_kleeify_events = 0;
#endif

#ifdef KLEEIFY
unsigned g_klee_sent_keyv = 0;
#endif

static int Handle_input(int new_input)
{
	return x_event(new_input);
}

// rochran: removed static from Input_loop()
void Input_loop(void)
{

#ifndef KLEE
#ifndef NUKLEAR
	if (play_input) {
		INFO("\treading input events...\n");
		read_input_events();
		//print_input_events();
	}

	INFO("\tNuklear config:\n");
	INFO("\tplayback active: %d\n", playback_active);
	INFO("\tloss rate: %f\n", simulated_loss_rate);
	INFO("\tburst loss active: %d\n", simulated_burst_loss_active);
	INFO("\tburst loss size: %d\n", simulated_burst_loss_size);
	INFO("\tburst loss count: %d\n", simulated_burst_loss_count);
	INFO("\tburst loss rate: %f\n", simulated_burst_loss_rate);
	INFO("\tburst loss start: %d\n", simulated_burst_loss_start);
	INFO("\tquit round: %d\n", quit_round);

	if (simulated_burst_loss_count == 0) 
		srand48((unsigned)time(NULL) * Get_process_id());
	else
		srand48(231090);
#endif
#endif

#ifdef KLEEIFY_NET_FRAME
	goto kleeify_net_frame_start;
#endif

	DEBUG_PRINTF("Input_loop()");
	fd_set rfds, tfds;
	int max, n, netfd, result, clientfd;
	struct timeval tv;

	if ((result = Net_input()) == -1) {
		error("Bad server input");
		return;
	}

#ifdef OLDSKOOL
	DEBUG_PRINTF("Handle_input()");
	if (Handle_input(2) == -1)
		return;
#endif

	DEBUG_PRINTF("Net_flush()");
	if (Net_flush() == -1)
		return;

	DEBUG_PRINTF("ConnectionNumber()");
	if ((clientfd = ConnectionNumber(dpy)) == -1) {
		error("Bad client filedescriptor");
		return;
	}
	DEBUG_PRINTF("Net_fd()");
	if ((netfd = Net_fd()) == -1) {
		error("Bad socket filedescriptor");
		return;
	}

#ifdef OLDSKOOL
    Check_view_dimensions();
    Net_flush();
#endif

	DEBUG_PRINTF("Net_key_change()");
	Net_key_change();
	FD_ZERO(&rfds);
	FD_SET(clientfd, &rfds);
	FD_SET(netfd, &rfds);
	max = (clientfd > netfd) ? clientfd : netfd;

	for (tfds = rfds; ; rfds = tfds) {

#ifndef OLDSKOOL
		// Increment round count
		cliloopID++;
#endif

#ifdef NUKLEAR
		nuklear_merge();
#endif
		{
			char tmp_str[128];
			sprintf(tmp_str, "Start of main_loop %d", n++);
			DEBUG_PRINTF(tmp_str);
			DEBUG_PRINTF("nuklear_merge");
		}

#ifdef OLDSKOOL
		// Increment round count
		cliloopID++;
#endif


#ifndef NUKLEAR
#ifndef KLEE 
		if (quit_round == cliloopID) {
		        input_events_cleanup();
			printf("XPILOT: Round %d: Quiting game. \n", cliloopID);
			return;
		}

		if (record_input) {
			gettimeofday(&tv_loop_start, NULL);
		}

		if (play_input) {
			if (get_input_events_queued()) {
				playback_active = true;
				//struct timespec rem;
				//rem.tv_sec=rem.tv_nsec=0;
				//nanosleep(&(input_events[curr_input_event]->ts_wait_time), &rem);

				//printf("XPILOT: Round %d: nanosleep: sleep=%d(%d) rem=%d(%d). \n", 
				//		cliloopID,
				//		(input_events[curr_input_event]->ts_wait_time).tv_sec,
				//		(input_events[curr_input_event]->ts_wait_time).tv_nsec,
				//		rem.tv_sec,
				//		rem.tv_nsec);

				// TODO: check rem

				DEBUG_PRINTF("FD_ISSET(clientfd*) -> Handle_input()");
				if (Handle_input(1) == -1)
					return;

				DEBUG_PRINTF("FD_ISSET(clientfd*) -> Net_flush()");
				if (Net_flush() == -1) {
					error("Bad net flush after X input");
					return;
				}

				playback_active = false;
			}
		} 
#endif
#endif

#ifdef KLEE
		clData.pointerControl = 0;
		static unsigned klee_loop_count = 0;
		klee_loop_count++;
		if (klee_loop_count == KLEEIFY_PREPARE_LOOPS) {

#ifdef KLEEIFY_INIT
			{
				DEBUG_PRINTF("KLEEIFY_INIT Start Point");
				klee_init_symbolic_memory();
				klee_copy_symbolic_memory_name();
				klee_finish_constraints();
				klee_write_constraints();
				exit(1);
			}
#elif  KLEEIFY_NET_PACKET
			{
				DEBUG_PRINTF("KLEEIFY_NET_PACKET Start Point");
				g_kleeify_net_packet = 1;
				klee_disable_xwindows();
				klee_init_symbolic_memory();
				klee_make_symbolic_memory();
				klee_copy_symbolic_memory();

				if ((result = Net_packet()) == -1) {
					warn("Bad net input.  Have a nice day!");
				} else {
					klee_finish_constraints();
					klee_write_constraints();
				}
				exit(1);
			}
#elif  KLEEIFY_EVENTS
			{
				DEBUG_PRINTF("KLEEIFY_EVENTS Start Point");
				g_kleeify_events = 1;
				klee_disable_xwindows();
				klee_init_symbolic_memory();
				klee_make_symbolic_memory();
				klee_copy_symbolic_memory();

				XEvent event;
				klee_make_symbolic_unknown_size(&event, "event");
				Key_event(&event);

				exit(1);
			}
#endif

		}
#endif

		tv.tv_sec = 1;
		tv.tv_usec = 0;

#ifndef NUKLEAR
		if (maxMouseTurnsPS > 0) {
			int t = Client_check_pointer_move_interval();

			assert(t > 0);
			tv.tv_sec = t / 1000000;
			tv.tv_usec = t % 1000000;
		}
#endif

#ifdef NUKLEAR
		unsigned char *clientfd_isset = malloc(sizeof(unsigned char));
		unsigned char *netfd_isset = malloc(sizeof(unsigned char));

                cliver_select_event();
		klee_make_symbolic(clientfd_isset, sizeof(unsigned char), "clientfd_isset");
		klee_make_symbolic(netfd_isset, sizeof(unsigned char), "netfd_isset");
#endif

#ifndef NUKLEAR
		if ((n = select(max + 1, &rfds, NULL, NULL, &tv)) == -1) {
			if (errno == EINTR)
				continue;
			/* rcochran */
			perror("Ignoring Select failure...");
			continue;
			/* rcochran */
			error("Select failed");
			return;
		}

		if (n == 0) {
			if (maxMouseTurnsPS > 0 &&
					cumulativeMouseMovement != 0)
				continue;

			if (result <= 1) {
				warn("No response from server");
				continue;
			}
		}
#endif

#ifdef NUKLEAR
		if (*clientfd_isset) {
			free(clientfd_isset);
#else
			if (FD_ISSET(clientfd, &rfds)) {
#endif

				DEBUG_PRINTF("FD_ISSET(clientfd) -> Handle_input()");
				if (Handle_input(1) == -1)
					return;

				DEBUG_PRINTF("FD_ISSET(clientfd) -> Net_flush()");
				if (Net_flush() == -1) {
					error("Bad net flush after X input");
					return;
				}
			} 
#ifdef NUKLEAR
			else {
				free(clientfd_isset);
			}
#endif

#ifdef NUKLEAR
			if (*netfd_isset || result > 1) {
				free(netfd_isset);
#else
				if (FD_ISSET(netfd, &rfds) || result > 1) {
#endif

					struct timeval tv1, tv2;

					gettimeofday(&tv1, NULL);

#ifdef KLEEIFY_NET_FRAME
kleeify_net_frame_start:
					// Will need to init Frames here if it becomes symbolic.
					//if (Frames == NULL) {
					//  Net_init(NULL, NULL); // Initialize socket data structures.
					//  Receive_init(); // Initalize function pointer table.
					//}
					//Key_init();
					//Didn't call Net_setup, allocate Setup struct.
					if (Setup == NULL)
						if ((Setup = (setup_t *) malloc(sizeof(setup_t))) == NULL) {
							error("No memory for setup data");
							return -1;
						}

					klee_disable_xwindows();
					klee_init_symbolic_memory();
					klee_make_symbolic_memory();
					klee_copy_symbolic_memory();
#endif
					DEBUG_PRINTF("FD_ISSET(netfd) -> Net_input()");
					if ((result = Net_input()) == -1) {
						warn("Bad net input.  Have a nice day!");
						return;
					}

#ifdef KLEEIFY_NET_FRAME
					klee_finish_constraints();
					klee_write_constraints();
					_exit(1);
#endif
                                        // RAC This code is removed so that there is no ambiguity as to when a client sends a message
                                        // to the server, i.e., before processing the server to client message (which increments
                                        // last_loops) or after
					//if (result > 0) {
					//	/*
					//	 * Now there's a frame being drawn by the X server.
					//	 * So we shouldn't try to send more drawing
					//	 * requests to the X server or it might get
					//	 * overloaded which could cause problems with
					//	 * keyboard input.  Besides, we wouldn't even want
					//	 * to send more drawing requests because there
					//	 * may arive a more recent frame update soon
					//	 * and using the CPU now may even slow down the X server
					//	 * if it is running on the same CPU.
					//	 * So we only check if the X server has sent any more
					//	 * keyboard events and then we wait until the X server
					//	 * has finished the drawing of our current frame.
					//	 */
					//	DEBUG_PRINTF("FD_ISSET(netfd) -> Handle_input()");
					//	if (Handle_input(1) == -1)
					//		return;

					//	DEBUG_PRINTF("FD_ISSET(netfd) -> Net_flush()");
					//	if (Net_flush() == -1) {
					//		error("Bad net flush before sync");
					//		return;
					//	}

					//	XSync(dpy, False);

					//	DEBUG_PRINTF("FD_ISSET(netfd) ->(2) Handle_input()");
					//	if (Handle_input(1) == -1)
					//		return;
					//}

					if (newSecond) {
						gettimeofday(&tv2, NULL);
						clData.clientLag = 1e-3 * timeval_sub(&tv2, &tv1);
					}
				} 
#ifdef NUKLEAR
				else {
					free(netfd_isset);
				}
#endif
			}
		}

		void xpilotShutdown(void)
		{
			Net_cleanup();
			Client_cleanup();
			Record_cleanup();
			defaultCleanup();
			aboutCleanup();
			paintdataCleanup();
		}

		static void sigcatch(int signum)
		{
			printf("sigcatch\n");
			signal(SIGINT, SIG_IGN);
			signal(SIGTERM, SIG_IGN);
			xpilotShutdown();
			error("Got signal %d\n", signum);
			exit(1);
		}


		int Join(Connect_param_t *conpar)
		{
			DEBUG_PRINTF("XPILOT: Join()\n");
			signal(SIGINT, sigcatch);
			signal(SIGTERM, sigcatch);
			signal(SIGHUP, SIG_IGN);
			signal(SIGPIPE, SIG_IGN);

			if (Client_init(conpar->server_name, conpar->server_version) == -1) {
				DEBUG_PRINTF("XPILOT: Client_init() failed.\n");
				return -1;
			}

			if (Net_init(conpar->server_addr, conpar->login_port) == -1) {
				Client_cleanup();
				return -1;
			}
			if (Net_verify(conpar->user_name,
						conpar->nick_name,
						conpar->disp_name) == -1) {
				Net_cleanup();
				Client_cleanup();
				return -1;
			}
			if (Net_setup() == -1) {
				Net_cleanup();
				Client_cleanup();
				return -1;
			}
			if (Client_setup() == -1) {
				DEBUG_PRINTF("XPILOT: Client_setup() failed.\n");
				Net_cleanup();
				Client_cleanup();
				return -1;
			}
			if (Net_start() == -1) {
				warn("Network start failed");
				Net_cleanup();
				Client_cleanup();
				return -1;
			}
			if (Client_start() == -1) {
				DEBUG_PRINTF("XPILOT: Client_start() failed.\n");
				warn("Window init failed");
				Net_cleanup();
				Client_cleanup();
				return -1;
			}

			Input_loop();
			xpilotShutdown();

			return 0;
		}
