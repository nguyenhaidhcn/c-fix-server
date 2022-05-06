
#include "quickfix/FileStore.h"
#include "quickfix/FileLog.h"
#include "quickfix/SocketAcceptor.h"
#include "quickfix/SessionSettings.h"
#include "Application.h"
#include <string>
#include <iostream>
#include <fstream>

void wait()
{
    std::cout << "Type Ctrl-C to quit" << std::endl;
    while (true)
    {
        FIX::process_sleep(1);
    }
}

int main(int argc, char** argv)
{

    std::string file = "fix-server2.cfg";



    {
        std::string myText;

        // Read from the text file
        std::ifstream MyReadFile(file);

        // Use a while loop together with the getline() function to read the file line by line
        while (getline(MyReadFile, myText)) {
            // Output the text from the file
            //std::cout << myText;
        }
    }
    try
    {
        FIX::SessionSettings settings(file);

        Application application;
        FIX::FileStoreFactory storeFactory(settings);
        FIX::FileLogFactory logFactory(settings);
        FIX::SocketAcceptor acceptor(application, storeFactory, settings);

        acceptor.start();
        //wait();
        while (true) {
            FIX::process_sleep(5);
            //application.sendXMessages();
        }
        acceptor.stop();
        return 0;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
