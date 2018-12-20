#include <iostream>
#include <string>
#include <sstream>
#include <exception>

class Erreur : public std::exception {
	private:
		std::string _file;
		int _line;
		std::string _message;
	public:
		Erreur(const std::string message="",std::string file = __FILE__,const int line = __LINE__)
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
		virtual ~Erreur(){};
};