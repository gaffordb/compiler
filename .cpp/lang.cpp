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

LitData ELit::eval() { return value; }

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
    default:
    fprintf(stderr, "Invalid LitData type");
    exit(EXIT_FAILURE);
  }
  return ret;
}


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

/***** EMinus ******************************************************************/

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
