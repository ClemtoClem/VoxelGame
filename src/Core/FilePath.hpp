#ifndef FILE_PATH_HPP
#define FILE_PATH_HPP

#include <string>

/// \class FilePath
/// \brief class read file from its path
class FilePath {
public:
#ifdef _WIN32
    static const char PATH_SEPARATOR = '\\';
#else
    static const char PATH_SEPARATOR = '/';
#endif

    FilePath() = default;

    FilePath(const char* filepath): _filepath(filepath) {
        format();
    }

    FilePath(const std::string& filepath): _filepath(filepath) {
        format();
    }

    operator std::string() const { return _filepath; }

    const std::string& str() const { return _filepath; }

    const char* c_str() const { return _filepath.c_str(); }

    bool empty() const;

    /*! returns the path of a filepath */
    FilePath getDirectoryPath() const;

    /*! returns the file of a filepath  */
    std::string getFile() const;

    /*! returns the filename of a filepath  */
    std::string getFilename() const ;

    /*! returns the file extension */
    std::string getExtension() const;

    bool hasExtension(const std::string& ext) const;

    /*! adds file extension */
    FilePath addExtension(const std::string& ext = "") const {
        return FilePath(_filepath + ext);
    }

    FilePath changeExtension(const std::string& ext) const {
        return FilePath(_filepath.substr(0, _filepath.find_last_of('.')) + ext);
    }

    /*! concatenates two filepaths to this/other */
    FilePath operator +(const FilePath& other) const;

    bool operator ==(const FilePath& other) const {
        return other._filepath == _filepath;
    }

    bool operator !=(const FilePath& other) const {
        return !operator ==(other);
    }

    /*! output operator */
    friend std::ostream& operator<<(std::ostream& cout, const FilePath& filepath) {
        return (cout << filepath._filepath);
    }

private:
    void format();

    std::string _filepath;
};


namespace std {
    template <>struct hash<FilePath> {
        std::size_t operator()(const FilePath& k) const {
            return std::hash<std::string>()(k.str());
        }
    };
}

#endif // FILE_PATH_HPP