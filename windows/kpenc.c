 
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "kpcommon.h"

static void kp_enc_frame(unsigned char *payload, size_t payloadlen, const unsigned char *frame, unsigned int bsize, unsigned int quantizer, unsigned int qmin, unsigned int qmax, unsigned int width, unsigned int height, int verbose,int *perm);

 

int kp_dispatch(FILE *fi, FILE *fo, unsigned int bsize, unsigned int quantizer, unsigned int qmin, unsigned int qmax, unsigned int width, unsigned int height, int grayonly, int verbose) {
    size_t payloadlen = width*height;
    unsigned char *payload =  malloc(payloadlen);
    unsigned char *framey =  malloc(width*height*3/2);
    unsigned char *frameuv = framey+width*height;

    int *perm1=gen_perm(height,width,bsize);
    int *perm2=gen_perm(height,width/2,bsize); 

    while(!feof(fi)) {
        int readres = fread(framey, 1, width*height*3/2, fi);
        if(readres == 0)
            break;
        if(readres < width*height*3/2)
            memset(framey+readres, 0, width*height*3/2-readres);
        kp_enc_frame(payload, payloadlen, framey, bsize, quantizer, qmin, qmax, width, height, verbose,perm1);
        fwrite(payload, 1, payloadlen, fo);
        if(!grayonly) {
            kp_enc_frame(payload, payloadlen/2, frameuv, bsize, quantizer, qmin, qmax, width/2, height, verbose,perm2);
            fwrite(payload, 1, payloadlen/2, fo);
        }
    }
     free(payload);  free(framey); 
     free(perm1);  free(perm2);
    return 0;
}

static void kp_enc_frame(unsigned char *payload, size_t payloadlen, const unsigned char *frame, unsigned int bsize, unsigned int quantizer, unsigned int qmin, unsigned int qmax, unsigned int width, unsigned int height, int verbose,int *perm) {
 
    int cur=0,bi,bj,i;
    for( i=0;i<payloadlen;i++){
        payload[i]=frame[i];
    } 
    int perm_width=(width/bsize); 

    for( bi = 0; (bi+1)*bsize <= height; bi++)
    for( bj = 0; (bj+1)*bsize <= width; bj++) {
        
        int obi=perm[cur]/perm_width;
        int obj=perm[cur]%perm_width;
        cur++;

        for( i = 0; i < bsize; i++){
            memcpy(payload+(obi*bsize+i)*width+(obj*bsize),
                    frame+(bi*bsize+i)*width+(bj*bsize),
                    bsize);
        }
    }
}
