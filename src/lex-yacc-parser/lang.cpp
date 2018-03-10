#include <memory>
#include "lang.h"
#include <iostream>
#include <string>
/***** ELit *******************************************************************/

ELit::ELit(int _value) {
  this->value.data.i = _value;
  this->value.type = ival;
}

ELit::ELit(bool _value) {
  this->value.data.b = _value;
  this->value.type = bval;
}

ELit::ELit(LitData& ld) {
  TData t = ld.type;
  this->value.type = t;

  switch(t) {
    case ival: {
      this->value.data.i = ld.data.i;
      break;
    }
    case bval: {
      this->value.data.b = ld.data.b;
      break;
    }
    case strval: {
      this->value.data.str = ld.data.str;
      break;
    }
    case funval: {
      this->value.data.fun = ld.data.fun;
    }
  }
}

LitData ELit::eval() { return value; }
void ELit::subst(LitData val, const char* var) {  /*do nothing*/ }

std::ostream& operator <<(std::ostream &strm, LitData const& ld) {
  switch(ld.type) {
    case ival: {
      strm << ld.data.i;
      break;
    }
    case bval: {
      strm << (ld.data.b ? "#t" : "#f");
      break;
    }
    case strval: {
      strm << ld.data.str;
      break;
    }
    default:
    fprintf(stderr, "Invalid LitData type");
    exit(EXIT_FAILURE);
  }
  return strm;
}
/*
std::ostream& Exp::operator<<(std::ostream& strm) {
strm << *this->display();
return strm;
}
*/
std::ostream& operator<<(std::ostream& strm, shared_ptr<Exp> exp) {
  strm << *(exp->display());
  return strm;
}

shared_ptr<string> ELit::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  LitData ld = this->value;
  switch(ld.type) {
    case ival: {
      *ret = std::to_string(ld.data.i);
      break;
    }
    case bval: {
      *ret = (ld.data.b ? "#t" : "#f");
      break;
    }
    case strval: {
      string s(ld.data.str);
      *ret = s;
      break;
    }
    default:
    fprintf(stderr, "Invalid LitData type");
    exit(EXIT_FAILURE);
  }
  return ret;
}

/*to_string stuff for display purposes*/
/*Gross and inefficient, but this is only for debugging anyways*/
shared_ptr<string> EPlus::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(+ " + *this->e1->display() + " " + *this->e2->display() + ")";
  return ret;
}

shared_ptr<string> EMinus::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(- " + *this->e1->display() + " " + *this->e2->display() + ")";
  return ret;
}
shared_ptr<string> EDiv::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(/ " + *this->e1->display() + " " + *this->e2->display() + ")";
  return ret;
}
shared_ptr<string> EMult::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(* " + *this->e1->display() + " " + *this->e2->display() + ")";
  return ret;
}
shared_ptr<string> ELeq::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(<= " + *this->e1->display() + " " + *this->e2->display() + ")";
  return ret;
}
shared_ptr<string> EIf::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(if " + *this->e1->display() + " then ";
  *ret += *this->e2->display() + " else " + *this->e3->display() + ")";
  return ret;
}
shared_ptr<string> EVar::display(void) {
  if(this->e1 == nullptr) {
    shared_ptr<string> ret = make_shared<string>();
    string s(this->var);
    *ret = s;
    return ret;
  } else {
    return e1->display();
  }
}
shared_ptr<string> ELet::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(let (" + *this->e1->display() + ") in\n " + *this->e2->display() + ")";
  return ret;
}
shared_ptr<string> EFun::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(fun " + *this->e1->display() + " -> " + *this->e2->display() + ")";
  return ret;
}

shared_ptr<string> EApp::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(" + *this->e1->display() + " " + *this->e2->display() + ")";
  return ret;
}

/***** EPlus ******************************************************************/

EPlus::EPlus(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EPlus::eval() {
  if(e1->eval().type == ival && e2->eval().type == ival) {
    LitData ret;
    ret.type = ival;
    ret.data.i = e1->eval().data.i + e2->eval().data.i;
    return ret;
  } else {
    fprintf(stderr, "Cannot add expressions of these types.\n");
    exit(EXIT_FAILURE);
  }
}

void EPlus::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}

/***** EMinus *****************************************************************/

EMinus::EMinus(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EMinus::eval() {
  LitData e1d = e1->eval();
  LitData e2d = e2->eval();

  if(e1d.type == ival && e2d.type == ival) {
    LitData ret;
    ret.type = ival;
    ret.data.i = e1d.data.i - e2d.data.i;
    return ret;
  } else {
    fprintf(stderr, "Cannot subtract expressions of these types.\n");
    exit(EXIT_FAILURE);
  }
}

void EMinus::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}
/***** EMult ******************************************************************/

EMult::EMult(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EMult::eval() {
  LitData e1d = e1->eval();
  LitData e2d = e2->eval();
  if(e1d.type == ival && e2d.type == ival) {
    LitData ret;
    ret.type = ival;
    ret.data.i = e1d.data.i * e2d.data.i;
    return ret;
  } else {
    fprintf(stderr, "Cannot multiply expressions of these types.\n");
    exit(EXIT_FAILURE);
  }
}

void EMult::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}
/***** EDiv ******************************************************************/

