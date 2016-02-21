#if !defined _StdInpt
#define _StdInpt

#include <iostream>
#include <limits>

#include <cstdio>

#if defined _IO_ftrylockfile || __GNU_LIBRARY__ == 1
    #include <cstring>
#endif


#include "StdOutput.hpp"

namespace common {
    class StdInput{
    	private:
    	StdInput(){
            output = StdOutput::getInstance();
        }

    	StdInput(StdInput const&);

        void operator=(StdInput const&);

        StdOutput *output;
        

        /*
            Implementação deste metodo teve como base a implementação feita pela GNU da função fpurge() na GLIBC.
            Disponivel em <http://www.gnu.org/software/gnulib/coverage/gllib/fpurge.c.gcov.frameset.html>
            acessado em 10/10/14 as 11:23.
        */
        bool bufferIsEmpty(){
            /*** Código em C ***/
        #if defined _IO_ftrylockfile || __GNU_LIBRARY__ == 1
            /* Compatibilidade com: GNU libc, BeOS, Haiku, Linux libc5 */
            return strlen(stdin->_IO_read_ptr) == strlen(stdin->_IO_read_end);
            
        #elif defined __sferror || defined __DragonFly__
            /* Compatibilidade com: FreeBSD, NetBSD, OpenBSD, DragonFly, MacOS X, Cygwin */
            return stdin->_r <= 0;

        #else
            /* Caso não haja compatibilidade com os citados acima */
            puts("O porte da LIBC do seu sistema operacional não é compativel com este programa :(\n");
            exit(1);
        #endif
            /*******************/
        }

        public:
        
        static StdInput* getInstance(){
            static StdInput *instance = new StdInput;
            return instance;
        }

        void flush(){
            if(!this->bufferIsEmpty()){
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        int getInt(){
            int i;
            std::cin >> i;
            this->flush();
            return i;
        }

        int getInt(const char *strFormat){
            this->output->putString(strFormat);
            return this->getInt();
        }

        template<typename... Params>
        int getInt(const char *strFormat, Params... params){
            this->output->printF(strFormat, params...);
            return this->getInt();
        }

        double getDouble(){
            double d;
            std::cin >> d;
            this->flush();
            return d;
        }

        double getDouble(const char *strFormat){
            this->output->putString(strFormat);
            return this->getDouble();
        }

        template<typename... Params>
        double getDouble(const char *strFormat, Params... params){
            this->output->printF(strFormat, params...);
            return this->getDouble();
        }

        char getChar(){
            char c;
            std::cin >> c;
            this->flush();
            return c;
        }

        char getChar(const char *strFormat){
            this->output->putString(strFormat);
            return this->getChar();
        }

        template<typename... Params>
        char getChar(const char *strFormat, Params... params){
            this->output->printF(strFormat, params...);
            return this->getChar();
        }

        std::string getString(){
            std::string str;
            std::getline(std::cin, str);
            this->flush();
            return str;
        }

        std::string getString(const char *strFormat){
            this->output->putString(strFormat);
            return this->getString();
        }

        template<typename... Params>
        std::string getString(const char *strFormat, Params... params){
            this->output->printF(strFormat, params...);
            return this->getString();
        }

        bool getBool(std::string forTrue, std::string forFalse, std::string error){
            std::string input;

            while(true){
                input = this->getString();

                if(input == forTrue){
                    return true;
                }

                if(input == forFalse){
                    return false;
                }

                this->output->putString(error);
            }
        }

        bool getBool(std::string forTrue, std::string forFalse, int defaultVal){

            std::string input = this->getString();

            if(input == forTrue){
                return true;
            }

            if(input == forFalse){
                return false;
            }
            
            return (bool) defaultVal;
        }

        template<class T> T get(){
            T var;
            std::cin >> var;
            this->flush();
            return var;
        }

        template <class T> T get(const char *strFormat){
            this->output->putString(strFormat);
            return this->get<T>();
        }

        template <class T, typename... Params>
        T get(const char *strFormat, Params... params){
            this->output->printF(strFormat, params...);
            return this->get<T>();
        }

    };
}
#endif
