#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lvgl.h>
#include <x11.h>

#define X11_WIDTH 480
#define X11_HEIGHT 800

int main()
{
    lv_init();
    lv_x11_init("test", X11_WIDTH, X11_HEIGHT);

    static lv_disp_draw_buf_t disp_buf;
    void *buf = malloc(X11_WIDTH * X11_HEIGHT * 4);
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, X11_WIDTH * X11_HEIGHT);

    static lv_disp_drv_t disp_drv;          /*A variable to hold the drivers. Must be static or global.*/
    lv_disp_drv_init(&disp_drv);            /*Basic initialization*/
    disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
    disp_drv.flush_cb = lv_x11_flush;        /*Set a flush callback to draw to the display*/
    disp_drv.hor_res = X11_WIDTH;                 /*Set the horizontal resolution in pixels*/
    disp_drv.ver_res = X11_HEIGHT;                 /*Set the vertical resolution in pixels*/
    disp_drv.direct_mode = 1;

    lv_disp_t * disp;
    disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

    static lv_indev_drv_t indev_drv_point;           /*Descriptor of a input device driver*/
    lv_indev_drv_init(&indev_drv_point);             /*Basic initialization*/
    indev_drv_point.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
    indev_drv_point.read_cb = lv_x11_get_pointer;      /*Set your driver function*/
    lv_indev_drv_register(&indev_drv_point);         /*Finally register the driver*/

    static lv_indev_drv_t indev_drv_key;           /*Descriptor of a input device driver*/
    lv_indev_drv_init(&indev_drv_key);             /*Basic initialization*/
    indev_drv_key.type = LV_INDEV_TYPE_KEYPAD;    /*Touch pad is a pointer-like device*/
    indev_drv_key.read_cb = lv_x11_get_keyboard;      /*Set your driver function*/
    lv_indev_drv_register(&indev_drv_key);         /*Finally register the driver*/

    static lv_indev_drv_t indev_drv_encode;           /*Descriptor of a input device driver*/
    lv_indev_drv_init(&indev_drv_encode);             /*Basic initialization*/
    indev_drv_encode.type = LV_INDEV_TYPE_ENCODER;    /*Touch pad is a pointer-like device*/
    indev_drv_encode.read_cb = lv_x11_get_mousewheel;      /*Set your driver function*/
    lv_indev_drv_register(&indev_drv_encode);         /*Finally register the driver*/

    lv_demo_keypad_encoder();

    while(1) {
        lv_task_handler();
        lv_tick_inc(10); 
        usleep(1000*10);
    }

    return 0;
}