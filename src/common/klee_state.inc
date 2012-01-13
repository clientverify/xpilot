
// TYPE: client_data_t
//typedef struct {
// bool	talking	/* Some talk window is open? */
// bool	pointerControl	/* Pointer (mouse) control is on? */
// bool	restorePointerControl /* Pointer control should be restored later? */
// bool	quitMode	/* Client is in quit mode? */
// double	clientLag
// double	scaleFactor
// double	scale
// float	fscale
// double	altScaleFactor
//} client_data_t
KLEE_XX_VAR( clData )

// TYPE: xpargs_t
// LOW PRIORITY
//typedef struct {
//    bool help
//    bool version
//    bool text
//    bool list_servers /* list */
//    bool auto_connect /* join */
//    char shutdown_reason[MAX_CHARS] /* shutdown reason */
//} xp_args_t
KLEE_XX_VAR( xpArgs )

// TYPE: Connect_param_t
// LOW PRIORITY
//typedef struct Connect_param {
//    int		contact_port,
//				server_port,
//				login_port
//    char		nick_name[MAX_NAME_LEN],
//				user_name[MAX_NAME_LEN],
//				host_name[SOCK_HOSTNAME_LENGTH],
//				server_addr[MAX_HOST_LEN],
//				server_name[MAX_HOST_LEN],
//				disp_name[MAX_DISP_LEN]
//    unsigned	server_version
//    int		team
//} Connect_param_t
KLEE_XX_VAR( connectParam )

// TYPE: score_object_t
// INDEX: score_object
// SIZE: MAX_SCORE_OBJECTS
//typedef struct {
//  double	score,
//			life_time
//  int		x,
//			y,
//			hud_msg_len,
//			hud_msg_width,
//			msg_width,
//			msg_len
//  char	msg[10],
//			hud_msg[MAX_CHARS+10]
//} score_object_t
//
KLEE_XX_PTR( score_objects )

// TYPE: int
KLEE_XX_VAR( score_object )

// TYPE: int
KLEE_XX_VAR( oldServer )

// TYPE: ivec_t
KLEE_XX_VAR( selfPos )

// TYPE: ivec_t
KLEE_XX_VAR( selfVel )

// TYPE: short 
KLEE_XX_VAR( heading )

// TYPE: short 
KLEE_XX_VAR( nextCheckPoint )

// Count of currently owned items
// TYPE: u_byte
// SIZE: NUM_ITEMS
KLEE_XX_PTR( numItems )

// Last item count shown
// TYPE: u_byte
// SIZE: NUM_ITEMS
KLEE_XX_PTR( lastNumItems )

// Number of frames to show this item count
// TYPE: int
// SIZE: NUM_ITEMS
KLEE_XX_PTR( numItemsTime )

// How long to show changed item count for
// TYPE: double
KLEE_XX_VAR( showItemsTime )

// How long to flash score objects
// TYPE: double 
KLEE_XX_VAR( scoreObjectTime )

// TYPE: short
KLEE_XX_VAR( autopilotLight )

// Affects output of score on screen
// TYPE: int
//KLEE_XX_VAR( showScoreDecimals )

// TYPE: short
KLEE_XX_VAR( lock_id )		/* Id of player locked onto */
KLEE_XX_VAR( lock_dir )		/* Direction of lock */
KLEE_XX_VAR( lock_dist )		/* Distance to player locked onto */

// Player we get frame updates for
// TYPE: int
// LOW PRIORITY 
//KLEE_XX_VAR( eyesId ) 	       

// Player we get frame updates for
// TYPE: other_t
// LOW PRIORITY 
//KLEE_XX_PTR( eyes )

// are we snooping on someone else?
// TYPE: bool
// LOW PRIORITY 
//KLEE_XX_VAR( snooping )	        

// Team of player we get updates for
// TYPE: int
// LOW PRIORITY 
//KLEE_XX_VAR( eyeTeam )	        

// Player info
// TYPE: other_t
//typedef struct {
// double	score
// short	id
// uint16_t	team
// short	check
// short	round
// long	timing_loops
// short	timing
// short	life
// short	mychar
// short	alliance
// short	name_width	/* In pixels */
// short	name_len	/* In bytes */
// short	max_chars_in_names	/* name_width was calculated
//       			   for this value of maxCharsInNames */
// short	ignorelevel
// shipshape_t	*ship
// char	nick_name[MAX_CHARS]
// char	user_name[MAX_CHARS]
// char	host_name[MAX_CHARS]
// char	id_string[MAX_CHARS]
//} other_t
KLEE_XX_PTR( self )

