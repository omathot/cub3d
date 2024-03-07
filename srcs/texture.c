#include "../cub3d.h"
#include <sys/_types/_u_int32_t.h>

// Get the red channel
int get_r(int rgba) { return ((rgba >> 24) & 0xFF); }

// Get the green channel
int get_g(int rgba) { return ((rgba >> 16) & 0xFF); }

// Get the blue channel.
int get_b(int rgba) { return ((rgba >> 8) & 0xFF); }

// Get the alpha channel.
int get_a(int rgba) { return (rgba & 0xFF); }

void get_rgba(int i, mlx_image_t *to_place, int *r, int *g, int *b) {
  int rgba;
  rgba = (to_place->pixels[i * 4] << 24) | (to_place->pixels[i * 4 + 1] << 16) |
         (to_place->pixels[i * 4 + 2] << 8) | (to_place->pixels[i * 4 + 3]);
  (*r) = get_r(rgba);
  (*g) = get_g(rgba);
  (*b) = get_b(rgba);
}

char *get_data_line(t_param_mlx *param, char x) {
  char *to_return;
  int i;
  int j;
  int k;

  i = 0;
  k = 0;
  to_return =
      (char *)malloc(sizeof(ft_strlen(param->map.file_data[i]) * 2 + 1));
  while (param->map.file_data[i]) {
    j = 0;
    if (param->map.file_data[i][j] == x) {
      while (!(ft_isspace(param->map.file_data[i][j])))
        j++;
      j++;
      while (param->map.file_data[i][j]) {
        to_return[k] = param->map.file_data[i][j];
        j++;
        k++;
      }
      to_return[k] = '\0';
    }
    i++;
  }
  return (to_return);
}

t_texture_data normalize_collision_point(t_point collision_point, bool side) {
  t_texture_data data;

  if (!side) {
    data.wall_n = round(collision_point.x - 0.5);
    data.decimal = (collision_point.x - data.wall_n);
  } else {
    data.wall_n = round(collision_point.y - 0.5);
    data.decimal = (collision_point.y - data.wall_n);
  }
  return (data);
}

uint32_t get_collor(int r, int g, int b, int a);

void wall_texture(t_param_mlx *param, int screen_x, t_point collision_point,
                  char wall_face, double wall_height) {
  // take vertical row ON THE IMAGE(TEXTURE) that corresponds to the collision
  // "loop through resolution of the image and draw them as lines on the screen"
  int i = 0;
  int red = 0, green = 0, blue = 0, rgba = 0;
  // int y = 0;
  mlx_image_t *to_place;
  int screen_height = 720;
  to_place = NULL;
  if (wall_face == 'N')
    to_place = mlx_texture_to_image(param->mlx, param->map.wall_N);
  else if (wall_face == 'S')
    to_place = mlx_texture_to_image(param->mlx, param->map.wall_S);
  else if (wall_face == 'E')
    to_place = mlx_texture_to_image(param->mlx, param->map.wall_E);
  else if (wall_face == 'W')
    to_place = mlx_texture_to_image(param->mlx, param->map.wall_W);
  printf("heigh is = (%i), width = (%i)\n", to_place->height, to_place->width);
  int size = (to_place->height * to_place->width) - 1;
  while (i <= size) {
    rgba = (to_place->pixels[i * 4] << 24) |
           (to_place->pixels[i * 4 + 1] << 16) |
           (to_place->pixels[i * 4 + 2] << 8) | (to_place->pixels[i * 4 + 3]);
    red = get_r(rgba);
    green = get_g(rgba);
    blue = get_b(rgba);
    // alpha = get_a(rgba);
    // printf("pixel[%i] = (%i)\nred = (%i), green = (%i), blue = (%i)\n", i,
    //        to_place->pixels[i], red, green, blue);
    i++;
  }
  // pause();
  double magnitude =
      sqrt(pow((param->map.player.pos.x - collision_point.x), 2) +
           pow(param->map.player.pos.y - collision_point.y, 2));
  t_texture_data normalized = normalize_collision_point(
      collision_point, wall_face == 'E' || wall_face == 'W');
  // Now convert this to a texture coordinate
  int texture_x = (int)(normalized.decimal * to_place->width);
  // Calculate start_y and end_y ensuring we are within screen bounds
  double start_y =
      ((double)param->y_resolution / 2) - (wall_height / magnitude);
  if (start_y < 0)
    start_y = 0;

  int end_y = ((double)param->y_resolution / 2) + (wall_height / magnitude);
  if (end_y > screen_height)
    end_y = screen_height;

  // Clamp texture_x to within bounds
  if (texture_x < 0)
    texture_x = 0;
  else if (texture_x >= (int)to_place->width)
    texture_x = to_place->width - 1;

  // Loop over each y coordinate and draw the wall slice
  int y = 0;
  int y_diff = fabs(start_y - end_y) - 1;
  while (y < y_diff) {
    int texture_y =
        (int)((y / (wall_height / magnitude) / 2) * to_place->height);
    // Clamp texture_y to within bounds
    if (texture_y < 0)
      texture_y = 0;
    else if (texture_y >= (int)to_place->height)
      texture_y = to_place->height - 1;
    // int offset = (texture_y * to_place->width + texture_x) *
    //              4; // Assuming 4 bytes per pixel
    // Get the color from the texture
    // ((((y / wall_height) * to_place->height) * to_place->width) + texture_x)
    get_rgba(texture_y * to_place->width + texture_x, to_place, &red, &green,
             &blue);
    u_int32_t color = get_collor(red, green, blue, 255);
    // printf("color = (%d)\n", color);
    // Draw a vertical line at screen_x and y with the fetched color
    mlx_put_pixel(param->image_to_draw_pixel, floor(screen_x),
                  (floor(start_y) + y), color);
    // Increment the y coordinate
    y++;
  }
  mlx_delete_image(param->mlx, to_place);
}
