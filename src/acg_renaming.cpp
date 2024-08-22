#include "acg_renaming.h"

#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <algorithm>
using namespace media;
namespace fs = std::filesystem;

namespace media {
std::vector<std::string> Split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);
    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(start, delimiter);
    }
    result.push_back(str.substr(start));
    return result;
}
std::string ToLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c){return std::tolower(c);});

}

std::vector<Video> FindVideoFile(const std::string& dir_path) {

    const std::unordered_set<std::string> video_type_set {"mkv", "mp4", "avi", "mov", "flv", "mts", "m2ts"};
    const std::unordered_set<std::string> sub_type_set {"ass", "srt", "sub", "ssa","vtt","idx"};

    std::vector<Subtitle> subtitles;;
    std::vector<Video> videos_paths;
    std::vector<Video> videos;

    if (fs::exists(dir_path) && fs::is_directory(dir_path)) {
        for (const auto& entry : fs::directory_iterator(dir_path)) {
            if (entry.is_regular_file()) {
                fs::path path = entry.path();
                std::string file_name = path.filename().string();
                std::vector<std::string> s_array = Split(file_name, '.');
                std::string file_type = ToLower(s_array.back());
                
                if (video_type_set.contains(file_type)) {
                    Video video {title: file_name, file_path: path.string(), type: file_type};
                } else if (sub_type_set.contains(file_type)) {
                    Subtitle subtitle;
                    subtitle.type = file_type;
                    subtitle.file_path = path.string();
                }
            }
        }
    } else {
        std::cerr << "Falied to " << dir_path << std::endl;
    }
    return videos;
}

}
