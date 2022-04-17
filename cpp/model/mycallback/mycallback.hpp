//
//  callback.hpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 17/04/2022.
//

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
