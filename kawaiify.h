/* kawaiify.h --- Kawaii output for your terminal.
   Copyright (c) 2014 Joe Jevnik

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 2 of the License, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   You should have received a copy of the GNU General Public License along with
   this program; if not, write to the Free Software Foundation, Inc., 51
   Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA. */

#ifndef KAWAIIFY_H
#define KAWAIIFY_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Resets the colors of the terminal.
#define RESET    "\e[0m"

// The color format string.
#define COLORFMT "\e[38;2;%d;%d;%dm"

// Saturation and luminance constants
#define SATURATION 0.9
#define LUMINANCE  0.75

// The amount to increment the hue by.
#define HUESTEP    0.001

// A color type defined with RGB.
typedef struct{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} rgbcolor;

// A color type defined with HSL.
typedef struct{
  double        hue;
  double        saturation;
  double        luminance;
} hslcolor;

#endif
