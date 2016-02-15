/* kawaiify.c --- Kawaii output for your terminal.
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

#include "kawaiify.h"

// Converts an rgb color to an hsl one.
void to_hsl(const rgbcolor *c,hslcolor *d){
    double r,g,b,v,vm,m,r2,g2,b2,h,s,l;
    h = s = l = 0;
    r = c->red   / 255;
    g = c->green / 255;
    b = c->blue  / 255;
    v = fmax(fmax(r,g),b);
    m = fmin(fmin(r,g),b);
    l = (m + v) / 2.0;
    if (l <= 0){
        d->hue        = h;
        d->saturation = s;
        d->luminance  = l;
        return;
    }
    vm = v - m;
    s  = vm;
    if (s > 0){
        s /= (l <= 0.5) ? v + m : 2.0 - v - m;
    }else{
        d->hue        = h;
        d->saturation = s;
        d->luminance  = l;
        return;
    }
    r2 = (v - r) / vm;
    g2 = (v - g) / vm;
    b2 = (v - b) / vm;
    if (r == v){
        h = (g == m) ? 5.0 + b2 : 1.0 - g2;
    }else if (g == v){
        h = (b == m) ? 1.0 + r2 : 3.0 - b2;
    }else{
        h = (r == m) ? 3.0 + g2 : 5.0 - r2;
    }
    h /= 6.0;
    d->hue        = h;
    d->saturation = s;
    d->luminance  = l;
}

// Converts an hsl color to an rgb one.
void to_rgb (const hslcolor *c,rgbcolor *d){
    double v,r,g,b,m,sv,fract,vsf,mid1,mid2,h;
    int    sextant;
    r = g = b = c->luminance;
    h = c->hue;
    v = (c->luminance <= 0.5) ? (c->luminance * (1.0 + c->saturation))
        : (c->luminance + c->saturation - c->luminance * c->saturation);
    if (v > 0){
        m       = c->luminance + c->luminance - v;
        sv      = (v - m ) / v;
        h       *= 6.0;
        sextant =  (int) h;
        fract   =  h - sextant;
        vsf     =  v * sv * fract;
        mid1    =  m + vsf;
        mid2    =  v - vsf;
        switch (sextant){
        case 0:
            r = v;
            g = mid1;
            b = m;
            break;
        case 1:
            r = mid2;
            g = v;
            b = m;
            break;
        case 2:
            r = m;
            g = v;
            b = mid1;
            break;
        case 3:
            r = m;
            g = mid2;
            b = v;
            break;
        case 4:
            r = mid1;
            g = m;
            b = v;
            break;
        case 5:
            r = v;
            g = m;
            b = mid2;
            break;
        }
    }
    d->red   = (unsigned char) (r * 255.0);
    d->green = (unsigned char) (g * 255.0);
    d->blue  = (unsigned char) (b * 255.0);
}

// Generates a color from a hue, saving the result in c.
void getcolor(double d,rgbcolor *c){
    hslcolor h = { d,SATURATION,LUMINANCE };
    to_rgb(&h,c);
}

// Prints a character with a color.
void cputchar(rgbcolor *c,char d){
    printf(COLORFMT "%c",c->red,c->green,c->blue,d);
}

int main(void){
    rgbcolor c;
    int      d;
    double   f;
    hslcolor h = { 0.0,SATURATION,LUMINANCE };
    int      in_escape = 0;
    srand(time(NULL));
    f     = ((double) rand()) / ((double) RAND_MAX);
    h.hue = f;
    to_rgb(&h,&c);
    while((d = getchar()) != EOF){
        if (d == '\e'){
            in_escape = 1;
        }

        if (in_escape || d){
            putchar(d);
        }else{
            cputchar(&c,d);
            getcolor(f,&c);
            f = ((f + HUESTEP) >= 1) ? 0 : f + HUESTEP;
        }

        if (in_escape && d >= 64 && d <= 126 && d != '['){
            in_escape = 0;
        }
    }
    printf(RESET);
    return 0;
}
