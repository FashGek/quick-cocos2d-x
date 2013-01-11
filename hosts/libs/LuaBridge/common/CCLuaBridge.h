
#ifndef __LUA_BRIDGE_H_
#define __LUA_BRIDGE_H_

#include <string>
#include <map>
#include "CCLuaEngine.h"

extern "C" {
#include "lua.h"
}

using namespace std;

NS_CC_BEGIN

typedef enum {
    kCCLuaBridgeErrorOk                   = 0,
    kCCLuaBridgeErrorInvalidParameters    = -1,
    kCCLuaBridgeErrorClassNotFound        = -2,
    kCCLuaBridgeErrorMethodNotFound       = -3,
    kCCLuaBridgeErrorExceptionOccurred    = -4,
    kCCLuaBridgeErrorMethodSignature      = -5,
    kCCLuaBridgeErrorJavaVMError          = -6,
} CCLuaBridgeError;

typedef enum {
    kCCLuaBridgeTypeInvalid   = 0,
    kCCLuaBridgeTypeInt       = 1,
    kCCLuaBridgeTypeFloat     = 2,
    kCCLuaBridgeTypeBoolean   = 3,
    kCCLuaBridgeTypeString    = 4,
    kCCLuaBridgeTypeFunction  = 5,
    kCCLuaBridgeTypeArray     = 6,    // not used for CCLuaBridgeValueUnion
    kCCLuaBridgeTypeMap       = 7,    // not used for CCLuaBridgeValueUnion
    kCCLuaBridgeTypeVoid      = 8,    // not used for CCLuaBridgeValueUnion
} CCLuaBridgeType;

typedef union {
    int     intValue;
    float   floatValue;
    bool    boolValue;
    string  stringValue;
    int     functionRef;
} CCLuaBridgeValueUnion;

#define LUA_BRIDGE_REGISTRY_FUNCTION    "lua_bridge_function_id"        // table[function] = id
#define LUA_BRIDGE_REGISTRY_RETAIN      "lua_bridge_function_id_retain" // table[id] = retain count

class CCLuaBridge
{
public:
    static CCLuaStack *getStack(void);
    static int pushLuaFunctionById(int functionId);

    static int retainLuaFunctionById(int functionId);
    static int releaseLuaFunctionById(int functionId);
    
protected:
    static int retainLuaFunction(lua_State *L, int functionIndex, int *retainCountReturn);

    static lua_State *s_luaState;
    static int        s_newFunctionId;
};

NS_CC_END

#endif // __LUA_BRIDGE_H_
