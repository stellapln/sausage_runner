#ifndef _LIB_EXCEPT_IMAC_LSM
#define _LIB_EXCEPT_IMAC_LSM
#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <exception>



namespace sausageRunner {
	class Except : public std::exception {
		private:
			std::string _file;
			int _line;
			std::string _message;
		public:
			Except(const std::string message,std::string file,const int line)
			:_file(file),_line(line){
				std::ostringstream o;
				o << "Exception lancée:\n\tLigne : " << line << "\n\tFichier" << file << "\n\tMessage :  " << message;
				_message = o.str();
			}
			int getLine() const {return _line;}
			std::string getFile() const {return _file;}
			const char *what() const noexcept override{
				return _message.c_str();
			}
			virtual ~Except(){};
	};
}

#endif