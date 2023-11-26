#include "quick_loader.h"
#include <stdio.h>

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
int main(int argc,char** argv){
	
	if(argc<2){
		fprintf(stderr,"usage:\n");
		fprintf(stderr,"$ test_loader <text file path>\n");
		return -1;
	}

	// malloc&load on 1 function 
	const char* path=argv[1];
	QLoaded* q=qload(path,true);
	if(!q){
		fprintf(stderr,"cannot load: %s\n",path);
		return -1;
	}

	// q is QLoad header 
	// loaded body pointer is gotten by qloaded_bgn() 
	// after body already set 0, and body can use to standard C string 
	char* body=qloaded_bgn(q);
	printf("%s %s: %u/%u\n=====\n%s\n=====\n",
		path,(q->readsize==q->filesize)?"ready":"shorten",
		(unsigned)q->readsize,(unsigned)q->filesize,
		body);

	// unload and q be NULL 
	qunload(&q);
	printf("unload %s\n",q?"NG":"OK");
	return 0;
}