// Are we alive and playing?
// TYPE: short
KLEE_XX_VAR( selfVisible )

// Damaged by ECM
// TYPE: short
KLEE_XX_VAR( damaged )

// If self destructing 
// TYPE: short
KLEE_XX_VAR( destruct )

// If self destructing 
// TYPE: short
KLEE_XX_VAR( shutdown_delay )

// TYPE: short
KLEE_XX_VAR( shutdown_count )
// TYPE: short
KLEE_XX_VAR( thrusttime )
// TYPE: short
KLEE_XX_VAR( thrusttimemax )
// TYPE: short
KLEE_XX_VAR( shieldtime )
// TYPE: short
KLEE_XX_VAR( shieldtimemax )
// TYPE: short
KLEE_XX_VAR( phasingtime )
// TYPE: short
KLEE_XX_VAR( phasingtimemax )

// TYPE: int
KLEE_XX_VAR( roundDelay )
// TYPE: int
KLEE_XX_VAR( roundDelayMax )

// TYPE: bool
KLEE_XX_VAR( scoresChanged )

// MAP VARIABLES /////////////////////////////

// TYPE: unsigned
//KLEE_XX_VAR( RadarWidth )
// TYPE: unsigned
//KLEE_XX_VAR( RadarHeight )
	
// spacing of navigation points 
// TYPE: int
//KLEE_XX_VAR( backgroundPointDist )

// size of navigation points 
// TYPE: int
//KLEE_XX_VAR( backgroundPointSize )

// size of sparks and debris 
// TYPE: int
//KLEE_XX_VAR( sparkSize )

// size of shot 
// TYPE: int
//KLEE_XX_VAR( shotSize )

// size of team shot 
// TYPE: int
//KLEE_XX_VAR( teamShotSize )

// Display control for how long? 
// TYPE: double
//KLEE_XX_VAR( controlTime )

// Sparkling effect 
// TYPE: u_byte
KLEE_XX_VAR( spark_rand )

// previous value of spark_rand 
// TYPE: u_byte
KLEE_XX_VAR( old_spark_rand )

// Sum of fuel in all tanks 
// TYPE: double 
KLEE_XX_VAR( fuelSum )

// How much fuel can you take? 
// TYPE: double
KLEE_XX_VAR( fuelMax )

// Number of currently used tank 
// TYPE: short 
KLEE_XX_VAR( fuelCurrent )

// Number of tanks 
// TYPE: short
KLEE_XX_VAR( numTanks )

// Display fuel for how long? 
// TYPE: double
KLEE_XX_VAR( fuelTime )

// Fuel critical level 
// TYPE: double
KLEE_XX_VAR( fuelCritical )

// Fuel warning level 
// TYPE: double
KLEE_XX_VAR( fuelWarning )

// Fuel notify level 
// TYPE: double
KLEE_XX_VAR( fuelNotify )

// Shape of player's ship 
// TYPE: ship_t
// LOW PRIORITY
//KLEE_XX_PTR( shipShape )

// Force of thrust 
// TYPE: double
KLEE_XX_VAR( power )

// Saved power fiks 
// TYPE: double
KLEE_XX_VAR( power_s )

// How fast player acc-turns 
// TYPE: double
KLEE_XX_VAR( turnspeed )

// Saved turnspeed 
// TYPE: double
KLEE_XX_VAR( turnspeed_s )

// How much is lost in % 
// TYPE: double
KLEE_XX_VAR( turnresistance )

// Saved (see above) 
// TYPE: double
KLEE_XX_VAR( turnresistance_s )

// What the server is sending us 
// TYPE: double
KLEE_XX_VAR( displayedPower )

// What the server is sending us 
// TYPE: double
KLEE_XX_VAR( displayedTurnspeed )

// What the server is sending us 
// TYPE: double
KLEE_XX_VAR( displayedTurnresistance )

// GUI
// Sparkling effect configurable 
// TYPE: double
KLEE_XX_VAR( sparkProb )

// GUI
// Message output speed (config) 
// TYPE: int
KLEE_XX_VAR( charsPerSecond )

