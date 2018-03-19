#include <memory>
#include "lang.h"
#include <iostream>
#include <string>
#include <signal.h>
//NOTE to change with new types!
void check(shared_ptr<Typ> actual, shared_ptr<Typ> expected) {
  string t1 = expected->display(), t2 = actual->display();
  //bool valid = true;
  /*
  if(dynamic_cast<TInt*>(expected.get()) != nullptr) {
  t1 =
  valid = dynamic_cast<TInt*>(expected.get()) != nullptr;
} else if(dynamic_cast<TBool*>(expected.get()) != nullptr) {
valid = dynamic_cast<TBool*>(expected.get()) != nullptr;
} else {

}
*/
if(t1 == t2) {
  return;
} else {
  cerr << "Typecheck error.\nGiven: " << t1;
  cerr << "\nExpected: " << t2 << endl;
  raise(SIGINT);
  exit(EXIT_FAILURE);
}
}

TInt::TInt() { }
string TInt::display() { return "int"; }

TBool::TBool() { }
string TBool::display() {return "bool"; }

//TFun::TFun(TData _tin, TData _tout) : tin(_tin), tout(_tout) { }
TFun::TFun(shared_ptr<Typ> _tin, shared_ptr<Typ> _tout) : tin(_tin), tout(_tout) { }
string TFun::display() {
  return this->tin->display() + "->" + this->tout->display();
}

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
    case fixval: {
      this->value.data.fix = ld.data.fix;
    }
  }
}

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
    case funval: {
      strm << *(ld.data.fun->display());
      break;
    }
    case fixval: {
      strm << *(ld.data.fix->display());
      break;
    }
    default:
    printf("Given: %d", ld.type);
    fprintf(stderr, "Invalid LitData type");
    exit(EXIT_FAILURE);
  }
  return strm;
}

std::ostream& operator <<(std::ostream &strm, TData const& ld) {
  switch(ld) {
    case ival: {
      strm << "int";
      break;
    }
    case bval: {
      strm << "bool";
      break;
    }
    case strval: {
      strm << "string";
      break;
    }
    case funval: {
      strm << "fun";
      break;
    }
    case fixval: {
      strm << "fix";
      break;
    }
    default:
    printf("Given: %d", ld);
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
    case funval: {
      *ret = *ld.data.fun->display();
      break;
    }
    case fixval: {
      *ret = *ld.data.fix->display();
      break;
    }
    default:
    printf("Given: %d", ld.type);
    fprintf(stderr, "Invalid LitData type\n");
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
shared_ptr<string> EBigger::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(> " + *this->e1->display() + " " + *this->e2->display() + ")";
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
  *ret = "(let " + *this->e1->display() + " = " + *this->e2->display() + " in " + *this->e3->display() + ")";
  return ret;
}
shared_ptr<string> EFun::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(fun " + *this->e1->display() + " -> " + *this->e2->display() + ")";
  return ret;
}
shared_ptr<string> EFix::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  string name(this->fun_name);
  *ret = name;//"(fix " + name + " " + *this->e1->display() + " -> " + *this->e2->display() + ")";
  return ret;
}
shared_ptr<string> EApp::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(" + *this->e1->display() + " " + *this->e2->display() + ")";
  return ret;
}

/***** ELit ******************************************************************/

LitData ELit::eval() { return value; }
void ELit::subst(LitData val, const char* var) {  /*do nothing*/ }

shared_ptr<Typ> ELit::typecheck() {
  LitData ld = this->value;
  switch(ld.type) {
    case ival: {
      return make_shared<TInt>();
    }
    case bval: {
      return make_shared<TBool>();
    }
    default:
    cerr << "Invalid type of literal. Given " << ld.type << endl;
    exit(EXIT_FAILURE);
  }
}

/***** EPlus ******************************************************************/

