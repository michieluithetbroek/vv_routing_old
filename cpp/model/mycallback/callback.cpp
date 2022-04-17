//
//  callback.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 17/04/2022.
//

#include "mycallback.ih"

void Mycallback::callback()
{
    try
    {
        switch (where)
        {
            case GRB_CB_MIPSOL:
              callback_lazy();
              break;
                
            case GRB_CB_MIP:
              callback_user();
              break;
        }
    }
  
    catch (GRBException e)
    {
        cout << "Error number: " << e.getErrorCode() << " ------- ";
        cout << e.getMessage() << endl;
    }
  
    catch (string &e)
    {
        cout << "Error during Gurobi callback\n" << e << endl;
    }

    catch (...)
    {
        cout << "Unknown error during Gurobi callback" << endl;
    }
}
