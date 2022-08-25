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

int main(int argc, char** argv) {

	int count = 1;
	static string value;
	static string key;
	int start = 0;
	for(int i = 0; i < argc; i++)
	{
		string argStr(argv[i]);
		int start = argStr.find("=");
		key = argStr.substr(0, start);
		value = argStr.erase(0, (start+1));
		if(start > 0)
			break;
	}

	ifstream newfile = ifstream(value,ios_base::in);
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

