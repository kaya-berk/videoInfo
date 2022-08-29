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

void log_callback(void *, int, const char *, va_list){ }

static map<string, string> argumentParser(int argc, char **argv)
{
	map<string, string> parseArgs;

	int i = 0;
	int dum = 0;

	while(i < argc){
		string key;
		string value;
		string argStr(argv[i]);
		dum = argStr.find("=");

		if(dum > 0){
			key = argStr.substr(0, (dum));
			value = argStr.substr((dum+1), argStr.length());
		}
		else
		{
			key = argStr;
		}

		parseArgs.insert(pair<string, string>(key, value));
		i++;
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

	ifstream newfile = ifstream(filePath2, ios_base::in);
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
