#include "videoinfo.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

VideoInfo::VideoInfo(){ }

int VideoInfo::videoInfo(string filename)
{
	string strV(filename);

	AVFormatContext* pFormatCtx = NULL;
	pFormatCtx = avformat_alloc_context();
	AVCodecContext* pCodecCtx=NULL;

	int ret = avformat_open_input(&pFormatCtx, filename.data(), NULL, NULL);
	if (ret < 0){
		printf("Could not open file \n");
		vectorML.push_back(strV);
		return -1;
	}

	int ret2 = avformat_find_stream_info(pFormatCtx, NULL);
	if(ret2 < 0){
		printf("Could find stream info \n");
		return -1;
	}
	printf("Opened the file!!!! \n");

	int64_t duration = pFormatCtx->duration;
	printf("Duration: %" PRId64 "\n", duration);

	double videoFPS = av_q2d(pFormatCtx->streams[ret2]->r_frame_rate);
	cout <<"fps :"<<videoFPS<< "\n";

	pCodecCtx = pFormatCtx->streams[ret2]->codec;
	printf("Width : %d\n", pCodecCtx->width);
	printf("Height : %d\n", pCodecCtx->height);

	pCodecCtx = pFormatCtx->streams[ret2]->codec;
	printf("bit rate : %ld\n", pFormatCtx->bit_rate);

	avformat_close_input(&pFormatCtx);
	avformat_free_context(pFormatCtx);

	return 0;
}

vector<string> VideoInfo::getMissingLinks(){

	return vectorML;
};
