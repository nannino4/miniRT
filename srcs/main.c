#include "header.h"

void	init_scene(t_scene *scene)
{
	scene->w = 0;
	scene->h = 0;
	scene->mlx = 0;
	scene->win = 0;
	scene->threading = &create_img;
	scene->aa_func = &pixel_no_aa;
	scene->save = 0;
	scene->amb_l.brightness = 0;
	scene->light = 0;
	scene->selected_light = 0;
	scene->cam = 0;
	scene->obj = 0;
	scene->selected_obj = 0;
}

void	read_input(t_scene *scene, char *file)
{
	int			fd;
	char		*line;

	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
			add_element_to_scene(&line, scene);
	}
}

void	manage_scene(t_scene *scene)
{
	if (scene->save)
	{
		create_img_threaded(scene);
		printf(BGRN"Image Saved at program binary location !\n"RESET);
	}
	else
		scene->threading(scene);
	mlx_key_hook(scene->win, keyboard_input, scene);
	mlx_mouse_hook(scene->win, mouse_input, scene);
	mlx_hook(scene->win, 17, 1L<<2, exit_func, NULL);
	if(!scene->save)
	{
		main_info();
		mlx_loop(scene->mlx);
	}
}

int		check_name(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	if (s[i - 1] != 't' || s[i - 2] != 'r' || s[i - 3] != '.')
		return (0);
	return (1);
}

int	check_flags(int argc, char **argv, t_scene *scene)
{
	if (argc < 2)
		return (0);
	while (argc > 2)
	{
		if (!ft_strncmp(argv[argc - 1], "--save", 7))
			scene->save = 1;
		else if (!ft_strncmp(argv[argc - 1], "--aa", 5))
			scene->aa_func = &pixel_with_aa;
		else if (!ft_strncmp(argv[argc - 1], "--threaded", 11))
			scene->threading = &create_img_threaded;
		argc--;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_scene		scene;

	init_scene(&scene);
	if (check_flags(argc, argv, &scene) && check_name(argv[1]))
	{
		scene.mlx = mlx_init();
		read_input(&scene, argv[1]);
		scene.win = mlx_new_window(scene.mlx, scene.w, scene.h,
				"miniRT");
		manage_scene(&scene);
	}
	else
	{
		//TODO error: "invalid input format"
	}
	return (0);
}
