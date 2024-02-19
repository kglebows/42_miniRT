#ifndef STRUCT_H
# define STRUCT_H

/**
 * @brief Simple boolean definition for checks and returns
 * @param OK Positive outcome, value = 0
 * @param KO Negative outcome, value = 1
 */
typedef enum e_ok
{
	OK,
	KO
}			t_ok;

/**
 * @brief RGB colour representation. Values of 0-255
 * @param r RED
 * @param g GREEN
 * @param b BLUE
 */
typedef struct s_rgb
{
	int			r;
	int			g;
	int			b;
}				t_rgb;

/**
 * @brief POINT in XYZ coordinate system.
 * Z axis is a cross product of X and Y axises. X goes right, Y goes up, Z goes towards you.
 * @param x coordinate along the X axis (Width)
 * @param y coordinate along the Y axis (Height)
 * @param z coordinate along the Z axis (Depth)
 */
typedef struct s_point
{
	double		x;
	double		y;
	double		z;
}				t_point;

/**
 * @brief VECTOR in XYZ coordinate system. It represents a direction
 * in 3d space multiplied by its magnitude (lenght). Normalized Vector has a lenght = 1.
 * Z axis is a cross product of X and Y axises. X goes right, Y goes up, Z goes towards you.
 * @param x Direction along X axis multiplied by vector lenght (Width)
 * @param y Direction along Y axis multiplied by vector lenght (Height)
 * @param z Direction along Z axis multiplied by vector lenght (Depth)
 */
typedef struct s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

/**
 * @brief Ray represents a vector attached to a point.
 * @param origin A starting point of a vector
 * @param direction A vector consisting of direction multiplied by lenght.
 */
typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}				t_ray;




typedef struct		s_cam
{
//	t_img			img;
	t_point			point;
	t_point			normal;
	float			fov;
//	t_coord			hor;
//	t_coord			ver;
//	t_coord			llc;
	struct s_cam	*next;
}					t_cam;

typedef struct		s_resol
{
	int				x;
	int				y;
}					t_resol;

typedef struct		s_ambilight
{
	double			ratio;
	t_rgb			rgb;
}					t_ambilight;


/**
 * @brief Type of element
 * @param BG Background
 * @param SP Sphere
 * @param PL Plane
 * @param CY Cylinder
 */
typedef enum e_elemtype
{
	BG,
	SP,
	PL,
	CY
}			t_elemtype;

/**
 * @brief Unified sturcture for list of all elements.
 * @param type type of an element
 * @param center center of Sphere/Cylinder or point on plane
 * @param axis Normalized vector. Axis of cylinder/Plane face
 * @param oc Vector from center to camera
 * @param color rgb color of element
 * @param diameter diameter of sphere/cylinder
 * @param height height of cylinder
 * @param next next element on the list. NULL == end of list
 */
typedef struct		s_elem
{
	t_elemtype		type;
	t_point			center;
	t_vector		axis;
	t_vector		oc;
	t_rgb			color;
	double			ratio;
	double			diameter;
	double			height;
	struct s_elem	*next;
}					t_elem;


typedef struct		s_scene
{
	char			*line;
	char			**split;
	short int		qtys[9];
	t_resol			resol;
	t_ambilight		ambilight;
	t_cam			*cam;
	t_elem			*light;
	t_elem			*sp;
	t_elem			*pl;
	t_elem			*cy;
}					t_scene;


typedef struct s_dt
{
	u_int32_t		screen_width;
	u_int32_t		screen_height;
	// mlx_t			*mlx;
	// mlx_image_t		*img;
	t_vector		delta_u;
	t_vector		delta_v;
	t_point			pixel_center;
	t_point			cam_pos;
	t_elem			*elements;
}					t_dt;

typedef void		(*parse_function_arr)(t_scene *);
#endif
