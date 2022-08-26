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

static map<string, string> argumentParser(int argc, char **argv)
{
	map<string, string> parseArgs;
	string key;
	string value;
	int count = 1;
	int start = 0;
	int i = 0;

	while(i<argc){
		string argStr(argv[i]);
		int start = argStr.find("=");
		key = argStr.substr(0, start);
		value = argStr.substr((start+1),argStr.length());
		parseArgs.insert(pair<string, string>(key, value));
		i++;
		if(start>0)
			break;
		}
	return parseArgs;
}

int main(int argc, char** argv)
{
	int count = 1;

	map<string, string> args = argumentParser(argc, argv);

	if (!args.count("--file")) {
		cout << "Missing parameter Please use --file ";
		return 0;
	}

	string filePath2 = args["--file"];
	//string expectedFPS = args["fps"];
	//expectedFPS = "25.0";
	ifstream newfile = ifstream(filePath2,ios_base::in);
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
