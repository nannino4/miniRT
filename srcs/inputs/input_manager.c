#include "header.h"
#include "ANSI-color-codes.h"

int	keyboard_input(int key, void *param)
{
	t_scene	*scene;

	scene = (t_scene*)param;
	printf("key pressed : %d\n", key);
	if (key == 53)
		exit_func(NULL);
	else if (key == 8)
		camera_wheel(scene);
	else if (key == MOVE_FORWARD || key == MOVE_BACK || key == MOVE_UP || \
			key == MOVE_DOWN || key == MOVE_DX || key == MOVE_SX || \
			key == ROT_UP || key == ROT_DOWN || key == ROT_DX || key == ROT_SX)
	{
		transform_camera(scene->cam, key);
		create_img(scene);
	}
	return (key);
}

int	mouse_input(int button, int x, int y, void *param)
{
	t_scene	*scene;
	t_ray	ray;

	scene = (t_scene*)param;
	printf("pressed mouse button : %d at %d,%d\n", button, x, y);
	create_ray(scene, &ray, x, y);
	find_intersection(&ray, scene);
	if (ray.intersection.distance < MAX_DISTANCE)
	{
		//TODO
	}
	return (1);
}

/*
   int     idle(void *param)
   {
   t_scene     *scene;

   scene = (t_scene*)param;

   return (1);
   }
   */

void	terminal_info(void)
{
	system("clear");
	printf(BCYN"CAMERA MOVEMENT :\n\tW - Move Forward\n\t");
	printf("S - Move Backward\n\tA - Move Left\n\tD - Move Right\n");
	printf("CAMERA ROTATION\n\t◀- - Rotate Left\n\t");
	printf("-▶ - Rotate Right\n\t⬇ - Rotate down\n\t");
	printf("⬆ - Rotate Up\n\n\tC - Cycle cameras\n\n");
	printf(BBLU"Press ESC or click the close button \
			on the window to exit\n"reset);
}
