#include <stdlib.h>
#include "heading.h"
#include "utility.h"
#include "error_message.h"
#include "symbol.h"
#include "temp.h"
#include "tree.h"


void reCompile(std::string sourceName,std::string targetName)
{
    std::string shell_cmd= "g++ "+sourceName+" -o "+ targetName;
    system(shell_cmd.c_str());
}

void translateBack(T_exp root)
{

}
