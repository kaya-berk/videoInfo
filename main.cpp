#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "videoinfo.h"
#include <map>

using namespace std;

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

void log_callback(void *, int, const char *, va_list){

}

int main(int argc, char** argv) {

	static string key;
	static string value;
	int count = 1;
	int start = 0;
	map <string, string> fileNpth;
	int i = 0;

	while(i<argc){
		string argStr(argv[i]);
		int start = argStr.find("=");
		key = argStr.substr(0, start);
		value = argStr.substr((start+1),argStr.length());
		fileNpth.insert(pair<string, string>(key, value));
		i++;
		if(start>0)
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
