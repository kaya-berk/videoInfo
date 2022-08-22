#ifndef VIDEOINFO_H
#define VIDEOINFO_H

#include <string>
#include <vector>
using namespace std;

class VideoInfo
{
public:
	VideoInfo();
	int videoInfo(string filename1);
	vector<string> getMissingLinks();
private:
	vector<string> vectorML;
};

#endif // VIDEOINFO_H
