
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <unistd.h>

#include "lvgl/lvgl.h"
#include "lv_100ask_teach_demos/lv_100ask_teach_demos.h"
#include "lv_demos/src/lv_demo_widgets/lv_demo_widgets.h"
#include "lv_drivers/win32drv/win32drv.h"

#include <windows.h>


/*********************
 *      DEFINES
 * 
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void hal_init(void);
static int tick_thread(void *data);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t *disp_area;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void label_clicked_cb(lv_event_t *e)
{
    //如果是点击事件
     lv_event_code_t code = lv_event_get_code(e);
     if(code == LV_EVENT_CLICKED)
     {
        printf("label_clicked_cb\n");
     }
}

static lv_obj_t*registerbtn;
static lv_obj_t*loginbtn ;



//创建按钮的函数
static lv_obj_t* create_button(lv_obj_t* parent, const char* text, lv_align_t align, lv_coord_t x_ofs, lv_coord_t y_ofs, lv_event_cb_t event_cb)
{
    lv_obj_t *btn = lv_btn_create(parent);
    lv_obj_set_size(btn, 60, 60);
    lv_obj_align(btn, align, x_ofs, y_ofs);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_28, 0);
    lv_obj_set_align(label, LV_ALIGN_CENTER);

    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_ALL, NULL);

    return btn;
}


static void btn_clicked_cb(lv_event_t * e)
{
    lv_obj_t *btn = lv_event_get_target(e);
    lv_obj_t *label = lv_obj_get_child(btn, 0);
    const char *text = lv_label_get_text(label);

    // 获取当前显示的数据
    const char *current_text = lv_label_get_text(disp_area);

    // 更新显示数据
    static char new_text[256];
    snprintf(new_text, sizeof(new_text), "%s%s", current_text, text);
    lv_label_set_text(disp_area, new_text);
}



/*************** 
我创建的内容开始
***************/


static lv_obj_t * kb;

static lv_obj_t * pass_ta;
static lv_obj_t * pass_vis_btn;

void login_event_handler(lv_event_t * e) {
    // Handle the login button click event
    // You can add your login logic here
    printf("Login button clicked\n");
}

void register_event_handler(lv_event_t * e) {
    // Handle the register button click event
    // You can add your register logic here
    printf("Register button clicked\n");
}



void kb_event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_keyboard_def_event_cb(e);  // Use the default keyboard event callback
    }
    else if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);  // Hide the keyboard
    }
}

void ta_event_cb(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    if (code == LV_EVENT_FOCUSED) {
        lv_keyboard_set_textarea(kb, lv_event_get_target(e));  // Link the keyboard to this text area
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);  // Show the keyboard
    }
}


void pass_vis_btn_event_cb(lv_event_t * e) {
    static bool pass_visible = false;
    pass_visible = !pass_visible;
    if (pass_visible) {
        lv_textarea_set_password_mode(pass_ta, false);
        lv_label_set_text(lv_obj_get_child(pass_vis_btn, 0), "Hide");
    } else {
        lv_textarea_set_password_mode(pass_ta, true);
        lv_label_set_text(lv_obj_get_child(pass_vis_btn, 0), "Show");
    }
}

void create_login_screen() {
    lv_obj_t * scr = lv_scr_act();  // Get the current screen

    // Create a background
    lv_obj_t * bg = lv_obj_create(scr);
    lv_obj_set_size(bg, 800, 480);
    lv_obj_center(bg);
    lv_obj_set_style_bg_color(bg, lv_color_hex(0xFFFFFF), 0);  // White background

    // Create a label for the title
    lv_obj_t * title = lv_label_create(scr);
    lv_label_set_text(title, "Login");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_28, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);

    // Create a label for the username
    lv_obj_t * user_label = lv_label_create(scr);
    lv_label_set_text(user_label, "Username:");
    lv_obj_align(user_label, LV_ALIGN_CENTER, -150, -50);

    // Create a text area for the username
    lv_obj_t * user_ta = lv_textarea_create(scr);
    lv_obj_set_size(user_ta, 200, 40);
    lv_obj_align(user_ta, LV_ALIGN_CENTER, 50, -50);
    lv_textarea_set_placeholder_text(user_ta, "Enter your username");
    lv_obj_add_event_cb(user_ta, ta_event_cb, LV_EVENT_ALL, NULL);

    // Create a label for the password
    lv_obj_t * pass_label = lv_label_create(scr);
    lv_label_set_text(pass_label, "Password:");
    lv_obj_align(pass_label, LV_ALIGN_CENTER, -150, 10);

    // Create a text area for the password
    pass_ta = lv_textarea_create(scr);
    lv_obj_set_size(pass_ta, 200, 40);
    lv_obj_align(pass_ta, LV_ALIGN_CENTER, 50, 10);
    lv_textarea_set_password_mode(pass_ta, true);
    lv_textarea_set_placeholder_text(pass_ta, "Enter your password");
    lv_obj_add_event_cb(pass_ta, ta_event_cb, LV_EVENT_ALL, NULL);

    // Create a button for toggling password visibility
    pass_vis_btn = lv_btn_create(scr);
    lv_obj_set_size(pass_vis_btn, 60, 40);
    lv_obj_align_to(pass_vis_btn, pass_ta, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    lv_obj_add_event_cb(pass_vis_btn, pass_vis_btn_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_t * pass_vis_label = lv_label_create(pass_vis_btn);
    lv_label_set_text(pass_vis_label, "Show");
    lv_obj_center(pass_vis_label);

    // Create a button for login
    lv_obj_t * login_btn = lv_btn_create(scr);
    lv_obj_set_size(login_btn, 100, 50);
    lv_obj_align(login_btn, LV_ALIGN_CENTER, -60, 100);
    lv_obj_add_event_cb(login_btn, login_event_handler, LV_EVENT_CLICKED, NULL);

    // Create a label on the login button
    lv_obj_t * btn_label = lv_label_create(login_btn);
    lv_label_set_text(btn_label, "Login");
    lv_obj_center(btn_label);

    // Create a button for register
    lv_obj_t * register_btn = lv_btn_create(scr);
    lv_obj_set_size(register_btn, 100, 50);
    lv_obj_align(register_btn, LV_ALIGN_CENTER, 60, 100);
    lv_obj_add_event_cb(register_btn, register_event_handler, LV_EVENT_CLICKED, NULL);

    // Create a label on the register button
    lv_obj_t * reg_btn_label = lv_label_create(register_btn);
    lv_label_set_text(reg_btn_label, "Register");
    lv_obj_center(reg_btn_label);

    // Create a keyboard
    kb = lv_keyboard_create(scr);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);  // Initially hidden
    lv_obj_add_event_cb(kb, kb_event_cb, LV_EVENT_ALL, NULL);
}


/*************** 
我创建的内容结束
***************/


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
    /*Initialize LittlevGL*/
    lv_init();

    /*Initialize the HAL for LittlevGL*/
    lv_win32_init(hInstance, SW_SHOWNORMAL, 800, 480, NULL);

    /*Output prompt information to the console, you can also use printf() to print directly*/
    LV_LOG_USER("LVGL initialization completed!");

    //这是我的创建内容
    create_login_screen();//创建登录界面


    while(!lv_win32_quit_signal)
    {

        lv_task_handler();
        usleep(10000);       /*Just to let the system breath*/
    }
    return 0;
}
