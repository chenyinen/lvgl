#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lvgl.h>
#include "common.h"

static lv_obj_t * arc;
static lv_obj_t * label;
static void set_angle(void * obj, int32_t v)
{
    static int last_value = 0;
    if (v > last_value) {
        lv_arc_set_value(obj, v);
        lv_label_set_text_fmt(label, "%" LV_PRId32 "%%", v);
        last_value = v;
    }
    
}
static void wifi_connect_play(int value)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, arc);
    lv_anim_set_exec_cb(&a, set_angle);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_values(&a, 0, value);
    lv_anim_start(&a);
}
static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_anim_t *anim;
    static int i =10;

    if (i<=100) {
        anim = lv_anim_get(arc, set_angle);
        if (anim) {
            anim->end_value = i;
        }
        else {
            wifi_connect_play(i);
        }
        i+=10;
    }
}
/**
 * Create an arc which acts as a loader.
 */
void wifi_connecting_init(lv_obj_t *parent)
{
    arc = lv_arc_create(parent);
    lv_arc_set_value(arc, 0);
    lv_arc_set_rotation(arc, 270);
    lv_arc_set_bg_angles(arc, 0, 360);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_center(arc);

    label = lv_label_create(arc);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text_fmt(label, "%" LV_PRId32 "%%", 0);
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

    return ;
}