// GUI
// scale the hud-movement (speed) 
// TYPE: double
//KLEE_XX_VAR( hud_move_fact )

// scale the speed pointer length 
// TYPE: double
KLEE_XX_VAR( ptr_move_fact )

// Current modifiers in effect 
// TYPE: char[MAX_CHARS]
KLEE_XX_PTR( mods )

// Instruments on screen 
// TYPE: instruments_t
//KLEE_XX_VAR( instruments )

// Current frame update packet size 
// TYPE:  int
KLEE_XX_VAR( packet_size )

// lost packets per second 
// TYPE: int
KLEE_XX_VAR( packet_loss )

// dropped packets per second 
// TYPE: int
KLEE_XX_VAR( packet_drop )

// approximate lag in frames 
// TYPE: int
KLEE_XX_VAR( packet_lag )

// packet measurement in a second see Net_measurement() and
// Net_init_measurement(). Stats are used for debugging analysis
// and are drawn on display.
// TYPE: char*
//KLEE_XX_PTR( packet_measure )

// start of measurement 
// TYPE: long
KLEE_XX_VAR( packet_loop )

// Show username instead of nickname 
// TYPE: bool
//KLEE_XX_VAR( showUserName )

// Name of server connecting to 
// TYPE: char[MAX_CHARS]
KLEE_XX_PTR( servername )

// Version of the server 
// TYPE: unsigned
//KLEE_XX_VAR( version )

// Are shields toggled by a press? 
// TYPE: bool
KLEE_XX_VAR( toggle_shield )

// When shields are considered up 
// TYPE: bool
KLEE_XX_VAR( shields )

// drops shield for fire 
// TYPE: bool
KLEE_XX_VAR( auto_shield )

// Max FPS player wants from server 
// TYPE: int
KLEE_XX_VAR( maxFPS )
KLEE_XX_VAR( oldMaxFPS )

// FPS client is drawing at 
// TYPE: double
//KLEE_XX_VAR( clientFPS )

// What FPS to record at 
// TYPE: double
//KLEE_XX_VAR( recordFPS )

/* currentTime is obviously different each time we run klee, but 
 * we may need to make symbolic later on. */
// Current value of time() 
// TYPE: 
//KLEE_XX_VAR( currentTime )

// Did time() increment this frame? 
// TYPE: int
KLEE_XX_VAR( newSecond )
//KLEE_XX_VAR( maxMouseTurnsPS )
//KLEE_XX_VAR( mouseMovementInterval )
//KLEE_XX_VAR( cumulativeMouseMovement )

//FIXME
// modifier banks strings 
// TYPE: 
//extern char	modBankStr[][MAX_CHARS]

// First UDP port for clients 
// TYPE: int
KLEE_XX_VAR( clientPortStart )

// Last one (these are for firewalls) 
// TYPE: int
KLEE_XX_VAR( clientPortEnd )

// Which type of base warning you prefer 
// TYPE: int
//KLEE_XX_VAR( baseWarningType )


// TYPE: int
//KLEE_XX_VAR( maxCharsInNames )

// flag and index to drop item 
// TYPE: byte 
KLEE_XX_VAR( lose_item )

// one of the lose keys is pressed 
// TYPE: int
KLEE_XX_VAR( lose_item_active )

/* rcochran - see init_polymap() in client/client.c for KLEE-ification */
/* mapdata accessible to outside world */
#if 0
extern int	        num_playing_teams

/* static vars from client/client.c */
static double       teamscores[MAX_TEAMS]
static cannontime_t *cannons = NULL
static int          num_cannons = 0
static target_t     *targets = NULL
static int          num_targets = 0

extern fuelstation_t	*fuels
extern int		num_fuels
extern homebase_t	*bases
extern int		num_bases
extern checkpoint_t	*checks
extern int		num_checks
extern xp_polygon_t	*polygons
extern int		num_polygons, max_polygons
extern edge_style_t	*edge_styles
extern int		num_edge_styles, max_edge_styles
extern polygon_style_t	*polygon_styles
extern int		num_polygon_styles, max_polygon_styles
#endif

