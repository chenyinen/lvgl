#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lvgl.h>
#include "common.h"

static void move(void * obj, int32_t v)
{
    lv_obj_align(obj, LV_ALIGN_CENTER, 240 -v, 0);
    lv_img_set_angle(obj, v*10);
    lv_obj_set_style_img_recolor(obj, lv_palette_main(LV_PALETTE_RED), 0);
    lv_obj_set_style_img_recolor_opa(obj, v, 0);
}

void ui_example1(lv_obj_t *parent)
{
    lv_obj_t *img;
    
    img = lv_img_create(lv_scr_act());
    lv_img_set_src(img, "A:/home/share/call2.png");
    lv_obj_align(img, LV_ALIGN_RIGHT_MID, 0, 0);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, img);
    lv_anim_set_exec_cb(&a, move);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_values(&a, 0, 240);
    lv_anim_start(&a);

    return ;
}