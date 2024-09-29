#include "Logger.hpp"

std::shared_ptr<Logger> Logger::instance = nullptr;

Logger::Logger(bool removeLastFile) : _minLevel(Debug), _maxLevel(Fatal), _writeInTerminal(false) {
	if (removeLastFile) {
		removeFile();
	}
}

Logger::~Logger() {
	write_separation();
}

void Logger::removeFile() {
	if (std::remove(LOG_FILE) < 0) {
		if (instance != nullptr) {
			LOG(Warning) << "Unable to remove log file";
		} else {
			std::cerr << "Unable to remove log file" << std::endl;
		}
	}
}

std::shared_ptr<Logger> Logger::getInstance() {
	if (instance == nullptr) {
		instance = std::make_shared<Logger>();
	}
	return instance;
}

void Logger::enableWriteInTerminal() {
	_writeInTerminal = true;
}

void Logger::disableWriteInTerminal() {
	_writeInTerminal = false;
}

void Logger::setMinLevel(LogLevel level) {
	_minLevel = level;
}

void Logger::setMaxLevel(LogLevel level) {
	_maxLevel = level;
}

void Logger::write(const std::string &msg) {
	std::lock_guard<std::mutex> lock(_mutex); // Lock the mutex for the duration of this scope
	if (_msg_level >= _minLevel && _msg_level <= _maxLevel) {
		std::ostringstream ss;

		// time
		time_t now = time(nullptr);
		struct tm* timeinfo = localtime(&now);
		char date[20];
		strftime(date, sizeof(date), "%y-%m-%d %H:%M:%S", timeinfo);

		// Logger
		ss << "[" << getLabel(_msg_level) << "] " << date << " - " << _msg_file << ":" << _msg_line << " - ";
		size_t len = ss.str().length();

		for (size_t j = 0; j < msg.length(); j++) {
			if (msg[j] == '\n' && j < msg.length()-1) {
				ss << msg[j];
				for (size_t i = 0; i < len; i++) ss << " ";
			} else if (msg[j] != '\n') {
				ss << msg[j];
			}
		}
		ss << std::endl;

		_file.open(LOG_FILE, std::ios::app);
		if (_file.is_open()) {
			_file << ss.str();
		}
		_file.close();
		if (_writeInTerminal) {
			std::cerr << getColor(_msg_level) << ss.str() << "\e[0m";
		}
	}
}

void Logger::write_separation(char sig) {
	std::lock_guard<std::mutex> lock(_mutex); // Lock the mutex for the duration of this scope
	std::string sep(60, sig);
	_file.open(LOG_FILE, std::ios::app);
	if (_file.is_open()) {
		_file << sep << std::endl;
	}
	_file.close();
	if (_writeInTerminal) {
		std::cerr << sep << std::endl;
	}
}

void Logger::write_break_line() {
	std::lock_guard<std::mutex> lock(_mutex); // Lock the mutex for the duration of this scope

	_file.open(LOG_FILE, std::ios::app);
	if (_file.is_open()) {
		_file << std::endl;
	}
	if (_writeInTerminal) {
		std::cerr << std::endl;
	}
	_file.close();
}

std::string Logger::getLabel(LogLevel type) {
	switch (type) {
		case Debug:		return " DEBUG ";
		case Info:		return " INFO  ";
		case Success:	return "SUCCESS";
		case Warning:	return "WARNING";
		case Error:		return " ERROR ";
		case Fatal:		return " FATAL ";
		default:		return "UNKNOWN";
	}
}

std::string Logger::getColor(LogLevel type) {
	switch (type) {
		case Debug:		return "\e[1;37m"; // white
		case Info:		return "\e[0;34m"; // blue
		case Success:	return "\e[1;32m"; // green
		case Warning:	return "\e[1;33m"; // yellow
		case Error:		return "\e[1;31m"; // red
		case Fatal:		return "\e[4;31m"; // red underlined
		default:		return "\e[0m";	// reset
	}
}