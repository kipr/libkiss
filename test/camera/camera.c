#include <kiss-graphics.h>
#include <kiss-input.h>
#include <math.h>
#include <blobtastic/camera.h>

#define TOU 3
#define ALPHA 0.02f

int is_foreground(short i, short b)
{
	return abs(i - b) > TOU ? 1 : 0;
}

void update(unsigned char *background)
{
	camera_update();
	
	unsigned char data[get_camera_frame_size()];
	
	put_camera_frame(data);
	
	int i = 0;
	for(i = 0; i < get_camera_frame_size(); i += 3) {
		if(!is_foreground(background[i + 0], data[i + 0])
			|| !is_foreground(background[i + 1], data[i + 1])
			|| !is_foreground(background[i + 2], data[i + 2]))
		{
			data[i] = data[i + 1] = data[i + 2] = 0;
		}
	}
	for(i = 0; i < get_camera_frame_size(); ++i) {
		background[i] = ALPHA * (float)data[i] + (1.0 - ALPHA) * (float)background[i];
	}
	graphics_blit(data, 0, 0, get_camera_frame_width(), get_camera_frame_height());
	graphics_update();
}

int main(int argc, char *argv[])
{
	// Open the default camera
	if(!camera_open()) {
		printf("Unable to open camera. Is there one plugged in?\n");
		return 1;
	}
	
	unsigned char data[get_camera_frame_size()];
	put_camera_frame_hsv(data);
	
	
	graphics_init(get_camera_frame_width(), get_camera_frame_height());
	
	while(!kiss_get_mouse_button(0)) {
		update(data);
	}
	
	
	
	graphics_quit();
	// camera_close();
	
	return 0;
}