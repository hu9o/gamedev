#include "JSON.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace rapidjson;


JSON::JSON(std::string path)
{
    //const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    std::ifstream t(path.c_str());
    std::stringstream buf;
    buf << t.rdbuf();
    std::string json = buf.str() + '\0';

	printf("Original JSON:\n%s\n", json.c_str());


#if 0
	// "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
	if (Parse<0>(json).HasParseError())
		return 1;

#else
	// In-situ parsing, decode strings directly in the source string. Source must be string.
	buffer = (char*) calloc(sizeof(char), json.length());
	memcpy(buffer, json.c_str(), json.length());
	if (ParseInsitu<0>(buffer).HasParseError())
	{
	    std::cerr << "Erreur d'analyse :" << std::endl
        << ParseInsitu<0>(buffer).GetParseError() << std::endl;
    }

#endif

}

JSON::~JSON()
{
    //dtor
}
