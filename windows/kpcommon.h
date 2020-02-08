 
#ifndef _kpCOMMON_H
#define _kpCOMMON_H
 
 

int seed=0;
int rnd(){
    seed=(seed<<4^113)&0xffffffff;
    return seed;
}

int *gen_perm(int height,int width,int bsize){
    int perm_height=(height/bsize);
    int perm_width=(width/bsize);
    int perm_size=perm_height*perm_width;
    int *perm= malloc(perm_size*4),i;
    
    for(i=0;i<perm_size;i++){
        perm[i]=i;
        int x=rnd()%(i+1);
        perm[i]=perm[x];
        perm[x]=i;    
    }
    return perm;    
}
 

#endif
