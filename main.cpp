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

	int count = 1;

	ifstream newfile("/home/mak/camRecords");
	av_log_set_callback(log_callback);
	if(newfile.is_open()){
		string rtsp;
		VideoInfo vi;

		while(getline(newfile, rtsp)) {
			cout << rtsp << "\n";
			cout <<"RTSP Link: " << count <<"\n";
			vi.videoInfo(rtsp);
			count++;

			}
			vector<string> vec = vi.getMissingLinks();
			cout << "Missing Links: " << "\n";
			for(int i = 0; i<vec.size(); i++){
				cout <<vec.at(i) << "\n";
			}
		}
	newfile.close();
	return 0;
}

