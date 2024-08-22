//
// Created by dd on 2024/8/21.
//

#ifndef ACG_RENAMING_H
#define ACG_RENAMING_H
#include <string>
#include <vector>

namespace media {

struct Subtitle {
    std::string language;
    std::string file_path;
    std::string type;
};

struct Video {
    std::string title;
    std::string file_path;
    std::string type;
    std::vector<Subtitle> subtitles;
};

std::vector<Video> FindVideoFile(const std::string& path);

void RenameVideoFile(Video& video);

}

#endif //ACG_RENAMING_H
