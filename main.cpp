#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "videoinfo.h"

using namespace std;

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

void log_callback(void *, int, const char *, va_list){

}

int main(int argc, const char** argv) {

	int count =1;

	ifstream newfile("/home/mak/camRecords");
	av_log_set_callback(log_callback);
	if(newfile.is_open()){
		std::string rtsp;
		VideoInfo vi;

		while(getline(newfile, rtsp)) {
			const char* charrtsp = rtsp.c_str();
			cout<<rtsp<<"\n";
			cout <<"RTSP Link: "<<count<<"\n";
			vi.video_info(charrtsp);
			count++;

			}
			std::vector<std::string> vec=vi.getmissingLinks();
			std::cout<<"Missing Links: "<< "\n";
			for(int i=0; i<vec.size();i++){
				std::cout<<vec.at(i)<<"\n";
			}
		}
	newfile.close();
	return 0;
}

