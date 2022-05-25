#ifndef STATIC_MODULES_H
#define STATIC_MODULES_H

// Add all in source modules:
#include "modelsmodule.h"

// Others
#include "interpret.h"

void add_static_modules( SLIInterpreter& engine )
{
  // Add all in source modules:
  engine.addmodule( new nest::ModelsModule() );
}

#endif
