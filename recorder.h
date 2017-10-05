// Vasili B
// 10/04/2017

#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <pthread.h>

void get_frame(char *, XImage *, int, int, int, int);
int save_frame(char *, char *, int, int);
unsigned long XGetPixel(XImage *, int, int);
