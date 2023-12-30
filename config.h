#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 1;	/* border pixel of windows */
static const unsigned int snap      = 5;	/* snap pixel */
static const int showbar            = 0;	/* 0 means no bar */
//static const int topbar             = 1;	/* 0 means bottom bar */
static const char *fonts[]          = { "xos4 terminus:size=13" };
static const char dmenufont[]       = "xos4 terminus:size=13";
static const char col_1[]				= "#181818";
static const char col_2[]				= "#888888";
static const char col_3[]				= "#e9d9b9";
static const char col_4[]				= "#000000";
static const char *colors[][3]      = {
	/*               fg     bg     border */
	[SchemeNorm] = { col_2, col_1, col_4, },
	[SchemeSel]  = { col_3, col_1, col_4, },
};

/* Auto start some programms */
static const char *const autostart[] = {
	"setxkbmap", "-option", "caps:swapescape", NULL,
	"xset", "r","rate","180","25", "m","0","0", "-dpms", "s", "off", NULL,
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
	{ "Open file",  NULL,   NULL,		0,		1,		-1 },
	{ "YAD",        NULL,   NULL,		0,		1,		-1 },
	{ "sent",       NULL,   NULL,		0,		1,		-1 },
	{ "imv",        NULL,   NULL,		0,		1,		-1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ " ",     monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STATUSBAR "dwmblocks"
/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static Key keys[] = {
    /* modifier         key				  			function	    argument */
    { MODKEY,           XK_d,						spawn,			SHCMD("dmenu_run") },
    { MODKEY,           XK_Return,					spawn,			SHCMD("st") },
//    { MODKEY,           XK_b,						togglebar,		{0} },
    { MODKEY,           XK_j,						focusstack,		{.i = +1 } },
    { MODKEY,           XK_k,						focusstack,		{.i = -1 } },
    { MODKEY,           XK_equal,					incnmaster,		{.i = +1 } },
    { MODKEY,           XK_minus,					incnmaster,		{.i = -1 } },
    { MODKEY,           XK_h,						setmfact,		{.f = -0.05} },
    { MODKEY,           XK_l,						setmfact,		{.f = +0.05} },
    { MODKEY,	      	XK_z,						zoom,			{0} },
    { MODKEY,           XK_Tab,						view,			{0} },
    { MODKEY,           XK_c,						killclient,		{0} },
    { ControlMask, 		XK_1,						setlayout,		{.v = &layouts[0]} },
    { ControlMask, 		XK_2,						setlayout,		{.v = &layouts[1]} },
    { ControlMask, 		XK_3,						setlayout,		{.v = &layouts[2]} },
    { MODKEY,			XK_space,					togglefloating, {0} },
    { MODKEY,           XK_0,						view,			{.ui = ~0 } },
    { MODKEY|ShiftMask, XK_0,						tag,			{.ui = ~0 } },
    { MODKEY,           XK_comma,					focusmon,       {.i = -1 } },
    { MODKEY,           XK_period,					focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask, XK_comma,					tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask, XK_period,					tagmon,         {.i = +1 } },
    { MODKEY,           XK_f,						spawn,          SHCMD("kis -f | dmenu -l 100 | xargs -0 nopen") },
    { 0,  		       	XK_Print,					spawn,          SHCMD("scrot") },
    { MODKEY, 	        XK_Print,					spawn,          SHCMD("scrot -s") },
    { MODKEY,           XK_End,						spawn,          SHCMD("doas pkill -kill -t tty1") },
    { MODKEY,           XK_Home,					spawn,          SHCMD("slock") },
    { 0,                XF86XK_AudioLowerVolume,	spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -1%") },
    { 0,                XF86XK_AudioMute,			spawn,          SHCMD("pactl set-sink-mute @DEFAULT_SINK@ toggle") },
    { 0,                XF86XK_AudioRaiseVolume,	spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +1%") },
    { 0,                XF86XK_AudioPrev,			spawn,          SHCMD("playerctl previous" ) },
    { 0,                XF86XK_AudioPause,			spawn,          SHCMD("playerctl pause") },
    { 0,                XF86XK_AudioNext,			spawn,          SHCMD("playerctl next") },
    { 0,                XF86XK_WLAN,				spawn,          SHCMD("rfkill unblock wifi") },
    TAGKEYS(            XK_1,                      0)
    TAGKEYS(            XK_2,                      1)
    TAGKEYS(            XK_3,                      2)
    TAGKEYS(            XK_4,                      3)
    TAGKEYS(            XK_5,                      4)
    TAGKEYS(            XK_6,                      5)
    TAGKEYS(            XK_7,                      6)
    TAGKEYS(            XK_8,                      7)
    TAGKEYS(            XK_9,                      8)
    { MODKEY|ShiftMask, XK_q,                     quit,		 {0} },
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
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
};
