// Vasili B
// 10/04/2017

#include "recorder.h"

#define WIDTH 100
#define HEIGHT 100

int main() {
    Display * dpy = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(dpy);
    
    XImage * image = XGetImage(dpy, root, 0, 0, WIDTH, HEIGHT, AllPlanes, ZPixmap);
    
    char frame[WIDTH*HEIGHT*3];
    
    get_frame(frame, image, 0, 0, WIDTH, HEIGHT);
    
    save_frame(frame, "test.ppm", WIDTH, HEIGHT);
}

void get_frame(char * frame, XImage * image,
               int x_offset, int y_offset, int w, int h) {
    unsigned long pixel;
    
    unsigned long r_mask = image->red_mask;
    unsigned long g_mask = image->green_mask;
    unsigned long b_mask = image->blue_mask;
    
    
    for (int y = y_offset; y < h; y++) {
        for (int x = x_offset; x < w; x++) {
            pixel = XGetPixel(image, x, y);
            
            frame[((y * w) + x) * 3 + 0] = (pixel & r_mask) >> 16;
            frame[((y * w) + x) * 3 + 1] = (pixel & g_mask) >> 8;
            frame[((y * w) + x) * 3 + 2] = (pixel & b_mask);
        }
    }
}

int save_frame(char * frame, char * filename, int w, int h) {
    FILE * out_file;
    
    out_file = fopen(filename, "w");
    
    if (!out_file) {
        printf("Could not open file");
        return(1);
    }
    
    fprintf(out_file, "P6\n");
    fprintf(out_file, "%d %d\n", w, h);
    fprintf(out_file, "%d\n", 255);
    
    for(int i = 0; i < w*h*3; i++)
        fprintf(out_file, "%c", frame[i]);
    
    fclose(out_file);
    
    return(0);
}
