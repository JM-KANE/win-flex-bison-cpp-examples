#include "object.h"

size_t object::constructed{};
size_t object::destructed{};

object::object()
{
    constructed++;
}

object::object(const object&)
{
    constructed++;
}

object::~object()
{
    destructed++;
}
