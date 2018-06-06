#pragma once
#include <iostream>

//(todo) Still not implemented... 
enum ERROR_TYPES {
	ERR_INIT,         /* The initialization failed*/
	ERR_NOINIT,       /* The object is not initialize */
	ERR_MALLOC,       /* Memory allocation failed */
	ERR_NOFILE,       /* The file was not found */
	ERR_FILEIO,       /* Read/Write related error */
	ERR_NONAME,       /* No entity or object with this name was found */
	ERR_ASSIMP,       /* Assimp related error */
	ERR_OPENGL,       /* GL related error */
	ERR_GLLINK,       /* Program linking failed */
	ERR_GLSHDR        /* Shader compilation failed */
};

struct Logger {
private:
	Logger(){}
	Logger(Logger const&){}					/* Don't want the compiler to generate copy constructor. */
	void operator=(Logger const&){}			/* Don't want the compiler to generate copy assignment operator. */
public:
	static Logger& GetInstance() {
		static Logger logger_instance;
		return logger_instance;
	}

	template<typename T>
	void OutputMsg(const char* caller_func_name, const T &msg_val) {
	#ifdef DEBUG_MODE
		std::cout << "MSG::" << caller_func_name << "::" << msg_val << "\n";
	#endif
	}
	template<typename T>
	void OutputMsgStr(const char* caller_func_name, const char* msg_str, const T &msg_val) {
   	#ifdef DEBUG_MODE
		std::cout << "MSG::" << caller_func_name << "::" << msg_str << "::" << msg_val << "\n";
	#endif
	}

	void OutputErrorMsg(const char* caller_obj_name, const char* caller_func_name, ERROR_TYPES err_type, const char* err_log) {
	#ifdef DEBUG_MODE
		std::cerr << "ERR::" << caller_obj_name << "::" << caller_func_name << "()::" << err_log << "\n";

		char action;
		std::cout << "\n\nExit?(y/n)\t>";
		std::cin >> action;
		if(action=='y')
			std::exit(0);
	#endif
	/* else write output in log file... */
	}

};

/* to avoid the need to write the "__func__" macro
in the arguments each time we call the function */
#define OutputErrorMsg(caller_obj_name, err_type, err_log) Logger::GetInstance().OutputErrorMsg(caller_obj_name, __func__, err_type, err_log)

#define OutputMsg(msg_val) Logger::GetInstance().OutputMsg(__func__, msg_val);
#define OutputMsgStr(msg_str, msg_val) Logger::GetInstance().OutputMsgStr(__func__, msg_str, msg_val);