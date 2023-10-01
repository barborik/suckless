/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 2;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrains Mono:size=10" };
static const char dmenufont[]       = "JetBrains Mono:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

static const char col_dblue[]       = "#161821";
static const char col_lblue[]       = "#6b7089";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_lblue, col_dblue, col_gray2 },
	[SchemeSel]  = { col_dblue, col_lblue, col_cyan  },
};

/* tagging */
static const char *tags[] = { "tty", "dev", "www", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY|ShiftMask,             KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY,                       KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier             key    function        argument */
	{ MODKEY,               40,    spawn,          {.v = dmenucmd } },   // d
	{ MODKEY,               36,    spawn,          {.v = termcmd } },    // enter
	{ MODKEY,               0,     togglebar,      {0} },                // NULL
	{ MODKEY,               0,     focusstack,     {.i = +1 } },         // NULL
	{ MODKEY,               0,     focusstack,     {.i = -1 } },         // NULL
	{ MODKEY,               0,     incnmaster,     {.i = +1 } },         // NULL
	{ MODKEY,               0,     incnmaster,     {.i = -1 } },         // NULL
	{ MODKEY,               0,     setmfact,       {.f = -0.05} },       // NULL
	{ MODKEY,               0,     setmfact,       {.f = +0.05} },       // NULL
	{ MODKEY,               0,     zoom,           {0} },                // NULL
	{ MODKEY,               0,     view,           {0} },                // NULL
	{ MODKEY|ShiftMask,     24,    killclient,     {0} },                // q
	{ MODKEY,               0,     setlayout,      {.v = &layouts[0]} }, // NULL
	{ MODKEY,               0,     setlayout,      {.v = &layouts[1]} }, // NULL
	{ MODKEY,               0,     setlayout,      {.v = &layouts[2]} }, // NULL
	{ MODKEY,               0,     setlayout,      {0} },                // NULL
	{ MODKEY|ShiftMask,     0,     togglefloating, {0} },                // NULL
	{ MODKEY,               0,     view,           {.ui = ~0 } },        // NULL
	{ MODKEY|ShiftMask,     0,     tag,            {.ui = ~0 } },        // NULL
	{ MODKEY,               0,     focusmon,       {.i = -1 } },         // NULL
	{ MODKEY,               0,     focusmon,       {.i = +1 } },         // NULL
	{ MODKEY|ShiftMask,     0,     tagmon,         {.i = -1 } },         // NULL
	{ MODKEY|ShiftMask,     0,     tagmon,         {.i = +1 } },         // NULL
	{ MODKEY,               20,    setgaps,        {.i = -1 } },         // =
	{ MODKEY,               21,    setgaps,        {.i = +1 } },         // ´
	{ MODKEY|ShiftMask,     0,     setgaps,        {.i = 0  } },         // NULL
	TAGKEYS(                10,                    0)                    // 1
	TAGKEYS(                11,                    1)                    // 2
	TAGKEYS(                12,                    2)                    // 3
	TAGKEYS(                13,                    3)                    // 4
	TAGKEYS(                14,                    4)                    // 5
	TAGKEYS(                15,                    5)                    // 6
	TAGKEYS(                16,                    6)                    // 7
	TAGKEYS(                17,                    7)                    // 8
	TAGKEYS(                18,                    8)                    // 9
	{ MODKEY|ShiftMask,     0,    quit,            {0} },                // NULL


        { MODKEY,               107,  spawn,           SHCMD("maim -s -u | xclip -selection clipboard -t image/png -i") },      // prtscr
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