EPlus::EPlus(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EPlus::eval() {
  typecheck();
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

shared_ptr<Typ> EPlus::typecheck() {
  auto expected = make_shared<TInt>();
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  check(this->e1->typecheck(), expected);
  check(this->e2->typecheck(), expected);
  return expected;
}

/***** EMinus *****************************************************************/

EMinus::EMinus(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EMinus::eval() {
  typecheck();
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

shared_ptr<Typ> EMinus::typecheck() {
  auto expected = make_shared<TInt>();
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  check(this->e1->typecheck(), expected);
  check(this->e2->typecheck(), expected);
  return expected;
}

/***** EMult ******************************************************************/

EMult::EMult(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EMult::eval() {
  typecheck();
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

shared_ptr<Typ> EMult::typecheck() {
  auto expected = make_shared<TInt>();
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  check(this->e1->typecheck(), expected);
  check(this->e2->typecheck(), expected);
  return expected;
}

/***** EDiv ******************************************************************/

EDiv::EDiv(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EDiv::eval() {
  typecheck();
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

shared_ptr<Typ> EDiv::typecheck() {
  auto expected = make_shared<TInt>();
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  check(this->e1->typecheck(), expected);
  check(this->e2->typecheck(), expected);
  return expected;
}

/***** ELeq ******************************************************************/

ELeq::ELeq(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData ELeq::eval() {
  typecheck();
  LitData e1d = e1->eval();
  LitData e2d = e2->eval();
  if(e1d.type == ival && e2d.type == ival) {
    LitData ret;
    ret.type = bval;
    ret.data.b = e1d.data.i <= e2d.data.i;
    return ret;
  } else {
    fprintf(stderr, "Cannot compare expressions of these types.\n");
    cout << "Given: " << *e1->display() << ", and " << *e2->display() << endl;
    exit(EXIT_FAILURE);
  }
}

void ELeq::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}

shared_ptr<Typ> ELeq::typecheck() {
  auto expected = make_shared<TInt>();
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  check(this->e1->typecheck(), expected);
  check(this->e2->typecheck(), expected);
  return make_shared<TBool>();
}

/***** EBigger ******************************************************************/

EBigger::EBigger(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EBigger::eval() {
  typecheck();
  LitData e1d = e1->eval();
  LitData e2d = e2->eval();
  if(e1d.type == ival && e2d.type == ival) {
    LitData ret;
    ret.type = bval;
    ret.data.b = e1d.data.i > e2d.data.i;
    return ret;
  } else {
    fprintf(stderr, "Cannot compare expressions of these types.\n");
    cout << "Given: " << *e1->display() << ", and " << *e2->display() << endl;
    raise(SIGINT);
    exit(EXIT_FAILURE);
  }
}

void EBigger::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}

shared_ptr<Typ> EBigger::typecheck() {
  auto expected = make_shared<TInt>();
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  check(this->e1->typecheck(), expected);
  check(this->e2->typecheck(), expected);
  return make_shared<TBool>();
}

/***** EIf ******************************************************************/

EIf::EIf(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Exp> _e3)
: e1(_e1), e2(_e2), e3(_e3) { }

LitData EIf::eval() {
  typecheck();
  LitData e1d = e1->eval();
  if(e1d.type == bval) {

    if(e1d.data.b) {
      return e2->eval();
    } else {
      return e3->eval();
    }
  } else {
    fprintf(stderr,"Error. Expected boolean in the guard of the if statement.");
    exit(EXIT_FAILURE);
  }
}

void EIf::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
  this->e3->subst(val, var);
}

shared_ptr<Typ> EIf::typecheck() {
  printf("TC-IF\n");
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e3->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts

  check(this->e1->typecheck(), make_shared<TBool>()); //check guard
  //printf("guard cleared\n");
  //cout << this->e2->typecheck()->display() << endl;
  //cout << this->e3->typecheck()->display() << endl;
  //check(this->e2->typecheck(), this->e3->typecheck());
  //printf("if cleared\n");
  return this->e2->typecheck();
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
    //cout << "Substitution performed! " << var << " is now " << val << endl;
    shared_ptr<Exp> ret = make_shared<ELit>(val);
    this->e1 = ret;
    return;
  }
}

shared_ptr<Typ> EVar::typecheck() {
  const string var(this->var);
  cout << this->ctx.count(var) << endl;
  auto ret = this->ctx[var];

  // For potential future debugging
  for(auto const &kv : this->ctx)
    cout << kv.first << " == " << var <<  " " << (kv.first == var) << endl;

  if(ret == nullptr) {
    fprintf(stderr, "Error: Unmapped variable: %s\n", this->var);
    exit(EXIT_FAILURE);
  }
  return ret;
  //this->e1->typecheck(); Not sure if I need this!!//TODO
}

/***** ELet ******************************************************************/

ELet::ELet(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Exp> _e3, shared_ptr<Typ> _tv)
: e1(_e1), e2(_e2), e3(_e3), tv(_tv) { }

LitData ELet::eval() {
  typecheck();
  LitData e1d = e1->eval(); //should be str
  if(e1d.type == strval) {
    const char* var = e1d.data.str;
    LitData e2d = e2->eval();
    e3->subst(e2d, var);
    LitData e3d = e3->eval();
    return e3d;
  } else {
    fprintf(stderr, "Invalid let expression!\n");
    exit(EXIT_FAILURE);
  }
}

void ELet::subst(LitData val, const char* var) {
  LitData ld = this->e1->eval();
  if(ld.type == strval && strcmp(ld.data.str, var) == 0) {
    //prevent shadowing
    return;
  }
  this->e2->subst(val, var);
  this->e3->subst(val, var);
}

shared_ptr<Typ> ELet::typecheck() {
  printf("TC-LET\n");
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  check(this->tv, this->e2->typecheck());

  this->e3->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  return this->e3->typecheck();
  /*
  EVar* evar = dynamic_cast<EVar*>(this->e1.get());
  if(evar == nullptr) {}
  TData tguard = (*evar->ctx)[evar->var];
  //NOTE: currently not *really* typechecking e1
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end());
  this->e2->typecheck(tguard);

  this->e3->ctx.insert(this->ctx.begin(),this->ctx.end());
  this->e3->typecheck();
  */
}

/***** EFun ******************************************************************/

EFun::EFun(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Typ> _tin, shared_ptr<Typ> _tout)
: e1(_e1), e2(_e2), tin(_tin), tout(_tout) { }

LitData EFun::eval() {
  typecheck();
  LitData ret;
  ret.type = funval;
  ret.data.fun = this;
  return ret;
}

void EFun::subst(LitData val, const char* var) {
  LitData ld = this->e1->eval();
  if(ld.type == strval && strcmp(ld.data.str, var) == 0) {
    //prevent shadowing
    return;
  }
  this->e2->subst(val, var);
}

shared_ptr<Exp> EFun::apply(LitData val, const char* var) {
  this->e2->subst(val, var); //fill in body with arg
  return this->e2;
}

shared_ptr<Typ> EFun::typecheck() {
  printf("TC-FUN\n");
  auto tin = this->tin;
  auto tout = this->tout;
  //cout << "IN " << tin->display() << endl;
  //cout << "OUT " << tout->display() << endl;
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  check(this->e2->typecheck(), tout);
  //cout << "RET " << make_shared<TFun>(tin, tout)->display() << endl;
  TFun* tfun;
  if((tfun = dynamic_cast<TFun*>(this->e1->typecheck().get())) != nullptr) {
    tout = tfun->tout;
  }
  return make_shared<TFun>(tin, tout);
}

/***** EFix ******************************************************************/

EFix::EFix(const char* _fun_name, shared_ptr<Exp> _e1, shared_ptr<Exp> _e2, shared_ptr<Typ> _tin, shared_ptr<Typ> _tout)
: fun_name(_fun_name), e1(_e1), e2(_e2), tin(_tin), tout(_tout) { }

LitData EFix::eval() {
  typecheck();
  LitData ret;
  ret.type = fixval;
  ret.data.fix = this;
  return ret;
}

void EFix::subst(LitData val, const char* var) {
  if(var == fun_name ||
    (e1->eval().type == strval && var == e1->eval().data.str)) {
      return; //prevent shadowing
    }
    this->e2->subst(val, var);
  }

  shared_ptr<Exp> EFix::apply(LitData val, const char* var) {
    this->e2->subst(val, var);
    return this->e2;
  }

  shared_ptr<Typ> EFix::typecheck() {

    auto tin = this->tin;
    auto tout = this->tout;
    this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
    check( this->e2->typecheck(), tin);
    return make_shared<TFun>(tin, tout);
  }
  /***** EApp ******************************************************************/

  EApp::EApp(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

  LitData EApp::eval() {
    typecheck();
    LitData e1d = e1->eval();
    LitData e2d = e2->eval();
    //cout << "Application: " << *this->display() << endl;
    if(e1d.type == funval) {
      LitData vardata = e1d.data.fun->e1->eval();
      if(vardata.type == strval) {
        const char* var = vardata.data.str;
        return e1d.data.fun->apply(e2d, var)->eval();
      } else {
        fprintf(stderr, "Invalid function application. Expected valid variable in fun\n");
        exit(EXIT_FAILURE);
      }
    } else if (e1d.type == fixval) {
      auto fixexp = e1d.data.fix;
      LitData vardata = fixexp->e1->eval();
      if(vardata.type == strval) {
        const char* var = vardata.data.str;
        const char* fun_name = fixexp->fun_name;
        fixexp->apply(fixexp->eval(), fun_name);
        LitData ret = fixexp->apply(e2d, var)->eval();
        return ret;
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
  shared_ptr<Typ> EApp::typecheck() {
    printf("TC-APP\n");
    TFun* tfun;
    shared_ptr<Typ> tin, tout;
    this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
    if((tfun = dynamic_cast<TFun*>(this->e1->typecheck().get())) != nullptr) {
      tin = tfun->tin;
      this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
      check(tin, this->e2->typecheck()); //exits if fails
      tout = tfun->tout;
      return tout;
    } else {
      cerr << "Expected function as first argument, given " << this->e1->typecheck()->display();
      exit(EXIT_FAILURE);
    }
  }
