#include <memory>
#include "lang.h"
#include <iostream>
#include <string>
#include <signal.h>
#include <sstream>

using namespace std;

unsigned int g_stack_next_alloc = 1;
unordered_map<unsigned int, shared_ptr<LitData> > g_stack;

/***** MISC ******************************************************************/
//for typechecking
void check(shared_ptr<Typ> actual, shared_ptr<Typ> expected) {
  string t1 = actual->display(), t2 = expected->display();
  //just compare string values rather than dealing with dynamic_casts
  if(t1 == t2) {
    return;
  } else {
    cerr << "Typecheck error.\nGiven: " << t1;
    cerr << "\nExpected: " << t2 << endl;
    raise(SIGINT);
    exit(EXIT_FAILURE);
  }
}

//for making data out of exp
LitData make_data(shared_ptr<Exp> e) {
  auto typ = e->typecheck();
  string tbase = typ->display();
  LitData ld = e->eval();
  LitData ret;
  if(tbase == "int") {
    ret.type = ival;
    ret.data.i = ld.data.i;
  } else if(tbase == "bool") {
    ret.type = bval;
    ret.data.b = ld.data.b;
  } else if(tbase == "unit") {
    ret.type = unitval;
    ret.data.pair = nullptr;
  } else {
    return ld; //should be appropriate LitData
  }
  return ret;
}

//for making exp out of data (if possible)
std::pair<TData, shared_ptr<Exp> > data_to_exp(LitData ld) {
  TData t = ld.type;
  if(t == ival || t == bval || t == strval || t == unitval) {
    return pair<TData, shared_ptr<Exp> >(t, nullptr);
  } else if(t == funval) {
    return pair<TData, shared_ptr<Exp> >(t, ld.data.fun);
  } else if(t == fixval) {
    return pair<TData, shared_ptr<Exp> >(t, ld.data.fix);
  } else if(t == pairval) {
    return pair<TData, shared_ptr<Exp> >(t, ld.data.pair);
  } else if(t == ptrval) {
    return pair<TData, shared_ptr<Exp> >(t, ld.data.ptr);
  } else if(t == listval) {
    return pair<TData, shared_ptr<Exp> >(t, ld.data.lst);
  } else {
    cerr << "Unknown type in data_to_exp.\n" << endl;
    exit(EXIT_FAILURE);
  }
}

/*************************STACK**************************************/
void set_ptr(unsigned int addr, shared_ptr<LitData> val) {
  //ensure ptr has been allocated
  if(addr < g_stack_next_alloc) {
    g_stack[addr] = val;
  } else {
    cerr << "Error: Cannot set unallocated pointer." << endl;
    exit(EXIT_FAILURE);
  }
}

unsigned int ptr_alloc() {
  return g_stack_next_alloc++;
}

shared_ptr<LitData> get_ptr(unsigned int addr) {
  //ensure ptr has been allocated
  if(addr < g_stack_next_alloc) {
    return g_stack[addr];
  } else {
    cerr << "Error: Cannot set unallocated pointer." << endl;
    exit(EXIT_FAILURE);
  }
}

/***** Types *****************************************************************/

TInt::TInt() { }
string TInt::display() { return "int"; }

TBool::TBool() { }
string TBool::display() {return "bool"; }

TUnit::TUnit() { }
string TUnit::display() {return "unit"; }

TRef::TRef(shared_ptr<Typ> _t) : t(_t) { }
string TRef::display() {return "<" + this->t->display() + ">"; }

TFun::TFun(shared_ptr<Typ> _tin, shared_ptr<Typ> _tout) : tin(_tin), tout(_tout) { }
string TFun::display() {
  return this->tin->display() + "->" + this->tout->display();
}

TPair::TPair(shared_ptr<Typ> _t1, shared_ptr<Typ> _t2) : t1(_t1), t2(_t2) { }
string TPair::display() {
  return this->t1->display() + "*" + this->t2->display();
}

TArray::TArray(shared_ptr<Typ> _t) : t(_t) { }
string TArray::display() {return "array<" + this->t->display() + ">"; }

TArrGet::TArrGet(shared_ptr<Typ> _t) : t(_t) { }
string TArrGet::display() {return "<" + this->t->display() + "> || " + this->t->display(); }

TList::TList(shared_ptr<Typ> _t) : t(_t) { }
string TList::display() {return "{" + this->t->display() + "}"; }