EDiv::EDiv(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EDiv::eval() {
  LitData e1d = e1->eval();
  LitData e2d = e2->eval();
  if(e1d.type == ival && e2d.type == ival) {
    if(e2d.data.i == 0) {
      fprintf(stderr, "Cannot divide by zero.\n");
      exit(EXIT_FAILURE);
    }
    LitData ret;
    ret.type = ival;
    ret.data.i = e1d.data.i * e2d.data.i;
    return ret;
  } else {
    fprintf(stderr, "Cannot divide expressions of these types.\n");
    exit(EXIT_FAILURE);
  }
}

void EDiv::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}

/***** ELeq ******************************************************************/

ELeq::ELeq(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData ELeq::eval() {
  LitData e1d = e1->eval();
  LitData e2d = e2->eval();
  if(e1d.type == ival && e2d.type == ival) {
    LitData ret;
    ret.type = bval;
    ret.data.b = e1d.data.i <= e2d.data.i;
    return ret;
  } else {
    fprintf(stderr, "Cannot compare expressions of these types.\n");
    exit(EXIT_FAILURE);
  }
}

void ELeq::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}

/***** EIf ******************************************************************/

EIf::EIf(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Exp> _e3)
: e1(_e1), e2(_e2), e3(_e3){ }

LitData EIf::eval() {
  LitData e1d = e1->eval();
  LitData e2d = e2->eval();
  LitData e3d = e3->eval();
  if(e1d.type == bval && e2d.type == e3d.type) {
    LitData ret;
    ret.type = e2d.type;
    if(e2d.type == bval) {
      ret.data.b = e1d.data.b ? e2d.data.b : e3d.data.b;
    } else if (e2d.type == ival){
      ret.data.i = e1d.data.b ? e2d.data.i : e3d.data.i;
    } else {
      fprintf(stderr, "Unexpected type encountered.\n");
      exit(EXIT_FAILURE);
    }
    return ret;
  } else {
    fprintf(stderr, "Invalid if statement.\n");
    exit(EXIT_FAILURE);
  }
}

void EIf::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
  this->e3->subst(val, var);
}

/***** EVar *******************************************************************/

EVar::EVar(const char* _var) : var(_var), e1(nullptr) { }

LitData EVar::eval() {
  //if var does not have a value
  if(e1 == nullptr) {
    LitData ret;
    ret.type = strval;
    ret.data.str = this->var;
    return ret;
  } else {
    return e1->eval();
  }
}

void EVar::subst(LitData val, const char* var) {
  if(strcmp(this->var, var) == 0) {
    shared_ptr<Exp> ret = make_shared<ELit>(val);
    this->e1 = ret;
    return;
  }
}

/***** ELet ******************************************************************/

ELet::ELet(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Exp> _e3) : e1(_e1), e2(_e2), e3(_e3) { }

LitData ELet::eval() {
  LitData e1d = e1->eval(); //should be str
  if(e1d.type == strval) {  // && e2d.type == e3d.type) {
    const char* var = e1d.data.str;
    LitData e2d = e2->eval();
    e3->subst(e2d, var);
    LitData e3d = e3->eval();
    return e3d;
  } else {
    fprintf(stderr, "Cannot compare expressions of these types.\n");
    exit(EXIT_FAILURE);
  }
}

void ELet::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}

/***** EFun ******************************************************************/

EFun::EFun(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EFun::eval() { //TODO figure out if this works??
  LitData ret = {
    .type = funval,
    .data.fun = this
  };
  return ret;
  /*
  LitData e1d = e1->eval();
  LitData e2d = e2->eval();
  if(e1d.type == ival && e2d.type == ival) {
  LitData ret;
  ret.type = bval;
  ret.data.b = e1d.data.i <= e2d.data.i;
  return ret;
} else {
fprintf(stderr, "Shouldn't eval function.\n");
exit(EXIT_FAILURE);
}
*///DO NOTHING?
}

void EFun::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}

/***** EApp ******************************************************************/

EApp::EApp(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EApp::eval() {//TODO TYPECHECK!! maybe
  LitData e1d = e1->eval();
  LitData e2d = e2->eval();
  if(e1d.type == funval) {
    LitData vardata = e1d.data.fun->e1->eval();
    if(vardata.type == strval) {
      const char* var = vardata.data.str;
      e1->subst(e2d, var);
      return e1->eval();
    } else {
      fprintf(stderr, "Invalid function application. Expected valid variable in fun\n");
      exit(EXIT_FAILURE);
    }
  } else {
    fprintf(stderr, "Invalid function application.\n");
    exit(EXIT_FAILURE);
  }
}

void EApp::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}
/*
shared_ptr<Exp> subst(LitData val, const char* var, shared_ptr<Exp> exp) {
ELit lit(val);

}
*/
