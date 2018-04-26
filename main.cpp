#include "programManager.h"
#include "databaseSystemManagment.h"

int main(){

    DatabaseSystemManagment dsm("data");
    dsm.import();
    //ProgramManager pm("data");
    //pm.start();

    return 0;
}
