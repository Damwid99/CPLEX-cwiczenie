#include <ilopl/iloopl.h>
#include <sstream>
 
#ifdef ILO_WINDOWS
#define DIRSEP "\\"
#else
#define DIRSEP "/"
#endif
#ifndef DATADIR
#define DATADIR ".." DIRSEP ".."  DIRSEP ".." DIRSEP ".." DIRSEP "opl" DIRSEP
#endif
 
ILOSTLBEGIN
 
int main(int argc, char* argv[]) {
    IloEnv env;
 
    int status = 127;
    try {
        IloOplErrorHandler handler(env, cout);
        IloOplModelSource modelSource(env, DATADIR "cutstock" DIRSEP "model_1.mod");
        IloOplSettings settings(env, handler);
        settings.setWithWarnings(IloFalse);
        IloOplModelDefinition def(modelSource, settings);
        IloCplex cplex(env);
        IloOplModel opl(def, cplex);
        IloOplDataSource dataSource(env, DATADIR "cutstock" DIRSEP "data.dat");
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