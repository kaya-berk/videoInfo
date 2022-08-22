#ifndef VIDEOINFO_H
#define VIDEOINFO_H

#include <string>
#include <vector>
class VideoInfo
{
public:
	VideoInfo();
	int video_info(const char* filename1);
	std::vector<std::string> getmissingLinks();
private:
	std::vector<std::string> vectorML;
};

#endif // VIDEOINFO_H
