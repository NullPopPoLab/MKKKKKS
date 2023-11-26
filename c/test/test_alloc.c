#include "safe_alloc.h"
#include <stdio.h>
#include <string.h>

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
int main(int argc,char** argv){

	// alloc 
	size_t size=1000000000;
	int i,a=0;

	char* p=safe_alloc(size);
	if(!p){
		fprintf(stderr,"cant alloc %u bytes\n",(unsigned)size);
		return -1;
	}
	printf("alloc OK\n");

	// alread zero cleared 
	for(i=a=0;i<size;++i)a|=p[i];
	printf("clear %s\n",a?"NG":"OK");

	// free 
	// pointer is NULL after freed 
	safe_free(&p);
	printf("free %s\n",p?"NG":"OK");

	return 0;
}
