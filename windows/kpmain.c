 

#include <stdio.h>
#include <fcntl.h>

int blocksize = 8;
int quantizer = 4;
int qmin = 1;
int qmax = -1;
char framesize[50];
unsigned int framewidth = 0, frameheight = 0;
int grayonly = 0;
int verbose = 0;

int kp_dispatch(FILE *fi, FILE *fo, unsigned int blocksize, unsigned int quantizer, unsigned int qmin, unsigned int qmax, unsigned int width, unsigned int height, int grayonly, int verbose);

int main(int argc, char *argv[]) {
    _setmode( _fileno( stdin ), _O_BINARY );
	_setmode( _fileno( stdout ), _O_BINARY );
	sscanf(argv[1],"%s",framesize);
	
    if(framesize && framesize[0]) {
        sscanf(framesize, "%ux%u", &framewidth, &frameheight);
    }
	fprintf(stderr,"%u %u\n",framewidth,frameheight);
    return kp_dispatch(stdin, stdout, blocksize, quantizer, qmin, qmax, framewidth, frameheight, grayonly, verbose);
}
