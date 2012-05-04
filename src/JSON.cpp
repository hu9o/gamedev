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
    std::string json = buf.str();

	printf("Original JSON:\n%s\n", json.c_str());


#if 0
	// "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
	if (Parse<0>(json).HasParseError())
		return 1;
#else
	// In-situ parsing, decode strings directly in the source string. Source must be string.
	char* buffer = (char*) malloc(sizeof(char) * json.length());
	memcpy(buffer, json.c_str(), json.length());
	if (ParseInsitu<0>(buffer).HasParseError())
		std::cerr << "Erreur d'analyse" << std::endl;
#endif

	printf("\nParsing succeeded.\n");

	////////////////////////////////////////////////////////////////////////////
	// 2. Access values in
/*
	printf("\nAccess values in m_doc:\n");
	assert(IsObject());	// Document is a JSON value represents the root of DOM. Root can be either an object or array.

	assert(HasMember("map"));

	// tiles
	assert(HasMember("tiles"));
	assert((*this)["tiles"].IsString());
	printf("tiles path = %s\n", (*this)["tiles"].GetString());


	{
        assert(HasMember("cases"));
		const Value& a = (*this)["cases"];	// Using a reference for consecutive access is handy and faster.
		assert(a.IsArray());

		for (SizeType i = 0; i < a.Size(); i++)
		{
            assert(a[i].IsObject());

            printf(" - char: %c; terr: %s;\n", a[i]["char"].GetString()[0], a[i]["terr"].GetString());
		}
	}

	assert(m_doc["t"].IsBool());		// JSON true/false are bool. Can also uses more specific function IsTrue().
	printf("t = %s\n", m_doc["t"].GetBool() ? "true" : "false");

	assert(m_doc["f"].IsBool());
	printf("f = %s\n", m_doc["f"].GetBool() ? "true" : "false");

	printf("n = %s\n", m_doc["n"].IsNull() ? "null" : "?");

	assert(m_doc["i"].IsNumber());	// Number is a JSON type, but C++ needs more specific type.
	assert(m_doc["i"].IsInt());		// In this case, IsUint()/IsInt64()/IsUInt64() also return true.
	printf("i = %d\n", m_doc["i"].GetInt());	// Alternative (int)m_doc["i"]

	assert(m_doc["pi"].IsNumber());
	assert(m_doc["pi"].IsDouble());
	printf("pi = %g\n", m_doc["pi"].GetDouble());
*/
}

JSON::~JSON()
{
    //dtor
}
