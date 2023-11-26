#include "quick_loader.h"
#include "quick_text.h"
#include <stdio.h>

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
//! called by each extracted line 
static bool extracted_line(void* user,const char* bgn,const char* end)
{
	const char* org=user;

	// end may not 0 terminated 
	// for use as standard C string, create a standard instance 
	char* s=qtext_alloc(bgn,end);

	printf("%6d: %s\n",(int)(bgn-org),s);

	qtext_free(&s);
	return true;
}

/* ----------------------------------------------------------------------- */
int main(int argc,char** argv){
	
	if(argc<2){
		fprintf(stderr,"usage:\n");
		fprintf(stderr,"$ test_loader <text file path>\n");
		return -1;
	}

	QLoaded* q=qload(argv[1],true);
	if(!q){
		fprintf(stderr,"cannot load: %s\n",argv[1]);
		return -1;
	}

	char* bgn=qloaded_bgn(q);
	char* end=qloaded_end(q);
	const char* cur=qtext_ext_lines(bgn,bgn,end,extracted_line);
	printf("%6d: [EOF] %s\n",(int)(cur-bgn),cur);

	qunload(&q);
	return 0;
}
