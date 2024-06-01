#include <ilopl/iloopl.h>
#include <sstream>
using namespace std;
#ifdef ILO_WINDOWS
#define DIRSEP "\\"
#else
#define DIRSEP "/"
#endif
#ifndef DATADIR
#define DATADIR  ".." DIRSEP "cplex" DIRSEP
#endif
 
ILOSTLBEGIN
 
int main(int argc, char* argv[]) {
    IloEnv env;
 
    int status = 127;
    try {
        IloOplErrorHandler handler(env, cout);
        IloOplModelSource modelSource(env, "..\\cplex\\model_4.mod");
        IloOplSettings settings(env, handler);
        settings.setWithWarnings(IloFalse);
        IloOplModelDefinition def(modelSource, settings);
        IloCplex cplex(env);
        IloOplModel opl(def, cplex);
        IloOplDataSource dataSource(env, "..\\cplex\\data.dat");
        opl.addDataSource(dataSource);
        opl.generate();
 
        if (cplex.solve()) {
            cout << endl
<< "OBJECTIVE: " << fixed << setprecision(2) << opl.getCplex().getObjValue()
<< endl;
            opl.postProcess();
            opl.printSolution(cout);
            status = 0;
        }
        else {
            cout << "No solution!" << endl;
            status = 1;
        }
    }
    catch (IloOplException& e) {
        cout << "### OPL exception: " << e.getMessage() << endl;
    }
    catch (IloException& e) {
        cout << "### CONCERT exception: ";
        e.print(cout);
        status = 2;
    }
    catch (...) {
        cout << "### UNEXPECTED ERROR ..." << endl;
        status = 3;
    }
 
    env.end();
 
    cout << endl << "--Press <Enter> to exit--" << endl;
    getchar();
 
    return status;
}