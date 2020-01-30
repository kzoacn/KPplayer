/*
    Copyright (C) 2014  StarBrilliant <m13253@hotmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <fftw3.h>
#include <glib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "kpcommon.h"

static void kp_dec_frame(unsigned char *payload, size_t payloadlen, const unsigned char *frame, unsigned int bsize, unsigned int quantizer, unsigned int qmin, unsigned int qmax, unsigned int width, unsigned int height, int verbose,int *perm);




int *gen_perm_reverse(int height,int width,int bsize){
    int perm_height=(height/bsize);
    int perm_width=(width/bsize);
    int perm_size=perm_height*perm_width;
    int *perm=gen_perm(height,width,bsize);
    int *perm_re=g_malloc(perm_size*4);
    for(int i=0;i<perm_size;i++)
        perm_re[perm[i]]=i;
    return perm_re;    
}

int kp_dispatch(FILE *fi, FILE *fo, unsigned int bsize, unsigned int quantizer, unsigned int qmin, unsigned int qmax, unsigned int width, unsigned int height, int grayonly, int verbose) {
    size_t payloadlen = width*height;
    unsigned char *payload = g_malloc(payloadlen);
    unsigned char *framey = g_malloc(width*height*3/2);
    unsigned char *frameuv = framey+width*height;

    int *perm1=gen_perm_reverse(height,width,bsize);
    int *perm2=gen_perm_reverse(height,width/2,bsize); 

    while(!feof(fi)) {
        int readres = fread(framey, 1, width*height*3/2, fi);
        if(readres == 0)
            break;
        if(readres < width*height*3/2)
            memset(framey+readres, 0, width*height*3/2-readres);
        kp_dec_frame(payload, payloadlen, framey, bsize, quantizer, qmin, qmax, width, height, verbose,perm1);
        fwrite(payload, 1, payloadlen, fo);
        if(!grayonly) {
            kp_dec_frame(payload, payloadlen/2, frameuv, bsize, quantizer, qmin, qmax, width/2, height, verbose,perm2);
            fwrite(payload, 1, payloadlen/2, fo);
        }
    }
    g_free(payload); g_free(framey); 
    g_free(perm1); g_free(perm2);
    return 0;
}

static void kp_dec_frame(unsigned char *payload, size_t payloadlen, const unsigned char *frame, unsigned int bsize, unsigned int quantizer, unsigned int qmin, unsigned int qmax, unsigned int width, unsigned int height, int verbose,int *perm) {
    for(int i=0;i<payloadlen;i++){
        payload[i]=frame[i];
    } 
    int perm_width=(width/bsize); 

    int cur=0;
    for(int bi = 0; (bi+1)*bsize <= height; bi++)
    for(int bj = 0; (bj+1)*bsize <= width; bj++) {
        
        int obi=perm[cur]/perm_width;
        int obj=perm[cur]%perm_width;
        cur++;

        for(int i = 0; i < bsize; i++)
        for(int j = 0; j < bsize; j++){
            int pos=(bi*bsize+i)*width+(bj*bsize+j);
            int npos=(obi*bsize+i)*width+(obj*bsize+j);
            payload[npos]=frame[pos];
        }
    }
}
