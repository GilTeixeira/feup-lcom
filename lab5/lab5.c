#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <minix/driver.h>
#include "test5.h"
#include "pixmap.h"

static int proc_args(int argc, char **argv);
static unsigned short parse_ushort(char *str, int base);
static unsigned long parse_ulong(char *str, int base);
static short parse_short(char *str, int base);
static void print_usage(char **argv);

int main(int argc, char **argv) {
	/* Initialize service */
	sef_startup();

	if (argc == 1) { /* Prints usage of the program if no arguments are passed */
		print_usage(argv);
		return 0;
	} else
		return proc_args(argc, argv);
}

static void print_usage(char **argv) {
	printf(
			"Usage: one of the following:\n"
					"\t service run %s -args \"init <decimal no.- mode> <decimal no.- delay>\"\n"
					"\t service run %s -args \"square <decimal no.- x> <decimal no.- y> <decimal no.- size> <decimal no.- color>\"\n"
					"\t service run %s -args \"line <decimal no.- xi> <decimal no.- yi> <decimal no.- xf> <decimal no.- yf> <decimal no.- color>\"\n"
					"\t service run %s -args \"xpm <char pointer.- xpm> <decimal no.- xi> <decimal no.- yi>\"\n"
					"\t service run %s -args \"move <char pointer.- xpm> <decimal no.- xi> <decimal no.- yi>  <decimal no.- xf> <decimal no.- yf> <decimal no.- speed> <decimal no.- frame_rate>\"\n"
					"\t service run %s -args \"controller\"\n",
			argv[0], argv[0], argv[0]);
}

static int proc_args(int argc, char **argv) {
	unsigned short mode, delay, x, y, size, xi, yi, xf, yf;
	unsigned long color;
	short speed, frame_rate;
	char **xpm;

	if (strncmp(argv[1], "init", strlen("init")) == 0) {
		if (argc != 4) {
			printf("video: wrong no. of arguments for video_test_init()\n");
			return 1;
		}
		mode = parse_ushort(argv[2], 10); /* Parses string to unsigned short */
		if (mode == USHRT_MAX)
			return 1;

		delay = parse_ushort(argv[3], 10); /* Parses string to unsigned short */
		if (delay == USHRT_MAX)
			return 1;

		printf("video::video_test_init(%d, %d)\n", mode, delay);
		return video_test_init(mode, delay);

	} else if (strncmp(argv[1], "square", strlen("square")) == 0) {
		if (argc != 6) {
			printf("video: wrong no. of arguments for video_test_square()\n");
			return 1;
		}

		x = parse_ushort(argv[2], 10); /* Parses string to unsigned short */
		if (x == USHRT_MAX)
			return 1;

		y = parse_ushort(argv[3], 10); /* Parses string to unsigned short */
		if (y == USHRT_MAX)
			return 1;

		size = parse_ushort(argv[4], 10); /* Parses string to unsigned short */
		if (size == USHRT_MAX)
			return 1;

		color = parse_ushort(argv[5], 10); /* Parses string to unsigned short */
		if (color == USHRT_MAX)
			return 1;

		printf("video::video_test_square(%d, %d, %d, %d)\n", x, y, size, color);
		return video_test_square(x, y, size, color);

	} else if (strncmp(argv[1], "line", strlen("line")) == 0) {
		if (argc != 7) {
			printf("video: wrong no of arguments for video_test_line()\n");
			return 1;
		}

		xi = parse_ushort(argv[2], 10); /* Parses string to unsigned short */
		if (xi == USHRT_MAX)
			return 1;

		yi = parse_ushort(argv[3], 10); /* Parses string to unsigned short */
		if (yi == USHRT_MAX)
			return 1;

		xf = parse_ushort(argv[4], 10); /* Parses string to unsigned short */
		if (xf == USHRT_MAX)
			return 1;

		yf = parse_ushort(argv[5], 10); /* Parses string to unsigned short */
		if (yf == USHRT_MAX)
			return 1;

		color = parse_ulong(argv[6], 10); /* Parses string to unsigned long */
		if (color == ULONG_MAX)
			return 1;

		printf("video::video_test_line(%d, %d, %d, %d, %d)\n", xi, yi, xf, yf, color);
		return video_test_line(xi, yi, xf, yf, color);

	} else if (strncmp(argv[1], "xpm", strlen("xpm")) == 0) {
		if (argc != 5) {
			printf("video: wrong no of arguments for test_xpm()\n");
			return 1;
		}

		xpm=penguin;

		xi = parse_ushort(argv[3], 10); /* Parses string to unsigned short */
		if (xi == USHRT_MAX)
			return 1;

		yi = parse_ushort(argv[4], 10); /* Parses string to unsigned short */
		if (yi == USHRT_MAX)
			return 1;

		printf("video::test_xpm(%d, %d, %d)\n", xpm, xi, yi);
		return test_xpm(xpm, xi, yi);

	} else if (strncmp(argv[1], "move", strlen("move")) == 0) {
		if (argc != 9) {
			printf("video: wrong no of arguments for test_move()\n");
			return 1;
		}

		/* TODO: Parse XPM */

		xi = parse_ushort(argv[3], 10); /* Parses string to unsigned short */
		if (xi == USHRT_MAX)
			return 1;

		yi = parse_ushort(argv[4], 10); /* Parses string to unsigned short */
		if (yi == USHRT_MAX)
			return 1;

		xf = parse_ushort(argv[5], 10); /* Parses string to unsigned short */
		if (xf == USHRT_MAX)
			return 1;

		yf = parse_ushort(argv[6], 10); /* Parses string to unsigned short */
		if (yf == USHRT_MAX)
			return 1;

		speed = parse_short(argv[7], 10); /* Parses string to short */
		if (speed == SHRT_MAX)
			return 1;

		frame_rate = parse_short(argv[8], 10); /* Parses string to short */
		if (frame_rate == SHRT_MAX)
			return 1;

		printf("video::test_move(%d, %d, %d, %d, %d, %d, %d)\n", xpm, xi, yi, xf, yf, speed, frame_rate);
		return test_move(xpm, xi, yi, xf, yf, speed, frame_rate);

	} else if (strncmp(argv[1], "controller", strlen("controller")) == 0) {
		if (argc != 2) {
			printf("video: wrong no of arguments for test_controller()\n");
			return 1;
		}

		printf("video::test_controller()\n");
		return test_controller();

	}

	else {
		printf("video: %s - no valid function!\n", argv[1]);
		return 1;
	}
}

