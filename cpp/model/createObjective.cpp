//
//  createObjective.cpp
//  vv_routing
//
//  Created by Michiel uit het Broek on 14/04/2022.
//

#include "model.ih"

void Model::createObjective()
{
  d_model.set(GRB_StringAttr_ModelName, "model1");
  d_model.set(GRB_IntAttr_ModelSense, GRB_MINIMIZE);
}
