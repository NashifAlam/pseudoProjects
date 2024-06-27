#include "authentication.h"

bool computeSHA256(uint32_t& input, unsigned long length, unsigned char * md)
{
	std::string inp;
	inp.to_string(input);

    SHA256_CTX context;
    if(!SHA256_Init(&context))
        return false;

    if(!SHA256_Update(&context, inp.c_str(), length))
        return false;

    if(!SHA256_Final(md, &context))
        return false;

    return true;
}
