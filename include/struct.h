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

/**
 * @brief Main data structure that holds all information needed for the program.
 */
typedef struct s_dt
{

}				t_dt;

#endif