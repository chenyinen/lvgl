#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <lvgl.h>
#include <x11.h>
#include "common.h"
#define X11_WIDTH 480
#define X11_HEIGHT 800


int main()
{
    lv_init();
    lv_x11_init("ui_project", X11_WIDTH, X11_HEIGHT);

    static lv_disp_draw_buf_t disp_buf;
    void *buf = malloc(X11_WIDTH * X11_HEIGHT * 4);
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, X11_WIDTH * X11_HEIGHT);

    static lv_disp_drv_t disp_drv;          
    lv_disp_drv_init(&disp_drv);            
    disp_drv.draw_buf = &disp_buf;          
    disp_drv.flush_cb = lv_x11_flush;       
    disp_drv.hor_res = X11_WIDTH;           
    disp_drv.ver_res = X11_HEIGHT;          
    disp_drv.direct_mode = 1;

    static lv_group_t * g;
    lv_disp_t * disp;
    lv_indev_t *indev;
    g = lv_group_create();
    lv_group_set_default(g);
    disp = lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv_point;       
    lv_indev_drv_init(&indev_drv_point);         
    indev_drv_point.type = LV_INDEV_TYPE_POINTER;
    indev_drv_point.read_cb = lv_x11_get_pointer;
    lv_indev_drv_register(&indev_drv_point);     

    static lv_indev_drv_t indev_drv_key;         
    lv_indev_drv_init(&indev_drv_key);           
    indev_drv_key.type = LV_INDEV_TYPE_KEYPAD;   
    indev_drv_key.read_cb = lv_x11_get_keyboard; 
    lv_indev_drv_register(&indev_drv_key);       

    static lv_indev_drv_t indev_drv_encode;      
    lv_indev_drv_init(&indev_drv_encode);        
    indev_drv_encode.type = LV_INDEV_TYPE_ENCODER;    
    indev_drv_encode.read_cb = lv_x11_get_mousewheel; 
    indev = lv_indev_drv_register(&indev_drv_encode);         
    lv_indev_set_group(indev, g);
    
    ui_app_init();

    while(1) {
        lv_task_handler();
        lv_tick_inc(10); 
        usleep(1000*10);
    }

    return 0;
}