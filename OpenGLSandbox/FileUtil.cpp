#include "FileUtil.h"



bool FileUtil::isChainInFile(std::string filename, std::string chainToFind){
	//std::cout << "cf : " << chainToFind << std::endl;
	std::ifstream file(filename);
	if (!file){
		std::cout << "File \"" << filename << "\"not found" << std::endl;
		file.close();
		return false;
	}
	std::string line;
	while (std::getline(file, line)){
		if (line.find(chainToFind, 0)!=std::string::npos){
			return true;
		}
	}
	file.close();
	return false;
}

bool FileUtil::arrayToFile(std::string filename, float *arr, int ID, int rows, int cols, int writtingMode){
	int c=cols;
	int idc = ID; //Corrected ID
	int writeStartOffset = 0;
	std::ofstream file(filename.c_str(), std::ios::app);
	
	if (writtingMode==MODE_OVERRIDE){
		file.close();
		file = std::ofstream(filename.c_str(), std::ios::trunc);
	}

	if (!file){
		std::cout << "File \"" << filename << "\"not found" << std::endl;
		file.close();
		return false;
	}
	if ( FileUtil::isChainInFile(filename, std::string("#array "+std::to_string(ID)) ) ){
		std::cout << "WARNING ID : " << ID << " already used. ";
		idc+=1;
		while (FileUtil::isChainInFile(filename, std::string("#array "+std::to_string(idc)))){
			//std::cout << "here"<<idc << std::endl;
			idc+=1;
		}
		if (writtingMode==MODE_DONOTHING){

		std::cout << "You Should set the value to " << idc<< std::endl;
		file.close();
		return false;
		}
	}
		/*if (writtingMode==MODE_ADD){
			std::ifstream read_file(filename);
			std::string line;
			if (read_file){
				while (!getline(read_file, line)){
					std::cout << line << std::endl;
					writeStartOffset+=1;
					file << std::endl;
				}
				
			}
			read_file.close();
			file << std::endl;
		}
	}*/
	//std::cout << "OK" << std::endl;
	std::cout << "Start at : " << writeStartOffset << std::endl;
	file << "#array " << ID << std::endl;
	for (int i=0;i<(rows*cols);i++){
		//std::cout <<"Writting" << std::endl;
		file << arr[i] << " ";
		if (i>=c-1){
			c+=cols;
			file << std::endl;
		}
	}
	file << "#end" << std::endl;
	file.close();
	return true;

}

void FileUtil::fileToArray(std::string filename, int ID, float *dst){
	std::ifstream file(filename);
	std::string arrIdentifier = "#array "+std::to_string(ID);
	int arrayPos = 0;
	if (!file){
		std::cout << "File \"" << filename << "\"not found" << std::endl;
		file.close();
		return;
	}
	std::string line;
	while (std::getline(file, line)){
		arrayPos++;
		if (line==arrIdentifier){
			break;
		}
	}
}

void FileUtil::stringToFile(std::string content, std::string filename){
	std::ofstream file(filename.c_str(), std::ios::app);
	if (!file){
		std::cout << "ERROR while opening file : " << filename << std::endl;
		file.close();
	}
	file << content;
	file.close();
}

void FileUtil::startlog(std::string logfile){

	std::ifstream read_file(logfile.c_str());
	int i =0;
	if (!read_file){
		std::cout << "File " << logfile << "not found\n";
		read_file.close();
		return;
	}
	std::string line;
	while (std::getline(read_file, line)){
	//	std::cout << line << std::endl;
		i++;
	}
	read_file.close();

	std::ofstream file(logfile.c_str(), std::ios::app);
	if (!file){
		std::cout << "File " << logfile << "not found\n";
		file.close();
		return;
	}
	/*time_t t = time(0);
	_CRT_SECURE_NO_War
	struct tm * now = localtime( & t );
	file << "[" << now->tm_mday << "/"<<
		now->tm_mon<<"/" << now->tm_year <<
		" " << now->tm_hour<<":"<<now->tm_min
		<< ":" << now->tm_sec;
	delete now;*/
	file << i << "\t" << __TIMESTAMP__ << std::endl; 
	file.close();
}



