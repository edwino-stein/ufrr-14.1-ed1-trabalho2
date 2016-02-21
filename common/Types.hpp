#if !defined _BaseTypes
#define _BaseTypes

#include <typeinfo>
namespace common {

    class Types{

    	private:
    		Types(){}
    		Types(Types const&);
            void operator=(Types const&);

    	public:

    	static Types* getInstance(){
            static Types *instance = new Types;
            return instance;
        }

        template<typename Param>
        static bool isInt(Param var){
        	return typeid(var) == typeid(int);
    	}

    	template<typename Param>
        static bool isDouble(Param var){
        	return typeid(var) == typeid(double);
    	}

    	template<typename Param>
        static bool isFloat(Param var){
        	return typeid(var) == typeid(float);
    	}

    	template<typename Param>
        static bool isReal(Param var){
        	return (typeid(var) == typeid(float)) || typeid(var) == typeid(double);
    	}

    	template<typename Param>
        static bool isChar(Param var){
        	return typeid(var) == typeid(char);
    	}


    	template<typename Param>
        static bool isString(Param var){

        	if(typeid(var) == typeid(char *)){
        		return true;
        	}

        	if(typeid(var) == typeid(const char *)){
        		return true;
        	}

        	if(typeid(var) == typeid(std::string)){
        		return true;
        	}

        	return false;
    	}

    	template<typename Param>
        static bool isBool(Param var){
        	return typeid(var) == typeid(bool);
    	}

    	template <class T, typename Param>
        static bool is(Param var){
        	return typeid(var) == typeid(T);
    	}
    };
}

#endif