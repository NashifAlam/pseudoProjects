
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include <string>

typedef struct DirInfo
{
	std::string fileType;
	std::string accessType;
	ino_t INODE_Det;
	std::string nameID;
	std::string accessTime;
	

	void printDirectoryInformation()
	{
		std::cout <<accessType << "\t"
					<< INODE_Det<<"\t";
		std::cout.width(10);
		std::cout << std::right << nameID;
		std::cout <<"\t" <<accessTime;
	}
} dirInfo;

std::string resolveMode(mode_t modeID)
{
	//initialsations
	int extr = 0;
	std::string str;
	mode_t tempMode = modeID;

	//Resolve the file type
	switch (tempMode & S_IFMT) {
           case S_IFBLK:  str += "chd ";break;
           case S_IFCHR:  str += "chd ";break;
           case S_IFDIR:  str += "dir ";break;// std::cout <<"directory\t";        
           case S_IFIFO:  str += "fip ";break;
           case S_IFLNK:  str += "sym ";break;
           case S_IFREG:  str += "reg ";break;//str += "regular file\t";       
           case S_IFSOCK: str += "soc ";break;
           default:       str += "un? ";break;
    }

	//Resolve the access rights 
	for(mode_t temp = modeID; temp > 100; temp /= 8 )
	{
		extr = temp % 8;

		switch(extr)
		{
			case 1 :	str.insert(4, "--x"); break;
			case 2 :	str.insert(4, "-w-"); break;
			case 3 :	str.insert(4, "-wx"); break;
			case 4 :	str.insert(4, "r--"); break;
			case 5 :	str.insert(4, "r-x"); break;
			case 6 :	str.insert(4, "rw-"); break;
			case 7 :	str.insert(4, "rwx"); break;
			default :	str.insert(4, "---");	break;
		}
		//str = str + std::to_string(extr);

	}
	
	return str;
}

int main(int argc, char * argv[])
{
	
	//Argument Check
	if(argc != 3)
	{
		std::cout << "Parameter mismatch use format _ls -[options] [directory]";
		exit(0);
	}

	//Initialisations
	std::vector <dirInfo> dir;
	dirInfo tempDirInfo;
	DIR *pDir;
	struct dirent *directoryInformation;
	struct stat statInstance;
	
	//Directory open fail check
	if((pDir = opendir(argv[2])) == NULL)
	{	
		std::cout << "Opendir Failed\n";
		exit(0);
	}

	//Reading and assigning dir structure the value
	while((directoryInformation = (readdir(pDir))))
	{
		stat(directoryInformation-> d_name, &statInstance);
		tempDirInfo.accessType = resolveMode(statInstance.st_mode);
		tempDirInfo.INODE_Det = directoryInformation -> d_ino;
		tempDirInfo.nameID = directoryInformation -> d_name;
		tempDirInfo.accessTime = ctime(&statInstance.st_atime);

		dir.push_back(tempDirInfo);
		
		
	}

	//TODO: check the parameter list

	//sort by name 
	std::sort(dir.begin(), 
				dir.end(), 
				[](const dirInfo &dir1_It, const dirInfo &dir2_It)
				{	
					return dir1_It.nameID < dir2_It.nameID;
				}
			);

	//print the directory
	for( dirInfo &It : dir)
	{
		It.printDirectoryInformation();
	}
}			
				