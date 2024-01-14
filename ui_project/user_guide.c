#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lvgl.h>
#include "common.h"

struct user_guide_ctx_info {

};
lv_obj_t *test_label;
lv_obj_t *qrcode_context;
static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    lv_group_remove_all_objs(lv_group_get_default());
    lv_obj_clear_flag(qrcode_context, LV_OBJ_FLAG_HIDDEN);
}

void user_guide_init(lv_obj_t *parent)
{
    lv_obj_t *label;
    
    lv_group_remove_all_objs(lv_group_get_default());

    label = lv_label_create(parent);
    lv_group_add_obj(lv_group_get_default(), label);

    lv_label_set_text(label, "user guide");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_event_cb(label, event_handler, LV_EVENT_LONG_PRESSED_REPEAT, NULL);

    qrcode_context = lv_obj_create(parent);
    lv_obj_set_size(qrcode_context, lv_obj_get_width(parent), lv_obj_get_height(parent));
    lv_obj_add_flag(qrcode_context, LV_OBJ_FLAG_HIDDEN);

    return ;
}