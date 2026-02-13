#include "aof.hpp"

// Use builder pattern.

/*
Step 1: Create "/data" folder if it doesn't exist.
Step 2: open "data/pepperdb.aof" as append mode
Step 3: if the file is new (size 0) write header:  AOFX1
                                                   0
This class also will contain the append method which writes the logs to the file.
*/

AOF::AOF(const std::string &filename) : filename(filename)
{
    std::string dir = "data";

    AOF::create_dir_and_file_if_not_exists(dir, this->filename);

    dir += '/' + filename;
    AOF::file.open(dir, std::ios::app);
}

AOF& AOF::GetInstance()
{
    static AOF instance("pepperdb.aof");
    return instance;
}

void AOF::create_dir_and_file_if_not_exists(const std::string &dir, const std::string &filename)
{
    if (!std::filesystem::exists(dir))
    {
        std::filesystem::create_directories(dir);

        std::ofstream file(dir + "/" + filename, std::ios::app);

        if (file.is_open())
        {
            file << "AOFX1\n"
                 << "0\n";
        }

        file.close();
    }
}

void AOF::appendCommand(const std::string &command)
{
    AOF::file << command << "\n";
    AOF::file.flush();
}
