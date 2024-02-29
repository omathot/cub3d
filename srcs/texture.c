#include "../cub3d.h"

void wall_texture(t_param_mlx *param, t_point collision_point, char wall_face)
{
  // determine if collide on horizontal or vertical axis
  // take vertical row ON THE IMAGE(TEXTURE) that corresponds to the collision
  // "loop through resolution of the image and draw them as lines on the screen"
  // - in quotes cause I dont'get that part as much
  
  // int height = 400;
  // int width = 400;
  mlx_texture_t  *wall_N;
  mlx_texture_t  *wall_S;
  mlx_texture_t  *wall_E;
  mlx_texture_t  *wall_W;
  if (wall_face == 'N')
    mlx_texture_to_image(param->mlx, wall_N);
  if (wall_face == 'S')
    mlx_texture_to_image(param->mlx, wall_S);
  if (wall_face == 'W')
    mlx_texture_to_image(param->mlx, wall_W);
  if (wall_face == 'E')
    mlx_texture_to_image(param->mlx, wall_E);
  // mlx_new_image(param->mlx, width, height);

}
