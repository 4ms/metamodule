
class LVGLDriver {

	LVGLDriver()
	{
		static lv_disp_buf_t disp_buf;
		static lv_color_t buf[LV_HOR_RES_MAX * LV_VER_RES_MAX / 10]; /*Declare a buffer for 1/10 screen size*/
		lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX / 10); /*Initialize the display buffer*/
	}
};