/***** EUnit *******************************************************************/
EUnit::EUnit() { }

LitData EUnit::eval() {
  LitData ret;
  ret.type = unitval;
  return ret;
}

void EUnit::subst(LitData val, const char* var) { }
shared_ptr<Typ> EUnit::typecheck() { return make_shared<TUnit>(); }

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
      break;
    }
    case fixval: {
      this->value.data.fix = ld.data.fix;
      break;
    }
    case pairval: {
      this->value.data.pair = ld.data.pair;
      break;
    }
    case unitval: {
      this->value.data.pair = nullptr;
      break;
    }
    case ptrval: {
      this->value.data.ptr = ld.data.ptr;
      break;
    }
    case listval: {
      this->value.data.lst = ld.data.lst;
      break;
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
    case pairval: {
      strm << *(ld.data.pair->display());
      break;
    }
    case unitval: {
      strm << "()";
      break;
    }
    case ptrval: {
      strm << *(ld.data.ptr->display());
      break;
    }
    case listval: {
      strm << *(ld.data.ptr->display());
      break;
    }
    default:
    printf("Given: %d", ld.type);
    fprintf(stderr, "Invalid LitData type.\n");
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
    case pairval: {
      strm << "pair";
      break;
    }
    case unitval: {
      strm << "unit";
      break;
    }
    case ptrval: {
      strm << "ptr";
      break;
    }
    case listval: {
      strm << "list";
      break;
    }
    default:
    printf("Given: %d", ld);
    fprintf(stderr, "Invalid LitData type!\n");
    exit(EXIT_FAILURE);
  }
  return strm;
}

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
    case pairval: {
      *ret =  *(ld.data.pair->display());
      break;
    }
    case unitval: {
      *ret = "()";
      break;
    }
    case ptrval: {
      *ret = *(ld.data.ptr->display());
      break;
    }
    case listval: {
      *ret = *(ld.data.lst->display());
      break;
    }
    default:
    fprintf(stderr, "Given: %d\n",ld.type);
    fprintf(stderr, "Invalid LitData type\n");
    exit(EXIT_FAILURE);
  }
  return ret;
}

/***** Expression Display Definitions *****************************************/
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

shared_ptr<string> EGeq::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(>= " + *this->e1->display() + " " + *this->e2->display() + ")";
  return ret;
}

shared_ptr<string> EBigger::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(> " + *this->e1->display() + " " + *this->e2->display() + ")";
  return ret;
}

shared_ptr<string> ESmaller::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(< " + *this->e1->display() + " " + *this->e2->display() + ")";
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
  *ret = "(let " + *this->e1->display() + " = " + *this->e2->display() + " in\n" + *this->e3->display() + ")";
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
  *ret = "(fix " + name + " " + *this->e1->display() + " -> " + *this->e2->display() + ")";
  return ret;
}

shared_ptr<string> EApp::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(" + *this->e1->display() + " " + *this->e2->display() + ")";
  return ret;
}

shared_ptr<string> EPair::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(" + *this->e1->display() + " . " + *this->e2->display() + ")";
  return ret;
}

shared_ptr<string> EFst::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(fst " + *this->e->display() + ")";
  return ret;
}

shared_ptr<string> ESnd::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(snd " + *this->e->display() + ")";
  return ret;
}

shared_ptr<string> EUnit::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "()";
  return ret;
}

shared_ptr<string> ERef::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(ref " + *this->e->display() + ")";
  return ret;
}

shared_ptr<string> EDeref::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(#" + *this->e->display() + ")";
  return ret;
}

shared_ptr<string> ESet::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(" + *this->e1->display() + " := " + *this->e2->display() + ")";
  return ret;
}

shared_ptr<string> ESeq::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(" + *this->e1->display() + " ; " + *this->e2->display() + ")";
  return ret;
}

shared_ptr<string> EPtr::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(Address: " + to_string(this->addr) + ")";
  return ret;
}

shared_ptr<string> EWhile::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(while " + *this->guard->display() + " do\n" + *this->body->display() + "\nend)";
  return ret;
}

shared_ptr<string> EArrRef::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(new " + this->t->display() + "[" + *this->e->display() + "])";
  return ret;
}

shared_ptr<string> EArrGet::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(" + *this->arr->display() + "[" + *this->index->display() + "])";
  return ret;
}

