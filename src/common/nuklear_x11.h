#ifndef __CLIVER_X11__
#define __CLIVER_X11__

#define XLIB_ILLEGAL_ACCESS
#include <X11/Xlib.h>
#include <X11/X.h>
#include <stdlib.h>
#include <string.h>

Display*     nuklear_XOpenDisplay(char*);
int          nuklear_XCloseDisplay(Display*);
KeySym       nuklear_XStringToKeysym(char*);
KeySym       nuklear_XLookupKeysym(XKeyEvent*,int);
XFontStruct* nuklear_XQueryFont(Display*,GContext);
XFontStruct* nuklear_XLoadQueryFont(Display*,char *);
int          nuklear_XParseGeometry(char*,int*,int*,unsigned int*,unsigned int*);
Window       nuklear_XCreateWindow(Display*,Window,int,int,unsigned int,unsigned int,unsigned int,int,unsigned int,Visual*,unsigned long,XSetWindowAttributes*);
Window       nuklear_XCreateSimpleWindow(Display*,Window,int,int,unsigned int,unsigned int,unsigned int,unsigned long,unsigned long);
Pixmap       nuklear_XCreateBitmapFromData(Display*,Drawable,char *,unsigned,unsigned int);
Pixmap       nuklear_XCreatePixmap(Display*,Drawable,unsigned int,unsigned int,unsigned int);
GC           nuklear_XCreateGC(Display*,Drawable,unsigned long,XGCValues*);
Atom         nuklear_XInternAtom(Display*,char*,Bool);
Cursor       nuklear_XCreateFontCursor(Display*,unsigned int);
Cursor       nuklear_XCreatePixmapCursor(Display*,Pixmap,Pixmap,XColor*,XColor*,unsigned int,unsigned int);
Cursor       nuklear_XCreateGlyphCursor(Display*,Font,Font,unsigned int,unsigned int,XColor*,XColor*);
int          nuklear_XFlush(Display*);
int          nuklear_XSync(Display*,Bool);
int          nuklear_XEventsQueued(Display*,int);
int          nuklear_XPilotHash(unsigned char*,int);
int          nuklear_XNextEvent(Display*,XEvent*);
int          nuklear_XPending(Display*);

#endif //__CLIVER_X11__
