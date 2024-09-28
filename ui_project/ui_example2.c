#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lvgl.h>
#include "common.h"

int width;
lv_obj_t *img;
static void event_cb(lv_event_t * e)
{
    /*The original target of the event. Can be the buttons or the container*/
    lv_draw_ctx_t * draw_ctx = lv_event_get_draw_ctx(e);
    
    memset(draw_ctx->clip_area, 0, sizeof(draw_ctx->clip_area));
}
static void move(void * obj, int32_t v)
{
 

    lv_obj_set_style_arc_width(obj, v, 0);
}

void ui_example_2(lv_obj_t *parent)
{
    lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE);

    img = lv_img_create(lv_scr_act());
    lv_obj_set_size(img, 480, 800);
    lv_obj_set_style_bg_img_src(img, "A:/home/share/test.jpg", 0);
    //lv_obj_set_style_bg_img_src(lv_scr_act(), "A:/home/share/test.jpg", 0);
    lv_obj_add_event_cb(img, event_cb, LV_EVENT_DRAW_MAIN, NULL);
    lv_obj_t *obj;


    lv_obj_t * arc = lv_arc_create(lv_scr_act());
    lv_obj_set_size(arc, 940, 940);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_arc_set_value(arc, 360);
    lv_obj_remove_style(arc, NULL, LV_PART_INDICATOR);   /*Be sure the knob is not displayed*/
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_center(arc);
    //lv_obj_set_style_arc_width(arc, 240, 0);
    lv_obj_set_style_arc_color(arc, lv_color_black(), 0);
    //lv_obj_set_style_bg_color();
    //lv_obj_add_event_cb(obj, event_cb, LV_EVENT_DRAW_MAIN, NULL);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, arc);
    lv_anim_set_exec_cb(&a, move);
    lv_anim_set_time(&a, 1500);
    lv_anim_set_delay(&a, 1500);
    lv_anim_set_values(&a, 0, 470);
    lv_anim_start(&a);

    return ;
}