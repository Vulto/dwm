/* appearance */
static const unsigned int borderpx  = 1;	/* border pixel of windows */
static const unsigned int gappx     = 0;	/* gaps between windows */
static const unsigned int snap      = 5;	/* snap pixel */
static const int showbar            = 1;	/* 0 means no bar */
static const int topbar             = 1;	/* 0 means bottom bar */
static const char *fonts[]          = { "xos4 terminus:size=12" };
static const char dmenufont[]       = "xos4 terminus:size=13";
static const char col_1[]				= "#181818";
static const char col_2[]				= "#666666";
static const char col_3[]				= "#ebdbb2";
static const char col_4[]				= "#000000";
static const char *colors[][3]      = {
	/*               fg     bg     border */
	[SchemeNorm] = { col_2, col_1, col_4, },
	[SchemeSel]  = { col_3, col_1, col_4, },
};

/* Auto start some programms */
static const char *const autostart[] = {
	"dwmblocks", NULL,
	"xset", "r","rate","180","25", "m","0","0", "-dpms", "s", "off", NULL,
	"xmodmap","/home/vulto/.config/keyconfig","-e","clear lock", NULL,
	"unclutter","--timeout","1", NULL,

	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { " ", " ", " ", " " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 *	1 << 8 means tag to 9th space
	 *	-1 means tag window to all spaces
	 */
	/* class      instance	title	tags_mask	sfloating	monitor */
	{ "Open file",  NULL,   NULL,		0,          1,          -1 },
	{ "YAD",        NULL,   NULL,		0,          1,          -1 },
	{ "sent",       NULL,   NULL,		0,          1,          -1 },
	{ "st",         NULL,   NULL,		0,				1,          -1 },
	{ "Sxiv",       NULL,   NULL,		0,          1,          -1 },
	{ "rdesktop",   NULL,   NULL,		1 << 3,		0,          -1 },
	{ "retroarch",  NULL,   NULL,		0,          1,          -1 },
	{ "Steam",		 NULL,   NULL,		0,          1,          -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const char *upvol[]   = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "+1%",  NULL };
static const char *downvol[] = { "/usr/bin/pactl", "set-sink-volume", "@DEFAULT_SINK@", "-1%",  NULL };
static const char *mutevol[] = { "/usr/bin/pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };

static const char *audioprev[] = { "/usr/bin/playerctl", "previous",	NULL };
static const char *audioplay[] = { "/usr/bin/playerctl", "play-pause",	NULL };
static const char *audionext[] = { "/usr/bin/playerctl", "next",	NULL };

static const char *calculator[] = { "/home/vulto/sources/scripts/asd",	NULL };
static const char *mixer[] = { "/home/vulto/sources/scripts/mixer",	NULL };
static const char *files[] = { "st", "-g", "100x34", "-e", "cfiles",	NULL };

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      tile },    /* first entry is default */
	{ " ",     monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[] = { "st", NULL };

static Key keys[] = {
	/* modifier         key								function			 argument */
	{ MODKEY,           XK_d,							spawn,			 {.v = dmenucmd } },
	{ MODKEY,           XK_Return,					spawn,			 {.v = termcmd } },
	{ MODKEY,           XK_b,							togglebar,		 {0} },
	{ MODKEY,           XK_j,							focusstack,		 {.i = +1 } },
	{ MODKEY,           XK_k,							focusstack,		 {.i = -1 } },
	{ MODKEY,           XK_i,							incnmaster,		 {.i = +1 } },
	{ MODKEY,           XK_o,							incnmaster,		 {.i = -1 } },
	{ MODKEY,           XK_h,							setmfact,		 {.f = -0.05} },
	{ MODKEY,           XK_l,							setmfact,		 {.f = +0.05} },
	{ MODKEY|ShiftMask, XK_Return,					zoom,				 {0} },
	{ MODKEY,           XK_Tab,						view,				 {0} },
	{ MODKEY,           XK_c,							killclient,		 {0} },
	{ MODKEY,           XK_f,							setlayout,		 {.v = &layouts[0]} },
	{ MODKEY,           XK_t,							setlayout,		 {.v = &layouts[1]} },
	{ MODKEY,           XK_m,							setlayout,		 {.v = &layouts[2]} },
	{ MODKEY,           XK_space,						setlayout,		 {0} },
	{ MODKEY,           XK_minus,						setgaps,			 {.i = -1 } },
	{ MODKEY,           XK_equal,						setgaps,			 {.i = +1 } },
	{ MODKEY|ShiftMask, XK_equal,						setgaps,			 {.i = 0  } },
	{ MODKEY|ShiftMask, XK_space,						togglefloating, {0} },
	{ MODKEY,           XK_0,							view,				 {.ui = ~0 } },
	{ MODKEY|ShiftMask, XK_0,							tag,				 {.ui = ~0 } },
	{ MODKEY,           XK_comma,						focusmon,		 {.i = -1 } },
	{ MODKEY,           XK_period,					focusmon,		 {.i = +1 } },
	{ MODKEY|ShiftMask, XK_comma,						tagmon,			 {.i = -1 } },
	{ MODKEY|ShiftMask, XK_period,					tagmon,			 {.i = +1 } },
	{ MODKEY,           XK_a,							spawn,			 {.v = calculator } }, 	
	{ MODKEY,           XK_p,							spawn,			 {.v = mixer } }, 	
	{ MODKEY,           XK_u,							spawn,			 {.v = files } }, 	
	{ 0,                XF86XK_AudioLowerVolume,	spawn,			 {.v = downvol } },
	{ 0,                XF86XK_AudioMute,        spawn,			 {.v = mutevol } }, 
	{ 0,                XF86XK_AudioRaiseVolume,	spawn,			 {.v = upvol   } },
	{ 0,                XF86XK_AudioPrev,			spawn,			 {.v = audioprev } },
	{ 0,                XF86XK_AudioPause,			spawn,			 {.v = audioplay } },
	{ 0,                XF86XK_AudioNext,			spawn,			 {.v = audionext } }, 	
	TAGKEYS(            XK_1,                      0)
	TAGKEYS(            XK_2,                      1)
	TAGKEYS(            XK_3,                      2)
	TAGKEYS(            XK_4,                      3)
	TAGKEYS(            XK_5,                      4)
	TAGKEYS(            XK_6,                      5)
	TAGKEYS(            XK_7,                      6)
	TAGKEYS(            XK_8,                      7)
	TAGKEYS(            XK_9,                      8)
	{ MODKEY|ShiftMask, XK_q,							  quit,			 {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