KLEE_XX_VAR(num_playing_teams)
/* static vars from client/client.c */
KLEE_XX_PTR( teamscores )
//KLEE_XX_PTR( cannons )
//KLEE_XX_PTR( targets )
//KLEE_XX_PTR( fuels )
KLEE_XX_PTR( bases )
//KLEE_XX_PTR( checks )
/* rcochran - polygons is an array of structs that contain pointers... */
//KLEE_XX_PTR( polygons )
//KLEE_XX_PTR( edge_styles )
//KLEE_XX_PTR( polygon_styles ) /* rcochran - struct contains pointers */

/* dynamic global game data */

/* rcochran - Others is a an array other_t structs which contain info on the
 * other players(bots too?). Each other_t struct has a pointer to a
 * shipshape string.. so we need to disable shipshape, or add a
 * "KLEE_XX_make_concrete()" etc. until fixedpoint is completed, shipshape is
 * broken anyways. */
KLEE_XX_PTR( Others )

/* rcochran - FIXME need to better understand dynamic data, this data is
* allocated and freed each frame. Do we need to klee-ify or is it mainly
* graphics data.
*/
#if 0 
KLEE_XX_PTR( refuel_ptr )
KLEE_XX_PTR( connector_ptr )
KLEE_XX_PTR( laser_ptr )
KLEE_XX_PTR( missile_ptr )
KLEE_XX_PTR( ball_ptr )
KLEE_XX_PTR( ship_ptr )
KLEE_XX_PTR( mine_ptr )
KLEE_XX_PTR( itemtype_ptr )
KLEE_XX_PTR( ecm_ptr )
KLEE_XX_PTR( trans_ptr )
KLEE_XX_PTR( paused_ptr )
KLEE_XX_PTR( appearing_ptr )
KLEE_XX_PTR( radar_ptr )
KLEE_XX_PTR( vcannon_ptr )
KLEE_XX_PTR( vfuel_ptr )
KLEE_XX_PTR( vbase_ptr )

/* rcochran - see Handle_fastshot/Handle_debris in client/client.c */
#if 0
extern debris_t		*debris_ptr[DEBRIS_TYPES]
extern int		 num_debris[DEBRIS_TYPES],
       max_debris[DEBRIS_TYPES]
extern debris_t		*fastshot_ptr[DEBRIS_TYPES * 2]
extern int		 num_fastshot[DEBRIS_TYPES * 2],
       max_fastshot[DEBRIS_TYPES * 2]
#endif

KLEE_XX_PTR( vdecor_ptr )
KLEE_XX_PTR( wreckage_ptr )
KLEE_XX_PTR( asteroid_ptr )
KLEE_XX_PTR( wormhole_ptr )
#endif

KLEE_XX_VAR( ball_shout )
KLEE_XX_VAR( need_cover )
KLEE_XX_VAR( start_loops )
KLEE_XX_VAR( end_loops )
KLEE_XX_VAR( time_left )

KLEE_XX_VAR( roundend )
KLEE_XX_VAR( played_this_round )

KLEE_XX_VAR( last_loops )
KLEE_XX_VAR( last_keyboard_change )
KLEE_XX_VAR( last_keyboard_update )
KLEE_XX_VAR( last_keyboard_ack )
KLEE_XX_PTR( keyv )
//KLEE_XX_PTR( keyv_new )
KLEE_XX_PTR( Setup )

#ifdef KLEEIFY
//KLEE_XX_VAR( g_klee_sent_keyv )
#endif

// FIXME
//
// extern setup_t *Setup

/* ------------------------------------------------------------------------- */

/* number of options in global option array */
//KLEE_XX_PTR(options)

/* keydefs maps system XEvent key ids to the XPilot key_t, this is client
 * specific so we should be able to use a higher level symbolic, like the
 * output of Generic_lookup_key in option.c
 */
//KLEE_XX_PTR( keydefs )

// used for help messages
// bool
//KLEE_XX_VAR( newbie )

// used by xpaint stuff
// char* 
//KLEE_XX_PTR( geometry ) 

/* messages.c: talk message data */
#if 0
extern message_t	*TalkMsg[]
extern message_t	*GameMsg[]
extern message_t	*TalkMsg_pending[]	/* store incoming messages */
extern message_t	*GameMsg_pending[]	/* while a cut is pending */
extern char		*HistoryMsg[]		/* talk window history */

extern int		maxLinesInHistory	/* lines to save in history */
extern selection_t	selection		/* in talk/draw window */
extern int		maxMessages
extern int		messagesToStdout

extern char		*talk_fast_msgs[]	/* talk macros */
#endif