static unsigned short parse_ushort(char *str, int base) {
	char *endptr;
	unsigned short val;

	/* Convert string to unsigned short */
	val = (unsigned short) strtoul(str, &endptr, base);

	/* Check for conversion errors */
	if ((errno == ERANGE && val == USHRT_MAX) || (errno != 0 && val == 0)) {
		perror("strtoul");
		return USHRT_MAX;
	}

	if (endptr == str) {
		printf("timer: parse_ushort: no digits were found in %s\n", str);
		return USHRT_MAX;
	}

	/* Successful conversion */
	return val;
}

static unsigned long parse_ulong(char *str, int base) {
	char *endptr;
	unsigned long val;

	/* Convert string to unsigned long */
	val = strtoul(str, &endptr, base);

	/* Check for conversion errors */
	if ((errno == ERANGE && val == ULONG_MAX) || (errno != 0 && val == 0)) {
		perror("strtoul");
		return ULONG_MAX;
	}

	if (endptr == str) {
		printf("timer: parse_ulong: no digits were found in %s\n", str);
		return ULONG_MAX;
	}

	/* Successful conversion */
	return val;
}

static short parse_short(char *str, int base) {
	char *endptr;
	short val;

	/* Convert string to long */
	val = (short) strtol(str, &endptr, base);

	/* Check for conversion errors */
	if ((errno == ERANGE && (val == SHRT_MAX || val == SHRT_MIN))
			|| (errno != 0 && val == 0)) {
		perror("strtol");
		return SHRT_MAX;
	}

	if (endptr == str) {
		printf("mouse: parse_short: no digits were found in %s\n", str);
		return SHRT_MAX;
	}

	/* Successful conversion */
	return val;
}


