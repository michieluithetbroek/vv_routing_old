//
//  callback.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 17/04/2022.
//

// Note that this class contains one protected int member
// variable: where. You can query this variable from your
// callback() method to determine where the callback was
// called from.

#pragma once

#include "./../model.hpp"

class Mycallback: public GRBCallback
{
  public:
    Model *d_model;
    
    Mycallback(Model *ptr_model);
   
  private:
    void callback_lazy();
    void callback_user();
  
  protected:
    void callback();
};
