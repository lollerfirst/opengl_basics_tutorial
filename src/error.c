#include <error.h>

const char* check_error(){
    switch (glGetError()){
        case GL_NO_ERROR: return NULL;
        case GL_INVALID_ENUM: return "An unacceptable value is specified for an enumerated argument";
        case GL_INVALID_VALUE: return "A numeric argument is out of range";
        case GL_INVALID_OPERATION: return "The specified operation is not allowed in the current state";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "The framebuffer object is not complete";
        case GL_OUT_OF_MEMORY: return "There is not enough memory left to execute the command";
        case GL_STACK_UNDERFLOW: return "An attempt has been made to perform an operation that would cause an internal stack to underflow";
        case GL_STACK_OVERFLOW: return "An attempt has been made to perform an operation that would cause an internal stack to overflow";
        default: return "Unspecified Error";
    }
}