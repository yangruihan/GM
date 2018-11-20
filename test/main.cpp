#include "./Interpreter/T_Interpreter.h"
#include "./Memory/T_Memory.h"
#include "./Value/T_BoolValue.h"
#include "./Value/T_IntValue.h"
#include "./Value/T_FloatValue.h"
 
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
