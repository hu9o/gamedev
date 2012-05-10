#pragma once

#include <iostream>
#include "rapidjson.h"

class JSON : public js::Document
{
    public:
        JSON(std::string path);
        virtual ~JSON();
    protected:
    private:
        char* buffer;
};

