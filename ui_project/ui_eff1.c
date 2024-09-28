#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lvgl.h>
#include "common.h"

static void move(void * obj, int32_t v)
{
    lv_draw_img_dsc_t draw_dsc;
    lv_draw_img_dsc_init(&draw_dsc);
    lv_canvas_draw_img(obj, 0, 0, "A:/home/share/1.png", &draw_dsc);

    draw_dsc.opa = v;
    lv_canvas_draw_img(obj, 0, 0, "A:/home/share/2.png", &draw_dsc);
}


void ui_app_init(lv_obj_t *parent)
{

    /*Create a buffer for the canvas*/
    static lv_color_t cbuf[LV_IMG_BUF_SIZE_TRUE_COLOR_ALPHA(160, 160)];

    /*Create a canvas and initialize its palette*/
    lv_obj_t * canvas = lv_canvas_create(lv_scr_act());
    lv_canvas_set_buffer(canvas, cbuf, 160, 160, LV_IMG_CF_TRUE_COLOR_ALPHA);

    lv_obj_center(canvas);

    lv_draw_img_dsc_t draw_dsc;
    lv_draw_img_dsc_init(&draw_dsc);
    lv_canvas_draw_img(canvas, 0, 0, "A:/home/share/1.png", &draw_dsc);

    lv_canvas_draw_img(canvas, 0, 0, "A:/home/share/2.png", &draw_dsc);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, canvas);
    lv_anim_set_exec_cb(&a, move);
    lv_anim_set_time(&a, 1500);
    lv_anim_set_values(&a, LV_OPA_COVER, LV_OPA_TRANSP);
    lv_anim_start(&a);


    return ;
}