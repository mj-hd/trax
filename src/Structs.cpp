#include <iostream>

#include "Structs.h"

char Cell::ToString() const { return TileChars[this->Type]; }

std::ostream& operator<<(std::ostream& stream, const Cell& c) { return stream << c.ToString(); }

void Operation::ToString(char* out) const {

#ifndef _NO_VALIDATIONS_

    if (sizeof(out) / sizeof(char) < 3)
        throw "String Too Short";

#endif

    out[0] = this->X + '@';
    out[1] = this->Y + '0';
    out[2] = (char)this->Type;
    out[3] = '\0';
}

Operation Operation::ToOperation(const char* notation) {
    Operation result;

#ifndef _NO_VALIDATIONS_
    if (sizeof(notation) / sizeof(char) < 3)
        throw "Invalid Notation";

    if (notation[3] != '\0')
        throw "Invalid Notation";

    if (('@' > notation[0]) ||
        ('0' > notation[1]))
        throw "Position Out of Range";
#endif

    result.X         = notation[0] - '@';
    result.Y         = notation[1] - '0';
    result.Type = (NotationType)notation[2];

    return result;
}

std::ostream& operator<<(std::ostream& stream, const Operation& o) {
    char tmp[3];

#ifndef _NO_VALIDATIONS_
    try {
#endif

        o.ToString(tmp);

#ifndef _NO_VALIDATIONS_
    }
    catch (const char* message) {
        std::cerr << message << std::endl;
        return stream;
    }
#endif

    return stream << tmp;
}
