/* user and group to drop privileges to */
static const char *user  = "nobody";
static const char *group = "nogroup";

static const char *colorname[NUMCOLS] = {
	[INIT] =   "black",     /* after initialization */
	[INPUT] =  "#005577",   /* during input */
	[FAILED] = "#CC3333",   /* wrong password */
};

/* treat a cleared input like a wrong password (color) */
static const int failonclear = 1;

/* enable blur */
#define BLUR
/* set blur radius */
static const int blurRadius=5;
/* enable Pixelation */
#define PIXELATION
/* set pixelation radius */
static const int pixelSize=5;

/* default message */
static const char * message = "ERROR: kernel panic";
/* text color */
static const char * text_color = "#ffffff";
/* text size (must be a valid size) */
static const char * font_name = "6x13";
