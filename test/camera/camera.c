#include <kiss-graphics.h>
#include <kiss-input.h>
#include <blobtastic/camera.h>

void update()
{
	camera_update();
	graphics_blit(get_camera_frame(), 0, 0, get_camera_frame_width(), get_camera_frame_height());
	graphics_update();
}

int main(int argc, char *argv[])
{
	// Open the default camera
	if(!camera_open()) {
		printf("Unable to open camera. Is there one plugged in?\n");
		return 1;
	}
	
	// Get the first frame
	camera_update();
	
	graphics_init(get_camera_frame_width(), get_camera_frame_height());
	
	unsigned char ***myFrame;
	myFrame = (unsigned char ***)get_camera_frame();
	
	printf("R(100, 100) = %u\n", myFrame[100][100][0]);
	
	while(!kiss_get_key_bit('A')) {
		update();
	}
	
	
	
	graphics_quit();
	camera_close();
	
	return 0;
}