shared_ptr<string> EArrSet::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(" + *this->arr->display() + "[" + *this->index->display() + "])";
  return ret;
}

shared_ptr<string> EList::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  stringstream sdata;
  string head;
  string tail;
  if(this->data == nullptr) {
    head = " ";
  } else {
    if(this->data->type == listval) {
      head = this->data->data.lst->display_inner();
    } else {
      sdata << *this->data;
      head = sdata.str();
    }
  } if(this->e != nullptr) {
    EList* elist = dynamic_cast<EList*>(this->e.get());
    if(elist == nullptr) {
      printf("Error. Unexpected type as tail of list");
    }
    tail = elist->display_inner();
  } else {
    tail = " ";
  }
  *ret = "{ " + sdata.str() + " " + tail + "} : " + this->t->display();
  return ret;
}

string EList::display_inner(void) {
  string ret;
  stringstream sdata;
  string head;
  string tail;
  if(this->data == nullptr) {
    head = " ";
  } else {
    if(this->data->type == listval) {
      head = this->data->data.lst->display_inner();
    } else {
      sdata << *this->data;
      head = sdata.str();
    }
  } if(this->e != nullptr) {
    EList* elist = dynamic_cast<EList*>(this->e.get());
    if(elist == nullptr) {
      printf("Error. Unexpected type as tail of list");
    }
    tail = elist->display_inner();
  } else {
    tail = " ";
  }
  ret =  sdata.str() + " " + tail;
  return ret;
}

shared_ptr<string> ECons::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(:: " + *this->e1->display() + *this->e2->display() + ")";
  return ret;
}

shared_ptr<string> ECar::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(car " + *this->e->display() + ")";
  return ret;
}

shared_ptr<string> ECdr::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(cdr " + *this->e->display() + ")";
  return ret;
}

shared_ptr<string> EEmpty::display(void) {
  shared_ptr<string> ret = make_shared<string>();
  *ret = "(empty? " + *this->e->display() + ")";
  return ret;
}

/***** ELit ******************************************************************/

LitData ELit::eval() { return value; }
void ELit::subst(LitData val, const char* var) { }

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

  LitData ret;
  ret.type = ival;
  ret.data.i = e1->eval().data.i + e2->eval().data.i;
  return ret;

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

  LitData ret;
  ret.type = ival;
  ret.data.i = e1d.data.i - e2d.data.i;
  return ret;

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

  LitData ret;
  ret.type = ival;
  ret.data.i = e1d.data.i * e2d.data.i;
  return ret;

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

  if(e2d.data.i == 0) {
    fprintf(stderr, "Cannot divide by zero.\n");
    exit(EXIT_FAILURE);
  }
  LitData ret;
  ret.type = ival;
  ret.data.i = e1d.data.i / e2d.data.i;
  return ret;
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
  LitData ret;
  ret.type = bval;
  ret.data.b = e1d.data.i <= e2d.data.i;
  return ret;
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

/***** EGeq ******************************************************************/

EGeq::EGeq(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EGeq::eval() {
  typecheck();
  LitData e1d = e1->eval();
  LitData e2d = e2->eval();
  LitData ret;
  ret.type = bval;
  ret.data.b = e1d.data.i >= e2d.data.i;
  return ret;
}

void EGeq::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}

shared_ptr<Typ> EGeq::typecheck() {
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

  LitData ret;
  ret.type = bval;
  ret.data.b = e1d.data.i > e2d.data.i;
  return ret;
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

/***** ESmaller ******************************************************************/

ESmaller::ESmaller(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData ESmaller::eval() {
  typecheck();
  LitData e1d = e1->eval();
  LitData e2d = e2->eval();

  LitData ret;
  ret.type = bval;
  ret.data.b = e1d.data.i < e2d.data.i;
  return ret;
}

void ESmaller::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}

shared_ptr<Typ> ESmaller::typecheck() {
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
  if(e1d.data.b) {
    return e2->eval();
  } else {
    return e3->eval();
  }
}

void EIf::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
  this->e3->subst(val, var);
}

shared_ptr<Typ> EIf::typecheck() {

  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e3->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts

  check(this->e1->typecheck(), make_shared<TBool>()); //check guard
  check(this->e2->typecheck(), this->e3->typecheck());

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
    shared_ptr<Exp> ret = make_shared<ELit>(val);
    this->e1 = ret;
    return;
  }
}

