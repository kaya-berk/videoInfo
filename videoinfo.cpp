#include "videoinfo.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

VideoInfo::VideoInfo()
{

}



int VideoInfo::video_info(const char *filename){

	static AVFormatContext* pFormatCtx = NULL;
	pFormatCtx = avformat_alloc_context();
	static AVCodecContext* pCodecCtx=NULL;
	int ret = avformat_open_input(&pFormatCtx, filename, NULL, NULL);
	std::string strV(filename);

	if (ret < 0){
		printf("Could not open file\n");
		vectorML.push_back(strV);
		return -1;
	}

	int ret2 = avformat_find_stream_info(pFormatCtx, NULL);
	if(ret2<0){
		printf("Could find stream info \n");
		return -1;
	}

	int64_t duration = pFormatCtx->duration;

	printf("Opened the file!!!!\n");

	printf("Duration: %" PRId64 "\n",duration);

	double videoFPS = av_q2d(pFormatCtx->streams[ret2]->r_frame_rate);

	std::cout<<"fps :"<<videoFPS<<std::endl;

	pCodecCtx=pFormatCtx->streams[ret2]->codec;
	printf("Width : %d\n",pCodecCtx->width);
	printf("Height : %d\n",pCodecCtx->height);

	pCodecCtx=pFormatCtx->streams[ret2]->codec;
	printf("bit rate : %ld\n",pFormatCtx->bit_rate);

	return 0;
}

std::vector<std::string> VideoInfo::getmissingLinks(){

	return vectorML;
};


