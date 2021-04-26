#pragma once

#define MAXPERIOD 99.0
#define MINPERIOD 10.0

extern void quit(Widget w, void *data);

extern void clear(Widget w, void *data);

extern void button_up(Widget w, int which_button, int x, int y, void *data);

extern void redraw(Widget w, int width, int height, void *data);

extern void  set_timeout_val(Widget w, float val, void *data);

extern void  tic(void *data);

extern void anim(Widget w, void *data);

extern void load(Widget w, char *string, void *data);

extern void loadb(Widget w, void *data);

extern void saveb(Widget w, void *data);

extern void modb(Widget w, void *data);

extern void helpb(Widget w, void *data);

extern void gridb(Widget w, void *data);