shared_ptr<Typ> EVar::typecheck() {
  const string var(this->var);
  auto ret = this->ctx[var];
  if(ret == nullptr) {
    fprintf(stderr, "Error: Unmapped variable: %s\n", this->var);
    raise(SIGINT);
    exit(EXIT_FAILURE);
  }
  return ret;
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
    cerr << "Expected var name in ELet, given " << *e1->display() << endl;
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
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  check(this->tv, this->e2->typecheck());

  this->e3->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  return this->e3->typecheck();
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
  auto tin = this->tin;
  auto tout = this->tout;

  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts

  check(this->e2->typecheck(), tout);

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
  if(var == fun_name || (e1->eval().type == strval && var == e1->eval().data.str)) {
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

  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  check(this->e2->typecheck(), tout); //NOTECHANGEchanged tin to tout
  return make_shared<TFun>(tin, tout);
}

/***** EApp ******************************************************************/

EApp::EApp(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EApp::eval() {
  typecheck();
  LitData e1d = e1->eval();
  LitData e2d = e2->eval();
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
  TFun* tfun;
  shared_ptr<Typ> tin, tout;
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  shared_ptr<Typ> t1 = this->e1->typecheck();
  if((tfun = dynamic_cast<TFun*>(t1.get())) != nullptr) {
    tin = tfun->tin;
    this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
    check(tin, this->e2->typecheck()); //exits if fails
    tout = tfun->tout;
    return tout;
  } else {
    cerr << "EApp typecheck failed. Expected function as first argument, given " << t1->display() << endl;
    exit(EXIT_FAILURE);
  }
}

/***** EPair ******************************************************************/

EPair::EPair(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData EPair::eval() {
  LitData ld;
  ld.type = pairval;
  ld.data.pair = this;
  return ld;
}

void EPair::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}

shared_ptr<Typ> EPair::typecheck() {
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  auto t1 = this->e1->typecheck();
  auto t2 = this->e2->typecheck();

  return make_shared<TPair>(t1, t2);
}

/***** EFst ******************************************************************/

EFst::EFst(shared_ptr<Exp> _e) : e(_e) { }

LitData EFst::eval() {
  typecheck();
  EPair* epair = dynamic_cast<EPair*>(this->e.get());
  if(epair != nullptr) {
    return epair->e1->eval();
  } else {
    //check if EPair hidden by EVar
    LitData edata = this->e->eval();
    if(edata.type == pairval) {
      epair = edata.data.pair;
      return epair->e1->eval();
    }
    cerr << "INTERNAL ERROR: FST TYPECHECK FAILED" << endl;
    cerr << "Given " << *this->e->display() << endl;
    cerr << "Type " << this->e->typecheck()->display() << endl;
    raise(SIGINT);
    exit(EXIT_FAILURE);
  }
}

void EFst::subst(LitData val, const char* var) {
  this->e->subst(val, var);
}

shared_ptr<Typ> EFst::typecheck() {
  this->e->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  TPair* tpair = dynamic_cast<TPair*>(this->e->typecheck().get());
  if(tpair != nullptr) {
    return tpair->t1;
  } else {
    cerr << "Expected EPair in EFst, given " <<  this->e << endl;
    exit(EXIT_FAILURE);
  }
}


/***** ESnd ******************************************************************/

ESnd::ESnd(shared_ptr<Exp> _e) : e(_e) { }

LitData ESnd::eval() {
  typecheck();
  EPair* epair = dynamic_cast<EPair*>(this->e.get());
  if(epair != nullptr) {
    return epair->e2->eval();
  } else {
    //check if EPair hidden by EVar
    LitData edata = this->e->eval();
    if(edata.type == pairval) {
      epair = edata.data.pair;
      return epair->e2->eval();
    }
    cerr << "INTERNAL ERROR: FST TYPECHECK FAILED" << endl;
    cerr << "Given " << *this->e->display() << endl;
    cerr << "Type " << this->e->typecheck()->display() << endl;
    raise(SIGINT);
    exit(EXIT_FAILURE);
  }
}

void ESnd::subst(LitData val, const char* var) {
  this->e->subst(val, var);
}

shared_ptr<Typ> ESnd::typecheck() {
  this->e->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  TPair* tpair = dynamic_cast<TPair*>(this->e->typecheck().get());
  if(tpair != nullptr) {
    return tpair->t2;
  } else {
    cerr << "Expected TPair in ESnd, given " <<  this->e->typecheck()->display() << endl;
    exit(EXIT_FAILURE);
  }
}

/***** ERef ******************************************************************/

ERef::ERef(shared_ptr<Exp> _e) : e(_e) { }

LitData ERef::eval() {
  typecheck();

  unsigned int addr = ptr_alloc();
  auto data = this->e->eval();
  set_ptr(addr, make_shared<LitData>(data));
  auto eptr = make_shared<EPtr>(addr, this->e->typecheck());

  eptr->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  LitData ld;
  ld.type = ptrval;
  ld.data.ptr = eptr.get();
  ld.data.ptr->self = eptr; //to prevent eptr from being destroyed lol
  return ld;
}

void ERef::subst(LitData val, const char* var) {
  this->e->subst(val, var);
}

shared_ptr<Typ> ERef::typecheck() {
  this->e->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  return make_shared<TRef>(this->e->typecheck());
}

/***** EDeref ******************************************************************/

EDeref::EDeref(shared_ptr<Exp> _e) : e(_e) { }

LitData EDeref::eval() {
  typecheck();

  EPtr* eptr = dynamic_cast<EPtr*>(this->e->eval().data.ptr);
  if(eptr != nullptr) {
    return *get_ptr(eptr->addr);
  } else {
    cerr << "Expected e in deref to be EPtr... Given " << this->e << endl;
    exit(EXIT_FAILURE);
  }
}

void EDeref::subst(LitData val, const char* var) {
  this->e->subst(val, var);
}

shared_ptr<Typ> EDeref::typecheck() {
  this->e->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts

  TRef* tref = dynamic_cast<TRef*>(this->e->typecheck().get());
  if(tref != nullptr) {
    return tref->t;
  } else {

    cerr << "Typecheck error in deref:\n";
    cerr << "Expected <t>, given " << this->e->typecheck()->display() << endl;
    exit(EXIT_FAILURE);
  }
}

/***** ESet ******************************************************************/

ESet::ESet(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }
LitData ESet::eval() {
  EArrGet* arr;
  if((arr = dynamic_cast<EArrGet*>(this->e1.get())) != nullptr) {
    arr->is_get = false; //tell EArrGet to behave as a write
  }
  typecheck();
  EPtr* eptr = this->e1->eval().data.ptr;
  if(eptr != nullptr) {
    set_ptr(eptr->addr, make_shared<LitData>(this->e2->eval()));
    return make_data(make_shared<EUnit>());
  } else {
    cerr << "Expected e1 of eset to be EPtr... Given " << this->e1 << endl;
    exit(EXIT_FAILURE);
  }
}

void ESet::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}

shared_ptr<Typ> ESet::typecheck() {
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts

  auto t2 = this->e2->typecheck();
  auto t1 = this->e1->typecheck();

  auto expected = make_shared<TRef>(t2);
  check(t1, expected);

  return make_shared<TUnit>();
}

/***** ESeq ******************************************************************/

ESeq::ESeq(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData ESeq::eval() {
  typecheck();
  e1->eval();
  return e2->eval();
}

void ESeq::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}

shared_ptr<Typ> ESeq::typecheck() {
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  return this->e2->typecheck();
}

/***** EPtr ******************************************************************/

EPtr::EPtr(unsigned int _addr, shared_ptr<Typ> _t) : addr(_addr), t(_t) { }

LitData EPtr::eval() {
  LitData ret;
  ret.type = ptrval;
  ret.data.ptr = this->self.get();
  return ret;
}

void EPtr::subst(LitData val, const char* var) {
  //get to var hidden by ptr
  shared_ptr<Exp> derived = data_to_exp(val).second;
  derived->subst(val, var);
}

shared_ptr<Typ> EPtr::typecheck() {
  return make_shared<TRef>(this->t);
}

/***** EWhile ******************************************************************/

EWhile::EWhile(shared_ptr<Exp> _guard, shared_ptr<Exp> _body) : guard(_guard), body(_body) { }

LitData EWhile::eval() {
  typecheck();
  guard->eval();
  if(guard->eval().data.b) {
    body->eval();
    this->eval();
  }
  return make_data(make_shared<EUnit>());
}

void EWhile::subst(LitData val, const char* var) {
  this->guard->subst(val, var);
  this->body->subst(val, var);
}

shared_ptr<Typ> EWhile::typecheck() {
  this->guard->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->body->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  check(this->guard->typecheck(), make_shared<TBool>());

  return make_shared<TUnit>();
}

/***** EArrRef ******************************************************************/

EArrRef::EArrRef(shared_ptr<Exp> _e, shared_ptr<Typ> _t) : e(_e), t(_t) { }

LitData EArrRef::eval() {
  typecheck();
  int size = this->e->eval().data.i;

  unsigned int addr = ptr_alloc();
  for(int i = 1; i < size; i++) {
    ptr_alloc();
  }
  auto eptr = make_shared<EPtr>(addr, this->e->typecheck());

  eptr->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  LitData ld;
  ld.type = ptrval;
  ld.data.ptr = eptr.get();
  ld.data.ptr->self = eptr; //to prevent eptr from being destroyed lol
  return ld;
}

void EArrRef::subst(LitData val, const char* var) {
  this->e->subst(val, var);
}

shared_ptr<Typ> EArrRef::typecheck() {
  this->e->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  check(this->e->typecheck(), make_shared<TInt>());

  return make_shared<TArray>(this->t);
}

/***** EArrGet ******************************************************************/

EArrGet::EArrGet(shared_ptr<Exp> _arr, shared_ptr<Exp> _index) : arr(_arr), index(_index), is_get(true) { }

LitData EArrGet::eval() {
  typecheck();
  int i = this->index->eval().data.i;
  EPtr* eptr = dynamic_cast<EPtr*>(this->arr->eval().data.ptr);
  if(eptr != nullptr) {
    if(!this->is_get) {
      auto eptr_index = make_shared<EPtr>(eptr->addr + i, eptr->t);
      LitData ld;
      ld.type = ptrval;
      ld.data.ptr = eptr_index.get();
      ld.data.ptr->self = eptr_index;
      return ld;
    }
    auto ret = get_ptr(eptr->addr + i); //zero indexed
    if(ret == nullptr) {
      return make_data(make_shared<EUnit>());
    } else {
      return *ret;
    }
  } else {
    cerr << "Expected arr in arrget to be EPtr... Given " << this->arr << endl;
    exit(EXIT_FAILURE);
  }
}

void EArrGet::subst(LitData val, const char* var) {
  this->arr->subst(val, var);
  this->index->subst(val, var);
}

shared_ptr<Typ> EArrGet::typecheck() {
  this->arr->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->index->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts

  TArray* tarray = dynamic_cast<TArray*>(this->arr->typecheck().get());
  if(tarray != nullptr) {
    check(this->index->typecheck(), make_shared<TInt>());
    if(this->is_get) {
      return tarray->t;
    } else {
      return make_shared<TRef>(tarray->t);
    }
  } else {
    cerr << "Typecheck error in arrget:\n";
    cerr << "Expected <t>, given " << this->arr->typecheck()->display() << endl;
    exit(EXIT_FAILURE);
  }
}

/***** EArrSet ******************************************************************/

EArrSet::EArrSet(shared_ptr<Exp> _arr, shared_ptr<Exp> _index) : arr(_arr), index(_index) { }

LitData EArrSet::eval() {
  typecheck();

  int i = this->index->eval().data.i;
  EPtr* eptr = dynamic_cast<EPtr*>(this->arr->eval().data.ptr);

  if(eptr != nullptr) {
    auto ret = get_ptr(eptr->addr + i); //zero indexed
    if(ret == nullptr) {
      return make_data(make_shared<EUnit>());
    } else {
      return *ret;
    }
  } else {
    cerr << "Expected arr in arrset to be EPtr... Given " << this->arr << endl;
    exit(EXIT_FAILURE);
  }
}

void EArrSet::subst(LitData val, const char* var) {
  this->arr->subst(val, var);
  this->index->subst(val, var);
}

shared_ptr<Typ> EArrSet::typecheck() {
  this->arr->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->index->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts

  TArray* tarray = dynamic_cast<TArray*>(this->arr->typecheck().get());
  if(tarray != nullptr) {
    check(this->index->typecheck(), make_shared<TInt>());
    return make_shared<TArrGet>(tarray->t);
  } else {
    cerr << "Typecheck error in array set:\n";
    cerr << "Expected <t>, given " << this->arr->typecheck()->display() << endl;
    exit(EXIT_FAILURE);
  }
}

/***** EList ******************************************************************/

EList::EList(shared_ptr<Typ> _t) : t(_t), e(nullptr), data(nullptr) { }
EList::EList(shared_ptr<Exp> _e, shared_ptr<LitData> _data) : t(_e->typecheck()), e(_e), data(_data) { }
EList::EList(shared_ptr<Exp> _e, shared_ptr<Typ> _t) : t(_t), e(_e) { }

LitData EList::eval() {
  LitData ld;
  ld.type = listval;
  ld.data.lst = this;
  return ld;
}

void EList::subst(LitData val, const char* var) {
  if(this->e != nullptr) {
    this->e->subst(val, var);
  }
}

shared_ptr<Typ> EList::typecheck() {
  return make_shared<TList>(this->t);
}

/***** ECons ******************************************************************/

ECons::ECons(shared_ptr<Exp> _e1, shared_ptr<Exp> _e2) : e1(_e1), e2(_e2) { }

LitData ECons::eval() {
  typecheck();
  LitData e1d = e1->eval();
  EList* head = e2->eval().data.lst;
  auto new_head = make_shared<EList>(head->self, e1->typecheck());
  new_head->data = make_shared<LitData>(e1d);

  LitData ret;
  ret.type = listval;
  ret.data.lst = new_head.get();
  ret.data.lst->self = new_head; //let our new head persist beyond this context!
  return ret;
}

void ECons::subst(LitData val, const char* var) {
  this->e1->subst(val, var);
  this->e2->subst(val, var);
}

shared_ptr<Typ> ECons::typecheck() {
  this->e1->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  this->e2->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  auto t1 = this->e1->typecheck();
  auto t2 = this->e2->typecheck();
  check(t2, make_shared<TList>(t1));
  return t2;
}

/***** ECar ******************************************************************/

ECar::ECar(shared_ptr<Exp> _e) : e(_e) { }

LitData ECar::eval() {
  typecheck();

  EList* head = e->eval().data.lst;
  return *head->data;
}

void ECar::subst(LitData val, const char* var) {
  this->e->subst(val, var);
}

shared_ptr<Typ> ECar::typecheck() {
  this->e->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  TList* tlist = dynamic_cast<TList*>(this->e->typecheck().get());
  if(tlist != nullptr) {
    return tlist->t;
  } else {
    cerr << "Typecheck error:" << endl;
    cerr << "Car expected TList, given " << this->e->typecheck()->display() << endl;
    exit(EXIT_FAILURE);
  }
}

/***** ECdr ******************************************************************/

ECdr::ECdr(shared_ptr<Exp> _e) : e(_e) { }

LitData ECdr::eval() {
  typecheck();
  EList* head = e->eval().data.lst;
  return head->e->eval();
}

void ECdr::subst(LitData val, const char* var) {
  this->e->subst(val, var);
}

shared_ptr<Typ> ECdr::typecheck() {
  this->e->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  TList* tlist = dynamic_cast<TList*>(this->e->typecheck().get());
  if(tlist != nullptr) {
    return tlist->t;
  } else {
    cerr << "Typecheck error:" << endl;
    cerr << "Cdr expected TList, given " << this->e->typecheck()->display() << endl;
    exit(EXIT_FAILURE);
  }
}

/***** EEmpty ******************************************************************/

EEmpty::EEmpty(shared_ptr<Exp> _e) : e(_e) { }

LitData EEmpty::eval() {
  typecheck();
  EList* head = e->eval().data.lst;
  LitData ld;
  ld.type = bval;
  ld.data.b = head->e == nullptr && head->data == nullptr;
  return ld;
}

void EEmpty::subst(LitData val, const char* var) {
  this->e->subst(val, var);
}

shared_ptr<Typ> EEmpty::typecheck() {
  this->e->ctx.insert(this->ctx.begin(),this->ctx.end()); //union of contexts
  TList* tlist = dynamic_cast<TList*>(this->e->typecheck().get());
  if(tlist != nullptr) {
    return make_shared<TBool>();
  } else {
    cerr << "Typecheck error:" << endl;
    cerr << "Empty? expected TList, given " << this->e->typecheck()->display() << endl;
    exit(EXIT_FAILURE);
  }
}
