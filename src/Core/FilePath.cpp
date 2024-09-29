#include "FilePath.hpp"

bool FilePath::empty() const {
    return _filepath.empty();
}

FilePath FilePath::getDirectoryPath() const
{
    size_t pos = _filepath.find_last_of(PATH_SEPARATOR);
    if (pos == std::string::npos) { return FilePath(); }
    return _filepath.substr(0, pos);
}

std::string FilePath::getFile() const{
    size_t pos = _filepath.find_last_of(PATH_SEPARATOR);
    if (pos == std::string::npos) { return _filepath; }
    return _filepath.substr(pos + 1);
}

std::string FilePath::getFilename() const{
    size_t pos = _filepath.find_last_of(PATH_SEPARATOR);
    if (pos == std::string::npos) { return _filepath; }
    std::string file = _filepath.substr(pos + 1);
    pos = file.find_first_of('.', 1);
    if (pos == std::string::npos) { return file; }
    return file.substr(0, pos);
}

std::string FilePath::getExtension() const{
    size_t pos = _filepath.find_last_of('.');
    if (pos == std::string::npos || pos == 0) { return ""; }
    return _filepath.substr(pos + 1);
}

bool FilePath::hasExtension(const std::string &ext) const{
    int offset = (int) _filepath.size() - (int) ext.size();
    return offset >= 0 && _filepath.substr(offset, ext.size()) == ext;
}

FilePath FilePath::operator+(const FilePath &other) const {
    if (_filepath.empty()) {
        return other;
    } else {
        if(other.empty()) {
            return _filepath;
        }
        FilePath copy(*this);
        if(other._filepath.front() != PATH_SEPARATOR) {
            copy._filepath += PATH_SEPARATOR;
        }
        copy._filepath += other._filepath;
        return copy;
    }
}

void FilePath::format() {
    for (size_t i = 0; i < _filepath.size(); ++i) {
        if (_filepath[i] == '\\' || _filepath[i] == '/') {
            _filepath[i] = PATH_SEPARATOR;
        }
    }
    while (!_filepath.empty() && _filepath.back() == PATH_SEPARATOR) {
        _filepath.pop_back();
    }
}