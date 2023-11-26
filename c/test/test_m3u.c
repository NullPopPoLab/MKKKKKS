#include "advanced_m3u.h"
#include "quick_loader.h"
#include "quick_text.h"
#include <stdio.h>

/* -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
static bool m3u_parse_error(void* user,int code,int lineloc,const char* linebgn,const char* lineend){

	// end may not 0 terminated 
	// for use as standard C string, create a standard instance 
	char* line=qtext_alloc(linebgn,lineend);

	fprintf(stderr,"error code %d in line %d; %s\n",code,lineloc,line);

	qtext_free(&line);
	return false;
}

/* ----------------------------------------------------------------------- */
int main(int argc,char** argv){

	AdvancedM3U* am3u=NULL;
	AdvancedM3UDevice* dev=NULL;
	QLoaded* img;
	const char* path;
	char dl;
	int i,j;

	if(argc<2){
		fprintf(stderr,"usage:\n");
		fprintf(stderr,"$ test_m3u <m3u file path>\n");
		return -1;
	}

	am3u=am3u_new();
	if(!am3u){
		fprintf(stderr,"am3u_new failed\n");
		return -1;
	}

	// set devices 
	am3u_set_default_device(am3u,'F');
	dev=am3u_get_device(am3u,'F');
	am3u_device_set_changer(dev,4);
	am3u_device_set_slots(dev,2);
	dev=am3u_get_device(am3u,'H');
	am3u_device_set_changer(dev,2);
	am3u_device_set_slots(dev,1);

	// load a M3U file 
	path=argv[1];
	img=qload(path,false);
	if(!img){
		fprintf(stderr,"cannot load %s\n",path);
	}
	else{
		// parse the M3U source 
		if(!am3u_parse(am3u,qloaded_bgn(img),img->readsize,m3u_parse_error,NULL)){
			fprintf(stderr,"am3u_parse() aborted\n");
		}
		qunload(&img);
	}

	// show parse info 
	for(dl=AM3U_DEVICE_MIN;dl<AM3U_DEVICE_MAX;++dl){
		dev=am3u_get_device(am3u,dl);
		if(dev->changee_max<1)continue;
		printf("Device %c: capacity=%d slots=%d\n",dl,dev->changee_max,dev->slot_max);
		for(i=0;i<dev->changee_max;++i){
			AdvancedM3UMedia* media=&dev->changee_tbl[i];
			int slot=-1;
			for(j=0;j<dev->slot_max;++j){
				if(i==dev->slot_tbl[j])slot=j;
			}
			if(!media->ready){
				printf("%3d:_:(empty)\n",i);
			}
			else{
				char slotinfo[32];
				if(slot<0)slotinfo[0]=0;
				else snprintf(slotinfo,sizeof(slotinfo)," (in slot:%d)",slot+1);

				printf("%3d:%c;%s%s%s%s\n",i,
					media->readonly?'R':'W',
					media->path,slotinfo,
					media->label?" ;":"",
					media->label?media->label:"");
			}
		}
	}

	am3u_free(&am3u);
	return 0;
}
