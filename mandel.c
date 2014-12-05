// Copyright 2014 <Nate>

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>

static int verbose_flag;

int mandel(float x, float y, int rez) {
  float ix = x;
  float iy = y;

  int i;
  for (i = 0; i < rez && !((pow(ix, 2) + pow(iy, 2) >= 4)); i++) {
    float nx = (pow(ix, 2) - pow(iy, 2) ) + x;
    float ny = 2*ix*iy + y;
    ix = nx;
    iy = ny;
  }
  return i;
}


int printmandel(float len, int rez) {
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < (len * 2); j++) {
      float step = 4 / (len - 1);
      float x = -2 + ((float) j * (step / 2) );
      float y = 2 - ((float) i * step);
      printf("%x", mandel(x, y, rez)%15);
      if (j == ((len * 2) - 1)) {
        printf("\n");
      }
    }
  }
  return 0;
}

float length = 65;

int resolution = 15;

int main(int argc, char **argv) {
  int c;
    
  while (1) {
    static struct option long_options[] = {
      {"verbose", no_argument, &verbose_flag, 1},
      {"brief", no_argument, &verbose_flag, 0},
      {"length", required_argument, 0, 'l'},
      {"resolution", required_argument, 0, 'r'},
      {0, 0, 0, 0}
    };
        
    int option_index = 0;
        
    c = getopt_long(argc, argv, "l:r:", long_options, &option_index);
        
    if (c == -1)
      break;

    switch (c) {
      case 0:
	if (long_options[option_index].flag != 0)
	  break;
	printf("option %s", long_options[option_index].name);
	if (optarg)
	  printf(" with arg %s", optarg);
	printf("\n");
	break;

      case 'l':
	printf("option -l with value `%s'\n", optarg);
	length = atof(optarg);
	break;

      case 'r':
	printf("option -r with value `%s'\n", optarg);
	resolution = atoi(optarg);
	break;

      case '?':
	break;

      default:
	abort();
    }
  }
  if (verbose_flag)
    puts("verbose flag is set");

  if (optind < argc) {
    printf("non-option ARGV-elements: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);
    putchar('\n');
  }
  printmandel(length, resolution);
  exit(0);
}
